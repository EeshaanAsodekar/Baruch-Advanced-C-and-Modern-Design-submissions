#include <iostream>
#include <memory>
#include <stdexcept>

//class Point {
//    double x;
//public:
//    Point(double x_) :x(x_) {}
//    double getX() {return x;}
//};
//
//int main()
//{
//    auto deleter = [](Point* pt)-> void
//    { std::cout << "Bye: " << pt->getX(); };
//
//    using SmartPoint = std::shared_ptr<Point>;
//    SmartPoint p1(new Point(10), deleter);
//
//
//    // gives output: Bye: 10
//    return 0;
//}

// free function custom deleter
// Subquestion (b)
void fileDeleter(FILE* file) {
    if (file) {
        std::cout << "Closing file via fileDeleter\n";
        fclose(file);
    }
}

int main() {
    // lambda function custom delete
    // Subquestion (b)
    auto lambdaDeleter = [](FILE* file){
        if (file) {
            std::cout << "Closing file via lambdaDeleter\n";
            fclose(file);
        }
    };
    // function object custom delete
    auto FileFinalizer = [](FILE* file)-> void {
        if (file) {
            std::cout << "Closing file via FileFinalizer\n";
            fclose(file);
        }
        };


    // Subquestion (c) and Subquestion (d)
    // testing the code using the 3 kind of deleter fucntions in combination
    // with throwing excpetions in a loop while writing to the file

    // testing fileDeleter
    try {
        FILE* file1;
        errno_t file = fopen_s(&file1, "file1.txt", "w");
        if (file != 0) {
            std::cerr << "Failed to open file1.txt\n";
            return 1;
        }
        std::shared_ptr<FILE> spFile1(file1, fileDeleter);
        for (int i = 0; i < 10; ++i) {
            fprintf(spFile1.get(), "Record %d\n", i);
            if (i == 5) {
                throw std::runtime_error("An error occurred");
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }

    // testing lambdaDeleter
    try {
        FILE* file2;
        errno_t file = fopen_s(&file2, "file2.txt", "w");
        if (file != 0) {
            std::cerr << "Failed to open file2.txt\n";
            return 1;
        }
        std::shared_ptr<FILE> spFile2(file2, lambdaDeleter);
        for (int i = 0; i < 10; ++i) {
            fprintf(spFile2.get(), "Record %d\n", i);
            if (i == 5) {
                throw std::runtime_error("Another error occurred");
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }

    // testing FileFinalizer
    try {
        FILE* file3;
        errno_t file = fopen_s(&file3, "file3.txt", "w");
        if (file != 0) {
            std::cerr << "Failed to open file3.txt\n";
            return 1;
        }
        std::shared_ptr<FILE> spFile2(file3, FileFinalizer);
        for (int i = 0; i < 10; ++i) {
            fprintf(spFile2.get(), "Record %d\n", i);
            if (i == 5) {
                throw std::runtime_error("Another error occurred!");
            }
        }
    }
    catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << '\n';
    }

    // yes, this approach does work as expected.
    // the files are closed as control reaches to the catch block
    // When the exception is thrown, the std::shared_ptr object goes out of scope and is destroyed. 
    // As part of its destruction, the std::shared_ptr object calls its deleter 
    // (which is the function that prints “Closing file...”) to clean up the resource it manages (in this case, the file)

    return 0;
}

