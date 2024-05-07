#include <iostream>
#include <string>
#include <tuple>
#include <vector>
#include <span>
#include <algorithm>
#include <typeinfo>
#include <boost/date_time/gregorian/gregorian.hpp>

typedef std::tuple<std::string, std::string, boost::gregorian::date> Person;

// Subquestion (b)
// using the lecture's print technique to print the tuples
template<typename Tuple, std::size_t N>
struct TuplePrinter
{
    static void print(const Tuple& pack)
    {
        TuplePrinter<Tuple, N - 1>::print(pack);
        std::cout << ", " << std::get<N - 1>(pack);
    }
};

template<typename Tuple> struct TuplePrinter<Tuple, 1>
{
    static void print(const Tuple& pack)
    {
        std::cout << std::get<0>(pack);
    }
};

// Subquestion (d)
// using the lecture's sorting technique to define a sort for one index between 2 tuples
template <int index> struct TupleSorter
{
    template <typename Tuple>
    bool operator () (const Tuple& left,
        const Tuple& right) const
    {
        // lexicographical sort
        return std::get<index>(left)
            < std::get<index>(right);
    }
};

// Subquestion (f)
// Function using range-based for loop
template<typename T>
void span_print_range_based(std::span<T> s) {
    for (const auto& elem : s) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

// Function using iterators
template<typename T>
void span_print_iterators(std::span<T> s) {
    for (auto it = s.begin(); it != s.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

// Function using indexing operator []
template<typename T>
void span_print_indexing(std::span<T> s) {
    for (int i = 0; i < s.size(); ++i) {
        std::cout << s[i] << ' ';
    }
    std::cout << '\n';
}

template<typename T>
std::tuple<std::span<T>,std::span<T>> span_ret_firstLastN(std::span<T> s,const int& N) {
    std::tuple<std::span<T>, std::span<T>> acc;

    std::get<0>(acc) = s.first(N);
    std::get<1>(acc) = s.last(N);

    return acc;
}

template <typename T>
void print_bytes(const std::span<T>& data) {
    auto const_bytes = std::as_bytes(data);
    for (auto const b : const_bytes) {
        std::cout << std::setw(2)
            << std::hex
            << std::uppercase
            << std::setfill('0')
            << std::to_integer<int>(b) << ' ';
    }
    std::cout << '\n';
}

int main()
{

    // Subquestion (a)
    Person person1(std::string("Marcus Apollo"), std::string("Rome"), boost::gregorian::date(2016, 3, 21));
    Person person2(std::string("John Doe"), std::string("Manhattan"), boost::gregorian::date(1990, 7, 21));
    Person person3(std::string("John Wick"), std::string("Bulgaria"), boost::gregorian::date(1999, 8, 10));
    Person person4(std::string("King Louis"), std::string("France"), boost::gregorian::date(1570,3,15));
    
    // computing the size of the tuple Person
    const int N = std::tuple_size <decltype(person1)>::value;

    std::cout << "printing person 1 before modification:" << std::endl;
    TuplePrinter<Person, N>::print(person1);
    std::cout << std::endl;

    std::cout << "\nprinting person 2 before modification:" << std::endl;
    TuplePrinter<Person, N>::print(person2);
    std::cout << std::endl;


    // modifying the created tuples
    std::get<0>(person1) = "Marcellus Smith";
    std::get<1>(person2) = "Queens";

    std::cout << "\n\nperson1 and person2 tuples modified!\n\n";

    std::cout << "\nprinting person 1 after modification:" << std::endl;
    TuplePrinter<Person, N>::print(person1);
    std::cout << std::endl;

    std::cout << "\nprinting person 2 after modification:" << std::endl;
    TuplePrinter<Person, N>::print(person2);
    std::cout << std::endl;


    // Subquestion (c)
    std::vector<Person> person_vec;
    person_vec.push_back(person1);
    person_vec.push_back(person2);
    person_vec.push_back(person3);
    person_vec.push_back(person4);
    
    // Subquestion (d)
    std::cout << "\n\nPrinting the person_vec before sorting:\n";
    std::for_each(person_vec.begin(), person_vec.end(), [](Person p) ->void {
        TuplePrinter<Person, N>::print(p); std::cout << "\n\n";
        });

    std::sort(person_vec.begin(), person_vec.end(), TupleSorter<1>());

    std::cout << "\n\nPrinting the person_vec after sorting on <1> address:\n";
    std::for_each(person_vec.begin(), person_vec.end(), [](Person p) ->void {
        TuplePrinter<Person, N>::print(p); std::cout << "\n\n";
        });

    std::sort(person_vec.begin(), person_vec.end(), TupleSorter<2>());

    std::cout << "\n\nPrinting the person_vec after sorting on <2> date of birth:\n";
    std::for_each(person_vec.begin(), person_vec.end(), [](Person p) ->void {
        TuplePrinter<Person, N>::print(p); std::cout << "\n\n";
        });



    // Subquestion (e)
    Person person_fix_arr[4];
    person_fix_arr[0] = person1;
    person_fix_arr[1] = person2;
    person_fix_arr[2] = person3;
    person_fix_arr[3] = person4;

    std::span<Person> s_fix_arr(person_fix_arr);
    std::span<Person> s_var_arr(person_vec);

    std::cout << "\n\nPrinting the person_fix_arr before modifying the 0th Person object:\n";
    std::for_each(person_fix_arr, person_fix_arr + 4, [](Person p) ->void {
        TuplePrinter<Person, N>::print(p); std::cout << "\n\n";
        });

    s_fix_arr[0] = Person(std::string("Zelle"), std::string("Queens"), boost::gregorian::date(2001, 3, 21));
        
    std::cout << "\n\nPrinting the person_fix_arr after modifying the 0th Person object:\n";
    std::for_each(person_fix_arr, person_fix_arr+4, [](Person p) ->void {
        TuplePrinter<Person, N>::print(p); std::cout << "\n\n";
        });

    /*
    * Answer to Subquestion (e)
    * std::span view are not read only; it is a mutable data view as we can see from the code above
    * I can change the 0th person object form the span view s_fix_arr
    * same can be done for the s_var_arr
    */

    // Subquestion (f)
    std::cout << "printing spans using three different span printing methods:\n";
    int arr[] = { 1,2,3 };
    std::vector<double> int_vec = { 9.5,1.0,11.7 };
    std::vector<double> int_vec2 = { 9.5,1.0,11.7 ,12.6,7.3,1.6,3.8,9.08,11,0};

    std::span<int> sarr(arr);
    std::span<double> svec(int_vec);

    span_print_indexing<int>(sarr);
    span_print_iterators<int>(sarr);
    span_print_range_based<int>(sarr);
    span_print_range_based<double>(svec);

    // Subquestion (g)
    int x = 3;
    auto tuppy = span_ret_firstLastN(std::span<double>(int_vec2), x);
    
    std::cout << "\nfirst 3 elements: \n";
    span_print_indexing(std::get<0>(tuppy));
    std::cout << "\nlast 3 elements: \n";
    span_print_indexing(std::get<1>(tuppy));
    
    // Subquestion (h)
    // testing the std::subspan
    std::cout << "\nprinting subspan of int_vec2 from 2 to 6:\n";
    std::span<double> sub_span = std::span<double>(int_vec2).subspan(2,6);
    span_print_indexing(sub_span);

    // Subquestion (i)
    std::cout << "\nSuquestion (i)\n" << std::endl;
    float data1[1]{ 3.141592f };
    print_bytes<float>(std::span{ data1 });

    int data2[1]{ 123456 };
    print_bytes<int>(std::span{ data2 });

    return 0;
}

