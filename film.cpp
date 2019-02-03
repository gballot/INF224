#include <string>
#include "film.h"

using namespace std;

void Film::create_tab(int length, int *tab) {
    chapters = new int[length];
    for(int i = 0 ; i < length ; i++) {
        chapters[i] = tab[i];
    }
    nb_chapters = length;
    setLength(sum_chapter_length(nb_chapters, tab));
}

int Film::sum_chapter_length(int nb_chapters, int *tab) const {
    int count = 0;
    for(int i = 0 ; i < nb_chapters ; i++) {
        count += tab[i];
    }
    return count;
}

void Film::setChapters(int nb_chap, int *tab) {
    delete [] chapters;
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
    stream << this->nb_chapters;
    for(int i = 0 ; i < nb_chapters ; i++) {
        stream << " "
               << this->chapters[i];
    }
    stream << endl;
}

Film& Film::operator=(const Film& from) {
    Video::operator=(from);
    if(chapters)
        delete [] chapters;
    this->deepCopy(from); 
    return *this;
}

void Film::deepCopy(const Film& from) {
    this->nb_chapters = from.getNbChapter();
    int tab[nb_chapters];
    from.getChapters(tab, nb_chapters);
    if(nb_chapters)
        this->create_tab(nb_chapters, tab);
    else
        this->chapters = nullptr;
}
