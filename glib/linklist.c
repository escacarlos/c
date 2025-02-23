#include <glib.h>
#include <stdio.h>

void print_slist(GSList *list) {
  for (GSList *l = list; l != NULL; l = l->next) {
    g_print("%s -> ", (char *)l->data);
  }
  g_print("NULL\n");
}

int main() {
  GSList *list = NULL;
  
  list = g_slist_append(list, "One");
  list = g_slist_append(list, "Two");
  list = g_slist_append(list, "Three");
  
  print_slist(list);
  
  list = g_slist_remove(list, "Two");
  print_slist(list);
  
  g_slist_free(list);
  return 0;
}
