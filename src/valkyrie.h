#ifndef VALKYRIE_H_INCLUDED
#define VALKYRIE_H_INCLUDED

#include <stdio.h>

/* From API C++ */
#if defined _WIN32 || defined __CYGWIN__
    #ifdef revolution_EXPORTS // define this when generating DLL
        #ifdef __GNUC__
            #define DLL_PUBLIC __attribute__((dllexport))
        #else
            #define DLL_PUBLIC __declspec(dllexport)
        #endif
    #else
        #ifdef __GNUC__
            #define DLL_PUBLIC __attribute__((dllimport))
        #else
            #define DLL_PUBLIC __declspec(dllimport)
        #endif
    #endif
    #define DLL_HIDDEN
#else
    #if __GNUC__ >= 4
        #define DLL_PUBLIC __attribute__ ((visibility("default")))
        #define DLL_HIDDEN __attribute__ ((visibility("hidden")))
    #else
        #define DLL_PUBLIC
        #define DLL_HIDDEN
    #endif
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define VK_API_MAJOR 0
#define VK_API_MINOR 1
#define VK_API_PATCH 0
#define VK_API_VERSION "0.1.0"

/* version related functions */
DLL_PUBLIC extern int VKApiMajorVersion(void);
DLL_PUBLIC extern int VKApiMinorVersion(void);
DLL_PUBLIC extern int VKApiPatchVersion(void);
DLL_PUBLIC extern int VKApiVersionIsAtLeast(int major, int minor, int patch);
DLL_PUBLIC extern const char *VKApiVersion(void);

#ifdef __cplusplus
}
#endif

#endif // VALKYRIE_H_INCLUDED
