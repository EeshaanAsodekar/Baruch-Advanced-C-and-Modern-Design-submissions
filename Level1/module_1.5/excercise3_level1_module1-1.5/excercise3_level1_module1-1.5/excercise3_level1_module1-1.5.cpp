#include <iostream>
#include <tuple>
#include <vector>
#include <numeric>
#include <algorithm>
#include <unordered_map> 
#include <cmath>
using namespace std;

// Subquestion (a)
template<typename T>
tuple<double, double, double, double, double> numeric_vector_stats(vector<T>& v) {
    tuple<double, double, double, double, double> stats;

    // mean
    double mean = std::accumulate(v.begin(), v.end(),0.0)*1.0 / v.size();
    get<0>(stats) = mean;

    // mean deviation
    vector<double> diff;
    for_each(v.begin(), v.end(), [&](T num)-> void {diff.push_back(abs(num - mean));});
    double mean_deviation = accumulate(diff.begin(), diff.end(),0.0) * 1.0 / v.size();
    get<1>(stats) = mean_deviation;

    // range
    T max = *max_element(v.begin(), v.end());
    T min = *min_element(v.begin(), v.end());
    double range = max - min;
    get<2>(stats) = range;

    // standard deviation & variance
    vector<double> diff_squared;
    for_each(v.begin(), v.end(), [&](double num) -> void {diff_squared.push_back(pow(num- mean, 2));});
    double variance = accumulate(diff_squared.begin(), diff_squared.end(), 0.0) * 1.0 / (v.size()-1);

    get<3>(stats) = sqrt(variance);
    get<4>(stats) = variance;

    return stats;
}

// Subquestion (c)
template<typename T>
tuple<double, T> calculate_median_mode(vector<T>& vec) {
    tuple<double, T> stats;
    double median;

    size_t size = vec.size();

    // median
    if (size % 2 == 0) {
        median = (vec[size / 2 - 1] + vec[size / 2]) / 2.0;
    }
    else {
        median = vec[size / 2];
    }

    // mode
    unordered_map<T, int> freq;
    for (int num : vec) {
        freq[num]++;
    }
    auto mode_var = max_element(freq.begin(), freq.end(), [](const std::pair<T, int>& p1, const std::pair<T, int>& p2) {
        return p1.second < p2.second;
        });

    auto max_freq = mode_var->second;

    T mode= mode_var->first;

    for (const auto &pair:freq) {
        if (pair.second == max_freq && pair.first < mode_var->first) {
            mode = pair.first;
        }
    }

    get<0>(stats) = median;
    get<1>(stats) = mode;

    return stats;
}

int main()
{
    vector<int> vec{ 1,2,2,3,4,7,8};

    auto stats_tuple = numeric_vector_stats<int>(vec);
    sort(vec.begin(), vec.end());
    auto median_mode_tuple = calculate_median_mode<int>(vec);
    
    double mean, mean_deviation, range, standard_deviation, variance, median, mode;
    tie(mean, mean_deviation, range, standard_deviation, variance) = stats_tuple;
    tie(median, mode) = median_mode_tuple;

    cout << "mean: " << mean << endl;
    cout << "mean deviation: " << mean_deviation << endl;
    cout << "range: " << range << endl;
    cout << "standard deviation: " << standard_deviation << endl;
    cout << "variance: " << variance << endl;
    cout << "median: " << median << endl;
    cout << "mode: " << mode << endl;

    return 0;
}
