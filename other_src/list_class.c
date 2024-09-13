#include <stdio.h>
#include <stdlib.h>
// #include <string.h>

struct node
{
  char *text;
  struct node *next;
  struct node *prev;
};

struct list
{
  struct node *head;
  struct node *tail;
  int count;
};

struct list *list_new()
{
  struct list *p = malloc(sizeof(*p));
  p->head = NULL;
  p->tail = NULL;
  p->count = 0;
  return p;
}

void list_del(struct list *self)
{
  struct node *cur, *next;
  cur = self->head;
  while (cur)
  {
    free(cur->text);
    next = cur->next;
    free(cur);
    cur = next;
  }
  free((void *)self);
}

void list_print(struct list *self)
{
  struct node *cur = self->head;
  printf("[");
  while (cur)
  {
    printf("'%s'", cur->text);
    cur = cur->next;
    if (cur)
    {
      printf(", ");
    }
  }
  printf("]\n");
}

int list_len(const struct list *self)
{
  return self->count;
}

void strcpy_(char *s, char *t)
{
  while (*s++ = *t++)
    ;
}

int strlen_(char *s)
{
  int i;
  while (s[i] != '\0')
  {
    i++;
  }
  return i;
}

char *strdup_(char *s)
{
  char *p = (char *)malloc(strlen_(s) + 1);
  if (p != NULL)
  {
    strcpy_(p, s);
  }
  return p;
}

void list_append(struct list *self, char *str)
{
  struct node *new_node = malloc(sizeof(struct node));
  new_node->text = strdup_(str);
  new_node->next = NULL;
  new_node->prev = self->tail;

  if (self->tail)
  {
    self->tail->next = new_node;
  }
  else
  {
    self->head = new_node;
  }

  self->tail = new_node;
  self->count++;
}

int strcmp_(char *s, char *t)
{
  int i;
  for (i = 0; s[i] == t[i]; i++)
    if (s[i] == '\0')
      return 0;
  return s[i] - t[i];
}

int list_index(struct list *self, char *str)
{
  struct node *cur = self->head;
  int index = 0;
  while (cur)
  {
    if (strcmp_(cur->text, str) == 0)
    {
      return index;
    }
    cur = cur->next;
    index++;
  }
  return -1;
}

int main(void)
{
  struct list *lst = list_new();
  list_append(lst, "Hello world");
  list_print(lst);
  list_append(lst, "Catch phrase");
  list_print(lst);
  list_append(lst, "Brian");
  list_print(lst);
  printf("Length = %d\n", list_len(lst));
  printf("Brian? %d\n", list_index(lst, "Brian"));
  printf("Bob? %d\n", list_index(lst, "Bob"));
  list_del(lst);
}
