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
    FilmPtr film(new Film("film", "film.mov", 3, chap)); 
    cout << "\n\n************************************\n"
        << "Now we create a Film and we will make 2 deep copies :\n";
    film->print(cout);

    /* a second film (deep copy) */
    Film film2(*film);

    /* a third film (deep copy) */
    FilmPtr film3(new Film());
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


    /* creates a group */
    Group * group = new Group("groupe");
    cout << "\n\n************************************\n"
        << "now we create a group :\n"
        << "name of the group : "
        << group->getName()
        << endl;

    /* fills the group */
    PhotoPtr photo1(new Photo("photo1", "images/photo1.jpeg", 27.6, 378.7));
    VideoPtr video1(new Video("video1", "videos/video1.mp4", 78));
    group->push_back(film);
    group->push_back(photo1);
    group->push_back(film3);
    group->push_back(video1);

    /* prints all the group */
    cout << "\nlet's print the two films the video "
        << "and the photo added in the group : \n";
    group->printAll(cout);


    /* creates a second group list */
    Group * group2 = new Group("groupe2");
    cout << "\n\n************************************\n"
        << "now we create a second group :\n"
        << "name of the group : "
        << group2->getName()
        << endl;

    /* fills the group */
    group2->push_back(film);
    group2->push_back(video1);
    group2->push_back(photo1);
    group2->push_back(film3);

    /* prints all the group */
    cout << "\nlet's print the two films the video "
        << "and the photo added in the group : \n";
    group2->printAll(cout);

    /* remove film from the two groups and check that it is automatically deleted */
    cout << "\n\n************************************\n"
        << "remove film from the two groups and check that it is automatically deleted\n"
        << "first delete `film` from main\n";
    film.reset();
    cout << "...\ndone\n";
    cout << "now delete film from group\n";
    group->pop_front();
    cout << "...\ndone\n";
    cout << "now delete film from group2\n";
    group2->pop_front();
    cout << "...\ndone\n";
    cout << "the film should have been automatically destroyed\n"
        << "check if 'delete media : film' has been printed\n"
        << "\n**************************************\n";

    /* delets the group */
    delete group;
    delete group2;

    return 0;
}
