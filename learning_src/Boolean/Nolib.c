#include <stdio.h>

typedef enum {false, true} bool;

int main() {
  bool x = false;
  if(x){
    printf("x is true.");
  }
  else{
    printf("x is false.");
  }
}