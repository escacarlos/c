#include <stdio.h>

typedef enum {false, true} bool;
#define TRUE 1
#define FALSE 0

int main() {
  bool x = true;
  if(x){
    printf("x is true.");
  }
  else if(!x){
    printf("x is false.");
  }
}