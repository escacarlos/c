#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

/*
    Exercise 6-3. Write a cross-referencer that prints a list of all words in a document, and, for each word, a list of the line numbers on which it occurs. Remove noise
    words like "the," "and," and so on.
*/

struct tnode // the tree node:
{
    char *word;          // points to the text
    char *lines;         // str that contains line(s) word appears on
    struct tnode *left;  // left child
    struct tnode *right; // right child
};

#define MAXWORD 100
#define BUFSIZE 100
#define MAXLINESTRSIZE 10000
#define MAXDIGITSNUM 50 // used to store sprintf output, Note: unsigned long int max == 20 digits
#define STOPWORDLEN 198 // number of stop words

struct tnode *addtree(struct tnode *p, char *w);
struct tnode *talloc(void);
void treeprint(struct tnode *p);
void ungetch(int c);
int getword(char *, int);
int binsearch(char *word);
int getword(char *word, int lim);
int getch(void);
int addLineNumToStr(char *dest);
char *mystrdup(char *);

enum boolean
{
    FALSE,
    TRUE
};

char *stopWords[STOPWORDLEN] = { // stop words are typically "filler" words in a language. List based on nltk's data set (https://www.nltk.org). Must be in alphabetical order
    "_", "a", "about", "above", "after", "again", "against", "ain", "all", "am", "an", "and", "any", "are", "aren", "aren't", "as", "at", "b", "be", "because", "been",
    "before", "being", "below", "between", "both", "but", "by", "c", "can", "couldn", "couldn't", "d", "did", "didn", "didn't", "do", "does", "doesn", "doesn't", "doing",
    "don", "don't", "down", "during", "e", "each", "f", "few", "for", "from", "further", "g", "h", "had", "hadn", "hadn't", "has", "hasn", "hasn't", "have", "haven", "haven't",
    "having", "he", "her", "here", "hers", "herself", "him", "himself", "his", "how", "i", "if", "in", "into", "is", "isn", "isn't", "it", "its", "it's", "itself", "j",
    "just", "k", "l", "ll", "m", "ma", "me", "mightn", "mightn't", "more", "most", "mustn", "mustn't", "my", "myself", "n", "needn", "needn't", "no", "nor", "not", "now", "o",
    "of", "off", "on", "once", "only", "or", "other", "our", "ours", "ourselves", "out", "over", "own", "p", "q", "r", "re", "s", "same", "shan", "shan't", "she", "she's",
    "should", "shouldn", "shouldn't", "should've", "so", "some", "such", "t", "than", "that", "that'll", "the", "their", "theirs", "them", "themselves", "then", "there",
    "these", "they", "this", "those", "through", "to", "too", "u", "under", "until", "up", "v", "ve", "very", "w", "was", "wasn", "wasn't", "we", "were", "weren", "weren't",
    "what", "when", "where", "which", "while", "who", "whom", "why", "will", "with", "won", "won't", "wouldn", "wouldn't", "x", "y", "you", "you'd", "you'll", "your",
    "you're", "yours", "yourself", "yourselves", "you've", "z"};
char buf[BUFSIZE]; // buffer for ungetch
int bufp = 0;      // next free position in buf
int lineNum = 1;
int caseInsensitive = FALSE;

// word frequency count
int main(int argc, char *argv[])
{
    if (argc <= 2) // if 1 arg (no args given), value will equal 0 after loop. If 2 args, process 2nd arg and value will equal 0 after loop
    {
        while (--argc > 0)
            if (strcmp(*++argv, "-i") == 0)
                caseInsensitive = TRUE;
            else
                argc = -1; // prints usage
    }
    if (argc != 0)
    {
        printf("usage: getWords [-i]");
        return 1;
    }
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
        if ((isalpha(word[0]) || word[0] == '_') && binsearch(word) == -1) // if first char is alpha and not in the stop word list
        {
            root = addtree(root, word);
            if (root == NULL)
                return 1;
        }
    treeprint(root);
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
        char *str = (char *)malloc(MAXLINESTRSIZE); // get chunk of memory for string
        str[0] = '\0';                              // ensure it is a null string before addLineNumToStr is called
        if (p != NULL)
        {
            if (addLineNumToStr(str) == -1) // if -1, error occurred
                return NULL;
            p->lines = str;
        }
        else
        {
            printf("Error: could not allocate memory for tree node\n");
            return p; // p == NULL
        }
        p->left = p->right = NULL;
    }
    else if ((result = strcmp(w, p->word)) == 0) // same word
    {
        if (addLineNumToStr(p->lines) == -1) // if -1, error occurred
            return NULL;
    }
    else if (result < 0) // less than into left subtree
    {
        p->left = addtree(p->left, w);
        if (p->left == NULL)
            return NULL;
    }
    else // greater than into right subtree
    {
        p->right = addtree(p->right, w);
        if (p->right == NULL)
            return NULL;
    }
    return p;
}

// in-order print of tree p
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%s ", p->word);
        printf("%s\n", p->lines);
        treeprint(p->right);
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
    if (caseInsensitive)
        c = tolower(c);
    if (c != EOF)
        *w++ = c;
    if (!isalpha(c) && c != '_')
    {
        if (word[0] == '\n')
            lineNum++;
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
    {
        *w = getch();
        if (caseInsensitive)
            *w = tolower(*w);
        if (!isalnum(*w) && *w != '_')
        {
            ungetch(*w);
            break;
        }
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

// find word in stopWords, stopWords must be in alphabetical order
int binsearch(char *word)
{
    int result, mid, low = 0, high = STOPWORDLEN - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        result = stricmp(word, stopWords[mid]); // case-insensitive comparison to see if matches stop word
        if (result < 0)
            high = mid - 1;
        else if (result > 0)
            low = mid + 1;
        else
            return mid;
    }
    return -1; // not found
}

int addLineNumToStr(char *dest)
{
    char numStr[MAXDIGITSNUM];
    int digits = 0, n = lineNum;
    while (n != 0)
    {
        n /= 10;
        digits++;
    }
    int len = strlen(dest);
    if (len == 0)
    {
        sprintf(numStr, "%d", lineNum);   // sprintf is the a part of the C standard library, but itoa is not (although widely implemented). Using sprintf from now on
        if (digits + 1 <= MAXLINESTRSIZE) // digits + 1 because of '\0'
            strcat(dest, numStr);
        else
        {
            printf("Error: not enough memory to add new line string to tree node\n");
            return -1;
        }
    }
    else
    {
        sprintf(numStr, ", %d", lineNum);
        int same = TRUE;
        for (int i = 0; i < digits; i++)
            if (numStr[i] != dest[len - digits + i])
            {
                same = FALSE;
                break;
            }
        if (!same)
        {
            if (len + digits + 3 <= MAXLINESTRSIZE) // digits + 3 because 1 for '\0', 1 for ',' and 1 for ' '
                strcat(dest, numStr);
            else
            {
                printf("Error: not enough memory to add new line string to tree node\n");
                return -1;
            }
        }
    }
    return 0;
}