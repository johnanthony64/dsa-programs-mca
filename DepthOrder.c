#include <stdio.h>
#include <stdlib.h>

// Structure for a binary tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!");
        exit(1);
    }
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create a binary tree using Depth order
struct Node* createBinaryTree() {
    struct Node* root = createNode(1);
    root->left = createNode(2);
    root->right = createNode(3);
    root->left->left = createNode(4);
    root->left->right = createNode(5);
    root->right->left = createNode(6);
    root->right->right = createNode(7);
    return root;
}

// Function to perform Inorder traversal
void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Function to perform Preorder traversal
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    printf("%d ", root->data);
    preorderTraversal(root->left);
    preorderTraversal(root->right);
}

// Function to perform Postorder traversal
void postorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    postorderTraversal(root->left);
    postorderTraversal(root->right);
    printf("%d ", root->data);
}

// Function to create a binary tree using Inorder and Preorder traversals
struct Node* buildTree(int* inorder, int* preorder, int inorderStart, int inorderEnd) {
    static int preorderIndex = 0;

    if (inorderStart > inorderEnd)
        return NULL;

    struct Node* newNode = createNode(preorder[preorderIndex++]);

    if (inorderStart == inorderEnd)
        return newNode;

    int inorderIndex;
    for (int i = inorderStart; i <= inorderEnd; i++) {
        if (inorder[i] == newNode->data) {
            inorderIndex = i;
            break;
        }
    }

    newNode->left = buildTree(inorder, preorder, inorderStart, inorderIndex - 1);
    newNode->right = buildTree(inorder, preorder, inorderIndex + 1, inorderEnd);

    return newNode;
}

int main() {
    // Create a binary tree using Depth order
    struct Node* root = createBinaryTree();

    printf("Inorder traversal: ");
    inorderTraversal(root);

    printf("\nPreorder traversal: ");
    preorderTraversal(root);

    printf("\nPostorder traversal: ");
    postorderTraversal(root);

    // Create a binary tree using Inorder and Preorder traversals
    int inorder[] = {4, 2, 5, 1, 6, 3, 7};
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int n = sizeof(inorder) / sizeof(inorder[0]);
    struct Node* newRoot = buildTree(inorder, preorder, 0, n - 1);

    printf("\n\nInorder traversal of new tree: ");
    inorderTraversal(newRoot);

    return 0;
}
