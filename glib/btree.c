#include <glib.h>
#include <stdio.h>

gint compare_ints(gconstpointer a, gconstpointer b) {
    return *(const int *)a - *(const int *)b;
}

gint print_tree(gpointer key, gpointer value, gpointer data) {
    g_print("%d -> %s\n", *(int *)key, (char *)value);
    return FALSE;  // Return FALSE to continue traversal (TRUE would stop it)
}

int main() {
    GTree *tree = g_tree_new(compare_ints);

    int k1 = 30, k2 = 10, k3 = 20, k4 = 40;
    g_tree_insert(tree, &k1, "Thirty");
    g_tree_insert(tree, &k2, "Ten");
    g_tree_insert(tree, &k3, "Twenty");
    g_tree_insert(tree, &k4, "Forty");

    g_tree_foreach(tree, print_tree, NULL);

    g_tree_destroy(tree);
    return 0;
}

