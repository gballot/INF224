#include "dataBase.h"

using namespace std;

PhotoPtr DataBase::createPhoto() {
    PhotoPtr photo(new Photo());
    mediaMap.insert(pair<string, MediaPtr>("", photo));
    return photo;
}

PhotoPtr DataBase::createPhoto(string name, string path, float latitude, float longitude) {
    PhotoPtr photo(new Photo(name, path, latitude, longitude));
    mediaMap.insert(pair<string, MediaPtr>(name, photo));
    return photo;
}

VideoPtr DataBase::createVideo() {
    VideoPtr video(new Video());
    mediaMap.insert(pair<string, MediaPtr>("", video));
    return video;
}

VideoPtr DataBase::createVideo(string name, string path, int length) {
    VideoPtr video(new Video(name, path, length));
    mediaMap.insert(pair<string, MediaPtr>(name, video));
    return video;
}

FilmPtr DataBase::createFilm() {
    FilmPtr film(new Film());
    mediaMap.insert(pair<string, MediaPtr>("", film));
    return film;
}

FilmPtr DataBase::createFilm(string name, string path, int length) {
    FilmPtr film(new Film(name, path, length));
    mediaMap.insert(pair<string, MediaPtr>(name, film));
    return film;
}

FilmPtr DataBase::createFilm(string name, string path, int length, int nb_chapters, int *tab) {
    FilmPtr film(new Film(name, path, length, nb_chapters, tab));
    mediaMap.insert(pair<string, MediaPtr>(name, film));
    return film;
}

FilmPtr DataBase::createFilm(string name, string path, int nb_chap, int *tab) {
    FilmPtr film(new Film(name, path, nb_chap, tab));
    mediaMap.insert(pair<string, MediaPtr>(name, film));
    return film;
}

GroupPtr DataBase::createGroup() {
    GroupPtr group(new Group());
    groupMap.insert(pair<string, GroupPtr>("", group));
    return group;
}

GroupPtr DataBase::createGroup(string name) {
    GroupPtr group(new Group(name));
    groupMap.insert(pair<string, GroupPtr>(name, group));
    return group;
}

void DataBase::printMedia(string name) {
    map<string, MediaPtr>::iterator it = mediaMap.find(name);
    if(it != mediaMap.end()) {
        get<1>(*it)->print(cout);
    }
}

void DataBase::printGroup(string name) {
    map<string, GroupPtr>::iterator it = groupMap.find(name);
    if(it != groupMap.end()) {
        get<1>(*it)->printAll(cout);
    }
}

void DataBase::openMedia(string name) {
    map<string, MediaPtr>::iterator it = mediaMap.find(name);
    if(it != mediaMap.end()) {
        get<1>(*it)->open();
    }
}
