//
// Created on 2020 - 6 - 13
// Written by TSH
//

#ifndef _C3TL_STACK_H_
#define _C3TL_STACK_H_

#include "deque.h"
#include "utility.h"

namespace c3
{

template< class T, class Container = c3::deque<T> >
class stack {

public:
    typedef Container                           container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

public:
    // 默认构造函数。值初始化容器。
    stack() : stack(Container()){ }
    // 以 cont 的内容复制构造底层容器 c 。
    explicit stack( const Container& cont );
    // 以 move(cont) 移动构造底层容器 c 。
    // explicit stack( Container&& cont );
    // 复制构造函数。适配器以 other.c 的内容复制构造。(隐式声明)
    stack( const stack& other );
    // 移动构造函数。适配器以 move(other.c) 构造。(隐式声明)
    // stack( stack&& other );

    // 销毁 stack 。调用元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。
    ~stack();

    // 返回 stack 中顶元素的引用。它是最近推入的元素。此元素将在调用 pop() 时被移除。等效于调用 c.back() 。
    reference top();
    const_reference top() const;

    // 检查底层容器是否为空，即是否 c.empty() 。
    bool empty() const;

    // 返回底层容器中的元素数，即 c.size() 。
    size_type size() const;

    // 将给定的元素 value 压入栈顶。
    void push( const value_type& value );
    //void push( value_type&& value );

    // 移除栈顶元素。
    void pop();

    // 交换容器适配器与 other 的内容。等效地调用 swap(c, other.c);
    void swap( stack& other );

protected:
    Container _c;

};


template< class T, class Container >
stack<T,Container>::stack( const Container& cont ) :
    _c(cont)
{}

template< class T, class Container >
stack<T,Container>::stack( const stack& other ) :
    _c(other._c)
{}

template< class T, class Container >
stack<T,Container>::~stack() { }

template< class T, class Container >
typename stack<T,Container>::reference stack<T,Container>::top() {
    return this->_c.back();
}

template< class T, class Container >
typename stack<T,Container>::const_reference stack<T,Container>::top() const {
        return this->_c.back();
}

template< class T, class Container >
bool stack<T,Container>::empty() const {
    return this->_c.empty();
}

template< class T, class Container >
typename stack<T,Container>::size_type stack<T,Container>::size() const {
    return this->_c.size();
}

template< class T, class Container >
void stack<T,Container>::push( const value_type& value ) {
    this->_c.push_back(value);
}

template< class T, class Container >
void stack<T,Container>::pop() {
    this->_c.pop_back();
}

template< class T, class Container >
void stack<T,Container>::swap( stack& other ) {
    c3::swap(this->_c, other._c);
}



}


#endif // _C3TL_STACK_H_
