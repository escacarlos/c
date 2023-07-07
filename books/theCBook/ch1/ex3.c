#include <stdio.h>

main() {

    int l,c;
    l=0;
    while((c=getchar())!=EOF){
        if(c=='\b')
            ++l;
    }
    printf("%d\n",l);
}
