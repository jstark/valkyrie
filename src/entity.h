#ifndef VALKYRIE_ENTITY_H_INCLUDED
#define VALKYRIE_ENTITY_H_INCLUDED

#include <string>
#include <map>

#include <boost/shared_ptr.hpp>

namespace valkyrie
{

#define LOG_DESTRUCTORS

#define kActionOK                   1 << 0
#define kActionFailed               1 << 1
#define kActionErrorIdAlreadyExists 1 << 2
#define kActionErrorIdDoesNotExist  1 << 3
#define kActionErrorInvalidArgs     1 << 4

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

using boost::shared_ptr;

template<typename TEntity>
class EntityDb
{
public:
    typedef TEntity entity_type;
    typedef int id_type;
    typedef std::map<id_type, shared_ptr<TEntity> > db_type;
    typedef typename db_type::size_type size_type;
    typedef typename db_type::const_iterator const_iterator;


    int add(boost::shared_ptr<TEntity> ref);
    shared_ptr<TEntity> find(int id) const;
    int remove(int id);
    size_type size() const { return db_.size(); }
    const_iterator begin() const { return db_.begin(); }
    const_iterator end() const { return db_.end(); }
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

template<typename TEntity>
shared_ptr<TEntity> EntityDb<TEntity>::find(int id) const
{
    typename db_type::const_iterator i = db_.find(id);
    if (i == db_.end())
    {
        return shared_ptr<TEntity>((TEntity *)0);
    }
    return i->second;
}

template<typename TEntity>
int EntityDb<TEntity>::remove(int id)
{
    int flag = db_.erase(id);
    if (!flag)
    {
        return kActionFailed | kActionErrorIdDoesNotExist;
    }
    return kActionOK;
}

template<typename T> boost::shared_ptr<T> make_shared(T* instance)
{
    return boost::shared_ptr<T>(instance);
}

}//~ valkyrie

#endif // VALKYRIE_ENTITY_H_INCLUDED
