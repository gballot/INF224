#include "dataBase.h"

using namespace std;
using namespace cppu;

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

void DataBase::deleteMedia(string name) {
    map<string, MediaPtr>::iterator it = mediaMap.find(name);
    if(it != mediaMap.end()) {
        for(map<string, GroupPtr>::iterator groupIt = groupMap.begin() ;
                groupIt != groupMap.end() ; groupIt++) {
            groupIt->second->remove(it->second);
        }
        mediaMap.erase(it);
    }
}

void DataBase::deleteGroup(string name) {
    map<string, GroupPtr>::iterator it = groupMap.find(name);
    if(it != groupMap.end()) {
        groupMap.erase(it);
    }
}

bool DataBase::processRequest(TCPConnection& cnx, const string& request, string& response) {
    stringstream requestStream;
    requestStream.str(request);
    string requestType;
    requestStream >> requestType;
    if(!requestType.compare("create")) {
        createRequest(requestStream, response);
    } else {
        cout << requestType;

        cout << request;
        cout<< endl;
        response = "done";
        TCPLock lock(cnx);
    }

    return true;//false;
}

void DataBase::createRequest(stringstream& stream, string& response) {
    string group_or_media;
    stream >> group_or_media;
    string name;
    stream >> name;
    if(!group_or_media.compare("group")) {
        if(name.compare(""))
            createGroup(name);
        else
            createGroup();
    } else {
        string path;
        stream >> path;
        if(!group_or_media.compare("photo")) {
            string latitude, longitude;
            stream >> latitude;
            stream >> longitude;
            if(name.compare("") && path.compare("") && latitude.compare("") && longitude.compare(""))
                createPhoto(name, path, stoi(latitude), stoi(longitude));
            else
                createPhoto();
        } else if(!group_or_media.compare("video")) {
            string length;
            stream >> length;
            if(name.compare("") && path.compare("") && length.compare(""))
                createVideo(name, path, stoi(length));
            else
                createVideo();
        } else if(!group_or_media.compare("film")) {
            string length;
            if(name.compare("") && path.compare("") && length.compare("")) {
                string nb_chapters;
                stream >> nb_chapters;
                if(nb_chapters.compare("")) {
                    string last_int;
                    stream >> last_int;
                    int nb_chap = stoi(nb_chapters);
                    int tab[nb_chap];
                    for(int i = 0 ; i < nb_chap ; i++) {
                        tab[i] = stoi(last_int);
                        stream >> last_int;
                    }
                    if(length.compare(""))
                        createFilm(name, path, stoi(length), nb_chap, tab);
                    else if(!length.compare("null"))
                        createFilm(name, path, nb_chap, tab);
                    else response = "fail";
                    return;
                } else
                    createFilm(name, path, stoi(length));
            } else
                createFilm();
        }
    }
    response = "done";
}
