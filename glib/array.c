#include <glib.h>
#include <stdio.h>

void print_array(GArray *arr) {
    for (guint i = 0; i < arr->len; i++) {
        g_print("%d ", g_array_index(arr, int, i));
    }
    g_print("\n");
}

int main() {
    GArray *arr = g_array_new(FALSE, FALSE, sizeof(int));

    int values[] = {10, 20, 30, 40, 50};
    g_array_append_vals(arr, values, 5);

    print_array(arr);

    int new_val = 99;
    g_array_insert_val(arr, 2, new_val);
    print_array(arr);

    g_array_free(arr, TRUE);
    return 0;
}
