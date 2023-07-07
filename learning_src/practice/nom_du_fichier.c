#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main() {
    char firstChar = 0xff; // force it so you *know* it changes.
    int fdInput = open("file.data", O_RDONLY);
    if (fdInput == -1) {
        perror("file");
        _exit(1);
    }

    read(fdInput, &firstChar, 1);
    printf("Taille du nom de fichier : %d\n", firstChar); // prints 97

    close(fdInput);
}

