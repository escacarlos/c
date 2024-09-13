#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TreeMapEntry
{
  char *key;
  int value;
  struct TreeMapEntry *__next;
  struct TreeMapEntry *__left;
  struct TreeMapEntry *__right;
};

struct TreeMap
{
  struct TreeMapEntry *__head;
  struct TreeMapEntry *__root;
  int __count;
};

void __TreeMap_put(struct TreeMap *self, char *key, int value)
{
  struct TreeMapEntry *cur, *left, *right;
  int cmp;
  cur = self->__root;
  while (cur != NULL)
  {
    cmp = strcmp(key, cur->key);
    if (cmp == 0)
    {
      cur->value = value;
      return;
    }
    if (cmp < 0)
    {
      cur = cur->__left;
    }
    else
    {
      cur = cur->__right;
    }
  }
}

void __TreeMap_put_list_tree(struct TreeMap *self, char *key, int value)
{
  cur = self->__root;
  right = NULL; // nearest right neighbor
  left = NULL;  // nearest left neightbor
  while (cur != NULL)
  {
    cmp = strcmp(key, cur->key);
    if (cmp == 0)
    {
      cur->value = value;
      return;
    }
    if (cmp < 0)
    { // turn left
      right = cur;
      cur = cur->__left;
    }
    else
    { // turn right
      left = cur;
      cur = cur->__right;
    }
  }
}

void __TreeMap_dump_tree(struct TreeMapEntry *cur, int depth)
{
  if (cur == NULL)
    return;
  for (int i = 0; i < depth; i++)
    printf("| ");
  printf("%s=%d\n", cur->key, cur->value);
  if (cur->__left != NULL)
  {
    __TreeMap_dump_tree(cur->__left, depth + 1);
  }
  if (cur->_right != NULL)
  {
    __TreeMap_dump_tree(cur->__right, depth + 1);
  }
}

int __TreeMap_get(struct TreeMap *self, char *key, int def)
{
  int cmp;
  struct TreeMapEntry *cur;
  if (key == NULL || self->__root == NULL)
    return def;

  cur = self->__root;
  while (cur != NULL)
  {
    cmp = strcmp(key, cur->key);
    if (cmp == 0)
      return cur->value;
    else if (cmp < 0)
      cur = cur->__left;
    else
      cur = cur->__right;
  }
  return def;
}

struct TreeMap *TreeMap_new()
{
  struct TreeMap *p = malloc(sizeof(*p));
  p->__head = NULL;
  p->__root = NULL;
  return p;
}

int main(void)
{
  struct TreeMap *map = TreeMap_new();

  map->put(map, "h", 22);
  map->put(map, "h", 42); // Replace
  map->put(map, "d", 8);
  map->put(map, "b", 123);
  map->put(map, "f", 6);
  map->dump(map);

  map->put(map, "k", 9);
  map->put(map, "m", 67);
  map->put(map, "j", 12);
  map->dump(map);
}