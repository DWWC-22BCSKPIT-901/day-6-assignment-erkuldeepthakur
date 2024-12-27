#include <iostream>
#include <queue>

using namespace std;

// Definition for a binary tree node with a `next` pointer.
struct Node {
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    Node(int _val, Node* _left, Node* _right, Node* _next) 
        : val(_val), left(_left), right(_right), next(_next) {}
};

// Function to connect next pointers in the tree.
Node* connect(Node* root) {
    if (!root) return nullptr;

    Node* current = root;

    // Outer loop to traverse levels
    while (current) {
        Node* dummy = new Node(0); // Dummy node for the next level
        Node* temp = dummy;

        // Inner loop to traverse nodes within the current level
        while (current) {
            if (current->left) {
                temp->next = current->left;
                temp = temp->next;
            }
            if (current->right) {
                temp->next = current->right;
                temp = temp->next;
            }
            current = current->next; // Move to the next node in the current level
        }

        current = dummy->next; // Move to the next level
        delete dummy; // Clean up the dummy node
    }

    return root;
}

// Helper function to print tree in level order using next pointers.
void printLevelOrder(Node* root) {
    Node* levelStart = root;

    while (levelStart) {
        Node* current = levelStart;
        levelStart = nullptr;

        while (current) {
            cout << current->val << " ";
            if (!levelStart) {
                if (current->left) levelStart = current->left;
                else if (current->right) levelStart = current->right;
            }
            current = current->next;
        }
        cout << "# "; // End of level
    }
    cout << endl;
}

// Example usage.
int main() {
    // Construct the tree from the example: [1,2,3,4,5,null,7]
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(7);

    // Connect the next pointers
    root = connect(root);

    // Print the tree level order traversal using next pointers
    cout << "Level Order Traversal with Next Pointers: ";
    printLevelOrder(root);

    return 0;
}
