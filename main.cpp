// #include "basic_string.h"
#include "vector.h"
#include "deque.h"
#include "stack.h"
#include "queue.h"
#include "algorithm.h"
#include "iostream.h"

using namespace c3;

int main(void) {
    vector<int> v{-3,-2,-1};
    for(int i=0; i< 20; ++i)
        v.push_back(i);
    v.clear();
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.pop_back();
    v.pop_back();
    v.pop_back();

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
