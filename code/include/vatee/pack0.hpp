#ifndef
#define

#define VATEE_EXPAND_0_AFTER_1(vatee_arg0) \
  VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 2) (vatee_arg0, VATEE_INTERNAL_EMPTY)

#define VATEE_EXPAND_0_AFTER_2(vatee_arg0, vatee_arg1) \
  VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 3) (vatee_arg0, vatee_arg1, VATEE_INTERNAL_EMPTY)

#define VATEE_EXPAND_0_BETWEEN_2(vatee_arg0, vatee_arg1) \
  VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 2) (vatee_arg0, vatee_arg1 VATEE_INTERNAL_EMPTY)

#define VATEE_EXPAND_0_BETWEEN_3(vatee_arg0, vatee_arg1, vatee_arg2) \
  VATEE_INTERNAL_EXPAND_MACRO(VATEE_PACKSIZE_0, 3) (vatee_arg0, vatee_arg1, vatee_arg2 VATEE_INTERNAL_EMPTY)

#endif