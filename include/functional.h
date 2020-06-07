#ifndef _C3TL_FUNCTIONAL_H_
#define _C3TL_FUNCTIONAL_H_

namespace c3
{

template< class T >
struct plus {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs + rhs;
    }
};

template< class T >
struct minus {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs - rhs;
    }
};

template< class T >
struct multiplies {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs * rhs;
    }
};

template< class T >
struct divides {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs / rhs;
    }
};

template< class T >
struct modulus {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs % rhs;
    }
};

template< class T >
struct negate {
    T operator()( const T& arg ) const {
        return -arg;
    }
};

template< class T >
struct equal_to {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs == rhs;
    }
};

template< class T >
struct not_equal_to {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs != rhs;
    }
};

template< class T >
struct greater {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs > rhs;
    }
};

template< class T >
struct less {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs < rhs;
    }
};

template< class T >
struct greater_equal {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs >= rhs;
    }
};

template< class T >
struct less_equal {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs <= rhs;
    }
};

template< class T >
struct logical_and {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs && rhs;
    }
};

template< class T >
struct logical_or {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs || rhs;
    }
};

template< class T >
struct logical_not {
    T operator()( const T& arg ) const {
        return !arg;
    }
};

template< class T >
struct bit_and {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs & rhs;
    }
};

template< class T >
struct bit_or {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs | rhs;
    }
};

template< class T >
struct bit_xor {
    T operator()( const T& lhs, const T& rhs ) const {
        return lhs ^ rhs;
    }
};

template< class T >
struct bit_not {
    T operator()( const T& arg ) const {
        return ~arg;
    }
};




} // namespace c3

#endif // _C3TL_FUNCTIONAL_H_