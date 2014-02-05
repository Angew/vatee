/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "vatee/pack0.hpp"
#include "vatee/punctuation.hpp"

#include <iostream>


template <class T, class U>
const T& as(const U &a)
{ return a; }


void print()
{}


#define VATEE_VARIADIC \
	template <class T VATEE_TRAILING_EXPAND_0_AFTER_1(class T)> \
	void print(const T &a VATEE_TRAILING_EXPAND_0_AFTER_2(const T, &a)) { \
		std::cout << a << '\n'; \
		VATEE_IF_NONEMPTY_0(print(VATEE_EXPAND_0_AFTER_1(a));) \
	}
#include VATEE_EMULATE_0()


#
#define VATEE_VARIADIC \
	VATEE_TEMPLATE_0(class T) \
	void test(VATEE_EXPAND_0_AFTER_2(const T, &a)) { \
		print(VATEE_EXPAND_0_AFTER_1(a)); \
		print(VATEE_EXPAND_0_BETWEEN_3(as<T, >VATEE_LPAREN a, VATEE_RPAREN)); \
	}
#include VATEE_EMULATE_0()


int main()
{
	test(1, 2.5, 'a', "s");
}
