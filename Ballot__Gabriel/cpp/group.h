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
        
        // gets the name of the group
        std::string getName() const { return this->name; }
        // print one by one all the medias in the group in a stream
        void printAll(std::ostream& stream) const;
};

typedef std::shared_ptr<Group> GroupPtr;

#endif
