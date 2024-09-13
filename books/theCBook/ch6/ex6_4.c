#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
    Exercise 6-4. Write a program that prints the distinct words in its input sorted into decreasing order of frequency of occurrence. Precede each word by its count.
*/

struct tnode // the tree node:
{
    char *word;          // points to the text
    int count;           // number of occurrences
    struct tnode *left;  // left child
    struct tnode *right; // right child
};

#define MAXWORD 100
#define BUFSIZE 100
#define MAXSUPPORTEDWORDS 10000

struct tnode *addtree(struct tnode *, char *);
void treeprint(void);
int getword(char *, int);
struct tnode *talloc(void);
char *mystrdup(char *);
int getword(char *word, int lim);
int getch(void);
void ungetch(int);
void qsortd(struct tnode *v[], int left, int right);
void swap(struct tnode *v[], int i, int j);

char buf[BUFSIZE];                                // buffer for ungetch
int bufp = 0;                                     // next free position in buf
struct tnode *treeNodes[MAXSUPPORTEDWORDS] = {0}; // initialized to null
int treeP = 0;                                    // next free position in treeNodes

// word frequency count
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if (isalpha(word[0]) || word[0] == '_')
            root = addtree(root, word);
    qsortd(treeNodes, 0, treeP - 1);
    treeprint();
    return 0;
}

// add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w)
{
    int result;

    if (p == NULL) // a new word has arrived
    {
        p = talloc(); // make a new node
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
        treeNodes[treeP++] = p;
    }
    else if ((result = strcmp(w, p->word)) == 0)
        p->count++;      // repeated word
    else if (result < 0) // less than into left subtree
        p->left = addtree(p->left, w);
    else // greater than into right subtree
        p->right = addtree(p->right, w);
    return p;
}

// in-order print of tree p
void treeprint(void)
{
    for (int i = 0; i < treeP; i++)
        printf("%4d %s\n", treeNodes[i]->count, treeNodes[i]->word);
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
    while ((c = tolower(getch())) == '\t' || c == ' ')
        ;
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_')
    {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = tolower(getch())) && *w != '_')
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

// sort v[left]...v[right] into decreasing order
void qsortd(struct tnode *v[], int left, int right)
{
    int i, last;
    if (left >= right) // do nothing if array contains fewer than two elements
        return;
    swap(v, left, (left + right) / 2); // move partition element to v[0]
    last = left;
    for (i = left + 1; i <= right; i++)   // partition
        if (v[left]->count < v[i]->count) // if v[left] is less than v[i], swap them to put them in order. Note: v[i], v[left] == increasing order and v[left], v[i] == decreasing order
            swap(v, ++last, i);
    swap(v, left, last); // restore partition element
    qsortd(v, left, last - 1);
    qsortd(v, last + 1, right);
}

// interchange v[i] and v[j]
void swap(struct tnode *v[], int i, int j)
{ // grab memory address of tnode and then swap where pointers are pointing
    struct tnode *temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}