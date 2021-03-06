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

/*! \fn const char *VKErrorMessage(int errcode);
* \brief Gets the error message for an error code.
* \param errcode the error code.
* \return returns the error message, or NULL if code is not
* an error.
*/
extern DLL_PUBLIC const char *VKErrorMessage(int errcode);

#define kTranslateXDof  1
#define kTranslateYDof  2
#define kTranslateZDof  4

/*! \fn int VKDofCode(int x, int y, int z);
* \brief Calculates the dof code of a constraint combination.
* \param x the x translation component. Pass 1 to constrain, or 0 otherwise.
* \param y the y translation component. Pass 1 to constrain, or 0 otherwise.
* \param z the z translation component. Pass 1 to constrain, or 0 otherwise.
* \return The dof code to be used with an spc constraint.
* @see \ref VKModelCreateSpc
*/
extern DLL_PUBLIC int VKDofCode(int x, int y, int z);

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
* \return the version's string representation as 'major.minor.patch'
* @see
*/
extern DLL_PUBLIC int VKModelCreate(int mid, const char *name);

/*! \fn void VKModelCreateNode(int mid, int nid, double x, double y, double z);
* \brief Creates a new FE node.
* \param mid the model's id, a positive integer.
* \param nid the node's id, a positive integer.
* \param x the node's x coordinate.
* \param y the node's y coordinate.
* \param z the node's z coordinate.
* \return Returns an error code. Use \ref VKErrorMessage to find out whether an error occurred. 
* @see \ref VKModelCreateNode, \ref VKModelCreateMaterial
*/
extern DLL_PUBLIC int VKModelCreateNode(int mid, int nid, double x, double y, double z);

/*! \fn void VKModelCreateMaterial(int modelid, int matid, double E, double rho, const char *name);
* \brief Creates a new description for an elastic material.
* \param modelid the model's id, a positive integer.
* \param matid the material's id, a positive integer.
* \param E the material's young modulus, a positive number.
* \param rho the material's density, a positive number.
* \param name the material's name, which can be NULL.
* \return Returns an error code. Use \ref VKErrorMessage to find out whether an error occurred. 
* @see \ref VKModelCreate
*/
extern DLL_PUBLIC int VKModelCreateMaterial(int modelid, int matid, double E, double rho, const char *name);

/*! \fn void VKModelCreateProperty(int mid, int pid, int matid, double A, const char *name);
* \brief Creates a new property description.
* \param mid the model's id, a positive integer.
* \param pid the property's id, a positive integer.
* \param matid the property's material id, which must exist in model.
* \param A the cross-section value, a positive number.
* \param name the property's name.
* \return Returns an error code. Use \ref VKErrorMessage to find out whether an error occurred. 
* @see \ref VKModelCreateMaterial
*/
extern DLL_PUBLIC int VKModelCreateProperty(int mid, int pid, int matid, double A, const char *name);

/*! \fn void VKModelCreateRod(int mid, int rid, int pid, int n1, int n2);
* \brief Creates a new rod element.
* \param mid the model's id, a positive integer.
* \param rid the element's id, a positive integer.
* \param pid the element's property id, which must exist in model.
* \param n1 the element's first node, which must exist in model.
* \param n2 the element's second node, which must exist in model.
* \return Returns an error code. Use \ref VKErrorMessage to find out whether an error occurred. 
* @see \ref VKModelCreateNode, \ref VKModelCreateProperty
*/
extern DLL_PUBLIC int VKModelCreateRod(int mid, int rid, int pid, int n1, int n2);

/*! \fn int VKModelCreateSpc(int mid, int sid, int dofs, int nid);
* \brief Creates a new single point constraint.
* \param mid the model's id, a positive integer.
* \param sid the spc's id, a positive integer.
* \param dofs the degrees to constrain.
* \param nid the node onto which the spc is applied, which must exist in model.
* \return Returns an error code. Use \ref VKErrorMessage to find out whether an error occurred. 
* @see \ref VKModelCreateForce
*/
extern DLL_PUBLIC int VKModelCreateSpc(int mid, int sid, int dofs, int nid);

/*! \fn int VKModelCreateForce(int mid, int fid, int nid, double magn, double nx, double ny, double nz);
* \brief Creates a new point load.
* \param mid the model's id, a positive integer.
* \param fid the force's id, a positive integer.
* \param nid the node id onto which the force will be applied, which must exist in model.
* \param magn the force's magnitude.
* \param nx the force's direction component in the x direction.
* \param ny the force's direction component in the y direction.
* \param nz the force's direction component in the z direction.
* \return Returns an error code. Use \ref VKErrorMessage to find out whether an error occurred. 
* @see \ref VKModelCreateSpc
*/
extern DLL_PUBLIC int VKModelCreateForce(int mid, int fid, int nid, double magn, double nx, double ny, double nz);

/*! \fn int VKModelPerformStaticAnalysis(int mid);
 * \brief Performs a static analysis on the given model (id).
 * \return Returns an error code. Use \ref VKErrorMessage to find out whether an error occurred. 
 * @see \ref VKErrorMessage
 */
extern DLL_PUBLIC int VKModelPerformStaticAnalysis(int mid);

/*! \typedef void (*VK_FOR_EACH_NODAL_RESULT_FUNCTION)(int nid, double ux, double uy, double uz, double react_x, double react_y, double react_z, void *data);
 *  \brief The function signature for callbacks used with \ref VKStaticAnalysisForEachNodalResult.
 * @see \ref VKStaticAnalysisForEachNodalResult
 */
typedef void (*VK_FOR_EACH_NODAL_RESULT_FUNCTION)(
        int nid,
        double ux,
        double uy,
        double uz,
        double react_x,
        double react_y,
        double react_z,
        void *data);

/*! int VKStaticAnalysisForEachNodalResult(int mid, VK_FOR_EACH_NODAL_RESULT_FUNCTION fun, void *data);
 *  \brief Runs a function for each nodal result.
 *  \param mid the model id.
 *  \param fun the function to run
 *  \param data the user data, if any.
 */
extern DLL_PUBLIC int VKStaticAnalysisForEachNodalResult(int mid, VK_FOR_EACH_NODAL_RESULT_FUNCTION fun, void *data);


/*! \typedef void (*VK_FOR_EACH_ELEMENT_RESULT_FUNCTION)(int eid, double stress, double strain, double force, void *data);
 *  \brief The function signature for callbacks used with \ref VKStaticAnalysisForEachElementResult.
 * @see \ref VKStaticAnalysisForEachElementResult
 */
typedef void (*VK_FOR_EACH_ELEMENT_RESULT_FUNCTION)(
        int eid,
        double stress,
        double strain,
        double force,
        void *data);

/*! int VKStaticAnalysisForEachElementResult(int mid, VK_FOR_EACH_ELEMENT_RESULT_FUNCTION fun, void *data);
 *  \brief Runs a function for each element result.
 *  \param mid the model id.
 *  \param fun the function to run
 *  \param data the user data, if any.
 */
extern DLL_PUBLIC int VKStaticAnalysisForEachElementResult(int mid, VK_FOR_EACH_ELEMENT_RESULT_FUNCTION fun, void *data);

/*! int VKStaticAnalysisPrintResults(int mid);
 *  \brief Prints nodal and elemental results in stdio.
 *  \param mid the model id.
 */
extern DLL_PUBLIC int VKStaticAnalysisPrintResults(int mid);
#ifdef __cplusplus
}
#endif

#endif // VALKYRIE_H_INCLUDED
