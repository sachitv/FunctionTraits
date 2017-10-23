//
//  main.cpp
//  FunctionTraits
//
//  Created by Sachit Vithaldas on 22/10/17.
//
//

#include <iostream>
#include <type_traits>
#include <functional>

#include "headers/functiontraits.h"

class Example
{
public:
    int exampleFn1(int&& a, int const& b, int c) const
    {
        return 5;
    }
    int operator()(int const a) const
    {
        return 5;
    }
    
    void blank()
    {
        return;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    using namespace custom_traits;
    using namespace std;
    
    std::function<int(double)> test;
    
    static_assert(is_const_member_function<decltype(&Example::exampleFn1)>::value, "");
    static_assert(is_const_member_function<decltype(&Example::operator())>::value, "");
    
    using E1 = function_traits<decltype(&Example::exampleFn1)>;
    static_assert(is_same<E1::return_type, int>(), "");
    static_assert(E1::arity == 3, "");
    static_assert(std::is_same<E1::argument<0>::type,int&&>::value,"");
    static_assert(std::is_rvalue_reference<E1::argument<0>::type>::value,"");
    
    using E2 = function_traits<decltype(&Example::operator())>;
    static_assert(E2::arity == 1, "");
    
    using E3 = function_traits<decltype(test)>;
    static_assert(is_same<E3::return_type, int>(), "");
    static_assert(is_floating_point<E3::argument<0>::type>::value, "");
    
    using E4 = function_traits<decltype(&Example::blank)>;
    static_assert(E4::arity == 0, "");

    cout<<"Success"<<endl;
    
    return 0;
}
