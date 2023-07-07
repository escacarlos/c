/*

#define: Substitutes a preprocessor macro.
#define MAX_ARRAY_LENGTH 20

#include: Inserts a particular header from another file.
#include <stdio.h>
#include "myheader.h"

	
#undef: Undefines a preprocessor macro.
#undef  FILE_SIZE
#define FILE_SIZE 42

#ifdef: Returns true if this macro is defined.
#ifndef: Returns true if this macro is not defined.
#if: Tests if a compile time condition is true.
#else: The alternative for #if.
#elif: #else and #if in one statement.
#endif: Ends preprocessor conditional.
#ifndef MESSAGE
   #define MESSAGE "You wish!"
#endif

#ifdef DEBUG
   -- Your debugging statements here --
#endif

#error: Prints error message on stderr.
#pragma: Issues special commands to the compiler, using a standardized method.

MACROS----------------------------------------------------------------

__DATE__: The current date as a character literal in "MMM DD YYYY" format.
__TIME__: The current time as a character literal in "HH:MM:SS" format.
__FILE__: This contains the current filename as a string literal.
__LINE__: This contains the current line number as a decimal constant.	
__STDC__: Defined as 1 when the compiler complies with the ANSI standard.
*/

#include <stdio.h>

#define  message_for(a, b)  \
   printf(#a " and " #b ": We love you!\n")
//The macro continuation operator (\) 
//is used to continue a macro that is too long for a single line.

#define tokenpaster(n) printf ("token" #n " = %d\n", token##n)
//(##)It permits two separate tokens in the macro definition to be joined into a single token

#if !defined (MESSAGE)
   #define MESSAGE "You wish!"
#endif

//Parameterized Macros
#define square(x) ((x) * (x))

#define MAX(x,y) ((x) > (y) ? (x) : (y))

int main(void) {

    printf("File :%s\n", __FILE__ );
    printf("Date :%s\n", __DATE__ );
    printf("Time :%s\n", __TIME__ );
    printf("Line :%d\n", __LINE__ );
    //printf("ANSI :%d\n", __STDC__ );

    //Preprocessor Operators
    message_for(Carole, Debra);

    //The Token Pasting (##) Operator
    int token34 = 40;
    tokenpaster(34);
    //This example shows the concatenation of token##n 
    //into token34 and here we have used both stringize and token-pasting.

    printf("Here is the message: %s\n", MESSAGE); 

    //Parameterized Macros
    
    printf("the square of 2 is %d\n", square(2));
    printf("the square of 5 is %d\n", square1(5));
    printf("Max between 20 and 10 is %d\n", MAX(10, 20));

}

int square1(int x) {
   return x * x;
}
