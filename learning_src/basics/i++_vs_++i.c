int main(void)
{
    // ++i will increment the value of i, and then return the incremented value.

    int i = 1;
    int j = ++i;
    // (i is 2, j is 2)

    // i++ will increment the value of i, but return the original value that i held before being incremented.

    i = 1;
    j = i++;
    // (i is 2, j is 1)

    return 0;
}
