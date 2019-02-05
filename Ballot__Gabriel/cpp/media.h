#ifndef MEDIA_H
#define MEDIA_H

#include <string>
#include <iostream>
#include <memory>

class Media {
    private :
        std::string name;
        std::string path;
    public :
        Media() : name("unknown_name"), path("unknown_path") {}
        Media(std::string name, std::string path) : name(name), path(path) {}

        virtual ~Media() {
            std::cout << "delete media : "
                << this->name
                << std::endl;
        }

        // sets the name of the media
        void setName(std::string name) { this->name = name; }
        // gets the name of the media
        std::string getName() const { return name; }

        // sets the path of the media
        void setPath(std::string path) { this-> path = path; }
        // gets the path of the media
        std::string getPath() const { return path; }

        // prints the media
        virtual void print(std::ostream& stream) const;
        // plays the media
        virtual void open() const = 0;
};

typedef std::shared_ptr<Media> MediaPtr;


#endif
