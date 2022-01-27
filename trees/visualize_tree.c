#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define DEBUG false

// Node width must be even

int main(int argc, char **argv, char **envp)
{
    BST *root = BSTNode(0);
    int node_width;
    int len;
    int count = 0;
    int inputdata_n;
    char inputdata_a;
    char todo;
	char mode;

    if (argc < 4) {
        printf("Usage: %s [NODE WIDTH] [a|n] [ELEMENTS]\n", argv[0]);
        return 0;
    }

    len = strlen(argv[3]);
    node_width = atoi(argv[1]);

    if ((node_width % 2) != 0) {
        printf("NODE WIDTH must be even\n");
        return 0;
    }

    if (node_width < 4) {
        printf("NODE WIDTH must be at least 4\n");
        return 0;
    }

    if (argv[2][0] == 'a') {
        mode = 'a';
        for(int i = 0; i < len; i++) {
            if (argv[3][i] == ' ') continue;
            if (DEBUG) printf("Input [NODE_WIDTH: %d] [mode a] %c\n", node_width, argv[3][i]);
            if (!bst_insert(root, argv[3][i])) return -1;
        }
    }
    else if (argv[2][0] == 'n') {
        mode = 'n';
        for(int i = 0; i < len; i++) {
            if (argv[3][i] == ' ') {
                if (count > 0) {
                    argv[3][i] = '\0';
                    if (DEBUG) printf("Input [NODE_WIDTH: %d] [mode n] %d\n", node_width, atoi(argv[3]+i-count));
                    if (!bst_insert(root, atoi(argv[3]+i-count))) return -1;
                    count = 0;
                }
                continue;
            }
            if (len-i-1 == 0) {
                //argv[3][i+1] = '\0';
                if (DEBUG) printf("Input [NODE_WIDTH: %d] [mode n] %d\n", node_width, atoi(argv[3]+i-count));
                if (!bst_insert(root, atoi(argv[3]+i-count))) return -1;
            }
            count++;
        }
    } else {
        printf("Please enter a valid mode. [a|n]\n");
        return 0;
    }

    if (DEBUG) printf("Tree successfully generated\n");

    visualize_tree(root, root, node_width, mode);

    while(1) {
        printf("What would you like to do? [i]nsert [d]elete [e]xit: ");
        scanf("%c", &todo);
        fflush(stdin);
        if(todo == 'i') {
            printf("Enter data to be inserted: ");
            if (mode == 'a') {
                scanf("%c", &inputdata_a);
                fflush(stdin);
                bst_insert(root, inputdata_a);
            } else {
                scanf("%d", &inputdata_n);
                fflush(stdin);
                bst_insert(root, inputdata_n);
            }
            visualize_tree(root, root, node_width, mode);
        }
        else if (todo == 'd') {
            printf("Enter data to be deleted: ");
            if (mode == 'a') {
                scanf("%c", &inputdata_a);
                fflush(stdin);
                bst_delete(&root, inputdata_a);
            } else {
                scanf("%d", &inputdata_n);
                fflush(stdin);
                bst_delete(&root, inputdata_n);
            }
            if (root == NULL) {
                printf("Tree is empty. exiting...\n");
                break;
            }
            visualize_tree(root, root, node_width, mode);
        } else if (todo == 'e') {
            break;
        }
    }

    return 0;
}
