#include <string>
#include "film.h"

using namespace std;

void Film::create_tab(int length, int *tab) {
    chapters = new int[length];
    for(int i = 0 ; i < length ; i++) {
        chapters[i] = tab[i];
    }
    nb_chapters = length;
}

int Film::sum_chapter_length(int nb_chapters, int *tab) {
    int count = 0;
    for(int i = 0 ; i < nb_chapters ; i++) {
        count += tab[i];
    }
    return count;
}

void Film::setChapters(int nb_chap, int *tab) {
    delete chapters;
    create_tab(nb_chap, tab);
}

int Film::getChapters(int *tab, int size) const {
    if (nb_chapters > size) 
        return -1;
    for(int i = 0 ; i < nb_chapters ; i++)
        tab[i] = chapters[i];
    return nb_chapters;
}

void Film::print(ostream& stream) const {
    Video::print(stream);
    stream << "nb_chapters : " << this->nb_chapters
        << endl;
    for(int i = 0 ; i < nb_chapters ; i++) {
        stream << "chapter " << i
            << "has length : " << this->chapters[i]
            << endl;
    }
}

Film::Film(const Film& from) : Video(from) {
    nb_chapters = from.getNbChapter();
    int tab[nb_chapters];
    from.getChapters(tab, nb_chapters);
    if(nb_chapters)
        create_tab(nb_chapters, tab);
    else
        chapters = nullptr;
}

Film& Film::operator=(const Film& from) {
    Video::operator=(from);
    nb_chapters = from.getNbChapter();
    int tab[nb_chapters];
    from.getChapters(tab, nb_chapters);
    delete chapters;
    if(nb_chapters)
        create_tab(nb_chapters, tab);
    else
        chapters = nullptr;
    return *this;
}

void Film::deepCopy(const Film&from) {
    nb_chapters = from.getNbChapter();
    int tab[nb_chapters];
    from.getChapters(tab, nb_chapters);
    if(nb_chapters)
        create_tab(nb_chapters, tab);
    else
        chapters = nullptr;
}
