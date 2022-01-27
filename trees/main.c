#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

// Node width must be even
#define NODE_WIDTH 4
#define DEBUG true

int linewidth;
int lines;

int power(int base, int exponent) {
    int ret = base;
    if (exponent > 0) { // positive exponent
        for(int i = 1; i < exponent; i++) {
            ret *= base;
        }
    }
    else if (exponent < 0) { // negative exponent
        if (DEBUG) printf("DEBUG: power - base %d, exponent %d, result 0\n", base, exponent);
        return 0;
    } else { // exponent = 0
        if (DEBUG) printf("DEBUG: power - base %d, exponent %d, result 1\n", base, exponent);
        return 1;
    }
    if (DEBUG) printf("DEBUG: power - base %d, exponent %d, result %d\n", base, exponent, ret);
    return ret;
}

unsigned int gotoline(int line, int nodelevel, BST *root, char *buffer) {
    int diff = nodelevel-root->level;
    if ((nodelevel == root->height) && (line > 0)) {
        return -1;
    }
    unsigned int actual_line = (linewidth*4*(diff))+(linewidth*line);
    char *marker = strstr(buffer+actual_line, "*");
    if (marker != NULL) {
        return marker-buffer;
    }
    return actual_line;
}

unsigned int gotocolumn(int nodelevel) {
    unsigned int ret = (linewidth-1)/power(2, nodelevel);
    if (DEBUG) printf("DEBUG: gotocolumn - nodelevel %d, index %d\n", nodelevel, ret);
    return ret;
}

bool add_padding(BST *node, BST *root, char *buffer, int line) {
    int diff;
    int caret;

    diff = root->height - node->level;

    if (node->properties & 0b11) { // NOT a leaf
        switch(diff) {
        case 0:
            return false;
        case 1:
            caret = gotoline(line, node->level+1, root, buffer);
            if (caret == -1) return false;
            buffer[caret] = ' ';
            caret += gotocolumn(node->level);
            buffer[caret] = '*';
            break;
        default: // NOT a leaf node but more than one level higher than deepest node
            for(int i = 1; i <= diff; i++) {
                caret = gotoline(line, node->level+i, root, buffer);
                if (caret == -1) return false;
                buffer[caret] = ' ';
                caret += gotocolumn(node->level);
                buffer[caret] = '*';
            }
            break;
        }
    } else { // a leaf node
        switch(diff) {
        case 0:
            return false;
        case 1:
            caret = gotoline(line, node->level+1, root, buffer);
            if (caret == -1) return false;
            buffer[caret] = ' ';
            caret += gotocolumn(node->level);
            buffer[caret] = '*';
            break;
        default: // a leaf node but more than one level higher than deepest node
            for(int i = 1; i <= diff; i++) {
                caret = gotoline(line, node->level+i, root, buffer);
                if (caret == -1) return false;
                buffer[caret] = ' ';
                caret += gotocolumn(node->level);
                buffer[caret] = '*';
            }
            break;
        }
    }
    return true;
}

bool visualize_tree(BST *node, BST *root, char *buffer) {
    int ret;
    int line;
    int column;
    int caret;
    int offset;
    int end;

    if (node->left != NULL) {
        visualize_tree(node->left, root, buffer);
    } else {
        add_padding(node, root, buffer, 0);
        add_padding(node, root, buffer, 1);
        add_padding(node, root, buffer, 2);
        add_padding(node, root, buffer, 3);
    }

    if (node->right != NULL) {
        visualize_tree(node->right, root, buffer);
    } else {
        add_padding(node, root, buffer, 0);
        add_padding(node, root, buffer, 1);
        add_padding(node, root, buffer, 2);
        add_padding(node, root, buffer, 3);
    }

    // line 1
    //for(int i = 0; i < 4; i++) {
    line = gotoline(0, node->level, root, buffer);
    //if (line == -1) break;
    buffer[line] = ' ';
    column = gotocolumn(node->level);
    caret = line + column - (NODE_WIDTH/2);
    printf("DEBUG: visualize_tree - node %d, line 1, caret %d\n", node->data, caret);
    ret = sprintf(buffer+caret, "[%2c]", node->data);
    buffer[caret+ret] = ' ';
    buffer[line+(2*column)] = '*'; //marker
    //}

    if (node->level != root->height) {
        //line 2
        line = gotoline(1, node->level, root, buffer);
        buffer[line] = ' ';
        column = gotocolumn(node->level);
        caret = line + column;
        printf("DEBUG: visualize_tree - node %d, line 2, caret %d\n", node->data, caret);
        switch(node->properties & 0b11) {
        case 0b00:
            printf("DEBUG: visualize_tree - node %d, line 2, caret %d, no child\n", node->data, caret);
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b10:
            printf("DEBUG: visualize_tree - node %d, line 2, caret %d, left child\n", node->data, caret);
            buffer[caret-1] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b01:
            printf("DEBUG: visualize_tree - node %d, line 2, caret %d, right child\n", node->data, caret);
            buffer[caret] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b11:
            printf("DEBUG: visualize_tree - node %d, line 2, caret %d, two children\n", node->data, caret);
            buffer[caret] = '|';
            buffer[caret-1] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        }

        //line 3
        line = gotoline(2, node->level, root, buffer);
        buffer[line] = ' ';
        column = gotocolumn(node->level);
        offset = gotocolumn(node->level+1);
        printf("DEBUG: visualize_tree - node %d, line 3, caret %d\n", node->data, caret);
        switch(node->properties & 0b11) {
        case 0b00:
            printf("DEBUG: visualize_tree - node %d, line 3, caret %d, no child\n", node->data, caret);
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b10:
            caret = line + column - offset;
            end = line + column - 1;
            printf("DEBUG: visualize_tree - node %d, line 3, caret %d, left child\n", node->data, caret);
            buffer[caret] = '+';
            for(int i = caret+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b01:
            caret = line + column;
            end = line + column + offset - 1;
            printf("DEBUG: visualize_tree - node %d, line 3, caret %d, right child\n", node->data, caret);
            buffer[caret] = '+';
            for(int i = caret+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b11:
            caret = line + column - offset;
            end = line + column - 1;
            printf("DEBUG: visualize_tree - node %d, line 3, caret %d, two children\n", node->data, caret);
            buffer[caret] = '+';
            for(int i = caret+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
            caret = line + column;
            end = line + column + offset - 1;
            buffer[caret] = '+';
            for(int i = caret+1; i < end; i++) {
                buffer[i] = '-';
            }
            buffer[end] = '+';
            buffer[line+(2*column)] = '*'; //marker
            break;
        }

        //line 4
        line = gotoline(3, node->level, root, buffer);
        buffer[line] = ' ';
        column = gotocolumn(node->level);
        offset = gotocolumn(node->level+1);
        printf("DEBUG: visualize_tree - node %d, line 4, caret %d\n", node->data, caret);
        switch(node->properties & 0b11) {
        case 0b00:
            printf("DEBUG: visualize_tree - node %d, line 4, caret %d, no child\n", node->data, caret);
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b10:
            caret = line + column - offset;
            printf("DEBUG: visualize_tree - node %d, line 4, caret %d, left child\n", node->data, caret);
            buffer[caret] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b01:
            caret = line + column + offset - 1;
            printf("DEBUG: visualize_tree - node %d, line 4, caret %d, right child\n", node->data, caret);
            buffer[caret] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b11:
            caret = line + column;
            printf("DEBUG: visualize_tree - node %d, line 4, caret %d, two children\n", node->data, caret);
            buffer[caret-offset] = '|';
            buffer[caret+offset-1] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        }
    }

    return true;
}

int main()
{
    FILE *of;
    char *buffer;
    size_t buffer_size;
    int arr[] = {'S','U','N','F','L','O','W','E','R'};
    //
    // {7, 3, 1, 0, 2, 5, 4, 6, 11, 9, 8, 10, 13, 12, 14};
    // {5, 2, 1};
    // {5, 2, 1, 3, 7, 6, 8};

    BST *root = BSTNode(arr[0]);

    for(int i = 1; i < 9; i++) {
        bst_insert(root, arr[i]);
    }

    linewidth = (power(2, root->height-1)*NODE_WIDTH)+1;
    lines = (4*(root->height-1))+1;
    buffer_size = linewidth*lines;
    buffer = (char*)malloc(buffer_size);

    // fill the buffer with spaces
    for(int i = 0; i < buffer_size; i++) {
        if (((i+1) % linewidth) == 0) {
            buffer[i] = '\0'; // set line-ends to null
            continue;
        }
        buffer[i] = ' ';
    }

    visualize_tree(root, root, buffer);

    for(int i = linewidth-1; i < buffer_size; i += linewidth) {
        buffer[i] = '\n';  // set line-ends to newline
    }

    of = fopen("tree.txt", "wb");

    fwrite(buffer, 1, linewidth*lines, of);
    fclose(of);

    return 0;
}
