#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <cstring>
#include <basic_string.h>
#include <vector.h>
#include <deque.h>
#include <stack.h>
#include <queue.h>
#include <functional.h>
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
            REQUIRE( v.empty() );
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
            REQUIRE( v.empty() );
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
    
    WHEN( "erasing from v.begin() + 3 to v.end() - 10." ) {
        v.erase(v.begin() + 3, v.end() - 10);
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


SCENARIO("DEQUE TESTS with dq as a deque<int> object", "[deque]") {
    c3::deque<int> dq;
    for(int i = 0; i < 16; ++i) {
        dq.push_back(i);
    }
    
    REQUIRE( dq.size() == 16 );

    WHEN( "pushing first from 0 to 15 and pushing back from 0 to -15" ) {
        THEN( "dq.front() and dq.back() should be as expected" ) {
            for (int i = 0; i < 16; ++i) {
                dq.push_front(i);
                dq.push_back(-i);
                REQUIRE(dq.front() == i);
                REQUIRE(dq.back() == -i);
            }
            REQUIRE( dq.size() == 48 );
        }
    }

    WHEN( "assigning dq 12 * integer 0x7FFFFFFF" ) {
        dq.assign(12, 0x7FFFFFFF);
        THEN( "the size change, and all elements in dq should equal to 0xFFFF" ) {
            REQUIRE( dq.size() == 12 );
            for(auto i : dq) {
                REQUIRE( i == 0x7FFFFFFF );
            }
        }
    }

    WHEN("popping front & back until dq is empty") {
        THEN( "dq.front() and dq.back() should be as expected, and the size change" ) {
            for (int i = 0; i < 8 - 1; ++i) {
                dq.pop_front();
                dq.pop_back();
                REQUIRE(dq.front() == i + 1);
                REQUIRE(dq.back() == 16 - i - 2);
            }
            dq.pop_front();
            dq.pop_back();
            REQUIRE( dq.empty() );
        }
    }

    WHEN( "the size is increased" ) {
        dq.resize( 32 );
        THEN( "the size and capacity change" ) {
            REQUIRE( dq.size() == 32 );
        }
    }

    WHEN( "the size is reduced" ) {
        dq.resize( 0 );
        THEN( "the size changes but not capacity" ) {
            REQUIRE( dq.empty() );
        }
    }

    WHEN( "shrinking dq to fit" ) {
        dq.push_back(1);
        dq.push_back(2);
        dq.push_back(3);
        dq.pop_back();
        dq.pop_back();
        dq.pop_back();
        dq.shrink_to_fit();
        THEN( "the size does not change" ) {
            REQUIRE( dq.size() == 16 );
        }
    }

    WHEN( "inserting 3 * -1 at dq.begin() + 2" ) {
        dq.insert(dq.begin() + 2, 3, -1);
        THEN( "the size change, and dq[0] - dq[7] should be as expected" ) {
            REQUIRE( dq.size() == 19);
            REQUIRE( dq[0] == 0 );
            REQUIRE( dq[1] == 1 );
            REQUIRE( dq[2] == -1 );
            REQUIRE( dq[3] == -1 );
            REQUIRE( dq[4] == -1 );
            REQUIRE( dq[5] == 2 );
            REQUIRE( dq[6] == 3 );
            REQUIRE( dq[7] == 4 );
        }
    }
    
    WHEN( "erasing from dq.begin() + 3 to dq.end() - 10." ) {
        dq.erase(dq.begin() + 3, dq.end() - 10);
        THEN( "the size and capacity change, and dq[0] - dq[7] should be as expected" ) {
            REQUIRE( dq.size() == 13);
            REQUIRE( dq[0] == 0 );
            REQUIRE( dq[1] == 1 );
            REQUIRE( dq[2] == 2 );
            REQUIRE( dq[3] == 6 );
            REQUIRE( dq[4] == 7 );
            REQUIRE( dq[5] == 8 );
            REQUIRE( dq[6] == 9 );
            REQUIRE( dq[7] == 10 );
        }
    }
}


SCENARIO("STRING TESTS with str as a basic_string<char> (aka. string) object", "[string]") {
    string str = "Test string";

    WHEN("appending const char*") {
        str.append(" is good");
        THEN( "the contents should be as expected, and length change" ) {
            REQUIRE( strcmp(str.c_str(), "Test string is good" ) == 0);
            REQUIRE( str.length() == strlen("Test string is good"));
        }
    }

    WHEN("str + const char*") {
        string str2 = str + ", is it good?";
        THEN( "the contents should be as expected, and length change" ) {
            REQUIRE( strcmp(str2.c_str(), "Test string, is it good?" ) == 0);
            REQUIRE( str2.length() == strlen("Test string, is it good?"));
        }
    }
    
    WHEN("str2 +=  str + const char*") {
        string str2 = "Test string, ";
        str2 += str + ", is it good?";
        THEN( "the contents should be as expected, and length change" ) {
            REQUIRE( strcmp(str2.c_str(), "Test string, Test string, is it good?" ) == 0);
            REQUIRE( str2.length() == strlen("Test string, Test string, is it good?"));
        }
    }
}


SCENARIO("ALGORITHM TESTS", "[algo]") {
    int arr[]={3, 9, 5, 1, 7};

    WHEN("sort an int array, using default compare method(\"less than\")") {
        sort(arr, arr+5);
        THEN( "the array should be ascending" ) {
            REQUIRE( (arr[0] == 1 && arr[1] == 3 && arr[2] == 5 && arr[3] == 7 && arr[4] == 9) );
        }
    }

    WHEN("sort an int array, using c3::greater") {
        sort(arr, arr+5, greater<int>());
        THEN( "the array should be decending" ) {
            REQUIRE( (arr[0] == 9 && arr[1] == 7 && arr[2] == 5 && arr[3] == 3 && arr[4] == 1) );
        }
    }
    
    WHEN("sort an int array, and find lower bound of 5") {
        sort(arr, arr+5);
        THEN( "should be 5" ) {
            REQUIRE( *lower_bound(arr, arr+5, 5) == 5 );
        }
    }

    WHEN("sort an int array with c3::greater, and find lower bound of 5") {
        sort(arr, arr+5, greater<int>());
        THEN( "should be 5" ) {
            REQUIRE( *lower_bound(arr, arr+5, 5, greater<int>()) == 5 );
        }
    }    

    WHEN("sort an int array, and find upper bound of 5") {
        sort(arr, arr+5);
        THEN( "should be 7" ) {
            REQUIRE( *upper_bound(arr, arr+5, 5) == 7 );
        }
    }

    WHEN("sort an int array with c3::greater, and find upper bound of 5") {
        sort(arr, arr+5, greater<int>());
        THEN( "should be 3" ) {
            REQUIRE( *upper_bound(arr, arr+5, 5, greater<int>()) == 3 );
        }
    }
    
    WHEN("sort an int array, then binary search for 5 and 6") {
        sort(arr, arr+5);
        THEN( "search for 5 -> true, 6 -> false" ) {
            REQUIRE( binary_search(arr, arr+5, 5) == true );
            REQUIRE( binary_search(arr, arr+5, 6) == false );
        }
    }
    
    WHEN("sort an int array, then binary search for 5 and 6, using c3::greater") {
        sort(arr, arr+5, greater<int>());
        THEN( "search for 5 -> true, 6 -> false" ) {
            REQUIRE( binary_search(arr, arr+5, 5, greater<int>()) == true );
            REQUIRE( binary_search(arr, arr+5, 6, greater<int>()) == false );
        }
    }

    WHEN("merge two arrays with unequal length into another array") {
        int arr2[] = {0, 2, 4, 6, 8, 10, 11};
        sort(arr, arr+5);
        sort(arr2, arr2+7);
        int arr3[12];
        merge(arr, arr+5, arr2, arr2+7, arr3);
        THEN( "merged array should be ascending" ) {
            bool flag = true;
            for(int i = 0; i < 12; ++i) {
                flag = flag && (arr3[i] == i);
            }
            REQUIRE(flag);
        }
    }
}
