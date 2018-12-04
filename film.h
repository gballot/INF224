#ifndef FILM_H
#define FILM_H

#include "video.h"

class Film : public Video {
    private :
        int nb_chapters = 0;
        int * chapters;
        int sum_chapter_length(int nb_chapters, int *tab);
        void create_tab(int length, int *tab);
    public :
        Film() {};
        Film(std::string name, std::string path, int length) :
            Video(name, path, length) {}
        Film(std::string name, std::string path, int length, int nb_chapters, int * tab) :
            Video(name, path, length), nb_chapters(nb_chapters) {
                create_tab(nb_chapters, tab);
            }
        Film(std::string name, std::string path, int nb_chap, int * tab) :
            Video(name, path, sum_chapter_length(nb_chap, tab)), nb_chapters(nb_chap) {
                create_tab(nb_chap, tab);
            }

        ~Film() { delete chapters; }

        void setChapters(int nb_chap, int *tab);
        int getChapters(int *tab, int size) const;
        int getNbChapter() const {
            return nb_chapters;
        }
        void print(std::ostream& stream) const override ;
};

#endif
