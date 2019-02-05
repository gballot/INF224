#ifndef VIDEO_H
#define VIDEO_H

#include "media.h"

class Video : public Media {
    private :
        int length = 0;
    public :
        Video() {}
        Video(std::string name, std::string path, int length) :
            Media(name, path), length(length) {}

        //sets the length of the film
        virtual void setLength(int length) { this->length = length; }
        // gets the length of the film
        int getLength() const { return length; }
        // prints the film in a strem
        void print(std::ostream& stream) const override;
        // plays the film
        void open() const override;
};

typedef std::shared_ptr<Video> VideoPtr;

#endif
