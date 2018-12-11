#ifndef GROUP_H
#define GROUP_H

#include <list>
#include "media.h"

class Group : public std::list<Media *> {
    private :
        std::string name;
    public :
        Group() : list<Media *>() {}
        Group(std::string name) : list<Media *>(), name(name) {}
        
        std::string getName() const { return this->name; }
        void printAll(std::ostream& stream) const;
};

#endif
