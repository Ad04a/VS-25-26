/*
Направете структура за книга, в която има полета за име, автор, жанр и цена.
Направете структура за библиотека, в която има полета за рафтове и поле за масив
за остатъчни книги с дължина 7. Библиотеката трябва да има 4 рафта, като на всеки
рафт има място за 7 книги (вие изберете как ще организирате самата структура, 
като и това ще се оценява. За целта може да си служите и с допълнителни,
измислени от вас, структури)

Направете функция, която добавя книга в библиотеката 
int donate_book(struct Library *lib, struct Book book). 
Трябва да се провери дали има място за поставяне, като всеки рафт трябва да
съдържа книги само от един автор. Ако книгите на някой рафт станат повече от
свободните места, започнете нов ред с този автор. Ако няма достатъчно място да
се създаде нова ред то книгата отива в масива с остатъчни книги. Функцията трябва
да връща 1, ако книгата е добавена успешно и 0, ако не е добавена нито на рафт,
нито в остатъчните книги. 

Направете функция, която да връща общата цена на остатъчните книги
*/

#include <string.h>
#include <stdio.h>

#define SHELF_LENGHT 7
#define NUM_SHELVES 4
#define OTHER_LEN 7

typedef struct {
    char name[50];
    char author[50];
    char genre[20];
    float price;
} Book;

typedef struct
{
    Book books[SHELF_LENGHT];
    int count;
} Shelf;

typedef struct 
{
    Shelf shelves[NUM_SHELVES];
    Book other[OTHER_LEN];
    int other_count;
} Library;

float SumOthers(const Library* lib)
{
    float sum = 0;
    for(int i=0 ;i <OTHER_LEN; i++)
    {
        sum += (lib->other+i)->price;
    }
    return sum;
}

Book nullbook = {"", "", "", -1};

void init_shelf(Shelf* shelf)
{
    for(int i = 0;i <SHELF_LENGHT; i++)
    {
        shelf->books[i] = nullbook;
    }
    shelf->count = 0;
}

void init_lib(Library *lib)
{
    for(int i =0; i<NUM_SHELVES; i++)
    {
        init_shelf(lib->shelves+i);
    }
    for(int i=0;i<OTHER_LEN; i++)
    {
        lib->other[i] = nullbook;
    }
    lib->other_count = 0;
}


int donate_book(Library *lib, Book book)
{
    int first_free_index = -1;
    int book_added = 0;
    for(int i=0; i<NUM_SHELVES; i++)
    {
        Shelf* shelf = lib->shelves+i;

        if(first_free_index == -1 && strcmp(shelf->books[0].author, nullbook.author)==0) first_free_index = i;

        if(strcmp(book.author, shelf->books[0].author)) continue;

        if(shelf->count >= SHELF_LENGHT) continue;

        shelf->books[shelf->count] = book;
        shelf->count += 1;
        book_added = 1;
    }
    if(book_added == 0 && first_free_index != -1)
    {
        Shelf* shelf = lib->shelves+first_free_index;
        shelf->books[shelf->count] = book;
        shelf->count += 1;
        book_added = 1;
    }

    if(book_added == 0 && lib->other_count < OTHER_LEN)
    {
        lib->other[lib->other_count] = book;
        lib->other_count += 1;
        book_added = 1;
    }

    return book_added;
}

void print_shelf(const Shelf* shelf)
{
    for(int i = 0;i <shelf->count; i++)
    {
        Book b = shelf->books[i];
        printf("[%c, %c, %c, %f] ", b.name[0], b.author[0], b.genre[0], b.price);
    }
}

void print_lib(const Library *lib)
{
    for(int i =0; i<NUM_SHELVES; i++)
    {
        print_shelf(lib->shelves+i);
        printf("\n");
    }
    for(int i=0;i<lib->other_count; i++)
    {
        Book b = lib->other[i];
        printf("[%c, %c, %c, %f] ", b.name[0], b.author[0], b.genre[0], b.price);
    }
}

int main()
{
    Library lib;
    init_lib(&lib);
    print_lib(&lib);

    Book b1 = {"neshto", "nqkoi", "n", 20};
    Book b2 = {"keshto", "kqkoi", "n", 3.2};
    Book b3 = {"teshto", "vqkoi", "n", 12};

    donate_book(&lib, b1);
    donate_book(&lib, b2);
    donate_book(&lib, b3);
    donate_book(&lib, b1);

    print_lib(&lib);
    for(int i=0 ; i<15; i++)
    donate_book(&lib, b1);
    donate_book(&lib, b2);
    donate_book(&lib, b3);
    donate_book(&lib, b1);
    for(int i=0 ; i<6; i++)donate_book(&lib, b3);
    print_lib(&lib);

    return 0;
}