#ifndef VALKYRIE_MODEL_H_INCLUDED
#define VALKYRIE_MODEL_H_INCLUDED

#include <string>
#include <map>
#include <iostream>
#include "valkyrie.h"
#include <boost/shared_ptr.hpp>

namespace valkyrie
{

class Node;

class DLL_PUBLIC Model
{
public:
    Model(int id, const std::string& name);

    bool addNode(boost::shared_ptr<Node> node);

    /* properties */
    const int get_id() const;
    const std::string get_name() const;
private:
    int id_;
    const std::string name_;
    std::map<int, boost::shared_ptr<Node> > nodes_;
};//~Model

}//~ns:valkyrie

#endif // VALKYRIE_MODEL_H_INCLUDED
