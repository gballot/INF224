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

void DataBase::addMedia(string group_name, string media_name) {
    map<string, GroupPtr>::iterator it = groupMap.find(group_name);
    if(it != groupMap.end()) {
        GroupPtr group_ptr = get<1>(*it);
        map<string, MediaPtr>::iterator it = mediaMap.find(media_name);
        if(it != mediaMap.end()) {
            MediaPtr media_ptr = get<1>(*it);
            group_ptr->push_back(media_ptr);
        }
    }
}

void DataBase::printMedia(string name, ostream& stream) {
    cout << "print occure" << endl;
    map<string, MediaPtr>::iterator it = mediaMap.find(name);
    if(it != mediaMap.end()) {
        cout << name << " found" << endl;
        get<1>(*it)->print(stream);
    } else 
        cout << name << " not found" << endl;
}

void DataBase::printGroup(string name, ostream& stream) {
    map<string, GroupPtr>::iterator it = groupMap.find(name);
    if(it != groupMap.end()) {
        get<1>(*it)->printAll(stream);
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
        cout << "create request" << endl;
        TCPLock lock(cnx);
        createRequest(requestStream, response);
    } else if(!requestType.compare("get")) {
        getRequest(requestStream, response);
    } else if(!requestType.compare("open")) {
        cout << "open request" << endl;
        openRequest(requestStream, response);
    } else if(!requestType.compare("delete")) {
        cout << "delete request" << endl;
        deleteRequest(requestStream, response);
    } else if(!requestType.compare("add")) {
        cout << "add request" << endl;
        addRequest(requestStream, response);
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
        cout << "group created " << name << endl;
    } else {
        string path;
        stream >> path;
        if(!group_or_media.compare("photo")) {
            string latitude, longitude;
            stream >> latitude;
            stream >> longitude;
            if(name.compare("") && path.compare("") && latitude.compare("") && longitude.compare(""))
                createPhoto(name, path, stof(latitude), stof(longitude));
            else
                createPhoto();
            cout << "photo created " << name << endl;
        } else if(!group_or_media.compare("video")) {
            string length;
            stream >> length;
            if(name.compare("") && path.compare("") && length.compare(""))
                createVideo(name, path, stoi(length));
            else
                createVideo();
            cout << "video created " << name << endl;
        } else if(!group_or_media.compare("film")) {
            string length;
            stream >> length;
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
                    cout << "(h)" << endl;
                    if(length.compare(""))
                        createFilm(name, path, stoi(length), nb_chap, tab);
                    else if(!length.compare("null"))
                        createFilm(name, path, nb_chap, tab);
                    else response = "fail";
                    return;
                } else {
                    cout << "(name path length)" << endl;
                    createFilm(name, path, stoi(length));
                }
            } else {
                cout << "()" << endl;
                createFilm();
            }
            cout << "film created " << name << endl;
        }
    }
    response = "done";
}

void DataBase::getRequest(stringstream& stream, string& response) {
    string group_or_media, name;
    stream >> group_or_media;
    stream >> name;
    stringstream responseStream;
    if(!group_or_media.compare("group")) {
        cout << "get group received " << name << endl;
        printGroup(name, responseStream);
        cout << responseStream.str();
    }
    else {
        cout << "get media receeived " << name << endl;
        printMedia(name, responseStream);
        cout << responseStream.str();
    }
    response = responseStream.str();
}


void DataBase::openRequest(stringstream& stream, string& response) {
    string name;
    stream >> name;
    if(name.compare("")) {
        openMedia(name);
    }
    response = "done";
}

void DataBase::deleteRequest(stringstream& stream, string& response) {
    string group_or_media, name;
    stream >> group_or_media;
    stream >> name;
    if(group_or_media.compare("group")) {
        if(name.compare("")) {
            deleteMedia(name);
        }
    } else {
        deleteGroup(name);
    }
    response = "done";
}

void DataBase::addRequest(stringstream& stream, string& response) {
    string group_name, media_name;
    stream >> group_name;
    stream >> media_name;
    if(group_name.compare("") && media_name.compare("")) {
        addMedia(group_name, media_name);
    }
    response = "done";
}

