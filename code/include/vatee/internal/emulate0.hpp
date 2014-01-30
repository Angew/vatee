/*
Copyright Petr Kmoch 2014.
Distributed under the Boost Software License, Version 1.0.
(See accompanying file ../../../../LICENSE or copy at http://www.boost.org/LICENSE_1_0.txt)
*/

#define VATEE_IF_NONEMPTY_0(...)

#define VATEE_NONEMPTY_0_COMMA

#define VATEE_PACKSIZE_0 0

VATEE_VARIADIC

#undef VATEE_IF_NONEMPTY_0
#define VATEE_IF_NONEMPTY_0(...) __VA_ARGS__

#undef VATEE_NONEMPTY_0_COMMA
#define VATEE_NONEMPTY_0_COMMA ,

#undef VATEE_PACKSIZE_0
#define VATEE_PACKSIZE_0 1

VATEE_VARIADIC

#undef VATEE_PACKSIZE_0
#define VATEE_PACKSIZE_0 2

VATEE_VARIADIC

#undef VATEE_PACKSIZE_0
#define VATEE_PACKSIZE_0 3

VATEE_VARIADIC

#undef VATEE_PACKSIZE_0
#define VATEE_PACKSIZE_0 4

VATEE_VARIADIC

#undef VATEE_IF_NONEMPTY_0
#undef VATEE_NONEMPTY_0_COMMA
#undef VATEE_PACKSIZE_0
#undef VATEE_VARIADIC
