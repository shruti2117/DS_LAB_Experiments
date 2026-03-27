#include <stdio.h>
#include <stdlib.h>

struct TreeNode {
    int val;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Create Node
struct TreeNode* createNode(int val){
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert Node (duplicates go to right)
struct TreeNode* insertNode(struct TreeNode* root, int val) {
    if (root == NULL)
        return createNode(val);

    if (val < root->val)
        root->left = insertNode(root->left, val);
    else
        root->right = insertNode(root->right, val);

    return root;
}

// Inorder Traversal
void inorder(struct TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->val);
        inorder(root->right);
    }
}

// Preorder Traversal
void preorder(struct TreeNode* root) {
    if (root != NULL) {
        printf("%d ", root->val);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal
void postorder(struct TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->val);
    }
}

// Find minimum node
struct TreeNode* findMin(struct TreeNode* root) {
    while (root->left != NULL)
        root = root->left;
    return root;
}

// Delete Node
struct TreeNode* deleteNode(struct TreeNode* root, int val, int *found) {
    if (root == NULL)
        return NULL;

    if (val < root->val)
        root->left = deleteNode(root->left, val, found);
    else if (val > root->val)
        root->right = deleteNode(root->right, val, found);
    else {
        *found = 1;

        // Node with one or no child
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children
        struct TreeNode* temp = findMin(root->right);
        root->val = temp->val;
        root->right = deleteNode(root->right, temp->val, found);
    }
    return root;
}

// Check if tree is empty
int isEmpty(struct TreeNode* root) {
    return root == NULL;
}

// Main
int main() {
    struct TreeNode* root = NULL;
    int choice, val;

    while (1) {
        printf("1. Insert Node\n");
        printf("2. In-Order Traversal\n");
        printf("3. Pre-Order Traversal\n");
        printf("4. Post-Order Traversal\n");
        printf("5. Delete Node\n");
        printf("6. Exit\n");

        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Data: ");
                scanf("%d", &val);
                root = insertNode(root, val);
                break;

            case 2:
                if (isEmpty(root))
                    printf("The tree is empty\n");
                else {
                    inorder(root);
                    printf("\n");
                }
                break;

            case 3:
                if (isEmpty(root))
                    printf("The tree is empty\n");
                else {
                    preorder(root);
                    printf("\n");
                }
                break;

            case 4:
                if (isEmpty(root))
                    printf("The tree is empty\n");
                else {
                    postorder(root);
                    printf("\n");
                }
                break;

            case 5: {
                printf("Delete: ");
                scanf("%d", &val);
                int found = 0;
                root = deleteNode(root, val, &found);
                if (!found)
                    printf("Value not found\n");
                break;
            }

            case 6:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}
