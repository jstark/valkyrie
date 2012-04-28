#ifndef VALKYRIE_H_INCLUDED
#define VALKYRIE_H_INCLUDED

#include <stdio.h>

/* From API C++ */
#if defined _WIN32 || defined __CYGWIN__
    #ifdef valkyrie_EXPORTS // define this when generating DLL
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

#define VK_API_MAJOR 1
#define VK_API_MINOR 0
#define VK_API_PATCH 0
#define VK_API_VERSION "1.0.0"

/* version related functions */

/*! \fn void VKApiMajorVersion(void);
* \brief Gets the library's major version.
* \return returns the \ref VK_API_MAJOR value.
* @see VKApiMinorVersion(), VKApiPatchVersion()
*/
extern DLL_PUBLIC int VKApiMajorVersion(void);

/*! \fn void VKApiMinorVersion(void);
* \brief Gets the library's minor version.
* \return returns the \ref VK_API_MINOR value.
* @see VKApiMajorVersion(), VKApiPatchVersion()
*/
extern DLL_PUBLIC int VKApiMinorVersion(void);

/*! \fn void VKApiPatchVersion(void);
* \brief Gets the library's patch version.
* \return returns the \ref VK_API_PATCH value.
* @see VKApiMajorVersion(), VKApiMinorVersion()
*/
extern DLL_PUBLIC int VKApiPatchVersion(void);

/*! \fn void VKApiVersionIsAtLeast(int major, int minor, int patch);
* \brief Checks the version of the Api.
* \param major the major version.
* \param minor the minor version.
* \param patch the patch version.
* \return returns whether the Api's version is at least the given version.
* @see VKApiMajorVersion(), VKApiMinorVersion()
*/
extern DLL_PUBLIC int VKApiVersionIsAtLeast(int major, int minor, int patch);

/*! \fn void VKApiVersion(void);
* \brief Gets the library's Api version.
* \return returns the \ref VK_API_VERSION value.
* @see VKApiMajorVersion(), VKApiMinorVersion()
*/
extern DLL_PUBLIC const char *VKApiVersion(void);

/*! \fn void VKModelCreate(int mid, const char *name);
* \brief Creates a new FE model.
* \param mid the model id, a positive integer.
* \param name the model's name. If \a name is NULL, the model's name
* will be an empty string.
* \return TODO
* @see
*/
extern int VKModelCreate(int mid, const char *name);

/*! \fn void VKModelCreateNode(int mid, int nid, double x, double y, double z);
* \brief Creates a new FE node.
* \param mid the model's id, a positive integer.
* \param nid the node's id, a positive integer.
* \param x the node's x coordinate.
* \param y the node's y coordinate.
* \param z the node's z coordinate.
* \return TODO
* @see
*/
extern int VKModelCreateNode(int mid, int nid, double x, double y, double z);

#ifdef __cplusplus
}
#endif

#endif // VALKYRIE_H_INCLUDED
