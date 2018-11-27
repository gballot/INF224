#include "media.h"

using namespace std;

void Media::print(std::ostream& stream) const {
    stream << "name : " << this->name 
        << "\npath : " << this->path 
        << endl;
}
