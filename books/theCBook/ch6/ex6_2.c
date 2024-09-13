#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
    Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each group of variable names that are identical in the first 6 characters, but
    different somewhere thereafter. Don't count words within strings and comments. Make 6 a parameter that can be set from the command line.
*/

struct tnode // the tree node:
{
    char *word;          // points to the text
    struct tnode *left;  // left child
    struct tnode *right; // right child
};

#define MAXWORD 100
#define BUFSIZE 100
#define DEFAULT_NUM_CHARS 6 // default number of chars to compare in a string
#define KEYWORD_LEN 44      // C17 standard has 44 keywords

struct tnode *addtree(struct tnode *, char *);
struct tnode *talloc(void);
void treeprint(struct tnode *, struct tnode *root);
void ungetch(int);
int getword(char *, int);
int binsearch(char *);
int getword(char *word, int lim);
int getch(void);
char *mystrdup(char *); // strdup conflicts with function name from strings.h so it was renamed to mystrdup

enum statusTypes
{
    NORMAL,
    STRING,
    SINGLE_LINE_COMMENT,
    MULTI_LINE_COMMENT,
    PREPROCESSOR
};
enum boolean
{
    FALSE,
    TRUE
};

char *keywords[KEYWORD_LEN] = { // Current 44 keywords as of C17 standard (ISO/IEC 9899:2017). These must be in alphabetical order
    "_Alignas", "_Alignof", "_Atomic", "_Bool", "_Complex", "_Generic", "_Imaginary", "_Noreturn", "_Static_assert", "_Thread_local", "auto", "break", "case", "char", "const",
    "continue", "default", "do", "double", "else", "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register", "restrict", "return", "short",
    "signed", "sizeof", "static", "struct", "switch", "typedef", "union", "unsigned", "void", "volatile", "while"};
char prevChar = '\0';             // keep track of last char
int type;                         // keep track of the current status
char buf[BUFSIZE];                // buffer for ungetch
int bufp = 0;                     // next free position in buf
int numChars = DEFAULT_NUM_CHARS; // number of characters to compare in a string to see if it is the same

// word frequency count
int main(int argc, char *argv[])
{
    if (argc <= 2) // if 1 arg (no args given), value will equal 0 after loop. If 2 args, process 2nd arg and value will equal 0 after loop
    {
        while (--argc > 0)
            if (**++argv == '-' && isdigit(*++*argv))
                numChars = atoi(*argv);
            else
                argc = -1; // prints usage
    }
    if (argc != 0)
    {
        printf("usage: getVars [-#]");
        return 1;
    }
    if (numChars == 0)
    {
        printf("error: zero is not a valid number\n");
        return 1;
    }

    struct tnode *root;
    char word[MAXWORD];
    char toAdd[MAXWORD];
    root = NULL;

    toAdd[0] = '\0'; // set to null string due to logic of while loop. Otherwise, it will print garbage
    while (getword(word, MAXWORD) != EOF)
    {
        if (word[0] == '"')
        {
            if (type == NORMAL && prevChar != '\'')
                type = STRING;
            else if (type == STRING)
                type = NORMAL;
        }
        else if (word[0] == '/')
        {
            if (prevChar == '/' && type == NORMAL)
                type = SINGLE_LINE_COMMENT;
            else if (type == MULTI_LINE_COMMENT && prevChar == '*')
                type = NORMAL;
        }
        else if (word[0] == '\n' && (type == SINGLE_LINE_COMMENT || type == PREPROCESSOR))
            type = NORMAL;
        else if (word[0] == '*' && prevChar == '/' && type == NORMAL)
            type = MULTI_LINE_COMMENT;
        else if (word[0] == '#' && (prevChar == '\n' || prevChar == '\0')) // if first line is a preprocessor, prevChar will be set to '\0'
            type = PREPROCESSOR;

        if (strlen(toAdd) > 0 && word[0] != '(') // if something is in toAdd from previous iteration and the current char is not a '(', then add it since not a function
            root = addtree(root, toAdd);
        toAdd[0] = '\0';                                                                     // reset toAdd each iteration
        if (type == NORMAL && (isalpha(word[0]) || word[0] == '_') && binsearch(word) == -1) // if normal word that starts with a letter or underscore and is not a keyword
            strcpy(toAdd, word);                                                             // prepare to add it
        if (type == PREPROCESSOR && prevChar == '#' && strcmp(word, "define") == 0)          // this turns off the preprocessor status since #define contains a variable name
            type = NORMAL;                                                                   // ifdef, ifndef, undef didn't seem appropriate to allow despite using variable names
        if (strlen(word) == 1)
            prevChar = word[0]; // save previous character for status type logic
    }
    if (strlen(toAdd) > 0) // if something is left in toAdd after loop ended, then add it
        root = addtree(root, toAdd);
    treeprint(root, root);
    return 0;
}

// find word in tab[0] ... tab[n-1], tab[] must be in alphabetical order
int binsearch(char *word)
{
    int result, mid, low = 0, high = KEYWORD_LEN - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if ((result = strcmp(word, keywords[mid])) < 0)
            high = mid - 1;
        else if (result > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1; // not found
}

// add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w)
{
    int result;
    if (p == NULL) // a new word has arrived
    {
        p = talloc(); // make a new node
        p->word = mystrdup(w);
        p->left = p->right = NULL;
    }
    else if ((result = strcmp(w, p->word)) < 0) // less than into left subtree
        p->left = addtree(p->left, w);
    else if (result > 0) // greater than into right subtree
        p->right = addtree(p->right, w);
    return p; // repeated word
}

// in-order print of tree p. This won't print the last matching item and must be manually printed
void treeprint(struct tnode *p, struct tnode *root)
{
    static char prevWord[MAXWORD] = {'\0'}; // set to null
    static int printPrev = FALSE;           // used to print prevWord if it matched the previous previous word but does not match current word. This system prevents duplicate prints
    if (p != NULL)
    {
        treeprint(p->left, root);                      // get all left words in recursive order (lowest left tree node first, then go up)
        if (strncmp(p->word, prevWord, numChars) == 0) // prevWord matches current word, print prevWord and update flag
        {
            printf("%s\n", prevWord);
            printPrev = TRUE;
        }
        else if (printPrev) // if current word does not match prevWord, but prevWord matched the previous prevWord, print it and update flag
        {
            printPrev = FALSE;
            printf("%s\n\n", prevWord); // the extra newline is a separator for each group
        }
        strcpy(prevWord, p->word);  // copy current word to prevWord for logic
        treeprint(p->right, root);  // get all right words in recursive order (lowest left tree node that has right node, then next lowest left node with a right node)
        if (p == root && printPrev) // last node in recursion, so print last matching word if any
            printf("%s\n", prevWord);
    }
}

struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) // make a duplicate of s
{
    char *p = (char *)malloc(strlen(s) + 1); // + 1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

// get next word or character from input
int getword(char *word, int lim)
{
    int c;
    char *w = word;
    while ((c = getch()) == '\t' || c == ' ')
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_')
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()) && *w != '_')
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
}

// get a (possibly pushed back) character
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

// push character back on input
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}