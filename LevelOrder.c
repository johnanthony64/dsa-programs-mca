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

// Function to insert a node in level order
struct Node* insertLevelOrder(int arr[], struct Node* root, int i, int n) {
    if (i < n) {
        struct Node* temp = createNode(arr[i]);
        root = temp;

        // Insert left child
        root->left = insertLevelOrder(arr, root->left, 2 * i + 1, n);

        // Insert right child
        root->right = insertLevelOrder(arr, root->right, 2 * i + 2, n);
    }
    return root;
}

// Function to perform inorder traversal
void inorderTraversal(struct Node* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("%d ", root->data);
        inorderTraversal(root->right);
    }
}

// Function to perform preorder traversal
void preorderTraversal(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorderTraversal(root->left);
        preorderTraversal(root->right);
    }
}

// Function to perform postorder traversal
void postorderTraversal(struct Node* root) {
    if (root != NULL) {
        postorderTraversal(root->left);
        postorderTraversal(root->right);
        printf("%d ", root->data);
    }
}

// Function to create a binary tree using inorder and preorder traversals
struct Node* buildTree(int inorder[], int preorder[], int inStart, int inEnd) {
    static int preIndex = 0;

    if (inStart > inEnd)
        return NULL;

    struct Node* newNode = createNode(preorder[preIndex++]);

    if (inStart == inEnd)
        return newNode;

    int inIndex;
    for (int i = inStart; i <= inEnd; i++) {
        if (inorder[i] == newNode->data) {
            inIndex = i;
            break;
        }
    }

    newNode->left = buildTree(inorder, preorder, inStart, inIndex - 1);
    newNode->right = buildTree(inorder, preorder, inIndex + 1, inEnd);

    return newNode;
}

// Driver code
int main() {
    // Create a binary tree using level order
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = insertLevelOrder(arr, root, 0, n);

    printf("Inorder traversal: ");
    inorderTraversal(root);
    printf("\n");

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");

    // Create a binary tree using inorder and preorder traversals
    int inorder[] = {4, 2, 5, 1, 6, 3, 7};
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int len = sizeof(inorder) / sizeof(inorder[0]);
    struct Node* newRoot = buildTree(inorder, preorder, 0, len - 1);

    printf("Inorder traversal of new tree: ");
    inorderTraversal(newRoot);
    printf("\n");

    return 0;
}
