#ifndef GROUP_H
#define GROUP_H

#include <list>
#include "media.h"

class Group : public std::list<MediaPtr> {
    private :
        std::string name;
    public :
        Group() : list<MediaPtr>() {}
        Group(std::string name) : list<MediaPtr>(), name(name) {}
        
        std::string getName() const { return this->name; }
        void printAll(std::ostream& stream) const;
};

typedef std::shared_ptr<Group> GroupPtr;

#endif
