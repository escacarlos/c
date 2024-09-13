#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*) malloc(sizeof(struct Node));
    new_node->data=new_data;
    new_node->next=(*head_ref);
    (*head_ref)=new_node;

}

void insertAfter(struct Node* prev_node, int new_data)
{
    if(prev_node==NULL)
    {
        printf("the given previous node cannot be NULL");
        return;
    }

    struct Node* new_node=(struct Node*) malloc(sizeof(struct Node));
    new_node->data = new_data;
    new_node->next=prev_node->next;
    prev_node->next=new_node;
}

void append(struct Node** head_ref, int new_data)
{
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    struct Node* last = *head_ref;
    new_node->data=new_data;
    new_node->next=NULL;

    if(*head_ref==NULL)
    {
        *head_ref=new_node;
        return;
    }

    while(last->next!=NULL)
    {
        last=last->next;
    }

    last->next = new_node;
    return;
}

void deleteN(struct Node** head, int position)
{
    struct Node* temp;
    struct Node* prev;
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
                if (prev == NULL)
                    break;
                temp = temp->next;
            }
        }
    }
}

void deleteNode(struct Node** head_ref, int key)
{
    struct Node* temp = *head_ref, *prev;

    if(temp!=NULL && temp->data ==key)
    {
        *head_ref =temp->next;
        free(temp);
        return;
    }

    while(temp!=NULL && temp->data!=key)
    {
        prev=temp;
        temp=temp->next;
    }

    if(temp==NULL)
        return;

    prev->next=temp->next;
    free(temp);
}

void pritntList(struct Node* n)
{
    while(n!=NULL)
    {
        printf(" %d ", n->data);
        n=n->next;
    }
    printf("\n");
}

int main()
{
    struct Node* head = NULL;
    struct Node* second = NULL;
    struct Node* third = NULL;

    // allocate 3 nodes in the heap
    head=(struct Node*)malloc(sizeof(struct Node));
    second=(struct Node*)malloc(sizeof(struct Node));
    third=(struct Node*)malloc(sizeof(struct Node));

    head->data=1; // assign data in first node
    head->next=second; // Link first node with second

    second->data=2; // assign data to second node
    second->next=third;

    third->data=3;
    third->next=NULL;

    pritntList(head);

    push(&head, 10);

    pritntList(head);

    append(&head, 25);

    pritntList(head);

    insertAfter(head->next->next, 34);

    pritntList(head);

    deleteN(&head, 2);

    pritntList(head);

    deleteNode(&head, 34);

    pritntList(head);

    return 0;
}
