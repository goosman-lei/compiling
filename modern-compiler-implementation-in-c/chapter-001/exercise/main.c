#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef char *string;
string String(char *);

typedef char bool;
#define TRUE 1
#define FALSE 0

typedef struct tree *T_tree;
struct tree {
    T_tree left;
    string key;
    T_tree right;
};


void *checked_malloc(int);
T_tree Tree(T_tree, string, T_tree);
T_tree insert(string, T_tree);
int member(string, T_tree);
void front_iterate(T_tree, int);

int main(int argc, char **argv) {
    T_tree t = NULL;
    t = insert("a", t);
    t = insert("b", t);
    t = insert("c", t);
    t = insert("d", t);
    t = insert("e", t);
    t = insert("f", t);
    t = insert("g", t);
    t = insert("h", t);
    t = insert("i", t);

    front_iterate(t, 1);

    printf("member(d) return: %d\n", member("d", t));
    printf("member(x) return: %d\n", member("x", t));
    return 0;
}

T_tree Tree(T_tree l, string k, T_tree r) {
    T_tree t = checked_malloc(sizeof(*t));
    t->left  = l;
    t->key   = k;
    t->right = r;
    return t;
}

T_tree insert(string key, T_tree t) {
    if (t == NULL)
        return Tree(NULL, key, NULL);
    else if (strcmp(key, t->key) < 0)
        return Tree(insert(key, t->left), t->key, t->right);
    else if (strcmp(key, t->key) > 0)
        return Tree(t->left, t->key, insert(key, t->right));
    else
        return Tree(t->left, key, t->right); // 已存在相同key则直接忽略掉
}

int member(string k, T_tree t) {
    if (t == NULL)
        return 0;
    else if (strcmp(k, t->key) < 0)
        return member(k, t->left);
    else if (strcmp(k, t->key) > 0)
        return member(k, t->right);
    else
        return 1;
}

void front_iterate(T_tree t, int level) {
    if (t == NULL)
        return ;
    front_iterate(t->left, level + 1);
    printf("(%s %d)\n", t->key, level);
    front_iterate(t->right, level + 1);
}


void *checked_malloc(int len) {
    void *p = malloc(len);
    assert(p);
    return p;
}