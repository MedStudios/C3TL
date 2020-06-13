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
    cout << "END OF VECTOR TESTS." << endl << endl;

    deque<int> dq;
    dq.push_back(1);
    dq.push_front(-1);
    dq.push_front(-2);
    dq.push_back(2);

    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.pop();
    s.pop();

    queue<int> q;
    q.push(1);
    q.push(2);
    q.push(3);
    q.pop();
    q.pop();


    // string str = "Test string";
    // str.append(" is good");


    int arr[]={3, 9, 5, 1, 7};
    sort(arr, arr+5);
    for(int i : arr) {
        cout << i << " ";
    }
    cout << endl << binary_search(arr, arr+6, 46) << endl;
    int arr2[]={0, 8, 4, 6, 2};
    int arr3[10];
    sort(arr2, arr2+5);
    for(int i : arr2) {
        cout << i << " ";
    }
    cout << endl;
    merge(arr, arr+5, arr2, arr2+5, arr3);
    for(int i : arr3) {
        cout << i << " ";
    }

    return 0;
}
