#ifndef VALKYRIE_VERSION_H_INCLUDED
#define VALKYRIE_VERSION_H_INCLUDED

#include "valkyrie.h"
#include <string>
#include <boost/noncopyable.hpp>

namespace valkyrie
{

// provides a simple versioning info for the API
class DLL_HIDDEN Version : boost::noncopyable
{
public:
    static int getMajor();
    static int getMinor();
    static int getPatch();
    static const std::string getVersion();
    static bool isAtLeast(int major, int minor, int patch);
};//~cl:Version

}//~ ns:valkyrie

#endif /* VALKYRIE_VERSION_H_INCLUDED */
