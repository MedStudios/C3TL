//
// Created on 2020 - 6 - 13
// Written by TSH
//

#ifndef _C3TL_QUEUE_H_
#define _C3TL_QUEUE_H_

#include "deque.h"
#include "utility.h"

namespace c3
{

template< class T, class Container = c3::deque<T> >
class queue {

public:
    typedef Container                           container_type;
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

public:
    // 默认构造函数。值初始化容器。
    queue() : queue(Container()){ }
    // 以 cont 的内容复制构造底层容器 c 。
    explicit queue( const Container& cont );
    // 以 move(cont) 移动构造底层容器 c 。
    // explicit queue( Container&& cont );
    // 复制构造函数。适配器以 other.c 的内容复制构造。(隐式声明)
    queue( const queue& other );
    // 移动构造函数。适配器以 move(other.c) 构造。(隐式声明)
    // queue( queue&& other );

    // 销毁 stack 。调用元素的析构函数，然后解分配所用的存储。注意，若元素是指针，则不销毁所指向的对象。
    ~queue();

    // 返回 queue 中首元素的引用。此元素将是调用 pop() 时第一个移除的元素。等效地调用 c.front() 。
    reference front();
    const_reference front() const;

    // 返回到 queue 中末元素的引用。这是最近推入的元素。等效地调用 c.back() 。
    reference back();
    const_reference back() const;

    // 检查底层容器是否为空，即是否 c.empty() 。
    bool empty() const;

    // 返回底层容器中的元素数，即 c.size() 。
    size_type size() const;

    // 向队列尾部插入元素 。
    void push( const value_type& value );
    //void push( value_type&& value );

    // 移除队首元素。
    void pop();

    // 交换容器适配器与 other 的内容。等效地调用 swap(c, other.c);
    void swap( queue& other );

protected:
    Container _c;

};


template< class T, class Container >
queue<T,Container>::queue( const Container& cont ) :
        _c(cont)
{}

template< class T, class Container >
queue<T,Container>::queue( const queue& other ) :
        _c(other._c)
{}

template< class T, class Container >
queue<T,Container>::~queue() {
    this->_c.~Container();
}

template< class T, class Container >
typename queue<T,Container>::reference queue<T,Container>::front() {
    return this->_c.front();
}

template< class T, class Container >
typename queue<T,Container>::const_reference queue<T,Container>::front() const {
    return this->_c.front();
}

template< class T, class Container >
typename queue<T,Container>::reference queue<T,Container>::back() {
    return this->_c.back();
}

template< class T, class Container >
typename queue<T,Container>::const_reference queue<T,Container>::back() const {
    return this->_c.back();
}

template< class T, class Container >
bool queue<T,Container>::empty() const {
    return this->_c.empty();
}

template< class T, class Container >
typename queue<T,Container>::size_type queue<T,Container>::size() const {
    return this->_c.size();
}

template< class T, class Container >
void queue<T,Container>::push( const value_type& value ) {
    this->_c.push_back(value);
}

template< class T, class Container >
void queue<T,Container>::pop() {
    this->_c.pop_front();
}

template< class T, class Container >
void queue<T,Container>::swap( queue& other ) {
    c3::swap(this->_c, other._c);
}



}



#endif // _C3TL_QUEUE_H_
