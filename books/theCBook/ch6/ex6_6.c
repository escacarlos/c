#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
    Exercise 6-6. Implement a simple version of the #define processor (i.e., no arguments) suitable for use with C programs, based on the routines of this section. You may
    also find getch and ungetch helpful.
*/

#define HASHSIZE 101
#define MAXLEN 1000
#define MAXWORD 100

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
int getline(char *s, int lim);

int main()
{
    char line[MAXLEN], name[MAXWORD], defn[MAXWORD], *s;
    int i, len;
    while ((len = getline(line, MAXLEN)) > 0)
    {
        for (int j = 0; j < len;)
            if (*(s = &line[j]) == '#' && strncmp(s, "#define", 7) == 0) // found a #define statement
            {
                j += 7;                             // skip it
                while (isspace(line[j]) && j < len) // skip spaces
                    j++;
                i = 0;
                while ((isalnum(line[j]) || line[j] == '_') && i < MAXWORD && j < len) // get name
                    name[i++] = line[j++];
                name[i] = '\0';
                while (isspace(line[j]) && j < len) // skip spaces
                    j++;
                i = 0;
                while (!isspace(line[j]) && i < MAXWORD && j < len) // get defn
                    defn[i++] = line[j++];
                defn[i] = '\0';
                install(name, defn); // add to hashtab
                break;               // skip rest of line
            }
            else if (isalpha(line[j]) || line[j] == '_') // possibly the #define identifier, so check!
            {
                i = 0;
                while ((isalnum(line[j]) || line[j] == '_') && i < MAXWORD && j < len) // get the next word
                    name[i++] = line[j++];
                name[i] = '\0';
                struct nlist *result = lookup(name); // check to see if in hashtab
                if (result != NULL)                  // if it is, print defn
                    printf("%s", result->defn);
                else // otherwise, print word
                    printf("%s", name);
            }
            else // print everything else
                putchar(line[j++]);
    }
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
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
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

// get line into s, return length
int getline(char *s, int lim)
{
    int c;
    char *original = s;
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
        *s++ = c;
    if (c == '\n')
        *s++ = c;
    *s = '\0';
    return s - original; // returns length
}