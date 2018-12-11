//
// main.cpp
// Created on 21/10/2018
//

#include <iostream>
#include "media.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"

using namespace std;

int main(/*int argc, const char* argv[]*/)
{
    /* a table of Medias */
    Media * tab[20];
    for(int i = 0 ; i < 10 ; i++) {
        Photo * photo = new Photo("photo", "photo.jpeg", 12.3, 1.3);
        Video * video = new Video("video", "video.mov", 24);
        tab[2*i] = photo;
        tab[2*i + 1] = video;
    }
     /* prints the Medias in the table */
    cout << "\n\n************************************\n"
        << "This is the content of the table :\n\n";
    for(int i = 0; i < 20 ; i++) {
        tab[i]->print(cout);
        cout << '\n';
    }

    /* delete the Medias in the table */
    for(int i = 0; i < 20 ; i++) {
        delete tab[i];
    }

    /* a first film */
    int chap[3] = {6, 8, 14};
    Film *film = new Film("film", "film.mov", 3, chap); 
    cout << "\n\n************************************\n"
        << "Now we create a Film and we will make 2 deep copies :\n";
    film->print(cout);

    /* a second film (deep copy) */
    Film film2(*film);

    /* a third film (deep copy) */
    Film *film3 = new Film();
    *film3 = *film;

    /* renaming film 2 and 3 */
    film3->setName("film3.mov");
    film2.setName("film2");
    film3->setPath("film3.mov");
    film2.setPath("film2.mov");

    /* changing chapters of film */
    int chap2[4] = {1, 1, 2, 1};
    film->setChapters(4, chap2);

    /* print the three films */
    cout << "\nNow these are the three films ordered :\n\n";
    film->print(cout);
    cout << endl;
    film2.print(cout);
    cout << endl;
    film3->print(cout);


    /* changes chapters of film2 and prints it */
    int chap3[5] = {2, 6, 7, 6, 19};
    film2.setChapters(5, chap3);
    cout << "\nNow we changed the chapters of film2 :\n\n";
    film2.print(cout);


    /* creates a list */
    Group * group = new Group("groupe");
    cout << "\n\n************************************\n"
        << "Now we create a Group :\n"
        << "name of the group : "
        << group->getName()
        << endl;

    /* fills the group */
    group->push_back(film);
    group->push_back(film3);

    /* prints all the group */
    cout << "\nlet's print the two films added in the group : \n";
    group->printAll(cout);

    /* deletes film and film3 */
    delete film;
    delete film3;

    /* delets the group */
    delete group;

    return 0;
}
