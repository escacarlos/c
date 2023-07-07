#include<stdio.h>

struct Books{
    int   id;
    char  author[50];
    char  title[50];
};

int main() {
    //declare `book1` and `book2` of type `Books`
    struct Books book1;
    struct Books book2;

    //the specifications for the `book1`
    book1.id = 1;
    strcpy(book1.author,"Zara Ali");
    strcpy(book1.title,"Tutorials for C Programming");

    //the specifications for the `book2`
    book2.id = 2;
    strcpy(book2.author,"Zaid Ali");
    strcpy(book2.title,"Tutorials for Java Programming");

    //display information for `book1` and `book2`
    printf( "The id of book1: %d\n", book1.id);
    printf( "The author of the book1: %s\n", book1.author);
    printf( "The title of the book1: %s\n", book1.title);

    printf( "The id of book2: %d\n", book2.id);
    printf( "The author of the book2: %s\n", book2.author);
    printf( "The title of the book2: %s\n", book2.title);

    return 0;
}