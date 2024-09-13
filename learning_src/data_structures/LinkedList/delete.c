// C code to delete a node from linked list
#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int number;
    struct Node *next;
};

void push(struct Node **head, int A)
{
    struct Node *n = (struct Node *)malloc(sizeof(struct Node));
    n->number = A;
    n->next = *head;
    *head = n;
}

void deleteN(struct Node **head, int position)
{
    struct Node *temp;
    struct Node *prev;
    temp = *head;
    prev = *head;
    for (int i = 0; i < position; i++)
    {
        if (i == 0 && position == 1)
        {
            *head = (*head)->next;
            free(temp);
        }
        else
        {
            if (i == position - 1 && temp)
            {
                prev->next = temp->next;
                free(temp);
            }
            else
            {
                prev = temp;

                // Position was greater than
                // number of nodes in the list
                if (prev == NULL)
                    break;
                temp = temp->next;
            }
        }
    }
}

void printList(struct Node *head)
{
    while (head)
    {
        printf("[%i] [%p]->%p\n", head->number, (void *)head, (void *)head->next);
        head = head->next;
    }
    printf("\n\n");
}

// Drivers code
int main()
{
    struct Node *list = (struct Node *)malloc(sizeof(struct Node));
    list->next = NULL;
    push(&list, 1);
    push(&list, 2);
    push(&list, 3);

    printList(list);

    // Delete any position from list
    deleteN(&list, 1);
    printList(list);
    return 0;
}
