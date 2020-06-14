// #include "basic_string.h"
#include "vector.h"
#include "deque.h"
#include "stack.h"
#include "queue.h"
#include "algorithm.h"
#include "iostream.h"

using namespace c3;

int main(void) {
    // vector tests
    cout << "VECTOR TESTS with v as a vector<int> object:" << endl;
    vector<int> v;
    for(int i=0; i< 33; ++i) {
        cout << "pushing back: " << i << endl;
        v.push_back(i);
        cout << "v.front(): " << v.front() << ", v.back(): " << v.back();
        cout << ", v.size(): " << v.size() << ", v.capacity(): " << v.capacity() << endl;
    }
    cout << "clear v." << endl;
    v.clear();
    cout << "pushing back 1, 2, 3.";
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    cout << "v.back(): " << v.back() << ", v.size(): " << v.size() << endl;;
    v.pop_back();
    cout << "popped back, v.back(): " << v.back() << ", v.size(): " << v.size() << endl;
    v.pop_back();
    cout << "popped back, v.back(): " << v.back() << ", v.size(): " << v.size() << endl;
    v.pop_back();
    cout << "popped back, v.back(): " << v.back() << ", v.size(): " << v.size();
    cout << ", in this line v.back() should have an invalid value." << endl;

    cout << "assigning v 12 copies of integer 10000." << endl;
    v.assign(12, 10000);
    cout << "v.size(): " << v.size() << ", v.capacity(): " << v.capacity() << endl;
    cout << "v[10]: " << v[10] << ", v.at(11): " << v.at(11) << endl;
    cout << "shrinking v to fit." << endl;
    v.shrink_to_fit();
    cout << "v.size(): " << v.size() << ", v.capacity(): " << v.capacity() << endl;
    cout << "v[10]: " << v[10] << ", v.at(11): " << v.at(11) << endl;
    cout << "resizing v to 64."<< endl;
    v.resize(64);
    cout << "v.size(): " << v.size() << ", v.capacity(): " << v.capacity() << endl;
    cout << "v[10]: " << v[10] << ", v.at(58): " << v.at(58) << endl;

    cout << "inserting 3 * -1 at v.begin() + 2." << endl;
    v.insert(v.begin() + 2, 3, -1);
    cout << "v[0] - v[7]: ";
    for(size_t i = 0; i < 8; ++i) {
        cout << v[i] << ", ";
    }
    cout << endl;
    cout << "v.size(): " << v.size() << ", v.capacity(): " << v.capacity() << endl;
    cout << "erasing from v.begin() + 3 to v.begin() + 6." << endl;
    v.erase(v.begin() + 3, v.begin() + 6);
    cout << "v[0] - v[7]: ";
    for(size_t i = 0; i < 8; ++i) {
        cout << v[i] << ", ";
    }
    cout << endl;
    cout << "v.size(): " << v.size() << ", v.capacity(): " << v.capacity() << endl;
    cout << "END OF VECTOR TESTS." << endl << endl;


    // DEQUE tests
    cout << "DEQUE TESTS with dq as a vector<int> object:" << endl;
    deque<int> dq;
    for(int i=0; i< 17; ++i) {
        cout << "pushing back: " << i << endl;
        dq.push_back(i);
        cout << "dq.front(): " << dq.front() << ", dq.back(): " << dq.back();
        cout << ", dq.size(): " << dq.size() << endl;
    }
    for(int i=0; i< 17; ++i) {
        cout << "popping front."<< endl;
        dq.pop_front();
        cout << "dq.front(): " << dq.front() << ", dq.back(): " << dq.back();
        cout << ", dq.size(): " << dq.size() << endl;
    }
    for(int i=100; i< 117; ++i) {
        cout << "pushing front: " << i << endl;
        dq.push_front(i);
        cout << "dq.front(): " << dq.front() << ", dq.back(): " << dq.back();
        cout << ", dq.size(): " << dq.size() << endl;
    }
    for(int i=100; i< 117; ++i) {
        cout << "popping back."<< endl;
        dq.pop_back();
        cout << "dq.front(): " << dq.front() << ", dq.back(): " << dq.back();
        cout << ", dq.size(): " << dq.size() << endl;
    }
    cout << "pushing back 0 to 16" << endl;
    for(int i=0; i< 17; ++i) {
        dq.push_back(i);
    }
    cout << "iterate from dq.begin() to dq.end():" << endl;
    for(auto i = dq.begin(); i != dq.end(); ++i ) {
        cout << *i << ", ";
    }
    cout << endl;
    cout << "using \"for(int & i : dq)\":" << endl;
    for(int & i : dq) {
        cout << i << ", ";
    }
    cout << endl;

    cout << "inserting 3 * -1 at dq.begin() + 2." << endl;
    dq.insert(dq.begin() + 2, 3, -1);
    cout << "dq[0] - dq[7]: ";
    for(size_t i = 0; i < 8; ++i) {
        cout << dq[i] << ", ";
    }
    cout << endl;
    cout << "dq.size(): " << dq.size() << endl;
    cout << "erasing from dq.begin() + 3 to dq.begin() + 6." << endl;
    dq.erase(dq.begin() + 3, dq.begin() + 6);
    cout << "dq[0] - dq[7]: ";
    for(size_t i = 0; i < 8; ++i) {
        cout << dq[i] << ", ";
    }
    cout << endl;
    cout << "dq.size(): " << dq.size() << endl;
    cout << "END OF VECTOR TESTS." << endl << endl;


    // string str = "Test string";
    // str.append(" is good");


    // ALGORITHM tests
    cout << "ALGORITHM TESTS" << endl;
    cout << "int arr[]={3, 9, 5, 1, 7};" << endl;
    int arr[]={3, 9, 5, 1, 7};
    cout << "sort arr." << endl;
    sort(arr, arr+5);
    cout << "arr after sort:" << endl;
    for(int i : arr) {
        cout << i << ", ";
    }
    cout << endl;
    cout << "lower bound of 5 in arr:" << endl;
    cout << *lower_bound(arr, arr+5, 5) << endl;
    cout << "upper bound of 5 in arr:" << endl;
    cout << *upper_bound(arr, arr+5, 6) << endl;
    cout << "binary search for 5 in arr:" << endl;
    cout << binary_search(arr, arr+5, 5) << endl;
    cout << "binary search for 6 in arr:" << endl;
    cout << binary_search(arr, arr+5, 6) << endl;
    cout << "int arr2[]={0, 8, 4, 6, 2};" << endl;
    int arr2[]={0, 8, 4, 6, 2};
    cout << "sort arr2." << endl;
    sort(arr2, arr2+5);
    cout << "arr2 after sort:" << endl;
    for(int i : arr2) {
        cout << i << ", ";
    }
    cout << endl;
    int arr3[10];
    cout << "merge arr and arr2 into arr3." << endl;
    merge(arr, arr+5, arr2, arr2+5, arr3);
    cout << "arr3:" << endl;
    for(int i : arr3) {
        cout << i << ", ";
    }
    cout << endl;

    return 0;
}
