#ifdef SERVER

/****************************************************/
/* version du code après l'étape 11 -client-server- */
/****************************************************/

#include <memory>
#include <string>
#include <iostream>
#include <sstream>
#include "media.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"
#include "dataBase.h"
#include "tcpserver.h"

using namespace std;
using namespace cppu;

const int PORT = 3331;


int main(/*int argc, const char* argv[]*/)
{
  // cree le TCPServer
  shared_ptr<TCPServer> server(new TCPServer());
  
  // cree l'objet qui gère les données
  shared_ptr<DataBase> base(new DataBase());

  // le serveur appelera cette méthode chaque fois qu'il y a une requête
  server->setCallback(*base, &DataBase::processRequest);
  
  // lance la boucle infinie du serveur
  cout << "Starting Server on port " << PORT << endl;
  int status = server->run(PORT);
  
  // en cas d'erreur
  if (status < 0) {
    cerr << "Could not start Server on port " << PORT << endl;
    return 1;
  }
  
  return 0;

}


#else

/****************************************************/
/* version du code avant l'étape 11 -client-server- */
/****************************************************/

#include <iostream>
#include "media.h"
#include "photo.h"
#include "video.h"
#include "film.h"
#include "group.h"
#include "dataBase.h"


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
        << "check if 'delete media : film' has been printed\n";

    /* delets the group2 */
    delete group;
    delete group2;

    /* creates a data base */
    cout << "\n\n**********************************\n"
        << "create a data base and add a photo, film and video\n";
    DataBase *db = new DataBase();
    PhotoPtr photo_db = db->createPhoto("photo-db", "photo-db.jpeg", 3.2, 8.9);
    VideoPtr video_db = db->createVideo("video-db", "video-db.mov", 67);
    FilmPtr film_db = db->createFilm("film-db", "film-db.mov", 3, chap);
    GroupPtr group_db = db->createGroup("group-db");
    group_db->push_back(photo_db);
    group_db->push_back(film_db);
    group_db->push_back(video_db);

    /* prints the content of the data base */
    cout << "now we print the film, video and photo added to the data base :\n\n";
    db->printMedia("photo-db");
    cout << "\n";
    db->printMedia("video-db");
    cout << "\n";
    db->printMedia("film-db");
    cout << "\n";
    cout << "let's see what append if we try to print film-unknown :\n";
    db->printMedia("film-unknown");
    cout << "nothing hoppfully...\n";

    /* print the group named group_db */
    cout << "\n\n*********************************\n"
        << "now we ask to print the group named group-unknown :\n";
    db->printGroup("group-unknown");
    cout << "/!\\ nothing must happen becouse group-unknown does'nt exist /!\\\n"
        << "we ask to print group-db, this one exists !\n";
    db->printGroup("group-db");

    /* remove a media from the data base */
    cout << "\n\n*************************\n"
        << "remove a media from the data base we will see if\n"
        << "it is removed from the group-db as expected...\n";
    db->deleteMedia("photo-db");
    cout << "photo-db deleted\n"
        << "print group-db again :\n";
    db->printGroup("group-db");

    return 0;
}

#endif
