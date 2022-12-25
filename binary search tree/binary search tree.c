#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//define node and node pointer
typedef struct node* node_ptr;
typedef struct node {
    int data;
    node_ptr left;
    node_ptr right;
    node_ptr parent;
} node;

//function prototype
void preOrder(node_ptr root);
void inOrder(node_ptr root);
void printTree(node_ptr root);
node_ptr search(node_ptr root, int key);
node_ptr newNode(int value);
bool insertNode(node_ptr* root_p, int value);
node_ptr leftMost(node_ptr current);
node_ptr inorderSuccessor(node_ptr current);
node_ptr rightMost(node_ptr current);
node_ptr inorderPredecessor(node_ptr current);
bool deleteNode(node_ptr* root_p, int delValue);
node_ptr nthSmallest(node_ptr root, int* n);
void sort(node_ptr root);


int main(void) {
    char command;
    node_ptr root = NULL;
    int newNum;
    int delNum;
    int searchNum;
    int nthSmallNum;
    int nthSmallNum_cpy;
    node_ptr searchNode;
    node_ptr nthSmallNode;

    //read file
    int number;
    int readFileStatus = 0;
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n");
    printf(" Please put 'data.txt' into the same path as this program\n");
    printf("* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\n\n");
    FILE* fp = fopen("data.txt", "r");
    if (!fp) {
        //if file does not exist, exit the program
        printf("Error. 'data.txt' is not exist.\n");
        exit(1);
    }
    printf("Reading file...\n");
    
    do {
        assert(readFileStatus = fscanf(fp, "%d", &number));
        if (readFileStatus != EOF) {
            printf("%d ", number);
            insertNode(&root, number);
        }

    } while (readFileStatus != EOF);
    //show
    printf("\nRead file successfully\n");  
    printf("Inorder traversal ");
    printTree(root);

    do{
        //instructions
        printf("\n===================== M E N U =====================\n");
        printf("Enter a number to execute the following functions.\n");
        printf("Enter 1: Insert a number\n");
        printf("Enter 2: Delete a number\n");
        printf("Enter 3: Find a number\n");
        printf("Enter 4: Find nth small number\n");
        printf("Enter 5: Sort\n"); 
        printf("Enter 6: Exit\n");     
        printf("===================================================\n");

        //read command
        printf("Command> ");
        scanf("%c", &command);
        //clear buffer
        while (getchar() != '\n');
        //execute the command
        switch (command){
        case '1':
            //insert
            printf("Enter the number to be inserted: ");
            while (scanf("%d", &newNum)!=1){
                while (getchar() != '\n'); //clear buffer
                printf("bad input, enter again\n");
                printf("Enter the number to be inserted: ");
            }
            while (getchar() != '\n'); //clear buffer

            if (insertNode(&root, newNum)) {
                printf("'%d' is added.\n", newNum);
            }
            else {
                printf("'%d' is repeated and cannot be added.\n", newNum);
            }
            printf("Inorder: ");
            printTree(root);
            break;

        case '2':
            //delete
            printf("Enter the number to be deleted: ");
            while (scanf("%d", &delNum) != 1) {
                while (getchar() != '\n'); //clear buffer
                printf("bad input, enter again\n");
                printf("Enter the number to be deleted: ");
            }
            while (getchar() != '\n'); //clear buffer

            if (deleteNode(&root, delNum)) {
                printf("'%d' is deleted.\n", delNum);
            }
            else {
                printf("'%d' is not in the tree.\n", delNum);
            }
            printf("Inorder: ");
            printTree(root);
            break;

        case '3':
            //search
            printf("Enter the number to be searched: ");
            while (scanf("%d", &searchNum) != 1) {
                while (getchar() != '\n'); //clear buffer
                printf("bad input, enter again\n");
                printf("Enter the number to be searched: ");
            }
            while (getchar() != '\n'); //clear buffer

            printf("Inorder: ");
            printTree(root);
            searchNode = search(root, searchNum);
            if (searchNode) {
                printf("Found '%d'\n", searchNum);
            }
            else {
                printf("Not found '%d'\n", searchNum);
            }
            break;

        case '4':
            //nth small number
            printf("nth small number, enter n: ");
            while (scanf("%d", &nthSmallNum) != 1) {
                while (getchar() != '\n'); //clear buffer
                printf("bad input, enter again\n");
                printf("nth small number, enter n: ");
            }
            while (getchar() != '\n'); //clear buffer

            nthSmallNum_cpy = nthSmallNum;
            printf("[ ");
            nthSmallNode = nthSmallest(root, &nthSmallNum_cpy);
            if (nthSmallNode) {
                printf("]\nFound %dth small number: '%d'\n", nthSmallNum, nthSmallNode->data);
            }
            else {
                printf("]\nNot found %dth small number\n", nthSmallNum);
            }
            break;

        case '5':
            //sort
            printf("Sorted: ");
            sort(root);
            break;

        case '6':
            //exit
            break;

        default:
            printf("Wrong command, enter again.\n");
            break;
        }

        if (command != '6') {
            printf("press enter to continue...");
            while (getchar() != '\n'); //clear buffer
        }
    } while (command != '6');

    printf("\nGoodbye~\n");

    fclose(fp);
    return 0;
}


//function implementation
void preOrder(node_ptr root) {
    /*print all nodes by preorder traversal*/

    if (root) {
        printf("%d ", root->data); //visit the node
        preOrder(root->left); //move left
        preOrder(root->right); //move right
    }
}


void inOrder(node_ptr root) {
    /*print all nodes by inorder traversal*/

    if (root) {
        inOrder(root->left); //move left
        printf("%d ", root->data); //visit the node

        inOrder(root->right); //move right
    }
}


void printTree(node_ptr root) {
    printf("[ ");
    inOrder(root);
    printf("]\n");
}


node_ptr search(node_ptr root, int key) {
    /*return node_ptr if found. otherwise, return NULL*/
    
    while (root) {

        if (key == root->data) {
            //found, return a pointer points to the node
            return root;
        }
        else if (key < root->data) {
            //move left
            root = root->left;
        }
        else {
            //move right
            root = root->right;
        }

    }
    //not found, return NULL
    return NULL;
}


node_ptr newNode(int value) {
    //create a new node and return node_ptr

    node_ptr temp = (node_ptr)malloc(sizeof(node));
    if (!temp) {
        //if memory is full
        fprintf(stderr, "Memory is full\n");
        exit(1);
    }
    temp->data = value;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;

    return temp;
}


bool insertNode(node_ptr* root_p, int value) {
    //insert a new node into binary search tree
    //return true if insert successfully, return false otherwise.
    node_ptr root = *root_p;
    if (!root) {
        *root_p = newNode(value);
        return true;
    }
    //search where to insert
    node_ptr father = NULL;
    while (root) {
        //parent=NULL when value already exists OR root is NULL
        if (value == root->data) {
            break;

        }
        else if (value < root->data) {
            if (!root->left) {
                //if it is the last node when searching, break the loop
                father = root;
                break;

            }
            //if it is not the last node, move forward
            root = root->left;
        }
        else {
            if (!root->right) {
                //if it is the last node when searching, break the loop
                father = root;
                break;

            }
            //if it is not the last node, move forward
            root = root->right;
        }
    }

    //if parent is not NULL, insert the number
    if (father) {
        node_ptr child = newNode(value);
        child->parent = father;
        if (value < father->data) {
            father->left = child;
        }
        else {
            father->right = child;
        }
        return true;

    }
    else {
        return false;
    }
}

node_ptr leftMost(node_ptr current) {
    //find the most left node
    node_ptr mostLeft = current;
    while (mostLeft->left) {
        mostLeft = mostLeft->left;
    }
    return mostLeft;
}


node_ptr inorderSuccessor(node_ptr current) {
    //case 1, current node has right child
    if (current->right) {
        return leftMost(current->right);
    }

    //case 2, current node has no right child
    node_ptr successor = current->parent;
    while (successor && current == successor->right) {
        current = successor;
        successor = current->parent;
    }
    return successor;
}


node_ptr rightMost(node_ptr current) {
    //find the most right node
    node_ptr mostRight = current;
    while (mostRight->right) {
        mostRight = mostRight->right;
    }
    return mostRight;
}


node_ptr inorderPredecessor(node_ptr current) {
    //case 1, current node has left child
    if (current->left) {
        return rightMost(current->left);
    }

    //case 2, current node has no left child
    node_ptr predecessor = current->parent;
    while (predecessor && current == predecessor->left) {
        current = predecessor;
        predecessor = current->parent;
    }
    return predecessor;
}


bool deleteNode(node_ptr* root_p, int delValue) {
    //using inorder successor
    node_ptr root = *root_p;
    node_ptr deleteNode = search(root, delValue);
    if (!deleteNode) {
        //not found, return false
        return false;
    }

    node_ptr trashNode = NULL;
    node_ptr trashNodeChild = NULL;
    if (deleteNode->left == NULL || deleteNode->right == NULL) {
        //case 1, deleteNode has no child
        //case 2, deleteNode has only left or right child
        trashNode = deleteNode;
    }
    else {
        //case 3, deleteNode has two children
        //adjust trashNode to case 1 or case 2
        trashNode = inorderSuccessor(deleteNode);
    }
    //set trashNodeChild
    if (trashNode->left) {
        trashNodeChild = trashNode->left;
    }
    else {
        trashNodeChild = trashNode->right;
    }
    //if trashNode has child, set trashNodeChild->parent
    if (trashNodeChild) {
        trashNodeChild->parent = trashNode->parent;
    }

    if (trashNode->parent == NULL) {
        //if trashNode is the root, set trashNodeChild to be new root
        *root_p = trashNodeChild;

    }
    else if (trashNode == trashNode->parent->left) {
        //if trashNode is left of its parent
        trashNode->parent->left = trashNodeChild;

    }
    else {
        trashNode->parent->right = trashNodeChild;

    }
    //if trashNode is not deleteNode, copy the value
    if (trashNode != deleteNode) {
        deleteNode->data = trashNode->data;
    }

    //free trashNode
    free(trashNode);

    return true;
}


node_ptr nthSmallest(node_ptr root, int* n) {
    node_ptr temp = NULL;

    if (root) {
        temp = nthSmallest(root->left, n); //move left

        if (*n > 1) {
            printf("%d ", root->data);
        }
        else if (*n == 1) {
            if (!temp) {
                //nth small number, return this node
                printf("'%d' ", root->data);
                return root;
            }
            else {
                //keep return the node
                return temp;
            }
        }
        //to calculate where the nth small number is
        *n = (*n) - 1;

        temp = nthSmallest(root->right, n); //move right
    }
    return temp;
}


void sort(node_ptr root) {
    printf("[ ");
    inOrder(root);
    printf("]\n");
}
