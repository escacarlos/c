#include <stdio.h>
#include "support_extern.h"

int count ;
extern void write_extern();
 
main() {
   count = 5;
   write_extern();
}