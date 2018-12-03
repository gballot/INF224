//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "media.h"
#include "photo.h"
#include "video.h"

using namespace std;

int main(/*int argc, const char* argv[]*/)
{
    Media * tab[20];
    for(int i = 0 ; i < 10 ; i++) {
        Photo * photo = new Photo("photo", "photo.jpeg", 12, 13);
        Video * video = new Video("video", "video.mov", 2.4);
        tab[2*i] = photo;
        tab[2*i + 1] = video;
    }
    for(int i = 0; i < 20 ; i++) {
        tab[i]->print(cout);
        cout << '\n';
    }
    return 0;
}
