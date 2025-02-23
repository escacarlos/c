#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

#define MAXSTACKSIZE 65536

//representing stack as struct
struct stack {
    int16_t pile[MAXSTACKSIZE];
    int32_t topOfStackPosition;
    int count;
};

//helper function to print stack
void printStack(struct stack *stack) {
    int i;
    if (stack->count > 0) {
        for (i = 0 ; i <= stack->topOfStackPosition ; i++){
            printf("%i ",stack->pile[i]);
        }
    }
    printf("\n");
}

//push to stack
void stackPush(struct stack *stack, int16_t value) {
    if (stack->count == 0) {
        stack->pile[0] = value;
        stack->topOfStackPosition = 0;
    } else {
        stack->topOfStackPosition++;
        stack->pile[stack->topOfStackPosition] = value;
    }
    stack->count++;
}

//pop from stack
void stackPop(struct stack *stack) {
    if (stack->topOfStackPosition == 0) {
        stack->count = 0;
        //printf("Stack is empty\n");
    } else {
        stack->topOfStackPosition--;
        stack->count--;
    }

}

//check valid entry function
bool validateCurrentOperation(char op) {
    if (op == '0' || op == '+' || op == '<' || op == '>' || op == '?' || op == '_' || op == '~' || op == '(' || op == ')') {
        return true;
    } else {
        return false;
    }
}

//0 operation
void zeroOperation(struct stack *stack) {
    stackPush(stack,0);
}

//+ operation
void plusOperation(struct stack *stack) {
    stack->pile[stack->topOfStackPosition]++;
}

//_ drop operation
void dropOperation(struct stack *stack) {
    stackPop(stack);
}

//~ dup operation
void dupOperation(struct stack *stack) {
    stackPush(stack,stack->pile[stack->topOfStackPosition]);
}

//? test operation
void testOperation(struct stack *stack) {
    if (stack->pile[stack->topOfStackPosition] != 0) {
        stack->pile[stack->topOfStackPosition]--;
        stackPush(stack,1);
    } else {
        stackPush(stack,0);
    }
}

//> rot R operation
void rotROperation(struct stack *stack) {
    int16_t N = stack->pile[stack->topOfStackPosition];
    stackPop(stack);

    if (N >= 2) {
        int16_t temp = stack->pile[stack->topOfStackPosition];
        int i;
        for (i = stack->topOfStackPosition ; i > stack->topOfStackPosition - N + 1; i--) {
            stack->pile[i] = stack->pile[i-1];
        }
        stack->pile[stack->topOfStackPosition - N + 1] = temp;
    }

}

//< rot L operation
void rotLOperation(struct stack *stack) {
    int16_t N = stack->pile[stack->topOfStackPosition];
    stackPop(stack);

    if (N >= 2) {
        int16_t temp = stack->pile[stack->topOfStackPosition - N + 1];
        int i;
        for (i = stack->topOfStackPosition - N + 1 ; i < stack->topOfStackPosition  ; i++) {
            stack->pile[i] = stack->pile[i+1];
        }
        stack->pile[stack->topOfStackPosition] = temp;
    }

}

//struct to find indexes of a loop
struct loopIndex {
    int startOfLoop;
    int endOfLoop;
};

//find indices of start and end of a loop
struct loopIndex findLoopIndices(int i, char *inputString) {
    struct loopIndex index = {0,0};
    index.startOfLoop = i - 1;

    int j;
    int depth = 0;
    for (j = i ; j < strlen(inputString) ; j++) {
        if (inputString[j] == '(') {
            depth++;
        }
        if (inputString[j] == ')') {
            if (depth == 1) {
                index.endOfLoop = j;
                return index;
            } else {
                depth--;
            }
        }
    }
    //case unmatched parentheses. setting end of loop out of bounds to catch it after function return.
    index.endOfLoop = strlen(inputString);
    return index;
}

// process operation
int processCurrentOperation(struct stack *my_stack, int *i, char *inputString) {

    char currentOp = inputString[*i];

    if (currentOp == '0') {
        zeroOperation(my_stack);
    }

    if (currentOp == '+') {
        plusOperation(my_stack);
    }

    if (currentOp == '_') {
        dropOperation(my_stack);
    }

    if (currentOp == '~') {
        dupOperation(my_stack);
    }

    if (currentOp == '?') {
        testOperation(my_stack);
    }

    if (currentOp == '>') {
        if (my_stack->pile[my_stack->topOfStackPosition] < 2) {
            printf("Cannot rotate. Top of stack < 2.");
            return 1;
        }

        // condition for stack to be sufficient: TopOfStackValue >= count -1
        if (my_stack->pile[my_stack->topOfStackPosition] <= my_stack->count - 1) {
            rotROperation(my_stack);
        }
        else {
            printf("Error. Stack insufficient.");
            return 1;
        }
    }

    if (currentOp == '<') {
        if (my_stack->pile[my_stack->topOfStackPosition] < 2) {
            printf("Cannot rotate. Top of stack < 2.");
            return 1;
        }

        // condition for stack to be sufficient: TopOfStackValue >= count -1
        if (my_stack->pile[my_stack->topOfStackPosition] <= my_stack->count - 1) {
            rotLOperation(my_stack);
        }
        else {
            printf("Error. Stack insufficient.");
            return 1;
        }
    }

    if (currentOp == '(') {

        //finding indexes for start and end of loop
        struct loopIndex index;
        index = findLoopIndices(*i, inputString);
        //catching unmatched parentheses
        if (index.endOfLoop == strlen(inputString)) {
            printf("Error. Unmatched parentheses.\n");
            return 3;
        }

        //Exit recursion criteria check
        if (my_stack->pile[my_stack->topOfStackPosition] == 0) {
            //exiting loop.
            *i = index.endOfLoop;
            return 0;
        }

        while(*i < strlen(inputString)) {
            *i = *i + 1;
            //reached end of loop
            if (inputString[*i] == ')') {
                *i = index.startOfLoop;
                break;
            }

            //recursive call for successive operations
            int returnCode = processCurrentOperation(my_stack,i,inputString);
            if (returnCode != 0)
                return returnCode;
        }
    }
    return 0;
}


//Main function
int main(int argc, char** argv) {

    //Defining stack to use
    struct stack my_stack = {{0},0, 0};

    if (argc != 2) {
        printf("Usage: ./stackman <filename>");
        return 0;
    }

    FILE *fileToOpen;
    fileToOpen = fopen(argv[1], "r");
    if (fileToOpen == NULL) {
        printf("File %s does not exist.\n", argv[1]);
        return -1;
    }

    char inputString[4096];
    fgets(inputString, sizeof inputString, fileToOpen);

    int i = 0;
    int returnCode = 0;
    for (i = 0 ; i < strlen(inputString) ; i++) {
        char currentOp = inputString[i];

        //Syntax validation for correct character
        bool isValid = validateCurrentOperation(currentOp);
        if (!isValid) {
            printf("Error, invalid syntax.");
            return 3;
        }

        //validating invalid operations on empty stack
        if (currentOp == '+' || currentOp == '_' || currentOp == '~' || currentOp == '?' || currentOp == '>' || currentOp == '<' || currentOp == '(' || currentOp == ')' ) {
            if (my_stack.count == 0) {
                printf("Error. Stack underflow.");
                return 1;
            }
        }

        returnCode = processCurrentOperation(&my_stack, &i, inputString);
        //stopping in case of any errors
        if (returnCode != 0)
            return returnCode;

        //preventing uncontrolled growth of stack.
        if (my_stack.count > MAXSTACKSIZE) {
            printf("Error. Stack overflow.");
            return 3;
        }
    }
    printStack(&my_stack);
    return returnCode;
}