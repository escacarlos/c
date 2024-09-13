#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define size(a) (sizeof(a) / sizeof(a[0])) // macro

typedef struct
{
  char *ptr;
  size_t size;
} CharArray;

size_t strlen_(char *s)
{
  size_t i = 0;
  while (s[i] != '\0')
  {
    i++;
  }
  return i;
}

void strcpy_(char *s, char *t)
{
  while (*s++ = *t++)
    ;
}

int main(int argc, char *argv[])
{
  CharArray s2;
  s2.size = 18;
  s2.ptr = (char *)malloc(s2.size * sizeof(char));
  if (s2.ptr == NULL)
  {
    perror("Failed to allocate memory");
    return EXIT_FAILURE;
  }

  char *s0 = (char *)malloc(17 * sizeof(char) + 1);
  if (s0 == NULL)
  {
    perror("Failed to allocate memory");
    free(s2.ptr);
    return EXIT_FAILURE;
  }

  char s1[] = "Carlos Escalante";
  size_t i;
  printf("s1 is a char array in the stack\n");
  printf("sizeof(s0): this is a pointer in bytes %zu\n", sizeof(s0));
  printf("sizeof(*s0): this is a char %zu\n", sizeof(*s0));
  printf("size of char s1[]: %zu\n", size(s1)); // Macro works for stack arrays (int, double, char)
  printf("size of char s1[] using strlen from string.h: %zu\n", strlen(s1));
  printf("size of char s1[] using my own strlen_: %zu\n", strlen_(s1));

  //  Making hard copies
  for (i = 0; i < s2.size && (s0[i] = s1[i]) != '\0' && (s2.ptr[i] = s1[i]) != '\0'; i++)
  {
    printf("%c", s0[i]);
  }
  s2.ptr[i] = s0[i] = '\0';

  printf("\ns0 and s2 are pointers to heap memory\n");
  printf("size of s0 using strlen from string.h: %zu\n", strlen(s0));
  printf("size of s2.ptr using my own strlen_: %zu\n", strlen_(s2.ptr));

  printf("\ns0: %s\n", s0);
  printf("s1: %s\n", s1);
  printf("s2: %s\n", s2);

  char *s3 = s1; // Alias to s1  (Shallow copy)
  s3[0] = 'c';
  printf("s1: %s\n", s1);
  printf("s1: %p\n", &s1); // this two lines show that arrays decay to pointers
  printf("s1: %p\n", s1);

  char *s4 = (char *)malloc(17 * sizeof(char) + 1);
  if (s4 == NULL)
  {
    perror("Failed to allocate memory");
    free(s0);
    free(s2.ptr);
    return EXIT_FAILURE;
  }
  // s4 = s2.ptr;    // Alias to s2.ptr THIS IS VERY BAD
  strcpy_(s4, s2.ptr); // I could have done this: strncpy(s4, s2.ptr, 17) or strcpy(s4, s2.ptr) from string.h
  s4[0] = 'c';
  printf("s2.ptr: %s\n", s2.ptr);
  printf("s2.ptr: %p\n", &s2.ptr); // this is the pointer in the stack tha holds the info of the heap memory
  printf("s2.ptr: %p\n", s2.ptr);  // this is the actual memory address in the heap

  int x = 5;
  int *ptr = &x; // Passing the address of x to the ptr variable

  // Normal pointer manipulation
  printf("x: %d\n", x);
  printf("ptr: %p\n", ptr);
  printf("&x: %p\n", &x);
  printf("*ptr: %d\n", *ptr);

  free(s0);
  free(s4);
  free(s2.ptr);

  return EXIT_SUCCESS;
}

/*
Summary of Common Format Specifiers printf
%d: For printing int values.
%u: For printing unsigned int values.
%f: For printing float values.
%lf: For printing double values.
%c: For printing char values.
%s: For printing null-terminated strings.
%p: For printing pointer values.
%zu: For printing size_t values (recommended for sizes returned by sizeof).
*/