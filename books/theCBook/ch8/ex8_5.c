#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>   // for localtime() and struct tm
#include <pwd.h>    // for getpwuid() and struct passwd
#include <grp.h>    // for getgrgid() and struct group
#include <string.h> // for strlen()

/*
    Exercise 8-5. Modify the fsize program to print the other information contained in the inode entry.
*/

void statfile(char *path);                    // prints the stats of a file in a ls -l style format
void dirwalk(char *path, void (*fp)(char *)); // fp is a function pointer. Used by calling function to specify a function to call when a file is found

int main(int argc, char *argv[])
{
    if (argc == 1) // if no command line args, list current dir
        statfile(".");
    else // otherwise, list each argument given
        while (--argc > 0)
            statfile(*++argv);
    return 0;
}

void statfile(char *path)
{
    struct stat stbuf; // stores the stat info
    struct tm *mt;     // stores the last modified time
    struct passwd *pw; // used to get the user name
    struct group *g;   // used to get the group name

    if (stat(path, &stbuf) == -1) // gets stat structure for the file at the specified path and stores it in stbuf. A return code of -1 indicates an error occurred
    {
        fprintf(stderr, "error: can't access %s\n", path);
        return;
    }
    if (path[strlen(path) - 1] == '/')
        path[strlen(path) - 1] = '\0'; // remove forward slash at end of string to clean up output

// prints file type: file == -, directory == d, character device == c, block device == b, named pipe (FIFO) == p, symbolic link == l, socket == s, unknown type == ?
#ifdef S_ISSOCK // S_ISSOCK might not be defined
    putchar((S_ISREG(stbuf.st_mode)) ? '-' : (S_ISDIR(stbuf.st_mode)) ? 'd'
                                         : (S_ISCHR(stbuf.st_mode))   ? 'c'
                                         : (S_ISBLK(stbuf.st_mode))   ? 'b'
                                         : (S_ISFIFO(stbuf.st_mode))  ? 'p'
                                         : (S_ISLNK(stbuf.st_mode))   ? 'l'
                                         : (S_ISSOCK(stbuf.st_mode))  ? 's'
                                                                      : '?');
#else
    putchar((S_ISREG(stbuf.st_mode)) ? '-' : (S_ISDIR(stbuf.st_mode)) ? 'd'
                                         : (S_ISCHR(stbuf.st_mode))   ? 'c'
                                         : (S_ISBLK(stbuf.st_mode))   ? 'b'
                                         : (S_ISFIFO(stbuf.st_mode))  ? 'p'
                                         : (S_ISLNK(stbuf.st_mode))   ? 'l'
                                                                      : '?');
#endif

    putchar((stbuf.st_mode & S_IRUSR) ? 'r' : '-'); // user read perms
    putchar((stbuf.st_mode & S_IWUSR) ? 'w' : '-'); // user write perms
    putchar((stbuf.st_mode & S_IXUSR) ? 'x' : '-'); // user execute perms
    putchar((stbuf.st_mode & S_IRGRP) ? 'r' : '-'); // group read perms
    putchar((stbuf.st_mode & S_IWGRP) ? 'w' : '-'); // group write perms
    putchar((stbuf.st_mode & S_IXGRP) ? 'x' : '-'); // group execute perms
    putchar((stbuf.st_mode & S_IROTH) ? 'r' : '-'); // other read perms
    putchar((stbuf.st_mode & S_IWOTH) ? 'w' : '-'); // other write perms
    putchar((stbuf.st_mode & S_IXOTH) ? 'x' : '-'); // other execute perms

    printf(" %3lu ", (long unsigned int)stbuf.st_nlink); // number of hard links to file

    if ((pw = getpwuid(stbuf.st_uid)) == NULL) // gets the user name based on the user id
        printf("%d ", stbuf.st_uid);           // if it could not be retrieved, print uid
    else
        printf("%s ", pw->pw_name); // otherwise print user name

    if ((g = getgrgid(stbuf.st_gid)) == NULL) // gets the group name based on the group id
        printf("%d ", stbuf.st_gid);          // if it could not be retrieved, print gid
    else
        printf("%s ", g->gr_name); // otherwise print group name

    printf("%13ld ", stbuf.st_size); // size in bytes

    if ((mt = localtime(&stbuf.st_mtime)) == NULL)            // get the date.
        printf("%4d-%02d-%02d %02d:%02d ", 1970, 1, 1, 0, 0); // Displays Epoch time if an error occurred in localtime and it returned NULL
    else
        printf("%4d-%02d-%02d %02d:%02d ", 1900 + mt->tm_year, mt->tm_mon, mt->tm_mday, mt->tm_hour, mt->tm_min); // tm_year == the number of years since 1900

    printf("%s\n", path); // print the path to the file including the parent directories

    if (S_ISDIR(stbuf.st_mode))  // if directory found, pass it to dirwalk. This is at the bottom of so statfile the order it is printed is somewhat alphabetical
        dirwalk(path, statfile); // dirwalk will look for another directory. If one it found, it will call statfile passing its path
}

void dirwalk(char *path, void (*fp)(char *))
{
    char name[FILENAME_MAX]; // stores path to the file
    DIR *dsp;                // directory stream pointer returned from opendir. Passed to readdir to get the info on it
    struct dirent *dp;       // directory entry pointer returned by readdir. Contains the name of the file returned

    if ((dsp = opendir(path)) == NULL)
    {
        fprintf(stderr, "error: can't open %s\n", path);
        return;
    }
    while ((dp = readdir(dsp)) != NULL) // get all files in the directory
    {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) // skip . and .. to prevent an infinite loop
            continue;
        if (strlen(path) + strlen(dp->d_name) + 2 > FILENAME_MAX) // check to see if the new path exceeds FILENAME_MAX
        {
            fprintf(stderr, "error length of name %s/%s is %ld characters and max supported size is %ld\n", path, dp->d_name,
                    (long unsigned int)strlen(path) + strlen(dp->d_name) + 1, (long unsigned int)FILENAME_MAX);
        }
        else
        {
            sprintf(name, "%s/%s", path, dp->d_name); // print the path/filename info into name and then passes it to statfile
            (*fp)(name);                              // call statfile once done to list info about the file
        }
    }
    closedir(dsp);
}