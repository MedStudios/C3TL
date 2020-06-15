#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstring>
#include <basic_string.h>
#include <vector.h>
#include <deque.h>
#include <stack.h>
#include <queue.h>
#include <algorithm.h>
#include <iostream.h>

using namespace c3;

SCENARIO("VECTOR TESTS with v as a vector<int> object", "[vector]") {
    c3::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    
    REQUIRE( v.size() == 16 );
    REQUIRE( v.capacity() >= 16 );

    WHEN( "pushing back from -1 to -17 (17 elements)" ) {
        THEN( "v.front() should be the first element (always 0), while v.back() should be the most recently pushed element, after that the size and capacity change" ) {
            for (int i = -1; i >= -17; --i) {
                v.push_back(i);
                REQUIRE(v.front() == 0);
                REQUIRE(v.back() == i);
            }
            REQUIRE( v.size() == 33 );
            REQUIRE( v.capacity() >= 33 );
        }
    }

    WHEN( "assigning v 12 * integer 0xFFFF" ) {
        v.assign(12, 0xFFFF);
        THEN( "the size and capacity change, and all elements in v should equal to 0xFFFF" ) {
            REQUIRE( v.size() == 12 );
            REQUIRE( v.capacity() >= 12 );
            for(auto i : v) {
                REQUIRE( i == 0xFFFF );
            }
        }
    }

    WHEN("popping back until v is empty") {
        THEN( "v.front() and v.back() should be as expected, and the size and capacity change" ) {
            for (int i = 15; i > 0; --i) {
                v.pop_back();
                REQUIRE(v.front() == 0);
                REQUIRE(v.back() == i - 1);
            }
            v.pop_back();
            REQUIRE( v.size() == 0 );
            REQUIRE( v.capacity() >= 0 );
        }
    }

    WHEN( "the size is increased" ) {
        v.resize( 32 );
        THEN( "the size and capacity change" ) {
            REQUIRE( v.size() == 32 );
            REQUIRE( v.capacity() >= 32 );
        }
    }

    WHEN( "the size is reduced" ) {
        v.resize( 0 );
        THEN( "the size changes but not capacity" ) {
            REQUIRE( v.size() == 0 );
            REQUIRE( v.capacity() >= 16 );
        }
    }

    WHEN( "more capacity is reserved" ) {
        v.reserve( 32 );
        THEN( "the capacity changes but not the size" ) {
            REQUIRE( v.size() == 16 );
            REQUIRE( v.capacity() >= 32 );
        }
    }

    WHEN( "less capacity is reserved" ) {
        v.reserve( 0 );
        THEN( "neither size nor capacity are changed" ) {
            REQUIRE( v.size() == 16 );
            REQUIRE( v.capacity() >= 16 );
        }
    }

    WHEN( "shrinking v to fit" ) {
        v.pop_back();
        v.pop_back();
        v.pop_back();
        v.pop_back();
        v.shrink_to_fit();
        THEN( "the capacity may change and equals to the size" ) {
            REQUIRE( v.size() == 12 );
            CHECK( v.capacity() == v.size() );
        }
    }

    WHEN( "inserting 3 * -1 at v.begin() + 2" ) {
        v.insert(v.begin() + 2, 3, -1);
        THEN( "the size and capacity change, and v[0] - v[7] should be as expected" ) {
            REQUIRE( v.size() == 19);
            REQUIRE( v.capacity() >= 19);
            REQUIRE( v[0] == 0 );
            REQUIRE( v[1] == 1 );
            REQUIRE( v[2] == -1 );
            REQUIRE( v[3] == -1 );
            REQUIRE( v[4] == -1 );
            REQUIRE( v[5] == 2 );
            REQUIRE( v[6] == 3 );
            REQUIRE( v[7] == 4 );
        }
    }
    
    WHEN( "erasing from v.begin() + 3 to v.begin() + 6." ) {
        v.erase(v.begin() + 3, v.begin() + 6);
        THEN( "the size and capacity change, and v[0] - v[7] should be as expected" ) {
            REQUIRE( v.size() == 13);
            REQUIRE( v.capacity() >= 13);
            REQUIRE( v[0] == 0 );
            REQUIRE( v[1] == 1 );
            REQUIRE( v[2] == 2 );
            REQUIRE( v[3] == 6 );
            REQUIRE( v[4] == 7 );
            REQUIRE( v[5] == 8 );
            REQUIRE( v[6] == 9 );
            REQUIRE( v[7] == 10 );
        }
    }
}
/*
int main(void) {

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


    // STRING tests
    cout << "STRING TESTS with str as a basic_string<char> (aka. string) object:" << endl;
    cout << "str = \"Test string\";" << endl;
    string str = "Test string";
    cout << "str:" << str << endl;
    cout << "str.append(\" is good\");" << endl;
    str.append(" is good");
    cout << "str: " << str << endl;
    cout << "str2 = str + \", why?\";" << endl;
    string str2 = str + ", why?";
    cout << "str2: " << str2 << endl;
    cout << "str2 += str + \" \";" << endl;
    str2 += str + " ";
    cout << "str2: " << str2 << endl << endl;

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
*/