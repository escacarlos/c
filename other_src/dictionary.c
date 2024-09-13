#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct dnode
{
  char *key;
  char *value;
  struct dnode *next;
};

struct pydict
{
  struct dnode *head;
  struct dnode *tail;
  int count;
};

/* Constructor - dct = dict */
struct pydict *pydict_new()
{
  struct pydict *p = malloc(sizeof(*p));
  if (!p)
  {
    perror("pydict_new: Failed to allocate memory");
  }
  p->head = NULL;
  p->tail = NULL;
  p->count = 0;
  return p;
}

/* Destructor - del(dct) */
void pydict_del(struct pydict *self)
{
  struct dnode *cur, *next;
  cur = self->head;
  while (cur)
  {
    free(cur->key);
    free(cur->value);
    next = cur->next;
    free(cur);
    cur = next;
  }
  free((void *)self);
}

// len(dct)
int pydict_len(const struct pydict *self)
{
  return self->count;
}

// print(lst)
// {'z': 'W', 'y': 'B', 'c': 'C', 'a', 'D'}
void pydict_print(struct pydict *self)
{
  struct dnode *cur = self->head;
  printf("{");
  while (cur)
  {
    printf("'%s':'%s'", cur->key, cur->value);
    cur = cur->next;
    if (cur)
    {
      printf(", ");
    }
  }
  printf("}\n");
}

struct dnode *pydict_find(struct pydict *self, char *key)
{
  struct dnode *cur = self->head;
  while (cur != NULL)
  {
    if (strcmp(cur->key, key) == 0)
    {
      return cur;
    }
    cur = cur->next;
  }
  return NULL;
}

// x.get(key) - Returns NULL if no found
char *pydict_get(struct pydict *self, char *key)
{
  struct dnode *entry = pydict_find(self, key);
  if (entry == NULL)
  {
    perror("pydict_get: key not present");
    return NULL;
  }
  return entry->value;
}

// x[key] = value; Insert or replace the value associated with a key
struct pydict *pydict_put(struct pydict *self, char *key, char *value)
{
  struct dnode *old = pydict_find(self, key);
  if (old != NULL)
  {
    char *new_value = strdup(value);
    if (!new_value)
    {
      perror("pydict_put: Failed to allocate memory");
      return self;
    }
    free(old->value);
    old->value = new_value;
  }
  else
  {
    struct dnode *new_node = malloc(sizeof(*new_node));
    if (!new_node)
    {
      perror("pydict_put: Failed to allocate memory");
      return self;
    }
    new_node->key = strdup(key);
    new_node->value = strdup(value);
    new_node->next = NULL;

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
  return self;
}

int main()
{
  struct pydict *dct = pydict_new();
  pydict_put(dct, "z", "Catch phrase");
  pydict_print(dct);
  pydict_put(dct, "z", "W");
  pydict_print(dct);
  pydict_put(dct, "y", "B");
  pydict_put(dct, "c", "C");
  pydict_put(dct, "a", "D");
  pydict_print(dct);
  printf("Length =%d\n", pydict_len(dct));
  printf("z=%s\n", pydict_get(dct, "z"));
  printf("x=%s\n", pydict_get(dct, "x"));
  printf("\nDump\n");
  for (struct dnode *cur = dct->head; cur != NULL; cur = cur->next)
  {
    printf("%s=%s\n", cur->key, cur->value);
  }
  pydict_del(dct);
  return 0;
}