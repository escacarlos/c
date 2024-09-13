#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct HashMapEntry
{
  char *key;
  int value;
  struct HashMapEntry *__prev;
  struct HashMapEntry *__next;
};

struct HashMap
{
  /*Private attributes*/
  int __buckets;
  struct HashMapEntry *__heads[8];
  struct HashMapEntry *__tails[8];
  int __count;

  /*Public methods*/
  void (*put)(struct HashMap *self, const char *key, const int value);
  int (*get)(const struct HashMap *self, const char *key, const int def);
  int (*size)(const struct HashMap *self);
  void (*dump)(const struct HashMap *self);
  void (*del)(struct HashMap *self);
  struct HashMapIter *(*iter)(struct HashMap *self);
};

int __HashMap_size(const struct HashMap *self);
void __HashMap_dump(const struct HashMap *self);
int __HashMap_get(const struct HashMap *self, const char *key, const int def);
void __HashMap_put(struct HashMap *self, const char *key, const int value);
void __HashMap_del(struct HashMap *self);
struct HashMapIter *__HashMap_iter(struct HashMap *self);

struct HashMap *HashMap_new()
{
  struct HashMap *p = (HashMap *)malloc(sizeof(*p));
  if (!p)
  {
    perror("HashMap_new: Failed to allocate memory");
    exit(EXIT_FAILURE);
  }

  p->__buckets = 8;
  for (int i = 0; i < p->__buckets; i++)
  {
    p->__heads[i] = NULL;
    p->__tails[i] = NULL;
  }
  p->__count = 0;

  p->put = &__HashMap_put;
  p->get = &__HashMap_get;
  p->size = &__HashMap_size;
  p->dump = &__HashMap_dump;
  p->del = &__HashMap_del;
  p->iter = &__HashMap_iter;
  return p;
}

void __HashMap_del(struct HashMap *self)
{
  struct HashMapEntry *cur, *next;
  for (int i = 0; i < self->__buckets; i++)
  {
    cur = self->__heads[i];
    while (cur)
    {
      free(cur->key);
      next = cur->__next;
      free(cur);
      cur = next;
    }
  }
  free((void *)self);
}

int __HashMap_size(const struct HashMap *self)
{
  return self->__count;
}

void __HashMap_dump(const struct HashMap *self)
{
  int i;
  struct HashMapEntry *cur;
  printf("Object HashMap@%p count=%d buckets=%d\n", self, self->__count, self->__buckets);
  for (cur = self->__heads[i]; cur != NULL; cur = cur->__next)
  {
    printf(" %s=%d [%d]\n", cur->key, cur->value, i);
  }
}

struct HashMapEntry *__HashMap_find(const struct HashMap *self, const char *key, int bucket)
{
  struct HashMapEntry *cur;
  if (self == NULL || key == NULL)
  {
    return NULL;
  }
  for (cur = self->__heads[bucket]; cur != NULL; cur = cur->__next)
  {
    if (strcmp(key, cur->key) == 0)
    {
      return cur;
    }
  }
  return NULL;
}

int getBucket(const char *str, const int buckets)
{

  unsigned int hash = 123456;
  printf("\nHashing %s\n", str);
  if (str == NULL)
    return 0;
  for (; *str; str++)
  {
    hash = (hash << 3) ^ *str;
    printf("%c, 0x%08x %d\n", *str, hash, hash % buckets);
  }
  return hash % buckets;
}

int __HashMap_get(const struct HashMap *self, const char *key, const int def)
{
  int bucket = getBucket(key, self->__buckets);
  struct HashMapEntry *retval = __HashMap_find(self, key, bucket);
  if (retval == NULL)
  {
    return def;
  }
  return retval->value;
}

void __HashMap_put(struct HashMap *self, const char *key, const int value)
{
  int bucket;
  struct HashMapEntry *old, *new_;
  char *new_key, *new_value;

  bucket = getBucket(key, self->__buckets);
  old = __HashMap_find(self, key, bucket);
  if (old != NULL)
  {
    old->value = value;
    return;
  }

  new_ = (HashMapEntry *)malloc(sizeof(*new_));
  if (!new_)
  {
    perror("__HashMap_put: Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  new_->__next = NULL;
  new_->key = strdup(key);
  new_->value = value;
  new_->__prev = self->__tails[bucket];

  if (self->__heads[bucket] == NULL)
  {
    self->__heads[bucket] = new_;
  }
  if (self->__tails[bucket] != NULL)
  {
    self->__tails[bucket]->__next = new_;
  }
  new_->__prev = self->__tails[bucket];
  self->__tails[bucket] = new_;
  self->__count++;
}

struct HashMapIter
{
  int __bucket;
  struct HashMap *__map;
  struct HashMapEntry *__current;
  struct HashMapEntry *(*next)(struct HashMapIter *self);
  void (*del)(struct HashMapIter *self);
};

struct HashMapEntry *__HashMapIter_next(struct HashMapIter *self)
{
  struct HashMapEntry *retval;

  while (self->__current == NULL)
  {
    self->__bucket++;
    if (self->__bucket >= self->__map->__buckets)
    {
      return NULL;
    }
    self->__current = self->__map->__heads[self->__bucket];
  }
  retval = self->__current;
  if (self->__current != NULL)
  {
    self->__current = self->__current->__next;
  }
  return retval;
}

void __HashMapIter_del(struct HashMapIter *self)
{
  free((void *)self);
}

struct HashMapIter *__HashMap_iter(struct HashMap *self)
{
  struct HashMapIter *iter = (HashMapIter *)malloc(sizeof(*iter));
  if (!iter)
  {
    perror("__HashMap_iter: Failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  iter->__map = self;
  iter->__bucket = 0;
  iter->__current = self->__heads[iter->__bucket];
  iter->next = &__HashMapIter_next;
  iter->del = &__HashMapIter_del;
  return iter;
}

int main()
{
  struct HashMap *HashMap = HashMap_new();
  struct HashMapEntry *cur;
  struct HashMapIter *iter;

  printf("Testing HashMap class\n");
  HashMap->put(HashMap, "z", 8);
  HashMap->put(HashMap, "z", 1);
  HashMap->put(HashMap, "y", 2);
  HashMap->put(HashMap, "b", 3);
  HashMap->put(HashMap, "a", 4);
  HashMap->dump(HashMap);

  printf("Length =%d\n", HashMap->size(HashMap));
  printf("z=%d\n", HashMap->get(HashMap, "z", 42));
  printf("x=%d\n", HashMap->get(HashMap, "x", 42));
  // for(cur = HashMap->__heads; cur != NULL; cur = cur->__next) {
  //     printf("%s=%d\n", cur->key, cur->value);
  // }
  printf("\nIterate\n");
  iter = HashMap->iter(HashMap);
  while (1)
  {
    cur = iter->next(iter);
    if (cur == NULL)
      break;
    printf("%s=%d\n", cur->key, cur->value);
  }
  iter->del(iter);

  HashMap->del(HashMap);
  return 0;
}