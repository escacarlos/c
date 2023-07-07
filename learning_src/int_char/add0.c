/*The '0' has an ASCII value of 48. so, we have to add 
its value to the integer value to convert it into the 
desired character. The program is as below:*/

#include<stdio.h>
int main(void)
{
    //Add '0' to Convert an int to char
    
    int number=71;
    int number1=7;

    char charValue = number+'0';
    char charValue1 = number1+'0';
    printf("The character value is : %c\n",charValue);
    printf("The value is : %c\n",charValue1);

    char charValue2[] = "stringValue X";
    int anyNumber;
    for (anyNumber= 0; anyNumber< 10; ++anyNumber)
    {
        charValue2[12] = anyNumber+ '0';
        puts(charValue2);
    }

    //Assign an int Value to char Value
    int number2 = 65;
    char charvalue3 = number2;

    printf("The character value : %c\n", charvalue3); 

    int number3 = 67;
    char charValue4 = (char)number3;
    printf("The character value = %c\n", charValue4);

    //sprintf() Function to Convert an Int to a Char

    //int sprintf(char *strValue, const char *format, [arg1, arg2, ... ]);
    /*strValue is a pointer to the char data type.
    format is used to display the type of output along with the placeholder.
    [arg1,arg2...] are the integer(s) to be converted.
    
    The function writes the data in the string pointed to by strValue and 
    returns the number of characters written to strValue, excluding the 
    null character. The return value is generally discarded. If any error 
    occurs during the operation, it returns -1. The program to convert an 
    integer to a character is as below:*/

    int number4 = 72;
    char charValue5[1];

    sprintf(charValue5, "%c", number4);
    printf("The character value = %s", charValue5);

    return 0;
}