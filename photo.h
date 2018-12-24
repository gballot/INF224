#ifndef PHOTO_H
#define PHOTO_H

#include "media.h"

class Photo : public Media {
    private :
        float latitude = 0;
        float longitude = 0;
    public :
        Photo() {}
        Photo(std::string name, std::string path, float latitude, float longitude) :
            Media(name, path), latitude(latitude), longitude(longitude) {}

        void setLatitude(float latitude) { this->latitude = latitude; }
        float getLatitude() const { return latitude; }

        void setLongitude(float longitude) { this->longitude = longitude; }
        float getLongitude() const { return longitude; }
        void print(std::ostream& stream) const override;
        void open() const override;
};

typedef std::shared_ptr<Photo> PhotoPtr;

#endif
