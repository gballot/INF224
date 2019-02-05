#ifndef FILM_H
#define FILM_H

#include "video.h"

class Film : public Video {
    private :
        int nb_chapters = 0;
        int *chapters;
        int sum_chapter_length(int nb_chapters, int *tab) const;
        void create_tab(int length, int *tab);
        void deepCopy(const Film&from);
    public :
        Film() {}
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
        Film(const Film& from) : Video(from) {
            this->deepCopy(from);
            }

        Film& operator=(const Film& from);

        ~Film() { delete [] this->chapters; }

        // sets the length
        void setLength(int length) override { if(length) return; }
        //set the chapters table
        void setChapters(int nb_chap, int *tab);
        // gets the chapters table
        int getChapters(int *tab, int size) const;
        // get the number of chapters
        int getNbChapter() const {
            return nb_chapters;
        }
        // print the video in a stream
        void print(std::ostream& stream) const override ;
};

typedef std::shared_ptr<Film> FilmPtr;

#endif
