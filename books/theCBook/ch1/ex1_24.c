/* checksyntax.c: Basic C syntax checker */

#include <stdio.h>

#define MAXLINE 1000
#define TRUE 1
#define FALSE 0

int getTheLine(char line[], int maxline);
void syntaxCheck();

int inComment, openCommentLine, openBraceLine, openBrace, error;

int main()
{
    inComment = openCommentLine = openBraceLine = openBrace = error = 0;

    printf("\nChecking for basic syntax errors.\n\n");

    syntaxCheck();

    if (inComment)
    {
        printf("%3d | Error: Unclosed comment found\n", openCommentLine);
        error = TRUE;
    }
    if (openBrace)
    {
        printf("%3d | Error: Unclosed brace found\n", openBraceLine);
        error = TRUE;
    }
    if (!error)
        printf("No basic syntax errors found. Well done!\n");

    putchar('\n');

    return 0;
}

int getTheLine(char s[], int lim)
{ /* slightly modified from K & R */
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

void syntaxCheck()
{
    int currChar, prevChar, nextChar, quote, doubleQuote, openParen, closedParen;
    int openBracket, closedBracket;

    openBrace = openBracket = closedBracket = FALSE;

    int currLine;
    char inputline[MAXLINE];
    char from[MAXLINE];
    int escaped;
    int constant;

    extern int inComment, openCommentLine, openBraceLine, openBrace, error;

    openCommentLine = openBraceLine = openParen = closedParen = FALSE;

    currLine = 1;

    while (getTheLine(inputline, MAXLINE) > 0)
    {

        doubleQuote = quote = FALSE;

        for (currChar = 0; inputline[currChar] != '\0'; ++currChar)
        {

            prevChar = (currChar - 1);
            nextChar = (currChar + 1);
            escaped = FALSE;
            constant = FALSE;

            if (inputline[currChar] != '\\' && inputline[prevChar] == '\\')
                escaped = TRUE;

            if (!escaped)
            {

                if (inputline[currChar] == '/' && inputline[nextChar] == '*' && !inComment)
                {
                    inComment = TRUE;
                    openCommentLine = currLine;
                }

                if (inputline[currChar] == '/' && inputline[prevChar] == '*' && inComment)
                    inComment = FALSE;
            }

            if (inputline[prevChar] == '\'' && inputline[nextChar] == '\'')
                constant = TRUE;

            if (!inComment && !escaped && !constant)
            {

                if (inputline[currChar] == '{' && openBrace && !doubleQuote)
                    ++openBrace;

                if (inputline[currChar] == '{' && !openBrace && !doubleQuote)
                {
                    ++openBrace;
                    openBraceLine = currLine;
                }

                if (inputline[currChar] == '}' && !openBrace && !doubleQuote)
                {
                    printf("%3d | Error: Orhpaned closing brace\n", currLine);
                    error = TRUE;
                }

                if (inputline[currChar] == '}' && openBrace)
                    --openBrace;

                if (inputline[currChar] == '\"' && doubleQuote)
                {
                    ++doubleQuote;
                    doubleQuote = 0;
                    ++currChar;
                }

                if (inputline[currChar] == '\"' && !doubleQuote)
                    ++doubleQuote;

                if (inputline[currChar] == '\n' && doubleQuote)
                {
                    printf("%3d | Error: Unbalanced double quotes\n", currLine);
                    doubleQuote = 0;
                    error = TRUE;
                }

                if (inputline[currChar] == '\'' && quote && !doubleQuote)
                {
                    ++quote;
                    quote = 0;
                    ++currChar;
                }

                if (inputline[currChar] == '\'' && !quote && !doubleQuote)
                    ++quote;

                if (inputline[currChar] == '\n' && quote)
                {
                    printf("%3d | Error: Unbalanced single quotes\n", currLine);
                    quote = 0;
                    error = TRUE;
                }

                if (inputline[currChar] == '(' && !doubleQuote)
                {
                    ++openParen;
                }

                if (inputline[currChar] == ')' && !doubleQuote)
                    ++closedParen;

                if (inputline[currChar] == '\n' && (openParen != closedParen))
                {
                    printf("%3d | Error: Unbalenced parentheses\n", currLine);
                    openParen = closedParen = 0;
                    error = TRUE;
                }

                if (inputline[currChar] == '[')
                    ++openBracket;

                if (inputline[currChar] == ']')
                    ++closedBracket;

                if (inputline[currChar] == '\n' && (openBracket != closedBracket))
                {
                    printf("%3d | Error: Unbalanced brackets\n", currLine);
                    openBracket = closedBracket = 0;
                    error = TRUE;
                }
            }
        }
        ++currLine;
    }
}