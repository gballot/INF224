#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <string>
#include <map>
#include <sstream>
#include "media.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"
#include "tcpserver.h"

class DataBase {
    private :
        std::map<std::string, MediaPtr> mediaMap;
        std::map<std::string, GroupPtr> groupMap;

        void createRequest(std::stringstream& stream, std::string& response);
        void getRequest(std::stringstream& stream, std::string& response);
        void openRequest(std::stringstream& stream, std::string& response);
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

        void printMedia(std::string name, std::ostream& stream);
        void printGroup(std::string name, std::ostream& stream);

        void openMedia(std::string name);

        void deleteMedia(std::string name);
        void deleteGroup(std::string name);


        bool processRequest(cppu::TCPConnection& cnx, const std::string& request, std::string& response);
};

#endif
