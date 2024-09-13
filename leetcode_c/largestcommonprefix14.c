#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// char* longestCommonPrefix(char** strs, int strsSize) {
//     char *ans;
//     if (strsSize == 0) {
//         ans = "";
//         return ans;
//     }
//     else {
//         ans = strdup(strs[0]);
//         ans = malloc(strlen(strs[0]));
//         strcpy(ans, strs[0]);
//     }

//     int i, j;
//     for (j = 0; ans[j] != '\0'; j++) {
//         for (i = 1; i < strsSize; i++) {
//             if (strs[i][j] != ans[j]) {
//                 goto OUT;
//             }
//         }
//     }
// OUT:
//     ans[j] = '\0';
//     return ans;
// }

char * longestCommonPrefix(char **strs, int strsSize){
    int i, j, k=0, shortest;
    bool isEqual;
    char *prefix;
    if (strsSize == 0) {
        prefix = "";
        return prefix;
    }
    else if (strsSize == 1)
        return strs[0];
    else 
    {
        prefix = strdup(strs[0]);
        prefix = (char *)malloc(strlen(strs[0])+1);
        strcpy(prefix, strs[0]);
        shortest = strlen(strs[0]);
        for(i=1; i<strsSize; i++)
            if(strlen(strs[i])<shortest)
                shortest = strlen(strs[i]);
        isEqual=true;
        for(i=0; i<shortest; i++)
        {                      
            for(j=0; j<strsSize-1; j++)
            {    
                if(strs[j][i]==strs[j+1][i])
                {                    
                    continue;
                }
                else
                {
                    isEqual=false;
                }                 
            }
            if(isEqual==true)
            {
                k++;
            }
        }
        prefix[k]='\0';
        return prefix;   
    }   
}

int main() {
    char *strs[20] = {
        "abcde",
        "abceawsdffd",
        "abcsdas",
        "abcefwfdf",
        "abcd",
        "abc",
        "aec"
    };
    char *s = longestCommonPrefix(strs, 7);
    printf("%s\n", s);
    s = longestCommonPrefix(NULL, 0);
    printf("%s\n", s);
    return 0;
}