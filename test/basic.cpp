/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#include "vatee/pack.hpp"

#include <iostream>


template <class T, class U>
const T& as(const U &a)
{ return a; }


#define VATEE_VARIADIC \
	template <class T VATEE_EXPAND_TRAILING_AFTER_1(class T)> \
	void print(const T &a VATEE_EXPAND_TRAILING_AFTER_2(const T, &a)) { \
		std::cout << a << '\n'; \
		VATEE_IF_VARIADIC(print(VATEE_EXPAND_AFTER_1(a));) \
	}
#include VATEE_EMULATE()


#define VATEE_VARIADIC \
	VATEE_TEMPLATE(class T) \
	void test(VATEE_EXPAND_AFTER_2(const T, &a)) { \
		print(VATEE_EXPAND_AFTER_1(a)); \
		print(VATEE_EXPAND_BETWEEN_3(as<T, >VATEE_LPAREN, VATEE_RPAREN)); \
	}
#include VATEE_EMULATE()


int main()
{
	test(1, 2.5, 'a', "s");
}
