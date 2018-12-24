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

        virtual void setLength(int length) { this->length = length; }
        int getLength() const { return length; }
        void print(std::ostream& stream) const override;
        void open() const override;
};

typedef std::shared_ptr<Video> VideoPtr;

#endif
