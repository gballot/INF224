#include <string>
#include "video.h"

using namespace std;

void Video::print(std::ostream& stream) const {
    Media::print(stream);
    stream << "length : " << this->length;
}

void Video::open() const {
    string str1 = "mpv ";
    string str2 = " &";
    string cmd = str1+this->getPath()+str2;
    system(cmd.c_str());
}
