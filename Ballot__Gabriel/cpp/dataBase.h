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

/* This class is the overall data base.
 * it is supposed to be unique. */
class DataBase {
    private :
        std::map<std::string, MediaPtr> mediaMap;
        std::map<std::string, GroupPtr> groupMap;

        // private class to manage create requests from the client
        void createRequest(std::stringstream& stream, std::string& response);
        // private class to manage get  requests from the client
        void getRequest(std::stringstream& stream, std::string& response);
        // private class to manage open requests from the client
        void openRequest(std::stringstream& stream, std::string& response);
        // private class to manage delete requests from the client
        void deleteRequest(std::stringstream& stream, std::string& response);
        // private class to manage add requests from the client
        void addRequest(std::stringstream& stream, std::string& response);
    public :
        DataBase() {}

        // create photo
        PhotoPtr createPhoto();
        PhotoPtr createPhoto(std::string name, std::string path, float latitude, float longitude);

        //create video
        VideoPtr createVideo();
        VideoPtr createVideo(std::string name, std::string path, int length);

        //create film
        FilmPtr createFilm();
        FilmPtr createFilm(std::string name, std::string path, int length);
        FilmPtr createFilm(std::string name, std::string path, int length, int nb_chapters, int *tab);
        FilmPtr createFilm(std::string name, std::string path, int nb_chap, int *tab);

        //create group
        GroupPtr createGroup();
        GroupPtr createGroup(std::string name);

        // add a media in a group
        void addMedia(std::string group_name, std::string media_name);

        //print a media
        void printMedia(std::string name, std::ostream& stream);
        //print a group
        void printGroup(std::string name, std::ostream& stream);

        //print all medias
        void printAllMedias(std::ostream& stream);
        //print all groups
        void printAllGroups(std::ostream& stream);

        //play a media in the server
        void openMedia(std::string name);

        //delete a media
        void deleteMedia(std::string name);
        //delete a group
        void deleteGroup(std::string name);


        // the processRequest function that is called for every incoming requests
        bool processRequest(cppu::TCPConnection& cnx, const std::string& request, std::string& response);
};

#endif
