#ifndef MEDIA_H
#define MEDIA_H

#include <string>


class Media {
    private :
        std::string name;
        std::string path;
    public :
        Media(std::string name, std::string path) : name(name), path(path) {}
        Media() {}

        ~Media() {}

        void setName(std::string name) { this->name = name; }
        std::string getName() const { return name; }

        void setPath(std::string path) { this-> path = path; }
        std::string getPath() const { return path; }

        void print(std::ostream& stream) const ;
};


#endif
