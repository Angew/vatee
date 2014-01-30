/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef VATEE_GUARD_INTERNAL_EXPANSION
#define VATEE_GUARD_INTERNAL_EXPANSION

#define VATEE_INTERNAL_EXPAND_MACRO(vatee_packsize, vatee_args) VATEE_INTERNAL_EXPAND_MACRO_I(vatee_packsize, vatee_args)

#define VATEE_INTERNAL_EXPAND_MACRO_I(vatee_packsize, vatee_args) \
	VATEE_INTERNAL_EXPAND_ ## vatee_packsize ## _ ## vatee_args

#define VATEE_INTERNAL_EXPAND_0_2(vatee_arg0, vatee_arg1)

#define VATEE_INTERNAL_EXPAND_0_3(vatee_arg0, vatee_arg1, vatee_arg2)

#define VATEE_INTERNAL_EXPAND_1_2(vatee_arg0, vatee_arg1) \
	vatee_arg0 ## 0 vatee_arg1()

#define VATEE_INTERNAL_EXPAND_1_3(vatee_arg0, vatee_arg1, vatee_arg2) \
	vatee_arg0 ## 0 vatee_arg1 ## 0 vatee_arg2()

#define VATEE_INTERNAL_EXPAND_2_2(vatee_arg0, vatee_arg1) \
	vatee_arg0 ## 0 vatee_arg1() \
	, vatee_arg0 ## 1 vatee_arg1()

#define VATEE_INTERNAL_EXPAND_2_3(vatee_arg0, vatee_arg1, vatee_arg2) \
	vatee_arg0 ## 0 vatee_arg1 ## 0 vatee_arg2() \
	, vatee_arg0 ## 1 vatee_arg1 ## 1 vatee_arg2()

#define VATEE_INTERNAL_EXPAND_3_2(vatee_arg0, vatee_arg1) \
	vatee_arg0 ## 0 vatee_arg1() \
	, vatee_arg0 ## 1 vatee_arg1() \
	, vatee_arg0 ## 2 vatee_arg1()

#define VATEE_INTERNAL_EXPAND_3_3(vatee_arg0, vatee_arg1, vatee_arg2) \
	vatee_arg0 ## 0 vatee_arg1 ## 0 vatee_arg2() \
	, vatee_arg0 ## 1 vatee_arg1 ## 1 vatee_arg2() \
	, vatee_arg0 ## 2 vatee_arg1 ## 2 vatee_arg2()

#define VATEE_INTERNAL_EXPAND_4_2(vatee_arg0, vatee_arg1) \
	vatee_arg0 ## 0 vatee_arg1() \
	, vatee_arg0 ## 1 vatee_arg1() \
	, vatee_arg0 ## 2 vatee_arg1() \
	, vatee_arg0 ## 3 vatee_arg1()

#define VATEE_INTERNAL_EXPAND_4_3(vatee_arg0, vatee_arg1, vatee_arg2) \
	vatee_arg0 ## 0 vatee_arg1 ## 0 vatee_arg2() \
	, vatee_arg0 ## 1 vatee_arg1 ## 1 vatee_arg2() \
	, vatee_arg0 ## 2 vatee_arg1 ## 2 vatee_arg2() \
	, vatee_arg0 ## 3 vatee_arg1 ## 3 vatee_arg2()

#endif	//VATEE_GUARD_INTERNAL_EXPANSION

