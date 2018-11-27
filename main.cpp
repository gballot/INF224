//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "media.h"
using namespace std;

int main(int argc, const char* argv[])
{
    std::cout << "Hello brave new world" << std::endl;
    Media * media = new Media("audio", "audio1.mp3");
    media->print(cout);
    return 0;
}
