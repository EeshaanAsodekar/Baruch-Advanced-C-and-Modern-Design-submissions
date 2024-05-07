#include <iostream>
#include <future>
#include <chrono>
#include <numeric>

// defining arbitrary functions
double F1(const double& a) {
    return a * a;
}

double F2(const double& a) {
    return a * 31;
}

double F3(const double& c) {
    return std::pow(c, 4);
}

double F4(const double& b, const double& d) {
    return std::pow(b, 3)*std::pow(d, 3);
}

// Subquestion (a)
double single_threaded(const double& a) {
    auto b = F1(a);
    auto c = F2(a);
    auto d = F3(c);

    return F4(b, d);
}

// Subquestion (b)
double multi_threaded(const double& a) {
    std::future<double> b(std::async(F1, a));
    double c = F2(a);
    double d = F3(c);

    return F4(b.get(),d);
}

// Subquestion (c)
double promise_threaded(const double& a) {
    std::promise<double> promise;
    std::future<double> future = promise.get_future();
    std::thread([&](){
        promise.set_value(F1(a));
        }).detach();

        double c = F2(a);
        double d = F3(c);

        return F4(future.get(), d);
}

// Subquestion (d)
double packaged_task_threaded(const double& a) {
    std::packaged_task<double(double)> task(F1);
    std::future<double> future = task.get_future();
    std::thread(std::move(task), a).detach();

    double c = F2(a);
    double d = F3(c);

    return F4(future.get(), d);
}

// Lightweight fucntion: summing up a vector
double add(const std::vector<double>& v) {
    return std::accumulate(v.begin(), v.end(), 0.0);
}

// Heavyweight function: matrix multiplication
std::vector<std::vector<double>> matmul(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
    std::vector<std::vector<double>> c(a.size(), std::vector<double>(b[0].size(), 0.0));
    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b[0].size(); ++j) {
            for (size_t k = 0; k < b.size(); ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
    return c;
}
// Lightweight fucntion: summing up a vector (multithreaded version)
double add_multithreaded(const std::vector<double>& v) {
    auto mid = v.begin() + v.size() / 2;
    std::future<double> future = std::async(std::launch::async, [&]() {
        return std::accumulate(v.begin(), mid, 0.0);
        });
    double sum2 = std::accumulate(mid, v.end(), 0.0);
    return future.get() + sum2;
}

// Heavyweight function: matrix multiplication (multithreaded)
std::vector<std::vector<double>> matmul_multithreaded(const std::vector<std::vector<double>>& a, const std::vector<std::vector<double>>& b) {
    std::vector<std::vector<double>> c(a.size(), std::vector<double>(b[0].size(), 0.0));
    std::vector<std::packaged_task<void()>> tasks;

    for (size_t i = 0; i < a.size(); ++i) {
        for (size_t j = 0; j < b[0].size(); ++j) {
            tasks.emplace_back([i,j,a,b, &c]() {
                for (size_t k = 0; k < b.size(); ++k) {
                    c[i][j] += a[i][k] * b[k][j];
                }
                });
        }
    }

    std::vector<std::thread> threads;
    for (auto& task : tasks) {
        threads.emplace_back(std::move(task));
    }

    for (auto& thread : threads) {
        thread.join();
    }

    return c;
}


int main()
{
    double a = 10;

    auto start = std::chrono::high_resolution_clock::now();
    auto result1 = single_threaded(a);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Single Threaded = " << duration.count() << " nanoseconds \n";

    start = std::chrono::high_resolution_clock::now();
    auto result2 = single_threaded(a);
    end = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Multi Threaded (std::async and std::future) = " << duration2.count() << " nanoseconds \n";

    start = std::chrono::high_resolution_clock::now();
    auto result3 = promise_threaded(a);
    end = std::chrono::high_resolution_clock::now();
    auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Multi Threaded (using promise) = " << duration3.count() << " nanoseconds \n";

    start = std::chrono::high_resolution_clock::now();
    auto result4 = packaged_task_threaded(a);
    end = std::chrono::high_resolution_clock::now();
    auto duration4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
    std::cout << "Multi Threaded (using std::packaged_task) = " << duration4.count() << " nanoseconds \n";

    std::cout << "\nresult1: " << result1 <<
        "\nresult2: " << result2 <<
        "\nresult3: " << result2 <<
        "\nresult4: " << result4 << std::endl;

    std::cout << "\npercentage change in execution time using method 1: " << 
        100 * (double)(duration2.count() - duration.count()) / (double)duration.count();
    std::cout << "\npercentage change in execution time  using method 2: " <<
        100 * (double)(duration3.count() - duration.count()) / (double)duration.count();
    std::cout << "\npercentage change in execution time  using method 3: " <<
        100 * (double)(duration4.count() - duration.count()) / (double)duration.count();


    for(int factor = 1; factor <= 100; factor*=10){
        // experimenting with light and heavy weight fucntions
        a = 10;

        // Create a vector and a matrix for testing
        std::vector<double> v(1'000'000*factor, a);
        std::vector<std::vector<double>> mat(10*factor, std::vector<double>(10*factor, a));


        std::cout << "\nvector size: " << 1'000'000 * factor << std::endl;
        std::cout << "\nsquare matrix no. of rows: " << 10 * factor << std::endl;

        // Measure the time for the lightweight function (addition)
        start = std::chrono::high_resolution_clock::now();
        auto sum1 = add(v);
        end = std::chrono::high_resolution_clock::now();
        auto duration1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\n\n\nAddition = " << duration.count() << " nanoseconds \n";

        // Measure the time for the heavyweight function (matrix multiplication)
        start = std::chrono::high_resolution_clock::now();
        auto result_1 = matmul(mat, mat);
        end = std::chrono::high_resolution_clock::now();
        auto duration2 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\nMatrix multiplication = " << duration.count() << " nanoseconds \n";

        // multithreaded addition
        start = std::chrono::high_resolution_clock::now();
        auto sum_2 = add_multithreaded(v);
        end = std::chrono::high_resolution_clock::now();
        auto duration3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\nAddition (multithreaded) = " << duration.count() << " nanoseconds \n";

        start = std::chrono::high_resolution_clock::now();
        auto result_2 = matmul_multithreaded(mat, mat);
        end = std::chrono::high_resolution_clock::now();
        auto duration4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
        std::cout << "\nMatrix multiplication (multithreaded) = " << duration.count() << " nanoseconds \n";

        std::cout << "\npercentage change in execution time for multithreaded for addition: " <<
            100 * (double)(duration2.count() - duration1.count()) / (double)duration1.count();

        std::cout << "\npercentage change in execution time for multithreaded for matrixmult: " <<
            100 * (double)(duration4.count() - duration3.count()) / (double)duration3.count();
    }

    return 0;
}
