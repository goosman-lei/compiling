typedef struct _table_node *table_node;
typedef struct _table *table;

struct _table {
    table_node head;
};

struct _table_node {
    char *name;
    int value;
    table_node next;
};

table namespace;

void ns_init();
void ns_set(char * const name, int value);
int ns_get(const char *name);
