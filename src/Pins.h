#ifndef PINS_H__
#define PINS_H__

// Load Pins_<platform>.h

#if !defined(PLATFORM)
# if defined(__SAM3X8E__)
#  if defined(__RADDS__)
#   define PLATFORM RADDS
#   define PLATFORM_DIR RADDS
#  else
#   define PLATFORM Duet
#   define PLAFTFORM_DIR Duer
#  endif
# elif defined(__SAM4E8E__) || defined(__SAM4E8C__)
#  if defined(DUET_NG)
#    define PLATFORM DuetNG
#    define PLATFORM_DIR DuetNG
#  elif defined(AX7)
#    define PLATFORM AX7M
#    define PLATFORM_DIR DuetNG
#  else
#    error Unknown platform
#  endif
# else
#  error Unknown platform
# endif
#endif

#define P_EXPAND(x) x
#define P_CONCAT(x,y) P_EXPAND(x)y
#define P_STR(x) #x
#define P_XSTR(x) P_STR(x)
#define P_INCLUDE_FILE P_XSTR(P_CONCAT(PLATFORM_DIR,P_CONCAT(/Pins_,P_CONCAT(PLATFORM,.h))))
#include P_INCLUDE_FILE
#endif // PINS_H__
