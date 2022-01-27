#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Node width must be even
#define NODE_WIDTH 14

int power(int base, int exponent) {
    int ret = base;
    if (exponent > 0) { // positive exponent
        for(int i = 1; i < exponent; i++) {
            ret *= base;
        }
    }
    else if (exponent < 0) { // negative exponent
        printf("DEBUG: power - base %d, exponent %d, result 0\n", base, exponent);
        return 0;
    } else { // exponent = 0
        printf("DEBUG: power - base %d, exponent %d, result 1\n", base, exponent);
        return 1;
    }
    printf("DEBUG: power - base %d, exponent %d, result %d\n", base, exponent, ret);
    return ret;
}

unsigned int gotoline(int line, int nodeheight, int rootheight, char *buffer) {
    printf("DEBUG: gotoline - line %d, nodeheight %d, rootheight %d\n", line, nodeheight, rootheight);
    unsigned int currentline = ((((power(2, rootheight-1)*NODE_WIDTH)+1)*(rootheight - nodeheight))*4)+(((power(2, rootheight-1)*NODE_WIDTH)+1)*line);
    //char *newline_pointer = strstr(buffer+currentline, "\n");
    /*
    if (newline_pointer != NULL) {
        //buffer[newline_pointer - buffer] = '.';
        printf("DEBUG: gotoline - newline found, index %u\n", (unsigned int)(newline_pointer - buffer));
        return newline_pointer - buffer;
    } else {
        printf("DEBUG: gotoline - currentline, index %u\n", currentline);
        return currentline;
    }*/
    return currentline;
}

unsigned int gotocolumn(int nodeheight) {
    int ret = (power(2, nodeheight-1)*NODE_WIDTH)/2;
    printf("DEBUG: gotocolumn - nodeheight %d, index %d\n", nodeheight, ret);
    return ret;
}

bool visualize_tree(BST *node, char *buffer, int rootheight) {
    printf("DEBUG: visualize_tree - start. NODE: %d\n", node->data);
    unsigned int start;
    unsigned int end;
    unsigned int temp;

    // line 1
    start = gotoline(0, node->height, rootheight, buffer);
    end = start + gotocolumn(node->height) - (NODE_WIDTH/2);
    /*
    printf("DEBUG: visualize_tree - line 1. pre-padding from start %d, to end %d\n", start, end);
    for(int i = start; i < end; i++) {
        buffer[i] = '.';
    }
    */
    /* --> print node here <-- */
    sprintf((buffer+end), "[%12d]", node->data);

    /*
    temp = start;
    start = end + NODE_WIDTH;
    end = temp + (power(2, node->height-1)*NODE_WIDTH);
    printf("DEBUG: visualize_tree - line 1. post-padding from start %d, to end %d\n", start, end);
    for(int i = start; i < end; i++) { // fill until the end of node line
        buffer[i] = '.';
    }
    if (start <= end) {
        buffer[end] = '\n';
    } else {
        buffer[end+1] = '\n';
    }
    */
    printf("DEBUG: visualize_tree - line 1 done\n");

    if (node->properties & 0b11) {
        // line 2
        start = gotoline(1, node->height, rootheight, buffer);
        end = start + gotocolumn(node->height) - 1;
        /*for (int i = start; i < end; i++) {
            buffer[i] = '.';
        }*/
        if (node->properties & 0b10) {  // Has left child
            buffer[end] = '|';
        } else {
            buffer[end] = '.';
        }
        if (node->properties & 0b01) {// Has right child
            buffer[end+1] = '|';
        } else {
            buffer[end+1] = '.';
        }
        /*
        temp = start;
        start = end + 2;
        end = temp + (power(2, node->height-1)*NODE_WIDTH);
        for(int i = start; i < end; i++) { // fill until the end of node line
            buffer[i] = '.';
        }
        buffer[end] = '\n';
        printf("DEBUG: visualize_tree - line 2 done\n");
        */
        // line 3
        start = gotoline(2, node->height, rootheight, buffer);
        end = start + gotocolumn(node->height-1);
        temp = start;
        /*for(int i = start; i < end; i++) {
            buffer[i] = '.';
        }*/
        start = end;
        end = temp + gotocolumn(node->height)-1;
        if (node->properties & 0b10) { // Has left child
            buffer[start] = '+';
            for(int i = start+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
        } /*else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }*/
        start = end + 1;
        end = start + gotocolumn(node->height-1)-1;
        if (node->properties & 0b01) { // Has right child
            buffer[start] = '+';
            for(int i = start+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
        } /*else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }
        start = end + 1;
        end = temp + (power(2, node->height-1)*NODE_WIDTH);
        for(int i = start; i < end; i++) { // fill until the end of node line
            buffer[i] = '.';
        }

        buffer[end] = '\n';
        printf("DEBUG: visualize_tree - line 3 done\n");
        */
        // line 4
        start = gotoline(3, node->height, rootheight, buffer);
        end = start + gotocolumn(node->height-1);
        temp = start;
        /*for(int i = start; i < end; i++) {
            buffer[i] = '.';
        }*/
        start = end;
        end = temp + gotocolumn(node->height)-1;
        if (node->properties & 0b10) { // Has left child
            buffer[start] = '|';
            /*for(int i = start+1; i <= end; i++) {
                buffer[i] = '.';
            }*/
        } /*else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }*/
        start = end + 1;
        end = start + gotocolumn(node->height-1)-1;
        if (node->properties & 0b01) { // Has right child
            /*for(int i = start; i < end; i++) {
                buffer[i] = '.';
            }*/
            buffer[end] = '|';
        } /*else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }
        start = end + 1;
        end = temp + (power(2, node->height-1)*NODE_WIDTH);
        for(int i = start; i < end; i++) { // fill until the end of node line
            buffer[i] = '.';
        }

        buffer[end] = '\n';
        printf("DEBUG: visualize_tree - line 4 done\n");*/
    }

    if (node->properties & 0b11) {
        if (node->left != NULL) {
            printf("DEBUG: visualize_tree - going left\n");
            visualize_tree(node->left, buffer, rootheight);
        }/* else {
            for(int i = 0; i < 4; i++) {
                start = gotoline(i, node->height-1, rootheight, buffer);
                end = start + gotocolumn(node->height);
                printf("DEBUG: visualize_tree - empty left sub-tree. pre-padding from start %d, to end %d\n", start, end);
                for(int j = start; j < end; j++) {
                    buffer[j] = '0' + node->data;
                }
                buffer[end] = '\n';
                printf("DEBUG: visualize_tree - empty left sub-tree padded\n");
            }
        }*/

        if (node->right != NULL) {
            printf("DEBUG: visualize_tree - going right\n");
            visualize_tree(node->right, buffer, rootheight);
        }/* else {
            for(int i = 0; i < 4; i++) {
                start = gotoline(i, node->height-1, rootheight, buffer);
                end = start + gotocolumn(node->height);
                printf("DEBUG: visualize_tree - empty left sub-tree. pre-padding from start %d, to end %d\n", start, end);
                for(int j = start; j < end; j++) {
                    buffer[j] = '0' + node->data;
                }
                buffer[end] = '\n';
                printf("DEBUG: visualize_tree - empty left sub-tree padded\n");
            }
        }*/
    }

    return true;
}

int main()
{
    FILE *of;
    char *buffer;
    size_t buffer_size;
    int linewidth;
    int lines;
    int arr[] = {5,4,3,2,1,6,7,8,9};
    // {5, 2, 1, 3};
    // {5, 2, 1, 3, 7, 6, 8};

    BST *root = BSTNode(arr[0]);

    for(int i = 1; i < 9; i++) {
        bst_insert(root, arr[i]);
    }

    linewidth = (power(2, root->height)*NODE_WIDTH)+1;
    lines = ((4*root->height)+1);
    buffer_size = linewidth*lines;
    buffer = (char*)malloc(buffer_size);

    // fill the buffer with spaces
    for(int i = 0; i < buffer_size; i++) {
        if (((i+1) % linewidth) == 0) {
            buffer[i] = '\n';
            continue;
        }
        buffer[i] = '.';
    }

    visualize_tree(root, buffer, root->height);

    of = fopen("tree.txt", "wb");

    fwrite(buffer, 1, linewidth*lines, of);
    fclose(of);

    return 0;
}


bool visualize_tree(BST *node, char *buffer, int rootheight) {
    printf("DEBUG: visualize_tree - start. NODE: %d\n", node->data);
    unsigned int start;
    unsigned int end;
    unsigned int temp;

    // line 1
    start = gotoline(0, node->height, rootheight, buffer);
    end = start + gotocolumn(node->height) - (NODE_WIDTH/2);
    printf("DEBUG: visualize_tree - line 1. pre-padding from start %d, to end %d\n", start, end);
    for(int i = start; i < end; i++) {
        buffer[i] = '.';
    }
    /* --> print node here <-- */
    sprintf((buffer+end), "[%12d]", node->data);

    temp = start;
    start = end + NODE_WIDTH;
    end = temp + (power(2, node->height-1)*NODE_WIDTH);
    printf("DEBUG: visualize_tree - line 1. post-padding from start %d, to end %d\n", start, end);
    for(int i = start; i < end; i++) { // fill until the end of node line
        buffer[i] = '.';
    }
    if (start <= end) {
        buffer[end] = '\n';
    } else {
        buffer[end+1] = '\n';
    }
    printf("DEBUG: visualize_tree - line 1 done\n");

    if (node->properties & 0b11) {
        // line 2
        start = gotoline(1, node->height, rootheight, buffer);
        end = start + gotocolumn(node->height) - 1;
        for (int i = start; i < end; i++) {
            buffer[i] = '.';
        }
        if (node->properties & 0b10) {  // Has left child
            buffer[end] = '|';
        } else {
            buffer[end] = '.';
        }
        if (node->properties & 0b01) {// Has right child
            buffer[end+1] = '|';
        } else {
            buffer[end+1] = '.';
        }

        temp = start;
        start = end + 2;
        end = temp + (power(2, node->height-1)*NODE_WIDTH);
        for(int i = start; i < end; i++) { // fill until the end of node line
            buffer[i] = '.';
        }
        buffer[end] = '\n';
        printf("DEBUG: visualize_tree - line 2 done\n");

        // line 3
        start = gotoline(2, node->height, rootheight, buffer);
        end = start + gotocolumn(node->height-1);
        temp = start;
        for(int i = start; i < end; i++) {
            buffer[i] = '.';
        }
        start = end;
        end = temp + gotocolumn(node->height)-1;
        if (node->properties & 0b10) { // Has left child
            buffer[start] = '+';
            for(int i = start+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
        } else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }
        start = end + 1;
        end = start + gotocolumn(node->height-1)-1;
        if (node->properties & 0b01) { // Has right child
            buffer[start] = '+';
            for(int i = start+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
        } else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }
        start = end + 1;
        end = temp + (power(2, node->height-1)*NODE_WIDTH);
        for(int i = start; i < end; i++) { // fill until the end of node line
            buffer[i] = '.';
        }

        buffer[end] = '\n';
        printf("DEBUG: visualize_tree - line 3 done\n");

        // line 4
        start = gotoline(3, node->height, rootheight, buffer);
        end = start + gotocolumn(node->height-1);
        temp = start;
        for(int i = start; i < end; i++) {
            buffer[i] = '.';
        }
        start = end;
        end = temp + gotocolumn(node->height)-1;
        if (node->properties & 0b10) { // Has left child
            buffer[start] = '|';
            for(int i = start+1; i <= end; i++) {
                buffer[i] = '.';
            }
        } else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }
        start = end + 1;
        end = start + gotocolumn(node->height-1)-1;
        if (node->properties & 0b01) { // Has right child
            for(int i = start; i < end; i++) {
                buffer[i] = '.';
            }
            buffer[end] = '|';
        } else {
            for(int i = start; i <= end; i++) {
                buffer[i] = '.';
            }
        }
        start = end + 1;
        end = temp + (power(2, node->height-1)*NODE_WIDTH);
        for(int i = start; i < end; i++) { // fill until the end of node line
            buffer[i] = '.';
        }

        buffer[end] = '\n';
        printf("DEBUG: visualize_tree - line 4 done\n");
    }

    if (node->properties & 0b11) {
        if (node->left != NULL) {
            printf("DEBUG: visualize_tree - going left\n");
            visualize_tree(node->left, buffer, rootheight);
        } else {
            for(int i = 0; i < 4; i++) {
                start = gotoline(i, node->height-1, rootheight, buffer);
                end = start + /*(*/gotocolumn(node->height)/*(power(2, (rootheight-node->height+1))-1))*/;
                printf("DEBUG: visualize_tree - empty left sub-tree. pre-padding from start %d, to end %d\n", start, end);
                for(int j = start; j < end; j++) {
                    buffer[j] = '0' + node->data;
                }
                buffer[end] = '\n';
                printf("DEBUG: visualize_tree - empty left sub-tree padded\n");
            }
        }

        if (node->right != NULL) {
            printf("DEBUG: visualize_tree - going right\n");
            visualize_tree(node->right, buffer, rootheight);
        } else {
            for(int i = 0; i < 4; i++) {
                start = gotoline(i, node->height-1, rootheight, buffer);
                end = start + /*(*/gotocolumn(node->height)/*(power(2, (rootheight-node->height+1))-1))*/;
                printf("DEBUG: visualize_tree - empty left sub-tree. pre-padding from start %d, to end %d\n", start, end);
                for(int j = start; j < end; j++) {
                    buffer[j] = '0' + node->data;
                }
                buffer[end] = '\n';
                printf("DEBUG: visualize_tree - empty left sub-tree padded\n");
            }
        }
    }

    return true;
}
