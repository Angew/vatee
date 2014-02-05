/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef VATEE_GUARD_PACK0
#define VATEE_GUARD_PACK0

#include "vatee/internal/compiler_version.hpp"

#include "vatee/internal/expansion.hpp"
#include "vatee/internal/facility.hpp"


#define VATEE_EXPAND_0_AFTER_1(vatee_arg0) \
	VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 2) (vatee_arg0, VATEE_INTERNAL_EMPTY)

#define VATEE_EXPAND_0_AFTER_2(vatee_arg0, vatee_arg1) \
	VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 3) (vatee_arg0, vatee_arg1, VATEE_INTERNAL_EMPTY)

#define VATEE_TRAILING_EXPAND_0_AFTER_1(vatee_arg0) \
	VATEE_NONEMPTY_0_COMMA VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 2) (vatee_arg0, VATEE_INTERNAL_EMPTY)

#define VATEE_TRAILING_EXPAND_0_AFTER_2(vatee_arg0, vatee_arg1) \
	VATEE_NONEMPTY_0_COMMA VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 3) (vatee_arg0, vatee_arg1, VATEE_INTERNAL_EMPTY)

#define VATEE_EXPAND_0_BETWEEN_2(vatee_arg0, vatee_arg1) \
	VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 2) (vatee_arg0, vatee_arg1 VATEE_INTERNAL_EMPTY)

#define VATEE_EXPAND_0_BETWEEN_3(vatee_arg0, vatee_arg1, vatee_arg2) \
	VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 3) (vatee_arg0, vatee_arg1, vatee_arg2 VATEE_INTERNAL_EMPTY)

#define VATEE_TEMPLATE_0(vatee_arg0) \
	VATEE_IF_NONEMPTY_0(template <) VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 2) (vatee_arg0, VATEE_INTERNAL_EMPTY) VATEE_IF_NONEMPTY_0(>)
	
#define VATEE_EMULATE_0() "vatee/internal/emulate0.hpp"

#endif	//VATEE_GUARD_PACK0
