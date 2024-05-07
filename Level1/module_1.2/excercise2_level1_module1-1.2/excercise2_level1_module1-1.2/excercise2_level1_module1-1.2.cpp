#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <utility>
using namespace std;
using namespace std::chrono;

// given template fucntion
template < typename T >
void SwapCopyStyle(T& a, T& b);

// move semantics based swap template fucntion
template < typename T >
void SwapMoveStyle(T& a, T& b);

int main()
{
    cout << "Subquestion (a)\n\n\n";
    // Subquestion (a)
    string str1 = "HelloWorld"; // source string
    string str2; // target string

    cout << "str1 before move: " << str1 << endl;
    cout << "str2 before move: " << str2 << endl;

    str2 = move(str1);
    cout << "\nstd::move performed on string!\n\n";

    cout << "str1 after move: " << str1 << endl;
    cout << "str2 after move: " << str2 << endl;

    // we can see that the str1 string is still valid, but in an unspecified state
    // and the str2 string contains the "HelloWorld" data which str1 held previously

    cout << "\n\n\nSubquestion (b)\n\n\n";

    // Subquestion (b)
    // let us create a vector with 50 random values and let us see the time taken to copy the data using 
    // (1) std::move (2) copy constructor (3) copy assignement operator

    srand(time(NULL));

    vector<int> vec1; // source vector
    vector<int> vec2; // target vector

    srand(time(NULL));
    for (int i = 0;i < 50 ;i++)
        vec1.push_back(rand());

    auto printIntEle = [](int i) { cout << i << " "; };

    cout << "\nvec1 before move:" << endl;
    for_each(vec1.begin(), vec1.end(),printIntEle);
    cout << "\nvec2 before move:" << endl;
    for_each(vec2.begin(), vec2.end(), printIntEle);


    auto start_vec_move = high_resolution_clock::now();
    vec2 = move(vec1);
    auto end_vec_move = high_resolution_clock::now();

    cout << "\nstd::move perfromed on vector!\n\n";


    cout << "\nvec1 after move:" << endl;
    for_each(vec1.begin(), vec1.end(), printIntEle);
    cout << "\nvec2 after  move:" << endl;
    for_each(vec2.begin(), vec2.end(), printIntEle);

    auto duration_vec_move = duration_cast<nanoseconds>(end_vec_move - start_vec_move);

    auto start_vec_copyConstr = high_resolution_clock::now();
    vector<int> vec3(vec2);
    auto end_vec_copyConstr = high_resolution_clock::now();
    auto duration_vec_copyConstr = duration_cast<nanoseconds>(end_vec_copyConstr - start_vec_copyConstr);

    vector<int> vec4;

    auto start_vec_copyAssignOpr = high_resolution_clock::now();
    vec4 = vec2;
    auto end_vec_copyAssignOpr = high_resolution_clock::now();
    auto duration_vec_copyAssignOpr = duration_cast<nanoseconds>(end_vec_copyAssignOpr - start_vec_copyAssignOpr);

    cout << "\n\nTime taken to perform std::move on vec2: " << duration_vec_move.count() << " nanoseconds" << endl;
    cout << "\n\nTime taken to create vec3 using copy constructor on vec3: " << duration_vec_copyConstr.count() << " nanoseconds" << endl;
    cout << "\n\nTime taken to use copy assignment operator on vec4: " << duration_vec_copyAssignOpr.count() << " nanoseconds" << endl;

    /*
    * for the latest run, this was the time taken for each operation:
    * Time taken to perform std::move on vec2: 1500 nanoseconds
    * Time taken to create vec3 using copy constructor on vec3: 5000 nanoseconds
    * Time taken to use copy assignment operator on vec4: 2400 nanoseconds
    * 
    * for each run, the time for the 3 operations differ, but in general we observe that the std::move
    * is faster than the copy constructor or the copy assignment operator operations becuase it enables move semantics
    * which involves trasnfering resources (the elements of the vector) rather than duplicating them.
    * 
    * also, in general, the copy assignment takes lesser time than the copy constructor because it can avoid allocating new memory.
    */

    cout << "\n\n\nSubquestion (c)\n\n\n";
    // Subquestion (c)
    /*
    * for the given template function SwapCopyStyle, three temporary copies are created.
    * copy1: the tmp
    * copy2: created during the a = b copy assignment operator; copy of b created
    * copy3: created during the b = tmp copy assignment operator; copy of tmp created 
    */

    vector<int> vec_x, vec_y;
    for (int i = 0;i < 100000;i++) vec_x.push_back(rand());
    for (int i = 0;i < 100000;i++) vec_y.push_back(rand());
    
    auto start_copySwap = high_resolution_clock::now();
    SwapCopyStyle<vector<int>>(vec_x, vec_y);
    auto end_copySwap = high_resolution_clock::now();
    auto duration_copySwap = duration_cast<nanoseconds>(end_copySwap - start_copySwap);
    cout << "for a vectors of size " << vec_x.size() << " SwapCopyStyle takes " << duration_copySwap.count() << " nanoseconds" << endl;

    auto start_moveSwap = high_resolution_clock::now();
    SwapMoveStyle<vector<int>>(vec_x, vec_y);
    auto end_moveSwap = high_resolution_clock::now();
    auto duration_moveSwap = duration_cast<nanoseconds>(end_moveSwap - start_moveSwap);
    cout << "for a vectors of size " << vec_x.size() << " SwapMoveStyle takes " << duration_moveSwap.count() << " nanoseconds" << endl;

    /*
    * for the latest run, these were the results obtained:
    * for a vectors of size 100000 SwapCopyStyle takes 112900 nanoseconds
    * for a vectors of size 100000 SwapMoveStyle takes 4700 nanoseconds
    * 
    * we can clearly see that move semantics based operations are far more time efficient than the ones based on 
    * copying over all the contents of an object. And this difference in time is far more apparent when large objects
    * are to be swapped
    */

    return 0;
}

template < typename T >
void SwapCopyStyle(T& a, T& b)
{
    // Swap a and b in copying way; temporary object needed
    T tmp(a); // Copy constructor
    a = b; // Copy all elements from b to a
    b = tmp; // Copy all elements from tmp to b
}

// if the move constructor and the move assignment operator are not defined for type T
// the copy constructor and the copy assignment operator will be used instead 
// when std::move() is called form this template fucntion
template < typename T >
void SwapMoveStyle(T& a, T& b)
{
    T tmp(move(a));
    a = move(b);
    b = move(tmp);
}