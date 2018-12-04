//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "media.h"
#include "photo.h"
#include "video.h"
#include "film.h"

using namespace std;

int main(/*int argc, const char* argv[]*/)
{
    Media * tab[20];
    for(int i = 0 ; i < 10 ; i++) {
        Photo * photo = new Photo("photo", "photo.jpeg", 12.3, 1.3);
        Video * video = new Video("video", "video.mov", 24);
        tab[2*i] = photo;
        tab[2*i + 1] = video;
    }
    for(int i = 0; i < 20 ; i++) {
        tab[i]->print(cout);
        cout << '\n';
    }
    for(int i = 0; i < 20 ; i++) {
        delete tab[i];
    }

    int chap[3] = {6, 8, 14};
    Film *film = new Film("film", "film.mov", 3, chap); 
    film->print(cout);
    int chap2[4] = {1, 1, 2, 1};
    film->setChapters(4, chap2);
    cout << endl;
    film->print(cout);
    delete film;

    return 0;
}
