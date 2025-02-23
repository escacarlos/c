#include <glib.h>
#include <stdio.h>

int main() {
    GHashTable *hash = g_hash_table_new(g_str_hash, g_str_equal);

    g_hash_table_insert(hash, "Alice", "Engineer");
    g_hash_table_insert(hash, "Bob", "Doctor");
    g_hash_table_insert(hash, "Charlie", "Artist");

    g_print("Alice: %s\n", (char *)g_hash_table_lookup(hash, "Alice"));
    g_print("Bob: %s\n", (char *)g_hash_table_lookup(hash, "Bob"));

    g_hash_table_remove(hash, "Alice");

    if (!g_hash_table_contains(hash, "Alice")) {
        g_print("Alice removed\n");
    }

    g_hash_table_destroy(hash);
    return 0;
}

