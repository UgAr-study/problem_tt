#include <stdio.h>
#include <stdlib.h>
#include <search.h>

struct tree_node {
    struct tree_node *left;
    struct tree_node *right;
    int data;
};

int search (int* inorder, int elem) {
    int pos = 0;
    while (inorder[pos] != elem)
        pos++;
    return pos;
}

struct tree_node* create (int data) {
    struct tree_node *res;
    res = (struct tree_node*) calloc (1, sizeof(struct tree_node));
    res->data = data;
    return res;
}

int recover (struct tree_node *tree, int *preorder, int *inorder, int len) {
    static int i = 0;
    int top;
    if (len == 0) {
        --i;
        return -1;
    }

    if (len == 1)
        return preorder[i];

    top = search (inorder, preorder[i] );
    i++;
    tree->left = (struct tree_node*) calloc (1, sizeof(struct tree_node));
    tree->left->data = recover (tree->left, preorder, inorder, top);
    i++;
    tree->right = (struct tree_node*) calloc (1, sizeof(struct tree_node));
    tree->right->data = recover (tree->right, preorder, inorder + top + 1, len - top - 1);

    return inorder[top];
}

void print (struct tree_node *tree) {

    if (tree->right == NULL && tree->left == NULL)
        return;

    printf ("%d %d %d\n", tree->data, tree->left->data, tree->right->data);
    print (tree->left);
    print (tree->right);
}

void delete (struct tree_node* tree) {

    if (tree->left == NULL && tree->right == NULL)
        return;

    delete (tree->left);
    free (tree->left);
    delete (tree->right);
    free (tree->right);
}

int main() {
    int i, len, *preorder, *inorder;
    struct tree_node* tree;
    tree = (struct tree_node*) calloc (1, sizeof(struct tree_node));

    scanf("%d", &len);
    preorder = (int*) calloc (len, sizeof(int));
    inorder = (int*) calloc(len, sizeof(int));

    for (i = 0; i < len; ++i)
        scanf("%d", preorder + i);
    for (i = 0; i < len; ++i)
        scanf("%d", inorder + i);

    tree->data = recover (tree, preorder, inorder, len);

    printf("%d\n", len);
    print (tree);
    delete(tree);
    return 0;
}
