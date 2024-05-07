#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;

// Subquestion (a)
template<typename T>
int find_index(const vector<T>& v, const T& x) {
    // it now points to the first element in v which is lesser than x
    auto it = lower_bound(v.begin(), v.end(), x);

    // if no such element found in the vector
    if (it == v.end()) {
        return -1;
    }

    // the iterator now points to [i+1] from the condition
    // v[i] <= x < v [i+1]​
    // decrementing it to point to element i
    it--;

    // converting the iterator into the integer index
    return distance(v.begin(), it);
}

// Subquestion (b)
template<typename T>
auto find_error(const vector<T>& v1, const vector<T>& v2, const int & i, const int &j) {
    tuple<vector<T>, vector<T>, vector<int>> error_info;
    vector<T> abs_error, rel_error;
    vector<int> error_indices;

    if (v1.size() != v2.size()) { 
        cout << "vector size mismatch; terminating!"; 
        return error_info = make_tuple(abs_error, rel_error, error_indices);
    }

    auto itr2 = v2.begin();
    for (auto itr1 = v1.begin()+i;itr1 != v1.begin()+j;itr1++) {

       /* cout << *itr1 << endl;
        cout << *itr2 << endl;
        cout << abs(*itr1 - *itr2) << endl;
        cout << "------------" << endl;*/

        abs_error.push_back(abs(*itr1 - *itr2));
        rel_error.push_back(abs_error.back()/(*itr1));

        if (abs_error.back() != 0) error_indices.push_back(distance(v1.begin(), itr1));
;
        itr2++;
    }
  
    error_info = make_tuple(abs_error, rel_error, error_indices);
    return error_info;
}

int main()
{
    vector<double>vec{ 1.0,3.5,22.0,11.4,54.6,221.5,15.6 };
    vector<double>vec2{ 2.0,3.5,44.0,11.4,54.6,221.5,15.6 };

    // Subquestion (a)
    // sorting the vector
    sort(vec.begin(), vec.end());

    cout << "vector v:\n";
    for_each(vec.begin(), vec.end(), [](double x)->void {cout << x << " ";});
    int this_index = find_index<double>(vec, 21.5);

    cout << "\n\n";
    cout << "for x = 21.5; v[i] <= x < v [i+1]​ condition satisfied at index: " << this_index << endl;
    
    
    // Subquestion (b)
    int i = 0, j = 4;
    auto error_tuple = find_error<double>(vec, vec2, i, j);

    auto vec_absE = get<0>(error_tuple);
    auto vec_relE = get<1>(error_tuple);
    auto vec_idxE = get<2>(error_tuple);

    cout << "\nvector1:" << endl;
    for_each(vec.begin(), vec.end(), [](double x)->void {cout << x << "\t";});
    cout << "\nvector2:" << endl;
    for_each(vec2.begin(), vec2.end(), [](double x)->void {cout << x << "\t";});
    cout << "\ni: " << i << " j:" << j << endl;

    cout << "\nabsolute error:" << endl;
    for_each(vec_absE.begin(), vec_absE.end(), [](double x)->void {cout << x << "\t";});
    cout << "\nrelative error:" << endl;
    for_each(vec_relE.begin(), vec_relE.end(), [](double x)->void {cout << x << "\t";});
    cout << "\nerror indices:" << endl;
    for_each(vec_idxE.begin(), vec_idxE.end(), [](int x)->void {cout << x << "\t";});

    return 0;
}
