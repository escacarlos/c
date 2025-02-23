#include <glib.h>
#include <stdio.h>

void print_list(GList *list) {
    for (GList *l = list; l != NULL; l = l->next) {
        g_print("%s <-> ", (char *)l->data);
    }
    g_print("NULL\n");
}

int main() {
    GList *list = NULL;

    list = g_list_append(list, "Apple");
    list = g_list_append(list, "Banana");
    list = g_list_append(list, "Cherry");

    print_list(list);

    list = g_list_remove(list, "Banana");
    print_list(list);

    g_list_free(list);
    return 0;
}
