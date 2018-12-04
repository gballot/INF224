#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <iostream>

class Media {
    private :
        std::string name;
        std::string path;
    public :
        Media() {}
        Media(std::string name, std::string path) : name(name), path(path) {}

        virtual ~Media() {}

        void setName(std::string name) { this->name = name; }
        std::string getName() const { return name; }

        void setPath(std::string path) { this-> path = path; }
        std::string getPath() const { return path; }

        virtual void print(std::ostream& stream) const;
        virtual void open() const = 0;
};


#endif
