#include "group.h"

void Group::printAll(std::ostream& stream) const {
    for(auto & it : *this) {
        it->print(stream);
        stream << endl;
    }
}

