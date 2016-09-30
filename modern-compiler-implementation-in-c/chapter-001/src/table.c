#include <stdlib.h>
#include "table.h"

void ns_init() {
    namespace = (table)malloc(sizeof(*namespace));
    namespace->head = NULL;
}
void ns_set(char * const name, int value) {
    table_node node = (table_node)malloc(sizeof(*node));
    node->name = name;
    node->value = value;
    node->next  = namespace->head;
    namespace->head = node;
}

int ns_get(const char *name) {
    table_node node = namespace->head;
    while (node != NULL) {
        if (strcmp(node->name, name) == 0) {
            return node->value;
        }
    }

    return 0;
}
