#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Exercise 6-5. Write a function undef that will remove a name and definition from the table maintained by lookup and install.
*/

#define HASHSIZE 101

struct nlist // table entry
{
    struct nlist *next; // next entry in chain
    char *name;         // defined name
    char *defn;         // replacement text
};

static struct nlist *hashtab[HASHSIZE]; // pointer table

struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
char *mystrdup(char *s);
unsigned hash(char *s);
void undef(char *s);
void printHashtable(void);

int main()
{
    install("consider", "value 1");
    install("three", "value 2");
    install("less", "value 3");
    install("taxes", "value 4");
    printHashtable();
    printf("Removing three\n");
    undef("three");
    printHashtable();
    return 0;
}

unsigned hash(char *s)
{
    unsigned hashval;
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    return hashval % HASHSIZE;
}

struct nlist *lookup(char *s)
{
    for (struct nlist *np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np; // found
    return NULL;       // not found
}

// put (name, defn) in hashtab
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) // not found
    {
        np = (struct nlist *)malloc(sizeof(*np));
        if (np == NULL || (np->name = mystrdup(name)) == NULL)
            return NULL;
        hashval = hash(name);
        np->next = hashtab[hashval]; // adds items in reverse order. First item points to null (default value of hashtab[i]). Second value points to first value and updates
        hashtab[hashval] = np;       // the pointer in hashtab to itself, and so on. So hashtab[n] -> 1, 1->next -> NULL. Then hashtab[n] -> 2, 2->next -> 1, 1->next -> NULL
    }
    else                        // already there
        free((void *)np->defn); // free memory used by previous defn
    if ((np->defn = mystrdup(defn)) == NULL)
        return NULL;
    return np;
}

char *mystrdup(char *s) // make a duplicate of s
{
    char *p = (char *)malloc(strlen(s) + 1); // + 1 for '\0'
    if (p != NULL)
        strcpy(p, s);
    return p;
}

void undef(char *s)
{
    unsigned hashval = hash(s);
    for (struct nlist *p = hashtab[hashval], *prev = NULL; p != NULL; prev = p, p = p->next)
        if (strcmp(s, p->name) == 0) // match found, now delete the contents, connect prev node to next node, and then delete node found
        {
            if (prev == NULL)               // at the beginning
                hashtab[hashval] = p->next; // set the top value to the next value
            else
                prev->next = p->next; // update the previous to point to the next one so the middle one can be deleted
            free(p->name);            // free the allocated memory for these strings from mystrdup/malloc
            free(p->defn);
            free(p); // then free the allocated memory for the nlist from install/malloc. Afterwards, no memory leaks and pointer is gone (if not root node) or null
            break;
        }
}

void printHashtable(void)
{
    struct nlist *p;
    for (int i = 0, j = 0; i < HASHSIZE; i++, j = 0)
    {
        p = hashtab[i];
        while (p != NULL)
        {
            for (int k = 0; k < j; k++)
                printf("\t");
            printf("%p %p %s %s\n", (void *)p, (void *)p->next, p->name, p->defn);
            p = p->next;
            j++;
        }
    }
}