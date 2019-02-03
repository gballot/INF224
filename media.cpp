#include "media.h"

using namespace std;

void Media::print(std::ostream& stream) const {
    stream << this->name 
           << " "
           << this->path
           << " ";
}
