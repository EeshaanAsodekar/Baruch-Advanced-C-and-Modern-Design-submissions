#include <iostream>
#include <forward_list>
#include <algorithm>
#include <iterator>

// Subquestion (b)
// template fucntion to get size of a forward_list
template <typename T>
size_t get_flist_size(const std::forward_list<T>& flist) {
    return std::distance(flist.begin(), flist.end());
}

// Subquestion (d)
// to erase values after a given position
template <typename T>
void erase_flist(std::forward_list<T>& flist, typename std::forward_list<T>::iterator itr) {
    flist.erase_after(itr,flist.end());
}

// to erase values in a range of iterators.
template <typename T>
void erase_flist(std::forward_list<T>& flist, 
    typename std::forward_list<T>::iterator itr_begin, 
    typename std::forward_list<T>::iterator itr_end) {
    flist.erase_after(itr_begin,itr_end);
}

int main()
{
    // Suquestion (a)
    std::forward_list<int> flist1; // default (int type) forward_list

    int n = 5, value = 15;
    std::forward_list<int> flist2(n, value);// list with n elements and a given value

    std::forward_list<int> flist3 = {99, 100, 101, 145, 1123};// list from a initializer list

    std::forward_list<int> flist4({ 9, 10, 11, 15, 123 });// list from a initializer list

    // Subquestion (b)
    std::cout << "size of list2: " << get_flist_size(flist2) << std::endl;

    // Subquestion (c)
    
    // utility function to print a int forward_list
    auto flist_printer = [](std::forward_list<int> flist) -> void {
        for_each(flist.begin(), flist.end(), [](int x) {std::cout << x << " ";});
        std::cout << "\n" << std::endl;
        };

    std::cout << "\nflist3 before making changes of Subquestion (c) :\n";
    flist_printer(flist3);

    std::cout << "flist3 - making changes of Subquestion (c) :\n";

    // insert a value after a given position
    auto it = flist3.before_begin();
    flist3.insert_after(it, value);
    flist_printer(flist3);

    // insert n copies of a value after a given position
    flist3.insert_after(it, n, value);
    flist_printer(flist3);

    // insert a range specified by two iterators
    std::forward_list<int> flist5 = { 6, 7, 8 };
    flist3.insert_after(it, flist5.begin(), flist5.end());
    flist_printer(flist3);

    // insert an initializer list
    flist3.insert_after(it, { 9, 10, 11 });
    flist_printer(flist3);



    // Subquestion (d)
    auto itr1 = std::find(flist3.begin(), flist3.end(), 100);
    auto itr2 = std::find(flist3.begin(), flist3.end(), 11);
    auto itr3 = std::find(flist3.begin(), flist3.end(), 15);

    std::cout << "\n\nflist3 before making changes of Subquestion (d) :\n";
    flist_printer(flist3);

    std::cout << "flist3 - making changes of Subquestion (d) :\n";

    erase_flist(flist3, itr1); // erasing values after a given position
    flist_printer(flist3);

    erase_flist(flist3, itr2,itr3); // erasing in a range of iterators.
    flist_printer(flist3);


    // Subquestion (e)
    std::cout << "\n\nSubquestion (e) :\n";
    // Splice after: Transfers elements from one list to another
    std::forward_list<int> flist6 = { 1, 7, 3 }, flist7 = { 4, 5, 6 };
    flist_printer(flist6);
    flist_printer(flist7);
    flist6.splice_after(flist6.before_begin(), flist7);
    std::cout << "flist6 after splicing: \n";
    flist_printer(flist6);

    // Merge: Merges two sorted lists
    std::forward_list<int> flist8 = { 1, 5, 3}, flist9 = { 4, 2, 6 };
    flist_printer(flist8);
    flist_printer(flist9);
    flist8.sort();
    flist9.sort();
    flist8.merge(flist9);
    std::cout << "flist8 after merging: \n";
    flist_printer(flist8);

    // in essence, we need to give sorted forward_list's as input to the merge fucntion
    // but, we can give an unsorted forward list as input to the splice fucntion.
    // This is because the std::merge is meant merge two sorted lists into a single sorted list

    return 0;
}

