/*
Направете структура за филм, в която има полета за име, година на издаване и жанр.
Направете структура за филмотека, в която има полета за рафтове и поле за масив за
остатъчни филми с дължина 10. Филмотеката трябва да има 5 рафта, като на всеки рафт
има място за 5 филма (вие изберете как ще организирате самата структура, като и 
това ще се оценява. За целта може да си служите и с допълнителни, измислени от вас, 
структури)

Направете функция, която добавя филм на рафта 
int add_film(struct Film_Library *fl, struct Film film). 
Трябва да се провери дали има място за поставяне, като всеки рафт трябва да 
съдържа филми от една и съща категория. Ако филмите на някой рафт станат повече 
от свободните места, започнете нов ред с тази категория. Ако няма достатъчно място 
да се създаде нова категория то филма отива в масива с остатъчни филми. Функцията 
трябва да връща 1, ако филма е добавен успешно и 0, ако не е добавен нито на рафт, 
нито в остатъчните филми.

Направете функция за принтиране на цялата филмотека.
*/
#include <stdio.h>
#include <string.h>

#define SHELF_LEN 5
#define NUM_SHELVES 5
#define OTHER_LEN 10

typedef struct
{
    char name[20];
    int year;
    char genre[20];
} Movie;

Movie nullmov = {" ", -1, " "};

typedef struct 
{
    Movie movies[SHELF_LEN];
} Shelf;

typedef struct 
{
    Shelf shelves[NUM_SHELVES];
    Movie other[OTHER_LEN];
} MovLib;

void print_mov(const Movie* mov)
{
    printf("[%c, %d, %c]", mov->name[0], mov->year, mov->genre[0]);
}

void print_shelf(const Shelf* shelf)
{
    for(int i=0; i<SHELF_LEN; i++)
    {
        print_mov(shelf->movies+i);
        printf(" ");
    }
}

void print_lib(const MovLib* lib)
{
    for(int i=0; i<NUM_SHELVES; i++)
    {
        print_shelf(lib->shelves+i);
        printf("\n");
    }

    for(int i=0 ;i<OTHER_LEN; i++)
    {
        print_mov(lib->other+i);
        printf(" ");
    }
}


void init_shelf(Shelf* shelf)
{
    for(int i=0; i<SHELF_LEN; i++)
    {
        *(shelf->movies+i) = nullmov;
    }
}

void init_lib(MovLib* lib)
{
    for(int i=0; i<NUM_SHELVES; i++)
    {
        init_shelf(lib->shelves+i);
    }

    for(int i=0 ;i<OTHER_LEN; i++)
    {
        *(lib->other+i) = nullmov;
    }
}

int add_film(MovLib *ml, Movie mov)
{
    int free_shelf_index = -1;
    int movie_added = 0;
    for(int i=0; i<NUM_SHELVES; i++)
    {
        if(free_shelf_index == -1 && strcmp(ml->shelves[i].movies[0].genre, nullmov.genre)==0) free_shelf_index = i;
        if(strcmp(mov.genre, ml->shelves[i].movies[0].genre)) continue;

        for(int j=0 ; j<SHELF_LEN; j++)
        {
            if(ml->shelves[i].movies[j].year != -1) continue; 

            ml->shelves[i].movies[j] = mov;
            movie_added = 1;
            break;
        }
        if(movie_added) break;
    }

    if(movie_added==0 && free_shelf_index != -1)
    {
        ml->shelves[free_shelf_index].movies[0] = mov;
        movie_added = 1;
    }

    if(movie_added) return movie_added;
    for(int i =0 ; i<OTHER_LEN; i++)
    {
        if(ml->other[i].year == -1)
        {
            ml->other[i] = mov;
            movie_added = 1;
            break;
        }
    }

    return movie_added;
}

int main()
{
    MovLib movlib;
    init_lib(&movlib);

    Movie m1 = {"nqkuv film", 1990, "comedy"};
    Movie m2 = {"drug film", 2005, "horror"};
    Movie m3 = {"c film", 1990, "action"};

    add_film(&movlib, m1);
    add_film(&movlib, m2);
    add_film(&movlib, m3);

    add_film(&movlib, m2);
    add_film(&movlib, m3);

    add_film(&movlib, m1);
    add_film(&movlib, m1);
    add_film(&movlib, m1);
    add_film(&movlib, m1);
    add_film(&movlib, m1);
    add_film(&movlib, m1);
    add_film(&movlib, m1);

    print_lib(&movlib);
}