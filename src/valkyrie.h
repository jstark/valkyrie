#ifndef VALKYRIE_H_INCLUDED
#define VALKYRIE_H_INCLUDED

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

#define VK_API_MAJOR 0
#define VK_API_MINOR 0
#define VK_API_PATCH 0
#define VK_API_VERSION "0.0.0"

#endif // VALKYRIE_H_INCLUDED
