#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct MapEntry
{
  char *key;
  int value;
  struct MapEntry *__prev;
  struct MapEntry *__next;
};

struct Map
{
  /*Private attributes*/
  struct MapEntry *__head;
  struct MapEntry *__tail;
  int __count;

  /*Public methods*/
  void (*put)(struct Map *self, const char *key, const int value);
  int (*get)(const struct Map *self, const char *key, const int def);
  int (*size)(const struct Map *self);
  void (*dump)(const struct Map *self);
  void (*del)(struct Map *self);
  struct MapIter *(*iter)(struct Map *self);
};

int __Map_size(const struct Map *self);
void __Map_dump(const struct Map *self);
int __Map_get(const struct Map *self, const char *key, const int def);
void __Map_put(struct Map *self, const char *key, const int value);
void __Map_del(struct Map *self);
struct MapIter *__Map_iter(struct Map *self);

struct Map *Map_new()
{
  struct Map *p = (Map *)malloc(sizeof(*p));
  if (!p)
  {
    perror("Map_new: Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  p->__head = NULL;
  p->__tail = NULL;
  p->__count = 0;

  p->put = &__Map_put;
  p->get = &__Map_get;
  p->size = &__Map_size;
  p->dump = &__Map_dump;
  p->del = &__Map_del;
  p->iter = &__Map_iter;
  return p;
}

void __Map_del(struct Map *self)
{
  struct MapEntry *cur, *next;
  cur = self->__head;
  while (cur)
  {
    free(cur->key);
    next = cur->__next;
    free(cur);
    cur = next;
  }
  free((void *)self);
}

int __Map_size(const struct Map *self)
{
  return self->__count;
}

void __Map_dump(const struct Map *self)
{
  struct MapEntry *cur;
  printf("Object Map count=%d\n", self->__count);
  for (cur = self->__head; cur != NULL; cur = cur->__next)
  {
    printf(" %s=%d\n", cur->key, cur->value);
  }
}

struct MapEntry *__Map_find(const struct Map *self, const char *key)
{
  struct MapEntry *cur = self->__head;
  while (cur != NULL)
  {
    if (strcmp(cur->key, key) == 0)
    {
      return cur;
    }
    cur = cur->__next;
  }
  return NULL;
}

int __Map_get(const struct Map *self, const char *key, const int def)
{
  struct MapEntry *retval = __Map_find(self, key);
  if (retval == NULL)
  {
    return def;
  }
  return retval->value;
}

void __Map_put(struct Map *self, const char *key, const int value)
{
  struct MapEntry *old = __Map_find(self, key);
  if (old != NULL)
  {
    old->value = value;
  }
  else
  {
    struct MapEntry *new_node = (MapEntry *)malloc(sizeof(*new_node));
    if (!new_node)
    {
      perror("__Map_put: Failed to allocate memory");
      exit(EXIT_FAILURE);
    }
    new_node->key = strdup(key);
    new_node->value = value;
    new_node->__next = NULL;
    new_node->__prev = self->__tail;

    if (self->__tail)
    {
      self->__tail->__next = new_node;
    }
    else
    {
      self->__head = new_node;
    }
    new_node->__prev = self->__tail;
    self->__tail = new_node;
    self->__count++;
  }
}

struct MapIter
{
  struct MapEntry *__current;
  struct MapEntry *(*next)(struct MapIter *self);
  void (*del)(struct MapIter *self);
};

struct MapEntry *__MapIter_next(struct MapIter *self)
{
  struct MapEntry *retval = self->__current;

  if (retval == NULL)
    return NULL;
  self->__current = self->__current->__next;
  return retval;
}

void __MapIter_del(struct MapIter *self)
{
  free((void *)self);
}

struct MapIter *__Map_iter(struct Map *self)
{
  struct MapIter *iter = (MapIter *)malloc(sizeof(*iter));
  if (!iter)
  {
    perror("__Map_iter: Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  iter->__current = self->__head;
  iter->next = &__MapIter_next;
  iter->del = &__MapIter_del;
  return iter;
}

int main()
{
  struct Map *map = Map_new();
  struct MapEntry *cur;
  struct MapIter *iter;

  printf("Testing Map class\n");
  map->put(map, "z", 8);
  map->put(map, "z", 1);
  map->put(map, "y", 2);
  map->put(map, "b", 3);
  map->put(map, "a", 4);
  map->dump(map);

  printf("Length =%d\n", map->size(map));
  printf("z=%d\n", map->get(map, "z", 42));
  printf("x=%d\n", map->get(map, "x", 42));
  // for(cur = map->__head; cur != NULL; cur = cur->__next) {
  //     printf("%s=%d\n", cur->key, cur->value);
  // }
  printf("\nIterate\n");
  iter = map->iter(map);
  while (1)
  {
    cur = iter->next(iter);
    if (cur == NULL)
      break;
    printf("%s=%d\n", cur->key, cur->value);
  }
  iter->del(iter);

  map->del(map);
  return 0;
}