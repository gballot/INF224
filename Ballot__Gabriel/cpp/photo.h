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

        // sets the latitude of the photo
        void setLatitude(float latitude) { this->latitude = latitude; }
        // gets the latitude of the photo
        float getLatitude() const { return latitude; }

        // sets the longitude of the photo
        void setLongitude(float longitude) { this->longitude = longitude; }
        // gets the longitude of the photo
        float getLongitude() const { return longitude; }
        // print the photo in a stream
        void print(std::ostream& stream) const override;
        // displays the photo
        void open() const override;
};

typedef std::shared_ptr<Photo> PhotoPtr;

#endif
