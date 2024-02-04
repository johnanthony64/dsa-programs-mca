#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;};

struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

void inOrderTraversal(struct Node* root) {
    if (root != NULL) {
        inOrderTraversal(root->left);
        printf("%d ", root->data);
        inOrderTraversal(root->right);
    }
}

void preOrderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

struct Node* searchBTF(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    if (key < root->data) {
        return searchBTF(root->left, key);
    }

    return searchBTF(root->right, key);
}

struct Node* searchDFT(struct Node* root, int key) {
    if (root == NULL || root->data == key) {
        return root;
    }

    printf("%d ", root->data);

    struct Node* leftResult = searchDFT(root->left, key);
    struct Node* rightResult = searchDFT(root->right, key);

    return (leftResult != NULL) ? leftResult : rightResult;
}

void print_menu() {
    printf("Menu:\n");
    printf("1. Binary Tree Traversal (BTF) - Inorder\n");
    printf("2. Depth-First Traversal (DFT) - Preorder\n");
    printf("3. Search using Binary Tree Traversal (BTF)\n");
    printf("4. Search using Depth-First Traversal (DFT)\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    struct Node* root = createNode(10);
    root->left = createNode(5);
    root->right = createNode(15);
    root->left->left = createNode(3);
    root->left->right = createNode(7);
    root->right->left = createNode(12);
    root->right->right = createNode(18);

    int choice;
    do {
        print_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Binary Tree Traversal (BTF) - Inorder: ");
                inOrderTraversal(root);
                printf("\n");
                break;

            case 2:
                printf("Depth-First Traversal (DFT) - Preorder: ");
                preOrderTraversal(root);
                printf("\n");
                break;

            case 3: {
                int keyBTF;
                printf("Enter the value for Binary Tree Traversal (BTF) search: ");
                scanf("%d", &keyBTF);
                struct Node* resultBTF = searchBTF(root, keyBTF);
                if (resultBTF != NULL) {
                    printf("Found %d using Binary Tree Traversal (BTF)\n", keyBTF);
                } else {
                    printf("%d not found using Binary Tree Traversal (BTF)\n", keyBTF);
                }
                break;
            }

            case 4: {
                int keyDFT;
                printf("Enter the value for Depth-First Traversal (DFT) search: ");
                scanf("%d", &keyDFT);
                printf("Depth-First Traversal (DFT) search path: ");
                struct Node* resultDFT = searchDFT(root, keyDFT);
                if (resultDFT != NULL) {
                    printf("\nFound %d using Depth-First Traversal (DFT)\n", keyDFT);
                } else {
                    printf("\n%d not found using Depth-First Traversal (DFT)\n", keyDFT);
                }
                break;
            }

            case 5:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 5);

    return 0;
}

