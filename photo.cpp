#include <string>
#include "photo.h"

using namespace std;

void Photo::print(std::ostream& stream) const {
    Media::print(stream);
    stream << "photo "
           << this->latitude 
           << " "
           << this->longitude;
}

void Photo::open() const {
    string str1 = "imagej ";
    string str2 = " &";
    string cmd = str1+this->getPath()+str2;
    system(cmd.c_str());
}
