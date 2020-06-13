#include "vector.h"
#include "deque.h"
#include "stack.h"
#include "queue.h"
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
    
    return 0;
}
