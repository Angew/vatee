/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#ifndef VATEE_GUARD_INTERNAL_COMPILER_VERSION
#define VATEE_GUARD_INTERNAL_COMPILER_VERSION

#ifndef VATEE_CONFIG_GCC_VERSION
	#ifdef __GNUC__
		#ifdef __GNUC_PATCHLEVEL__
			#define VATEE_CONFIG_GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__ )
		#else
			#define VATEE_CONFIG_GCC_VERSION ( __GNUC__ * 10000 + __GNUC_MINOR__ * 100 )
		#endif
	#endif
#endif


#ifndef VATEE_CONFIG_MSVC_VERSION
	#ifdef _MSC_VER
		#define VATEE_CONFIG_MSVC_VERSION ( _MSC_VER )
	#endif
#endif

#endif
