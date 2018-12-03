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
    std::cout << "Hello brave new world" << std::endl;
    Media * media = new Media("audio", "audio1.mp3");
    media->print(cout);
    Photo * photo = new Photo("photo", "photo1.jpeg", 12, 13);
    photo->print(cout);
    photo->open();
    Video * video = new Video("video", "video1.mov", 2.4);
    video->open();
    return 0;
}
