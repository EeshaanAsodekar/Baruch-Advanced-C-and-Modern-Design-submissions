#include <iostream>
#include <tuple>
#include <algorithm>
#include <complex>

using namespace std;

// Subquestion (a)
// funtions to compute the maximum of a tuple of numerical data
template <typename T, typename Tuple, size_t N>
struct tupleMaxFinder
{
    static T findTupleMax(const Tuple& pack) {
        return max(get<N - 1>(pack), tupleMaxFinder<T, Tuple, N - 1>::findTupleMax(pack));
    }
    
};

template <typename T, typename Tuple>
struct tupleMaxFinder<T,Tuple,1>
{
    static T findTupleMax(const Tuple& pack) {
        return get<0>(pack);
    }

};

// funtions to compute the sum of a tuple of numerical data
template <typename T, typename Tuple, size_t N>
struct tupleSumFinder
{
    static T findTupleSum(const Tuple& pack) {
        return get<N - 1>(pack) + tupleSumFinder<T, Tuple, N - 1>::findTupleSum(pack);
    }

};

template <typename T, typename Tuple>
struct tupleSumFinder<T, Tuple, 1>
{
    static T findTupleSum(const Tuple& pack) {
        return get<0>(pack);
    }

};

// funtions to compute the average of a tuple of numerical data
template <typename T, typename Tuple, size_t N>
struct tupleAvgFinder
{
    static T findTupleAvg(const Tuple& pack) {
        return (get<N - 1>(pack)+ (N-1)*tupleAvgFinder<T, Tuple, N - 1>::findTupleAvg(pack))/N;
    }

};

template <typename T, typename Tuple>
struct tupleAvgFinder<T, Tuple, 1>
{
    static T findTupleAvg(const Tuple& pack) {
        return get<0>(pack);
    }

};

int main()
{
    tuple<double, double, double> tuple_double3;
    tuple<double, double> tuple_double2;

    get<0>(tuple_double3) = 1.0;
    get<1>(tuple_double3) = 14.5;
    get<2>(tuple_double3) = 7.11;

    get<0>(tuple_double2) = 114.5;
    get<1>(tuple_double2) = 17.11;
    

    // Subquestion (b)
    const size_t size3 = std::tuple_size<decltype(tuple_double3)>::value;
    const size_t size2 = std::tuple_size<decltype(tuple_double2)>::value;

    auto max_ele = tupleMaxFinder<double, tuple<double, double, double>, size3>::findTupleMax(tuple_double3);
    cout << "max element of tuple_double3: " << max_ele << endl;

    auto max_ele2 = tupleMaxFinder<double, tuple<double, double>, size2>::findTupleMax(tuple_double2);
    cout << "max element of tuple_double2: " << max_ele2 << endl;

    auto sum2 = tupleSumFinder<double, tuple<double, double>, size2>::findTupleSum(tuple_double2);
    cout << "sum of tuple_double2: " << sum2 << endl;

    auto avg = tupleAvgFinder<double, tuple<double, double, double>, size3>::findTupleAvg(tuple_double3);
    cout << "avg element of tuple_double3: " << avg << endl;

    //Subquestion (c)
    tuple<complex<double>, complex<double>, complex<double>> tuple_complex3 = make_tuple(complex<double>(10, 20), complex<double>(11, 25), complex<double>(9, 24));

    const size_t sizeC3 = tuple_size<decltype(tuple_complex3)>::value;

    auto sum3C = tupleSumFinder<complex<double>, tuple<complex<double>, complex<double>, complex<double>>, sizeC3>::findTupleSum(tuple_complex3);
    cout << "sum of complex tuple: " << sum3C.real() << "+ " << sum3C.imag() << "i" << endl;

    //auto avgC = tupleAvgFinder<complex<double>, tuple<complex<double>, complex<double>, complex<double>>, sizeC3>::findTupleAvg(tuple_complex3);
    //cout << "avg element of tuple_double3: " << avgC.real() << endl;

    return 0;
}
