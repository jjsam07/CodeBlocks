#ifndef TREE_H_
#define TREE_H_

#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define DEBUG_LIB_DELETE false
#define DEBUG_DECREASE_LEVEL false
#define DEBUG_SET_LEVEL false
#define DEBUG_UPDATE_HEIGHT false
#define DEBUG_ROTATION false
#define DEBUG_LIB_VISUALIZE false
#define DEBUG_OTHER false

int node_width;
char mode;

typedef struct bst_node {
    int data;
    int height;
    int level;
    int properties; // 0b00     Node has no children (leaf node)
                    // 0b01     Node has right child
                    // 0b10     Node has left child
                    // 0b11     Node has two children
                    // 0b1000   Node is a left child
                    // 0b0100   Node is a right child
    struct bst_node *parent;
    struct bst_node *left;
    struct bst_node *right;
} BST;

bool visualize_tree(BST *, BST *, int, char);
bool left_rotation(BST *);
bool bst_update_height(BST *);
bool bst_set_level(BST *, int );

bool print_debug(BST *node, char *str) {
    char temp[2] = {node->data, 0};

    printf("DEBUG: node [%d] [%s] [%c%c%c%c%c] [H: %d] [L: %d] - %s", node->data,
                                                                            isprint(node->data) ? temp : "null",
                                                                            (node->properties & 0b10000) ? '1' : '0',
                                                                            (node->properties & 0b01000) ? '1' : '0',
                                                                            (node->properties & 0b00100) ? '1' : '0',
                                                                            (node->properties & 0b00010) ? '1' : '0',
                                                                            (node->properties & 0b00001) ? '1' : '0',
                                                                            node->height,
                                                                            node->level, str);
    return true;
}

BST *BSTNode(int indata) {
    BST *ret = (BST*)malloc(sizeof(BST));
    ret->data = indata;
    ret->height = 1;
    ret->level = 1;
    ret->properties = 0;
    ret->parent = NULL;
    ret->left = NULL;
    ret->right = NULL;

    return ret;
}

BST *BSTMax(BST *node) {
    if (node->right != NULL) {
        return BSTMax(node->right);
    } else {
        return node;
    }

    return NULL;
}

BST *BSTMin(BST *node) {
    if (node->left != NULL) {
        return BSTMax(node->left);
    } else {
        return node;
    }

    return NULL;
}

bool right_rotation(BST *root) {
    int nodelevel = root->level;
    printf("Before right-rotation on [%d] [%s]\n", root->data, isprint(root->data) ? (char[2]){root->data, '\0'} : "null");
    bst_set_level(root, 1);
    visualize_tree(root, root, node_width, mode);
    puts("");
    bst_set_level(root, nodelevel);

    /************************************************************/
    if (DEBUG_ROTATION) printf("DEBUG: right_rotation - node [%d] [%s] | ", root->data, isprint(root->data) ? (char[2]){root->data, '\0'} : "null");
    if (DEBUG_ROTATION) printf("parent [%d] [%s]\n", root->parent->data, isprint(root->parent->data) ? (char[2]){root->parent->data, '\0'} : "null");
    BST *child = root->left;
    int oldproperties;
    if (!(root->properties & 0b10000)) {
        switch(child->properties & 0b11) {
            case 0b01:
                if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b01\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                child->properties |= 0b10000;
                left_rotation(child);
                child = root->left;
                if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b01\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                break;
            case 0b11:
                if (child->right->height > child->left->height) {
                    if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b11\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                    child->properties |= 0b10000;
                    left_rotation(child);
                    child = root->left;
                    if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b11\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                }
                break;
        }
    }
    root->properties &= 0b01111;

    if (child->right != NULL) {
        oldproperties = child->right->properties;
        child->right->properties = (oldproperties ^ 0b1100) & 0b1100;
        child->right->properties |= (oldproperties & 0b0011);
        child->right->parent = root;
        if (DEBUG_ROTATION) printf("DEBUG: child properties updated\n");
    } else {
        root->properties &= 0b1101;
        child->properties |= 0b01;
    }
    root->left = child->right;
    child->right = root;
    child->parent = root->parent;
    if ((root->properties & 0b1100) == 0b1000) {
        root->parent->left = child;
        root->parent = child;
        oldproperties = root->properties;
        root->properties = (oldproperties ^ 0b1100) & 0b1100;
        root->properties |= (oldproperties & 0b0011);
        bst_update_height(child->parent);
        if (DEBUG_ROTATION) printf("DEBUG: root properties updated\n");
    }
    else if ((root->properties & 0b1100) == 0b0100) {
        root->parent->right = child;
        root->parent = child;
        oldproperties = child->properties;
        child->properties = (oldproperties ^ 0b1100) & 0b1100;
        child->properties |= (oldproperties & 0b0011);
        bst_update_height(child->parent);
    }
    else if ((root->properties & 0b1100) == 0b0000) {
        *(BST **)root->parent = child;
        root->parent = child;
        root->properties |= 0b0100;
        child->properties &= 0b0011;
        bst_update_height(child);
    }
    bst_set_level(child, root->level);
    if (DEBUG_ROTATION) printf("DEBUG: right_rotation - done\n");
    /************************************************************/


    nodelevel = child->level;
    printf("After right-rotation on [%d] [%s]\n", root->data, isprint(root->data) ? (char[2]){root->data, '\0'} : "null");
    bst_set_level(child, 1);
    visualize_tree(child, child, node_width, mode);
    puts("");
    bst_set_level(child, nodelevel);
    return true;
}

bool left_rotation(BST *root) {
    int nodelevel = root->level;
    printf("Before left-rotation on [%d] [%s]\n", root->data, isprint(root->data) ? (char[2]){root->data, '\0'} : "null");
    bst_set_level(root, 1);
    visualize_tree(root, root, node_width, mode);
    puts("");
    bst_set_level(root, nodelevel);

    /************************************************************/
    if (DEBUG_ROTATION) printf("DEBUG: left_rotation - node [%d] [%s] | ", root->data, isprint(root->data) ? (char[2]){root->data, '\0'} : "null");
    if (DEBUG_ROTATION) printf("parent [%d] [%s]\n", root->parent->data, isprint(root->parent->data) ? (char[2]){root->parent->data, '\0'} : "null");
    BST *child = root->right;
    int oldproperties;
    if (!(root->properties & 0b10000)) {
        switch(child->properties & 0b11) {
            case 0b10:
                if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b10\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                child->properties |= 0b10000;
                right_rotation(child);
                child = root->right;
                if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b10\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                break;
            case 0b11:
                if (child->left->height > child->right->height) {
                    if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b11\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                    child->properties |= 0b10000;
                    right_rotation(child);
                    child = root->right;
                    if (DEBUG_ROTATION) printf("DEBUG: child = [%d] [%s] case 0b11\n", child->data, isprint(child->data) ? (char[2]){child->data, '\0'} : "null");
                }
                break;
        }
    }
    root->properties &= 0b01111;

    if (child->left != NULL) {
        oldproperties = child->left->properties;
        child->left->properties = (oldproperties ^ 0b1100) & 0b1100;
        child->left->properties |= (oldproperties & 0b0011);
        child->left->parent = root;
        if (DEBUG_ROTATION) printf("DEBUG: child properties updated\n");
    } else {
        root->properties &= 0b1110;
        child->properties |= 0b10;
    }
    root->right = child->left;
    child->left = root;
    child->parent = root->parent;
    if ((root->properties & 0b1100) == 0b1000) {
        root->parent->left = child;
        root->parent = child;
        oldproperties = child->properties;
        child->properties = (oldproperties ^ 0b1100) & 0b1100;
        child->properties |= (oldproperties & 0b0011);
        bst_update_height(child->parent);
    }
    else if ((root->properties & 0b1100) == 0b0100) {
        root->parent->right = child;
        root->parent = child;
        oldproperties = root->properties;
        root->properties = (oldproperties ^ 0b1100) & 0b1100;
        root->properties |= (oldproperties & 0b0011);
        bst_update_height(child->parent);
        if (DEBUG_ROTATION) printf("DEBUG: root properties updated\n");
    }
    else if ((root->properties & 0b1100) == 0b0000) {
        *(BST **)root->parent = child;
        root->parent = child;
        root->properties |= 0b1000;
        child->properties &= 0b0011;
        bst_update_height(child);
    }
    bst_set_level(child, root->level);
    if (DEBUG_ROTATION) printf("DEBUG: left_rotation - done\n");
    /************************************************************/

    nodelevel = child->level;
    printf("After left-rotation on [%d] [%s]\n", root->data, isprint(root->data) ? (char[2]){root->data, '\0'} : "null");
    bst_set_level(child, 1);
    visualize_tree(child, child, node_width, mode);
    puts("");
    bst_set_level(child, nodelevel);
    return true;
}

bool bst_update_height(BST *node) {
    if (DEBUG_UPDATE_HEIGHT) printf("DEBUG: bst_update_height - node %d\n", node->data);
    if ((node->properties & 0b11) == 0b00) {
        node->height = 1;
    }
    else if ((node->properties & 0b11) == 0b01) {
        bst_update_height(node->right);
        node->height = node->right->height + 1;
    }
    else if ((node->properties & 0b11) == 0b10) {
        bst_update_height(node->left);
        node->height = node->left->height + 1;
    } else {
        bst_update_height(node->left);
        bst_update_height(node->right);

        if (node->left->height > node->right->height) {
            node->height = node->left->height + 1;
        }
        else if (node->left->height < node->right->height) {
            node->height = node->right->height + 1;
        } else {
            node->height = node->left->height + 1;
        }
    }
    if (DEBUG_UPDATE_HEIGHT) printf("DEBUG: bst_update_height - done\n");
    return true;
}

bool bst_set_level(BST *node, int level) {
    if (node->properties & 0b10) {
        bst_set_level(node->left, level+1);
        if (DEBUG_SET_LEVEL) {
            print_debug(node, "from left node ");
            printf("[%d] [%s] | bst_set_level\n", node->left->data, isprint(node->left->data) ? (char[2]){node->left->data, '\0'} : "null");
        }
    }
    if (node->properties & 0b01) {
        bst_set_level(node->right, level+1);
        if (DEBUG_SET_LEVEL) {
            print_debug(node, "from right node ");
            printf("[%d] [%s] | bst_set_level\n", node->right->data, isprint(node->right->data) ? (char[2]){node->right->data, '\0'} : "null");
        }
    }
    node->level = level;
    if (DEBUG_SET_LEVEL) {
        print_debug(node, "");
        printf("level set to %d | bst_set_level\n", level);
    }
    return true;
}

bool bst_decrease_level(BST *node) {
    if (node->properties & 0b10) bst_decrease_level(node->left);
    if (node->properties & 0b01) bst_decrease_level(node->right);
    node->level -= 1;
    if (DEBUG_DECREASE_LEVEL) print_debug(node, "level decreased | bst_decrease_level\n");
    return true;
}

bool bst_insert_real(BST *node, BST **root, int indata) {
    int newheight;

    if (node == NULL) {
        *root = BSTNode(indata);
        (*root)->parent = (BST *)root;
        return true;
    }

    if (indata < node->data) { // Left sub-tree
        if (node->left == NULL) {
            node->left = BSTNode(indata);
            node->left->parent = node;
            if (!(node->properties & 0b11)) node->height++;
            node->left->level = node->level+1;
            node->properties |= 0b10;
            node->left->properties |= 0b1000;
            return true;
        } else {
            if (bst_insert_real(node->left, root, indata)) {
                newheight = node->left->height + 1;
                if (newheight > node->height) {
                    node->height = newheight;
                }
                return true;
            } else {
                return false;
            }
        }
    }
    else if (indata > node->data) { // Right sub-tree
        if (node->right == NULL) {
            node->right = BSTNode(indata);
            node->right->parent = node;
            if (!(node->properties & 0b11)) node->height++;
            node->right->level = node->level+1;
            node->properties |= 0b01;
            node->right->properties |= 0b0100;
            return true;
        } else {
            if (bst_insert_real(node->right, root, indata)) {
                newheight = node->right->height + 1;
                if (newheight > node->height) {
                    node->height = newheight;
                }
                return true;
            } else {
                return false;
            }
        }
    }
    else { // Data already exists
        printf("Could not insert [%d] [%s]. Element/key already exists.\n", indata, isprint(indata) ? (char[2]){indata, '\0'} : "null");
        return false;
    }

    return false;
}

bool bst_insert(BST **root, int indata) {
    return bst_insert_real(*root, root, indata);
}

bool bst_delete_real(BST *node, BST **root, int indata) {
    BST *temp;
    int oldproperties;
    int oldheigth;
    int newproperties;
    int newheight;
    int nodelevel;
    int nodedata;

    if (DEBUG_LIB_DELETE) {
        print_debug(node, "current node | ");
        printf("deleting [%d] [%s] | bst_delete\n", indata, isprint(indata) ? (char[2]){indata, '\0'} : "null");
    }

    if (indata < node->data) { // In the left sub-tree
        if (node->left != NULL) {
            oldproperties = node->properties;
            oldheigth = node->left->height;
            if (bst_delete_real(node->left, root, indata)) {
                newproperties = node->properties;
                if ((oldproperties & 0b11) != (newproperties & 0b11)) {
                    if ((newproperties & 0b11) == 0b00) { // Parent of deleted child
                        node->height -= 1;
                        if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b00 | bst_delete\n");
                    }
                    if (DEBUG_LIB_DELETE) print_debug(node, "parent of deleted node | bst_delete\n");
                    if (DEBUG_LIB_DELETE) {
                        nodelevel = node->level;
                        bst_set_level(node, 1);
                        visualize_tree(node, node, node_width, mode);
                        bst_set_level(node, nodelevel);
                    }
                } else {
                    switch(newproperties & 0b11) { // Grandparent/ancestor of deleted child
                    case 0b10:
                        newheight = node->left->height;
                        if (newheight != oldheigth) {
                            node->height -= 1;
                            if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b10 | bst_delete\n");
                        }
                        break;
                    case 0b01:
                        newheight = node->left->height;
                        if (newheight != oldheigth) {
                            node->height -= 1;
                            if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b01 | bst_delete\n");
                        }
                        break;
                    case 0b11:
                        newheight = node->left->height;
                        if (newheight != oldheigth) {
                            if (node->left->height >= node->right->height) {
                                node->height -= 1;
                                if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b11 | bst_delete\n");
                            }
                        }
                        break;
                    }
                }
                return true;
            } else {
                return false;
            }
        } else {
            printf("Could not delete [%d]. Element/key not found\n", indata);
            return false;
        }
    }
    else if (indata > node->data) { // In the right sub-tree
        if (node->right != NULL) {
            oldproperties = node->properties;
            oldheigth = node->right->height;
            if (bst_delete_real(node->right, root, indata)) {
                newproperties = node->properties;
                if ((oldproperties & 0b11) != (newproperties & 0b11)) {
                    if ((newproperties & 0b11) == 0b00) { // Parent of deleted child
                        node->height -= 1;
                        if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b00 | bst_delete\n");
                    }
                    if (DEBUG_LIB_DELETE) print_debug(node, "parent of deleted node | bst_delete\n");
                        if (DEBUG_LIB_DELETE) {
                        nodelevel = node->level;
                        bst_set_level(node, 1);
                        visualize_tree(node, node, node_width, mode);
                        bst_set_level(node, nodelevel);
                    }
                } else {
                    switch(newproperties & 0b11) { // Grandparent/ancestor of deleted child
                    case 0b10:
                        newheight = node->right->height;
                        if (newheight != oldheigth) {
                            node->height -= 1;
                            if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b10 | bst_delete\n");
                        }
                        break;
                    case 0b01:
                        newheight = node->right->height;
                        if (newheight != oldheigth) {
                            node->height -= 1;
                            if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b01 | bst_delete\n");
                        }
                        break;
                    case 0b11:
                        newheight = node->right->height;
                        if (newheight != oldheigth) {
                            if (node->right->height >= node->left->height) {
                                node->height -= 1;
                                if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b11 | bst_delete\n");
                            }
                        }
                        break;
                    }
                }
                return true;
            } else {
                return false;
            }
        } else {
            printf("Could not delete [%d]. Element/key not found\n", indata);
            return false;
        }
    }
    else { // Found it!
        if ((node->properties & 0b11) == 0b00) { // Node is a leaf
            if (node->parent == (BST *)root) { // Root node
                if (DEBUG_LIB_DELETE) print_debug(node, "deleting root node... | bst_delete\n");
                free(node);
                *root = NULL;
                return true;
            }
            if (node->properties & 0b1000) { // Node is a left child
                node->parent->left = NULL;
                node->parent->properties &= 0b1101;

            }
            else if (node->properties & 0b0100) { // Node is a right child
                node->parent->right = NULL;
                node->parent->properties &= 0b1110;
            }
            if (DEBUG_LIB_DELETE) print_debug(node, "deleting leaf node... | bst_delete\n");
            free(node);
            return true;
        }
        else if ((node->properties & 0b11) == 0b11) { // Node has two children
            if (node->left->height <= node->right->height) { // Get immediate successor
                temp = BSTMin(node->right);
                if (DEBUG_LIB_DELETE) print_debug(temp, "immediate successor | bst_delete\n");
            } else { // Get immediate predecessor
                temp = BSTMax(node->left);
                if (DEBUG_LIB_DELETE) print_debug(temp, "immediate predecessor | bst_delete\n");
            }

            //node->data = temp->data; //setting node->data before deletion causes an infinite loop
            nodedata = temp->data;
            if (DEBUG_LIB_DELETE) print_debug(node, "deleting node with two children, recursing... | bst_delete\n");
            if (bst_delete_real(node, root, temp->data)) {
                node->data = nodedata; // setting it after deletion fixes the infinite loop problem
                return true;
            } else {
                return false;
            }
        }
        else if ((node->properties & 0b11) == 0b10) { // Node has a left child
            node->left->parent = node->parent;
            if (node->properties & 0b1000) { // Node is a left child
                node->parent->left = node->left;
            }
            else if (node->properties & 0b0100) { // Node is a right child
                node->parent->right = node->left;
                oldproperties = node->left->properties;
                node->left->properties = (oldproperties ^ 0b1100) & 0b1100;
                node->left->properties |= (oldproperties & 0b0011);
            } else { // Neither right nor left child... it is the root node
                *root = node->left;
                if (DEBUG_LIB_DELETE) print_debug(node, "deleting root node... | bst_delete\n");
            }
            if (DEBUG_LIB_DELETE) print_debug(node, "deleting node with left child... | bst_delete\n");
            bst_decrease_level(node->left);
            free(node);
            return true;
        }
        else if ((node->properties & 0b11) == 0b01) { // Node has a right child
            node->right->parent = node->parent;
            if (node->properties & 0b1000) { // Node is a left child
                node->parent->left = node->right;
                oldproperties = node->right->properties;
                node->right->properties = (oldproperties ^ 0b1100) & 0b1100;
                node->right->properties |= (oldproperties & 0b0011);
            }
            else if (node->properties & 0b0100) { // Node is a right child
                node->parent->right = node->right;
            } else { // Neither right nor left child... it is the root node
                *root = node->right;
                if (DEBUG_LIB_DELETE) print_debug(node, "deleting root node... | bst_delete\n");
            }
            if (DEBUG_LIB_DELETE) print_debug(node, "deleting node with right child... | bst_delete\n");
            bst_decrease_level(node->right);
            free(node);
            return true;
        }
    }

    return false;
}

bool bst_delete(BST **root, int indata) { // A wrapper of the real bst_delete function for convenience
    return bst_delete_real(*root, root, indata);
}

bool avl_insert_real(BST *node, BST **root, int indata) {
    int newheight;

    if (node == NULL) {
        *root = BSTNode(indata);
        (*root)->parent = (BST *)root;
        return true;
    }

    if (indata < node->data) { // Left sub-tree
        if (node->left == NULL) {
            node->left = BSTNode(indata);
            node->left->parent = node;
            if (!(node->properties & 0b11)) node->height++;
            node->left->level = node->level+1;
            node->properties |= 0b10;
            node->left->properties |= 0b1000;
            return true;
        } else {
            if (avl_insert_real(node->left, root, indata)) {
                newheight = node->left->height + 1;
                if (newheight > node->height) {
                    node->height = newheight;
                }
                if (node->properties & 0b01) {
                    if (node->left->height > node->right->height+1) {
                        right_rotation(node);
                    }
                } else {
                    if (node->height > 2) {
                        right_rotation(node);
                    }
                }
                return true;
            } else {
                return false;
            }
        }
    }
    else if (indata > node->data) { // Right sub-tree
        if (node->right == NULL) {
            node->right = BSTNode(indata);
            node->right->parent = node;
            if (!(node->properties & 0b11)) node->height++;
            node->right->level = node->level+1;
            node->properties |= 0b01;
            node->right->properties |= 0b0100;
            return true;
        } else {
            if (avl_insert_real(node->right, root, indata)) {
                newheight = node->right->height + 1;
                if (newheight > node->height) {
                    node->height = newheight;
                }
                if (node->properties & 0b10) {
                    if (node->left->height+1 < node->right->height) {
                        left_rotation(node);
                    }
                } else {
                    if (node->height > 2) {
                        left_rotation(node);
                    }
                }
                return true;
            } else {
                return false;
            }
        }
    }
    else { // Data already exists
        printf("Could not insert [%d] [%s]. Element/key already exists.\n", indata, isprint(indata) ? (char[2]){indata, '\0'} : "null");
        return false;
    }

    return false;
}

bool avl_insert(BST **root, int indata) {
    return avl_insert_real(*root, root, indata);
}

bool avl_delete_real(BST *node, BST **root, int indata) {
    BST *temp;
    int oldproperties;
    int oldheigth;
    int newproperties;
    int newheight;
    int nodelevel;
    int nodedata;

    if (DEBUG_LIB_DELETE) {
        print_debug(node, "current node | ");
        printf("deleting [%d] [%s] | avl_delete\n", indata, isprint(indata) ? (char[2]){indata, '\0'} : "null");
    }

    if (indata < node->data) { // In the left sub-tree
        if (node->left != NULL) {
            oldproperties = node->properties;
            oldheigth = node->left->height;
            if (avl_delete_real(node->left, root, indata)) {
                newproperties = node->properties;
                if (oldproperties != newproperties) {
                    if ((newproperties & 0b11) == 0b00) { // Parent of deleted child
                        node->height -= 1;
                        if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b00 left sub-tree| avl_delete\n");
                        if (DEBUG_LIB_DELETE) print_debug(node, "parent of deleted node | left sub-tree | avl_delete\n");
                        if (DEBUG_LIB_DELETE) {
                            nodelevel = node->level;
                            bst_set_level(node, 1);
                            visualize_tree(node, node, node_width, mode);
                            bst_set_level(node, nodelevel);
                        }
                    }
                    if (newproperties & 0b10000) { // A rotation on one of its children happened
                        if (DEBUG_LIB_DELETE) print_debug(node, "a rotation happened | left sub-tree | avl_delete\n");
                        node->properties &= 0b01111;
                    }
                } else {
                    newheight = node->left->height;
                    if (newheight != oldheigth) {
                        if (node->left->height >= node->right->height) {
                            node->height -= 1;
                            if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b11 left sub-tree | avl_delete\n");
                        }
                    }
                }

                if ((node->properties & 0b11) == 0b01) {
                    if (node->height > 2) {
                        if (node->parent != (BST *)root) node->parent->properties |= 0b10000;
                        left_rotation(node);
                    }
                } else if ((node->properties & 0b11) == 0b11) {
                    if (node->left->height+1 < node->right->height) {
                        if (node->parent != (BST *)root) node->parent->properties |= 0b10000;
                        left_rotation(node);
                    }
                }
                return true;
            } else {
                return false;
            }
        } else {
            printf("Could not delete [%d]. Element/key not found\n", indata);
            return false;
        }
    }
    else if (indata > node->data) { // In the right sub-tree
        if (node->right != NULL) {
            oldproperties = node->properties;
            oldheigth = node->right->height;
            if (avl_delete_real(node->right, root, indata)) {
                newproperties = node->properties;
                if (oldproperties != newproperties) {
                    if ((newproperties & 0b11) == 0b00) { // Parent of deleted child
                        node->height -= 1;
                        if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b00 right sub-tree | avl_delete\n");
                        if (DEBUG_LIB_DELETE) print_debug(node, "parent of deleted node | right sub-tree | avl_delete\n");
                        if (DEBUG_LIB_DELETE) {
                            nodelevel = node->level;
                            bst_set_level(node, 1);
                            visualize_tree(node, node, node_width, mode);
                            bst_set_level(node, nodelevel);
                        }
                    }
                    if (newproperties & 0b10000) { // A rotation on one of its children happened
                        if (DEBUG_LIB_DELETE) print_debug(node, "a rotation happened | right sub-tree | avl_delete\n");
                        node->properties &= 0b01111;
                    }
                } else {
                    newheight = node->right->height;
                    if (newheight != oldheigth) {
                        if (node->right->height >= node->left->height) {
                            node->height -= 1;
                            if (DEBUG_LIB_DELETE) print_debug(node, "height decreased | case 0b11 right sub-tree | avl_delete\n");
                        }
                    }
                }

                if ((node->properties & 0b11) == 0b10) {
                    if (node->height > 2) {
                        if (node->parent != (BST *)root) node->parent->properties |= 0b10000;
                        right_rotation(node);
                    }
                } else if ((node->properties & 0b11) == 0b11) {
                    if (node->right->height+1 < node->left->height) {
                        if (node->parent != (BST *)root) node->parent->properties |= 0b10000;
                        right_rotation(node);
                    }
                }
                return true;
            } else {
                return false;
            }
        } else {
            printf("Could not delete [%d]. Element/key not found\n", indata);
            return false;
        }
    }
    else { // Found it!
        if ((node->properties & 0b11) == 0b00) { // Node is a leaf
            if (node->parent == (BST *)root) { // Root node
                if (DEBUG_LIB_DELETE) print_debug(node, "deleting root node... | avl_delete\n");
                free(node);
                *root = NULL;
                return true;
            }
            if (node->properties & 0b1000) { // Node is a left child
                node->parent->left = NULL;
                node->parent->properties &= 0b1101;

            }
            else if (node->properties & 0b0100) { // Node is a right child
                node->parent->right = NULL;
                node->parent->properties &= 0b1110;
            }
            if (DEBUG_LIB_DELETE) {
                print_debug(node, "deleting leaf node of ");
                printf("[%d] [%s] | avl_delete\n", node->parent->data, isprint(node->parent->data) ? (char[2]){node->parent->data, '\0'} : "null");
            }
            free(node);
            return true;
        }
        else if ((node->properties & 0b11) == 0b11) { // Node has two children
            if (node->left->height <= node->right->height) { // Get immediate successor
                temp = BSTMin(node->right);
                if (DEBUG_LIB_DELETE) print_debug(temp, "immediate successor | avl_delete\n");
            } else { // Get immediate predecessor
                temp = BSTMax(node->left);
                if (DEBUG_LIB_DELETE) print_debug(temp, "immediate predecessor | avl_delete\n");
            }

            //node->data = temp->data; //setting node->data before deletion causes an infinite loop
            nodedata = temp->data;
            if (DEBUG_LIB_DELETE) print_debug(node, "deleting node with two children, recursing... | avl_delete\n");
            if (avl_delete_real(node, root, temp->data)) {
                node->data = nodedata; // setting it after deletion fixes the infinite loop problem
                return true;
            } else {
                return false;
            }
        }
        else if ((node->properties & 0b11) == 0b10) { // Node has a left child
            node->left->parent = node->parent;
            if (node->properties & 0b1000) { // Node is a left child
                node->parent->left = node->left;
            }
            else if (node->properties & 0b0100) { // Node is a right child
                node->parent->right = node->left;
                oldproperties = node->left->properties;
                node->left->properties = (oldproperties ^ 0b1100) & 0b1100;
                node->left->properties |= (oldproperties & 0b0011);
            } else { // Neither right nor left child... it is the root node
                *root = node->left;
                if (DEBUG_LIB_DELETE) print_debug(node, "deleting root node... | bst_delete\n");
            }
            if (DEBUG_LIB_DELETE) print_debug(node, "deleting node with left child... | avl_delete\n");
            bst_decrease_level(node->left);
            free(node);
            return true;
        }
        else if ((node->properties & 0b11) == 0b01) { // Node has a right child
            node->right->parent = node->parent;
            if (node->properties & 0b1000) { // Node is a left child
                node->parent->left = node->right;
                oldproperties = node->right->properties;
                node->right->properties = (oldproperties ^ 0b1100) & 0b1100;
                node->right->properties |= (oldproperties & 0b0011);
            }
            else if (node->properties & 0b0100) { // Node is a right child
                node->parent->right = node->right;
            } else { // Neither right nor left child... it is the root node
                *root = node->right;
                if (DEBUG_LIB_DELETE) print_debug(node, "deleting root node... | bst_delete\n");
            }
            if (DEBUG_LIB_DELETE) print_debug(node, "deleting node with right child... | avl_delete\n");
            bst_decrease_level(node->right);
            free(node);
            return true;
        }
    }

    return false;
}

bool avl_delete(BST **root, int indata) { // A wrapper of the real avl_delete function for convenience
    return avl_delete_real(*root, root, indata);
}

int power(int base, int exponent) {
    int ret = base;
    if (exponent > 0) { // positive exponent
        for(int i = 1; i < exponent; i++) {
            ret *= base;
        }
    }
    else if (exponent < 0) { // negative exponent
        if (DEBUG_OTHER) printf("DEBUG: power - base %d, exponent %d, result 0\n", base, exponent);
        return 0;
    } else { // exponent = 0
        if (DEBUG_OTHER) printf("DEBUG: power - base %d, exponent %d, result 1\n", base, exponent);
        return 1;
    }
    if (DEBUG_OTHER) printf("DEBUG: power - base %d, exponent %d, result %d\n", base, exponent, ret);
    return ret;
}

int gotoline(int line, int nodelevel, BST *root, char *buffer, int node_width) {
    int diff = nodelevel-root->level;
	int actual_line;
	int linewidth;
	char *marker;
    if ((nodelevel == root->height) && (line > 0)) {
        return -1;
    }
	linewidth = (power(2, root->height-1)*node_width)+1;
    actual_line = (linewidth*4*(diff))+(linewidth*line);
    marker = strstr(buffer+actual_line, "*");
    if (marker != NULL) {
        return marker-buffer;
    }
    return actual_line;
}

int gotocolumn(int nodelevel, BST *root, int node_width) {
	int linewidth = (power(2, root->height-1)*node_width)+1;
    int ret = (linewidth-1)/power(2, nodelevel);
    if (DEBUG_OTHER) printf("DEBUG: gotocolumn - nodelevel %d, index %d\n", nodelevel, ret);
    return ret;
}

bool add_padding(BST *node, BST *root, char *buffer, int line, int node_width) {
    int diff;
    int caret;

    diff = root->height - node->level;

    if (node->properties & 0b11) { // NOT a leaf
        switch(diff) {
        case 0:
            return false;
        case 1:
            caret = gotoline(line, node->level+1, root, buffer, node_width);
            if (caret == -1) return false;
            buffer[caret] = ' ';
            caret += gotocolumn(node->level, root, node_width);
            buffer[caret] = '*';
            break;
        default: // NOT a leaf node but more than one level higher than deepest node
            for(int i = 1; i <= diff; i++) {
                caret = gotoline(line, node->level+i, root, buffer, node_width);
                if (caret == -1) return false;
                buffer[caret] = ' ';
                caret += gotocolumn(node->level, root, node_width);
                buffer[caret] = '*';
            }
            break;
        }
    } else { // a leaf node
        switch(diff) {
        case 0:
            return false;
        case 1:
            caret = gotoline(line, node->level+1, root, buffer, node_width);
            if (caret == -1) return false;
            buffer[caret] = ' ';
            caret += gotocolumn(node->level, root, node_width);
            buffer[caret] = '*';
            break;
        default: // a leaf node but more than one level higher than deepest node
            for(int i = 1; i <= diff; i++) {
                caret = gotoline(line, node->level+i, root, buffer, node_width);
                if (caret == -1) return false;
                buffer[caret] = ' ';
                caret += gotocolumn(node->level, root, node_width);
                buffer[caret] = '*';
            }
            break;
        }
    }
    return true;
}

bool visualize_tree_real(BST *node, BST *root, char *buffer, int node_width, char mode) {
    if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - start\n");
    int ret;
    int line;
    int column;
    int caret;
    int offset;
    int delimiter;

    if (node->left != NULL) {
        visualize_tree_real(node->left, root, buffer, node_width, mode);
    } else {
        add_padding(node, root, buffer, 0, node_width);
        add_padding(node, root, buffer, 1, node_width);
        add_padding(node, root, buffer, 2, node_width);
        add_padding(node, root, buffer, 3, node_width);
    }

    if (node->right != NULL) {
        visualize_tree_real(node->right, root, buffer, node_width, mode);
    } else {
        add_padding(node, root, buffer, 0, node_width);
        add_padding(node, root, buffer, 1, node_width);
        add_padding(node, root, buffer, 2, node_width);
        add_padding(node, root, buffer, 3, node_width);
    }

    // line 1
    line = gotoline(0, node->level, root, buffer, node_width);
    buffer[line] = ' ';
    column = gotocolumn(node->level, root, node_width);
    caret = line + column - (node_width/2);
    if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 1, caret %d\n", node->data, caret);
    if (mode == 'a') {
        ret = sprintf(buffer+caret, "[%*c]", node_width-2, node->data);
        //ret = sprintf(buffer+caret, "[%*c||%*c]", (node_width-4)/2, node->data, (node_width-4)/2, node->parent->data);
    }
    else {
        ret = sprintf(buffer+caret, "[%*d]", node_width-2, node->data);
        //ret = sprintf(buffer+caret, "[%*d||%*d]", (node_width-4)/2, node->data, (node_width-4)/2, node->parent->data);
    }
    buffer[caret+ret] = ' ';
    buffer[line+(2*column)] = '*'; //marker

    if (node->level != root->height) {
        // line 2
        line = gotoline(1, node->level, root, buffer, node_width);
        buffer[line] = ' ';
        column = gotocolumn(node->level, root, node_width);
        caret = line + column;
        if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 2, caret %d\n", node->data, caret);
        switch(node->properties & 0b11) {
        case 0b00:
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 2, caret %d, no child\n", node->data, caret);
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b10:
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 2, caret %d, left child\n", node->data, caret);
            buffer[caret-1] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b01:
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 2, caret %d, right child\n", node->data, caret);
            buffer[caret] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b11:
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 2, caret %d, two children\n", node->data, caret);
            buffer[caret] = '|';
            buffer[caret-1] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        }

        // line 3
        line = gotoline(2, node->level, root, buffer, node_width);
        buffer[line] = ' ';
        column = gotocolumn(node->level, root, node_width);
        offset = gotocolumn(node->level+1, root, node_width);
        if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 3, caret %d\n", node->data, caret);
        switch(node->properties & 0b11) {
        case 0b00:
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 3, caret %d, no child\n", node->data, caret);
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b10:
            caret = line + column - offset;
            delimiter = line + column - 1;
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 3, caret %d, left child\n", node->data, caret);
            buffer[caret] = '+';
            for(int i = caret+1; i < delimiter; i++) {
                buffer[i] = '-';
            }
            buffer[delimiter] = '+';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b01:
            caret = line + column;
            delimiter = line + column + offset - 1;
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 3, caret %d, right child\n", node->data, caret);
            buffer[caret] = '+';
            for(int i = caret+1; i < delimiter; i++) {
                buffer[i] = '-';
            }
            buffer[delimiter] = '+';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b11:
            caret = line + column - offset;
            delimiter = line + column - 1;
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 3, caret %d, two children\n", node->data, caret);
            buffer[caret] = '+';
            for(int i = caret+1; i < delimiter; i++) {
                buffer[i] = '-';
            }
            buffer[delimiter] = '+';
            caret = line + column;
            delimiter = line + column + offset - 1;
            buffer[caret] = '+';
            for(int i = caret+1; i < delimiter; i++) {
                buffer[i] = '-';
            }
            buffer[delimiter] = '+';
            buffer[line+(2*column)] = '*'; //marker
            break;
        }

        // line 4
        line = gotoline(3, node->level, root, buffer, node_width);
        buffer[line] = ' ';
        column = gotocolumn(node->level, root, node_width);
        offset = gotocolumn(node->level+1, root, node_width);
        if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 4, caret %d\n", node->data, caret);
        switch(node->properties & 0b11) {
        case 0b00:
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 4, caret %d, no child\n", node->data, caret);
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b10:
            caret = line + column - offset;
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 4, caret %d, left child\n", node->data, caret);
            buffer[caret] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b01:
            caret = line + column + offset - 1;
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 4, caret %d, right child\n", node->data, caret);
            buffer[caret] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        case 0b11:
            caret = line + column;
            if (DEBUG_LIB_VISUALIZE) printf("DEBUG: visualize_tree - node %d, line 4, caret %d, two children\n", node->data, caret);
            buffer[caret-offset] = '|';
            buffer[caret+offset-1] = '|';
            buffer[line+(2*column)] = '*'; //marker
            break;
        }
    }

    return true;
}

// a function wrapper of visualize_tree_real for preparing output buffer
bool visualize_tree(BST *node, BST *root, int node_width, char mode) {
    char *buffer;
	int linewidth;
	int lines;
	int buffer_size;
	int start_column;
	int end_column;
	int temp = 0;
    linewidth = (power(2, root->height-1)*node_width)+1;
    if (DEBUG_LIB_VISUALIZE) printf("Tree height: %d\n", root->height);
    lines = (4*(root->height-1))+1;
    if (DEBUG_LIB_VISUALIZE) printf("Tree height: %d\n", root->height);
    buffer_size = linewidth*lines;
    if (DEBUG_LIB_VISUALIZE) printf("Allocating buffer...\n");
    buffer = (char*)malloc((linewidth*lines)+1);

    if (buffer != NULL) {
        if (DEBUG_LIB_VISUALIZE) printf("Output buffer allocated. %d bytes\n", buffer_size);
    } else {
        printf("Could not allocate buffer. %d\n", buffer_size);
        return false;
    }

    if (DEBUG_LIB_VISUALIZE) printf("Line width: %d\nLines: %d\n", linewidth, lines);

    // fill the buffer with null characters
    for(int i = 0; i < buffer_size; i++) {
        if (((i+1) % linewidth) == 0) {
            buffer[i] = '\0'; // set line-delimiters to null
            continue;
        }
        buffer[i] = ' ';
    }

	visualize_tree_real(node, root, buffer, node_width, mode);

	start_column = linewidth/2;
	end_column = linewidth/2;
	for(int i = 0; i < lines; i += 4) {
        buffer[(linewidth*i)+(linewidth-1)] = '\0';
        temp = strchr(buffer+(linewidth*i), '[') - (buffer + (linewidth*i));
        if (temp < start_column) start_column = temp;
        temp = strrchr(buffer+(linewidth*i), ']') - (buffer + (linewidth*i)) + 1;
        if (temp > end_column) end_column = temp;
    }

    if (DEBUG_LIB_VISUALIZE) printf("start_column = %d\n", start_column);

	for(int i = 0; i < lines; i++) {
        buffer[(i*linewidth)+end_column] = '\0';  // set line-delimiters to null
    }
    buffer[buffer_size] = '\0';

    for(int i = 0; i < lines; i++) {
        puts(buffer+(i*linewidth)+start_column);
    }

    //printf(buffer);
    free(buffer);

    return true;
}

void set_node_width(int width) {
    node_width = width;
}

void set_mode(char _mode) {
    mode = _mode;
}

#endif // TREE_H_
