#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

#define DEBUG false

// Node width must be even

int getelements(char **argv, BST **root) {
    int node_width = 4;
    int count = 0;
    int len = strlen(argv[2]);
    if (argv[1][0] == 'a') {
        for(int i = 0; i < len; i++) {
            if (argv[2][i] == ' ') continue;
            if (DEBUG) printf("Input [mode a] %c\n", argv[2][i]);
            avl_insert(root, argv[2][i]);
        }
    }
    else if (argv[1][0] == 'n') {
        for(int i = 0; i < len; i++) {
            if (argv[2][i] == ' ') {
                if (count > 0) {
                    argv[2][i] = '\0';
                    if (DEBUG) printf("Input [mode n] %d\n", atoi(argv[2]+i-count));
                    avl_insert(root, atoi(argv[2]+i-count));
                    if (count > node_width) node_width = count;
                    count = 0;
                }
                continue;
            }
            if (len-i-1 == 0) {
                if (DEBUG) printf("Input [mode n] %d\n", atoi(argv[2]+i-count));
                avl_insert(root, atoi(argv[2]+i-count));
                if (count > node_width) node_width = count;
            }
            count++;
        }
    }
    return node_width + (node_width % 2);
}

int getsequence(char **argv, BST **root) {
    int node_width = 4;
    int count = 0;
    int isdeletion = 0;
    int len = strlen(argv[2]);

    set_node_width(node_width);
    set_mode(argv[1][0]);

    if (argv[1][0] == 'a') {
        for(int i = 0; i < len; i++) {
            if (argv[2][i] == ' ') continue;
            if (argv[2][i] == '*') {
                isdeletion = 1;
                continue;
            }
            if (isdeletion) {
                if (argv[2][i] == ' ') continue;
                if (avl_delete(root, argv[2][i])) {
                    if (DEBUG) printf("Input [mode a] %c\n", argv[2][i]);
                    printf("Delete: %c\n", argv[2][i]);
                    visualize_tree(*root, *root, node_width, 'a');
                    puts("");
                    isdeletion = 0;
                }
            } else {
                avl_insert(root, argv[2][i]);
                if (DEBUG) printf("Input [mode a] %c\n", argv[2][i]);
                printf("Insert: %c\n", argv[2][i]);
                visualize_tree(*root, *root, node_width, 'a');
                puts("");
            }
        }
    }
    else if (argv[1][0] == 'n') {
        for(int i = 0; i < len; i++) {
            if (argv[2][i] == '*') {
                isdeletion = 1;
                continue;
            }
            if (argv[2][i] == ' ') {
                if (count > 0) {
                    argv[2][i] = '\0';
                    if (count > node_width) node_width = count;
                    set_node_width(node_width);
                    if (isdeletion) {
                        if (avl_delete(root, atoi(argv[2]+i-count))) {
                            if (DEBUG) printf("Input [mode n] %d\n", atoi(argv[2]+i-count));
                            printf("Delete: %d\n", atoi(argv[2]+i-count));
                            visualize_tree(*root, *root, node_width, 'n');
                            puts("");
                            isdeletion = 0;
                        }
                    } else {
                        avl_insert(root, atoi(argv[2]+i-count));
                        if (DEBUG) printf("Input [mode n] %d\n", atoi(argv[2]+i-count));
                        printf("Insert: %d\n", atoi(argv[2]+i-count));
                        visualize_tree(*root, *root, node_width, 'n');
                        puts("");
                    }
                    count = 0;
                }
                continue;
            }
            if (len-i-1 == 0) {
                if (DEBUG) printf("Input [mode n] %d\n", atoi(argv[2]+i-count));
                if (isdeletion) {
                    if (avl_delete(root, atoi(argv[2]+i-count))) {
                        if (DEBUG) printf("Input [mode n] %d\n", atoi(argv[2]+i-count));
                        printf("Delete: %d\n", atoi(argv[2]+i-count));
                        visualize_tree(*root, *root, node_width, 'n');
                        puts("");
                        isdeletion = 0;
                    }
                } else {
                    if (count > node_width) node_width = count;
                    set_node_width(node_width);
                    avl_insert(root, atoi(argv[2]+i-count));
                    if (DEBUG) printf("Input [mode n] %d\n", atoi(argv[2]+i-count));
                    printf("Insert: %d\n", atoi(argv[2]+i-count));
                    visualize_tree(*root, *root, node_width, 'n');
                    puts("");
                }
            }
            count++;
        }
    }
    return node_width + (node_width % 2);
}

int main(int argc, char **argv, char **envp)
{
    BST *root = NULL;
    int node_width;
    int inputdata_n;
    int issequence;
    char inputdata_a;
    char todo;
	char mode = 0;

    if (argc < 3) {
        printf("Usage: %s [a|n] [ELEMENTS|SEQUENCE]\n", argv[0]);
        puts(" mode:");
        puts(" a\taphabetic input data");
        puts(" n\tnumeric input data\n");
        puts(" ELEMENTS:");
        puts("\ta series of alphabetic or space-separated numeric data");
        puts("\tto be inserted in a tree.");
        puts("\tmanual insertion and deletion can be done afterwards.\n");
        puts(" SEQUENCE:");
        puts("\ta series of alphabetic or space-separated numeric data insertion and deletion.");
        puts("\tdata without a prepended asterisk (*) is insertion.");
        puts("\tdata with a prepended asterisk (*) is deletion.");
        puts("\tExample: BAC*A*C*B (Insert B,A, and C. Delete A, delete C, delete B.)");
        puts("\tExample: 2 1 3 *1 *3 *2 (Insert 2,1, and 3. Delete 1, delete 3, delete 2.)");
        return 0;
    }

    if (argv[1][0] == 'a') {
        mode = 'a';
    } else if (argv[1][0] == 'n') {
        mode = 'n';
    } else {
        puts("Invalid mode. [a|n]");
        return 0;
    }

    issequence = !(strstr(argv[2], "*") == NULL);

    if (issequence) {
        getsequence(argv, &root);
        return 0;
    } else {
        node_width = getelements(argv, &root);
    }

    set_node_width(node_width);
    set_mode(mode);

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
                avl_insert(&root, inputdata_a);
            } else {
                scanf("%d", &inputdata_n);
                fflush(stdin);
                avl_insert(&root, inputdata_n);
            }
            visualize_tree(root, root, node_width, mode);
        }
        else if (todo == 'd') {
            printf("Enter data to be deleted: ");
            if (mode == 'a') {
                scanf("%c", &inputdata_a);
                fflush(stdin);
                avl_delete(&root, inputdata_a);
            } else {
                scanf("%d", &inputdata_n);
                fflush(stdin);
                avl_delete(&root, inputdata_n);
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
