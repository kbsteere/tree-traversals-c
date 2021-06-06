// description: performs a traversal of a binary tree without recursion using the stack

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct tree_node
{
    int data;
    struct tree_node *left;
    struct tree_node *right;
} tree_node_t;

typedef struct stack_node
{
    struct tree_node *t;
    struct stack_node *next;

} stack_node_t;

// stack functions
void Push(stack_node_t **top_ref, tree_node_t *t);
tree_node_t *Pop(stack_node_t **top_ref);
bool IsEmpty(stack_node_t *top);

static void InOrder(tree_node_t *root)
{
    if (root != NULL)
    {
        tree_node_t *current = root;
        stack_node_t *s = NULL;
        bool done = 0;

        while (!done)
        {
            if (current != NULL) // check left most tree_node of the currnt tree_node
            {
                Push(&s, current); // push pointer to a tree node on the stack before traversing the node's left subtree
                current = current->left;
            }
            else
            {
                if (!IsEmpty(s))
                {
                    current = Pop(&s);
                    printf("%d ", current->data);
                    current = current->right;
                }
                else
                {
                    done = 1;
                }
            }
        }
    }
    else
    {
        perror("Error: *root parameter was NULL");
    }
}

void Push(stack_node_t **top_ref, tree_node_t *t)
{
    if (top_ref != NULL && t != NULL)
    {
        stack_node_t *new_tree_node = (stack_node_t *)malloc(sizeof(stack_node_t));

        if (new_tree_node == NULL)
        {
            printf("stack overflow\n");
            getchar();
            exit(0);
        }

        new_tree_node->t = t; // put data in new_tree_node;
        new_tree_node->next = (*top_ref); // link the old list of the new_tree_node
        (*top_ref) = new_tree_node; // move the head to point to the new_tree_node
    }
    else
    {
        perror("Error: **top_ref or *t are NULL");
    }
}

bool IsEmpty(stack_node_t *top)
{
    return (top == NULL) ? 1 : 0;
}

tree_node_t *Pop(stack_node_t **top_ref)
{
    if(IsEmpty(*top_ref))
    {
        printf("stack underflow\n");
        getchar();
        exit(0);
    }

    stack_node_t *top = (*top_ref);    
    tree_node_t *res = top->t;
    (*top_ref) = top->next;
    return res;
}

static tree_node_t *NewTreeNode(int data)
{
    tree_node_t *new_tree_node = (tree_node_t*)malloc(sizeof(tree_node_t));
    
    new_tree_node->data = data;
    new_tree_node->left = NULL;
    new_tree_node->right = NULL;

    return(new_tree_node);
}

static void PrintTree(tree_node_t *tree)
{
    printf("\n\n Tree Diagram\n");
    printf("     %d\n", tree->data);
    printf("    %c %c\n", 0x2f, 0x5c);
    printf("   %d   %d\n", tree->left->data, tree->right->data);
    printf(" %c  %c\n", 0x2f, 0x5c);
    printf("%d    %d\n", tree->left->left->data, tree->left->right->data);
}

int main(int argc, char **argv)
{
    tree_node_t *root = NewTreeNode(1);
    root->left = NewTreeNode(2);
    root->right = NewTreeNode(3);
    root->left->left = NewTreeNode(4);
    root->left->right = NewTreeNode(5);

    InOrder(root);
    PrintTree(root);
    
    free(root);
    return (0);
};