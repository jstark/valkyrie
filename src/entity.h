#ifndef VALKYRIE_ENTITY_H_INCLUDED
#define VALKYRIE_ENTITY_H_INCLUDED

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

namespace valkyrie
{

using boost::shared_ptr;

#define kActionOK                   1 << 0
#define kActionFailed               1 << 1
#define kActionErrorIdAlreadyExists 1 << 2

class Entity
{
public:
    Entity(int id, const std::string &name = "")
        : id_(id), name_(name) {}

    const int get_id() const { return id_; }
    const std::string get_name() const { return name_; }
private:
    int id_;
    std::string name_;
};

#define IS_ENTITY \
    using Entity::get_id; \
    using Entity::get_name;

template<typename TEntity>
class EntityDb
{
public:
    typedef TEntity entity_type;
    typedef std::map<int, shared_ptr<TEntity> > db_type;

    int add(boost::shared_ptr<TEntity> ref);
private:
    db_type db_;
};

template<typename TEntity>
int EntityDb<TEntity>::add(shared_ptr<TEntity> ref)
{
    int id = ref->get_id(); // must have this property
    if (db_.find(id) != db_.end())
    {
        return kActionFailed | kActionErrorIdAlreadyExists;
    } else
    {
        db_.insert(std::make_pair(id, ref));
        return kActionOK;
    }
}

}//~ valkyrie

#endif // VALKYRIE_ENTITY_H_INCLUDED
