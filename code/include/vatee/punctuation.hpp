/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef VATEE_GUARD_PUNCTUATION
#define VATEE_GUARD_PUNCTUATION

#include "vatee/internal/compiler_version.hpp"


#define VATEE_LPAREN \
	VATEE_INTERNAL_LPAREN VATEE_INTERNAL_CALL_NOW

#define VATEE_RPAREN \
	VATEE_INTERNAL_RPAREN VATEE_INTERNAL_CALL_NOW

#define VATEE_COMMA \
	VATEE_INTERNAL_COMMA VATEE_INTERNAL_CALL_NOW

#define VATEE_INTERNAL_CALL_NOW ()

#define VATEE_INTERNAL_CALL_LATER() ()

#define VATEE_INTERNAL_LPAREN() (

#define VATEE_INTERNAL_RPAREN() )

#define VATEE_INTERNAL_COMMA() ,

#endif	//VATEE_GUARD_PUNCTUATION
