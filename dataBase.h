#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <string>
#include <map>
#include "media.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"

class DataBase {
    private :
        std::map<std::string, MediaPtr> mediaMap;
        std::map<std::string, GroupPtr> groupMap;
    public :
        DataBase() {}

        PhotoPtr createPhoto();
        PhotoPtr createPhoto(std::string name, std::string path, float latitude, float longitude);

        VideoPtr createVideo();
        VideoPtr createVideo(std::string name, std::string path, int length);

        FilmPtr createFilm();
        FilmPtr createFilm(std::string name, std::string path, int length);
        FilmPtr createFilm(std::string name, std::string path, int length, int nb_chapters, int *tab);
        FilmPtr createFilm(std::string name, std::string path, int nb_chap, int *tab);

        GroupPtr createGroup();
        GroupPtr createGroup(std::string name);

        void printMedia(std::string name);
        void printGroup(std::string name);

        void openMedia(std::string name);
};

#endif
