#ifndef __AUTO_INIT_H__
#define __AUTO_INIT_H__

#ifdef __cplusplus
extern "C" {
#endif

#define USING_AUTO_INIT
//#define AUTO_INIT_USING_NEWLIB

/* Compiler Related Definitions */
#if defined(__CC_ARM) || defined(__CLANG_ARM)           /* ARM Compiler */
    #include <stdarg.h>
    #define AUTO_INIT_SECTION(x)        __attribute__((section(x)))
                   __attribute__((unused))
    #define AUTO_INIT_USED              __attribute__((used))
#elif defined (__IAR_SYSTEMS_ICC__)     /* for IAR Compiler */
    #include <stdarg.h>
    #define AUTO_INIT_SECTION(x)        @ x
    #define AUTO_INIT_USED              __root
#elif defined (__GNUC__)                /* GNU GCC Compiler */
    #ifdef AUTO_INIT_USING_NEWLIB
        #include <stdarg.h>
    #else
        /* the version of GNU GCC must be greater than 4.x */
        typedef __builtin_va_list       __gnuc_va_list;
        typedef __gnuc_va_list          va_list;
        #define va_start(v,l)           __builtin_va_start(v,l)
        #define va_end(v)               __builtin_va_end(v)
        #define va_arg(v,l)             __builtin_va_arg(v,l)
    #endif
    #define AUTO_INIT_SECTION(x)        __attribute__((section(x)))
                   __attribute__((unused))
    #define AUTO_INIT_USED              __attribute__((used))
#elif defined (__ADSPBLACKFIN__)        /* for VisualDSP++ Compiler */
    #include <stdarg.h>
    #define AUTO_INIT_SECTION(x)        __attribute__((section(x)))
                   __attribute__((unused))
    #define AUTO_INIT_USED              __attribute__((used))
#elif defined (_MSC_VER)
    #include <stdarg.h>
    #define AUTO_INIT_SECTION(x)
    #define AUTO_INIT_USED
#elif defined (__TI_COMPILER_VERSION__)
    #include <stdarg.h>
    /* The way that TI compiler set section is different from other(at least
     * GCC and MDK) compilers. See ARM Optimizing C/C++ Compiler 5.9.3 for more
     * details. */
    #define AUTO_INIT_SECTION(x)
    #define AUTO_INIT_USED
#else
    #error not supported tool chain
#endif

#ifdef USING_AUTO_INIT
typedef int (*init_fn_t)(void);
#ifdef _MSC_VER /* we do not support MS VC++ compiler */
    #define INIT_EXPORT(fn, level)
#else
    #define INIT_EXPORT(fn, level)                                                       \
        AUTO_INIT_USED const init_fn_t __auto_init_##fn AUTO_INIT_SECTION(".rti_fn."level) = fn
#endif
#else
#define INIT_EXPORT(fn, level)
#endif

/* board init routines will be called in board_init() function */
#define INIT_BOARD_EXPORT(fn)           INIT_EXPORT(fn, "1")

/* pre/device/component/env/app init routines will be called in init_thread */
/* components pre-initialization (pure software initilization) */
#define INIT_PREV_EXPORT(fn)            INIT_EXPORT(fn, "2")
/* device initialization */
#define INIT_DEVICE_EXPORT(fn)          INIT_EXPORT(fn, "3")
/* components initialization (dfs, lwip, ...) */
#define INIT_COMPONENT_EXPORT(fn)       INIT_EXPORT(fn, "4")
/* environment initialization (mount disk, ...) */
#define INIT_ENV_EXPORT(fn)             INIT_EXPORT(fn, "5")
/* appliation initialization (rtgui application etc ...) */
#define INIT_APP_EXPORT(fn)             INIT_EXPORT(fn, "6")

void level1_init(void);
void level2_6_init(void);

#ifdef __cplusplus
}
#endif

#endif /* __AUTO_INIT_H__ */
