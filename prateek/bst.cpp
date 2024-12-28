#include <iostream>
#include <cstdlib>
#include <vector>
#include<set>
#include <unordered_set>
using namespace std;

struct tree {
    int data;
    struct tree* left;
    struct tree* right;
};

typedef struct tree TREE;

class BST {
public:
    TREE* insert_into_bst(TREE*, int);
    void inorder(TREE*);
    void preorder(TREE*);
    void postorder(TREE*);
    TREE* delete_from_bst(TREE*, int);
    void degree(TREE*);
    void address(TREE* root);
    TREE* search(TREE* root, int data);
    int edges(TREE* , int&);
    void lesser(TREE*, int ,int* ,int &);
    TREE* findMin(TREE* root);
    TREE* findMax(TREE* root);
    TREE* create_node(int data);
    void load(TREE* root, vector<int>& arr);
    size_t calculateMemoryUsage(TREE*,int&);
    tree* delete_greater_than(tree* root, int K);
    TREE* delete_lesser_than(tree* root, int K);
    tree* inorder_predecessor(tree* root, int data);
    void  display_tree(tree* root);
    tree* inorder_successor(tree* root, int data);
    int count_leaf_nodes(tree* root);
    int out_degree_of_leaves(tree* root);
    int count_level_1(tree* root);
    tree* delete_duplicates(tree* root, set<int>& seen);
    tree* duplicate_tree(tree* root, tree* dup);
    int comparisons_to_search(tree* root, int data);
    TREE* findLargest(TREE* root);
    int findEdges(TREE* root, TREE* target, int edges);
    void removeDuplicates(TREE* &root);
    void removeDuplicates(TREE* &root, unordered_set<int> &seen);
    void deleteNode(TREE* &node);
};

// Function to insert a node into the BST
TREE* BST::insert_into_bst(TREE* root, int data) {
    TREE* newnode = (TREE*)malloc(sizeof(TREE));
    if (newnode == NULL) {
        cout << "Memory allocation failed" << endl;
        return root;
    }
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;

    if (root == NULL) {
        // Correct the assignment
        root = newnode;
        cout << "Root node inserted into tree" << endl;
        return root;
    }

    TREE* currnode = root;
    TREE* parent = NULL;

    while (currnode != NULL) {
        parent = currnode;
        if (newnode->data < currnode->data)
            currnode = currnode->left;
        else
            currnode = currnode->right;
    }

    if (newnode->data < parent->data)
        parent->left = newnode;
    else
        parent->right = newnode;

    cout << "Node inserted successfully" << endl;
    return root;
}

// Function to perform inorder traversal
void BST::inorder(TREE* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->data << "\t";
        inorder(root->right);
    }
}

// Function to perform preorder traversal
void BST::preorder(TREE* root) {
    if (root != NULL) {
        cout << root->data << "\t";
        preorder(root->left);
        preorder(root->right);
    }
}

// Function to perform postorder traversal
void BST::postorder(TREE* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << "\t";
    }
}

void BST::degree(TREE* root) {
    int op = 0;
    if (root!=NULL) {
        if(root->left && root->right) {
            op = 2;
        }
    else if(root->left || root->right) {
        op = 1;
    }
    }
    cout << "The outdegree of root is " << op << endl;
    cout << "The indegree of root is always 0" << endl;

}
void BST::address (TREE* root) {
    if(root != NULL) {
        cout << root << endl;
    }
    else {
        cout <<"No root node is present\n";
    }
}

TREE* BST::search(TREE* root, int data) {
    if (root == NULL) {
        cout << "Number not present\n";
        return NULL;
    }

    if (root->data == data) {
        cout << "Number is found\n";
        return root;
    }

    if (data < root->data)
        return search(root->left, data);
    else
        return search(root->right, data);
}

int BST::edges(TREE* root,int &cnt) {
    if(root != NULL) {
        edges(root->left,cnt);
        cnt++;
        edges(root->right,cnt);
    }
    return cnt;
}

void BST::lesser(TREE* root,int key,int a[],int &i) {
    if (root != NULL) {
        lesser(root->left,key,a,i);
        a[i++] = root->data;
        lesser(root->right,key,a,i);
    }
}
TREE* BST::findMin(TREE* root) {
    if (root == NULL) {
        cout << "The tree is empty.\n";
        return NULL;
    }

    TREE* current = root;
    while (current->left != NULL) {
        current = current->left;
    }

    return current;
}

TREE* BST::findMax(TREE* root) {
    if (root == NULL) {
        cout << "The tree is empty.\n";
        return NULL;
    }

    TREE* current = root;
    while (current->right != NULL) {
        current = current->right;
    }

    return current;
}

void BST::load(TREE* root, vector<int>& arr) {
    if (root != NULL) {
        load(root->left, arr);
        arr.push_back(root->data);
        load(root->right, arr);
    }
}

size_t BST::calculateMemoryUsage(TREE* root,int &cnt) {
    if (root == NULL) {
        return 0;
    }

    return (sizeof(TREE)*edges(root,cnt));
}

tree* BST:: delete_lesser_than(tree* root, int K) {
        if (root == NULL) 
            return root;
        root->left = delete_lesser_than(root->left, K);
        root->right = delete_lesser_than(root->right, K);
        if (root->data < K) {
            tree* right_subtree = root->right;
            delete root;
            return right_subtree;
        }
        return root;
    }

tree* BST::delete_greater_than(tree* root, int K) {
        if (root == NULL) return root;
        root->left = delete_greater_than(root->left, K);
        root->right = delete_greater_than(root->right, K);
        if (root->data > K) {
            tree* left_subtree = root->left;
            delete root;
            return left_subtree;
        }
        return root;
    }


tree* BST::inorder_successor(tree* root, int data) {
        tree* successor = NULL;
        while (root != NULL) {
            if (data < root->data) {
                successor = root;
                root = root->left;
            } else {
                root = root->right;
            }
        }
        return successor;
    }

tree* BST::inorder_predecessor(tree* root, int data) {
        tree* predecessor = NULL;
        while (root != NULL) {
            if (data > root->data) {
                predecessor = root;
                root = root->right;
            } else {
                root = root->left;
            }
        }
        return predecessor;
    }

int BST::count_leaf_nodes(tree* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return 1;
        return count_leaf_nodes(root->left) + count_leaf_nodes(root->right);
    }

    int BST::out_degree_of_leaves(tree* root) {
        if (root == NULL) return 0;
        if (root->left == NULL && root->right == NULL) return 0;
        return out_degree_of_leaves(root->left) + out_degree_of_leaves(root->right);
    }

 int BST::count_level_1(tree* root) {
        if (root == NULL) return 0;
        int count = 0;
        if (root->left != NULL) count++;
        if (root->right != NULL) count++;
        return count;
    }

tree* BST::delete_duplicates(tree* root, set<int>& seen) {
        if (root == NULL) return root;
        root->left = delete_duplicates(root->left, seen);
        root->right = delete_duplicates(root->right, seen);
        if (seen.find(root->data) != seen.end()) {
            tree* temp = delete_from_bst(root, root->data);
            return temp;
        } else {
            seen.insert(root->data);
        }
        return root;
    }
void BST::display_tree(tree* root) {
        if (root == NULL) {
            cout << "Tree is empty." << endl;
            return;
        }
        cout << "Current elements in the tree (in-order): ";
        inorder(root);
        cout << endl;
    }

tree* BST::create_node(int data) {
        tree* new_node = new tree();
        new_node->data = data;
        new_node->left = new_node->right = NULL;
        return new_node;
};
tree* BST::duplicate_tree(tree* root, tree* dup) {
    if (root == NULL)
        return NULL;

    dup = (tree*)malloc(sizeof(struct tree));
    if (dup == NULL)
        exit(0);

    dup->data = root->data;
    dup->left = duplicate_tree(root->left, dup->left);
    dup->right = duplicate_tree(root->right, dup->right);

    return dup;
}

int BST::comparisons_to_search(tree* root, int data) {
        int comparisons = 0;
        while (root != NULL) {
            comparisons++;
            if (data == root->data) return comparisons;
            root = (data < root->data) ? root->left : root->right;
        }
        return comparisons;
    }

TREE* BST::findLargest(TREE* root) {
    if (root == NULL) return NULL;
    TREE* largest = root;
    TREE* leftLargest = findLargest(root->left);
    TREE* rightLargest = findLargest(root->right);
    if (leftLargest && leftLargest->data > largest->data) largest = leftLargest;
    if (rightLargest && rightLargest->data > largest->data) largest = rightLargest;
    return largest;
}

int BST::findEdges(TREE* root, TREE* target, int edges) {
    if (root == NULL) return -1;
    if (root == target) return edges;
    int leftEdges = findEdges(root->left, target, edges + 1);
    if (leftEdges != -1) return leftEdges;
    return findEdges(root->right, target, edges + 1);
}

void BST::deleteNode(TREE* &node) {
    if (node) {
        deleteNode(node->left);
        deleteNode(node->right);
        delete node;
        node = nullptr;
    }
}

void BST::removeDuplicates(TREE* &root, unordered_set<int> &seen) {
    if (!root) return;

    // Check if the current node's value is already seen
    if (seen.find(root->data) != seen.end()) {
        // Delete the current node
        deleteNode(root);
    } else {
        // Mark the current node's value as seen
        seen.insert(root->data);
        // Recursively check left and right subtrees
        removeDuplicates(root->left, seen);
        removeDuplicates(root->right, seen);
    }
}

void BST::removeDuplicates(TREE* &root) {
    unordered_set<int> seen;
    removeDuplicates(root, seen);
}


// Function to delete a node from the BST
TREE* BST::delete_from_bst(TREE* root, int data) {
    TREE* currnode = root;
    TREE* parent = NULL;
    TREE* successor = NULL;
    TREE* p = NULL;

    if (root == NULL) {
        cout << "Tree is empty" << endl;
        return root;
    }

    // Find the node to be deleted
    while (currnode != NULL && currnode->data != data) {
        parent = currnode;
        if (data < currnode->data)
            currnode = currnode->left;
        else
            currnode = currnode->right;
    }

    if (currnode == NULL) {
        cout << "Item not found" << endl;
        return root;
    }

    // Case 1: Node has no or one child
    if (currnode->left == NULL)
        p = currnode->right;
    else if (currnode->right == NULL)
        p = currnode->left;
    else {
        // Case 2: Node has two children
        successor = currnode->right;
        TREE* successorParent = currnode;

        // Find the in-order successor (smallest in right subtree)
        while (successor->left != NULL) {
            successorParent = successor;
            successor = successor->left;
        }

        // Replace current node's data with successor's data
        currnode->data = successor->data;

        // Remove the successor node
        if (successorParent->left == successor)
            successorParent->left = successor->right;
        else
            successorParent->right = successor->right;

        free(successor);
        return root;
    }

    // If node to be deleted is root
    if (parent == NULL) {
        free(currnode);
        return p;
    }

    // Re-attach parent to the new subtree
    if (currnode == parent->left)
        parent->left = p;
    else
        parent->right = p;

    free(currnode);
    return root;
}

int main() {
    BST bst;
    TREE* root = NULL;
    TREE* head = NULL;
    int choice = 0;
    int data = 0,i = 0;
    int cnt = 0,k;
    set<int> seen_duplicates;

    while (1) {
        cout << "\n ****** MENU ******\n";
        cout << "1. Insert into BST\n";
        cout << "2. Inorder traversal\n";
        cout << "3. Preorder traversal\n";
        cout << "4. Postorder traversal\n";
        cout << "5. Delete from BST\n";
        cout << "6. Out degree and In degree\n";
        cout << "7. Address of the root node\n";
        cout << "8. Search a node\n";
        cout << "9. Edges of a node\n";
        cout << "10. Count of a node\n";
        cout << "11. Number of nodes lesser than key value\n";
        cout << "12. Number of nodes greater than key value\n";
        cout << "13. Lowest value in the tree\n";
        cout << "14. Maximum value in the tree\n";
        cout << "15. Delete nodes greater than k\n";
        cout << "16. Deletes nodes lesser than k\n";
        cout << "17. Calculate memory used in bytes\n";
        cout << "18. Print in-order successor of an item\n";
        cout << "19. Print in-order predecessor of an item\n";
        cout << "20. Count the number of leaf nodes\n";
        cout << "21. Load all the tree elements into an array\n";
        cout << "22. Print total out-degree of all leaf nodes\n";
        cout << "23. Count nodes at level 1\n";
        cout << "24. Count comparisons to search for an item\n";
        cout << "25. Count comparisons to search for maximum element\n";
        cout << "26. Number of root and leaf nodes\n";
        cout << "27. Edges between root node and max element\n";
        cout << "28. Copy of binary tree\n";
        cout << "29. Delete duplicates in the tree\n";
        cout << "*\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter the item to insert: ";
            cin >> data;
            root = bst.insert_into_bst(root, data);
            break;

        case 2:
            if (root == NULL)
                cout << "Tree is empty\n";
            else {
                cout << "Inorder traversal is...\n";
                bst.inorder(root);
                cout << endl;
            }
            break;

        case 3:
        {
            if (root == NULL)
                cout << "Tree is empty\n";
            else {
                cout << "Preorder traversal is...\n";
                bst.preorder(root);
                cout << endl;
            }
            break;
        }

        case 4:
        {
            if (root == NULL)
                cout << "Tree is empty\n";
            else {
                cout << "Postorder traversal is...\n";
                bst.postorder(root);
                cout << endl;
            }
            break;
        }

        case 5:
        {
            cout << "Enter the item to be deleted: ";
            cin >> data;
            root = bst.delete_from_bst(root, data);
            break;
        }

        case 6:
        {
            bst.degree(root);
            break;
        }

        case 7:
        {
            bst.address(root);
            break;
        }

        case 8:
        {
            cout << "Enter the number to search: ";
            cin >> data;
            bst.search(root, data);
            break;
        }

        case 9:
        {
            cnt = 0;
            cnt = bst.edges(root,cnt);
            if(cnt!=0){
                cout << "The number of edges are " << cnt-1 << endl;
            }
            else {

                cout << "No nodes are present " << endl;
            }
            break;
        }

        case 10:
        {
            cnt = 0;
            cnt = bst.edges(root,cnt);
            if(cnt!=0){
                cout << "The number elements are " << cnt << endl;
            }
            else {

                cout << "No nodes are present " << endl;
            }
            break;
        }

        case 11:
        {
            i=0;
            cnt = 0;
            int a[20],key;
            cout << "Enter the key value: ";
            cin >> key;
            bst.lesser(root,key,a,i);

            i=0;
            while(a[i]!='\0') {
                if(a[i] < key) {
                    cnt++;
                }
                else {
                    break;
                }
                i++;
            }

            cout << "Number of nodes lesser than key value are: " << cnt << endl;
            break;
        }

        case 12:
            {
                i=0;
                cnt = 0;
                int b[20],keyss;
                cout << "Enter the key value: ";
                cin >> keyss;
                bst.lesser(root,keyss,b,i);

                i=0;
                while(b[i]!='\0') {
                    if(b[i] > keyss) {
                        cnt++;
                    }
                    i++;
                }

                cout << "Number of nodes greater than key value are: " << cnt << endl;
                break;
            }

        case 13:
            {
             TREE* minNode = bst.findMin(root);
                if (minNode != NULL) {
                cout << "The minimum value in the BST is: " << minNode->data << endl;
                }
                break;
            }

        case 14:
            {
                 TREE* maxNode;
               maxNode = bst.findMax(root);
                if (maxNode != NULL) {
                cout << "The maximum value in the BST is: " << maxNode->data << endl;
                }
                break;

            }
        case 15:
            {
                cout << "Enter the value of K: ";
                cin >> k;
                cout << "Nodes greater than " << k << ": " << bst.delete_greater_than(root, k) << endl;
                break;
            }
        case 16:
            {
                cout << "Enter the value of K: ";
                cin >> k;
                cout << "Nodes lesser than " << k << ": " << bst.delete_lesser_than(root, k) << endl;
                break;
            }

        case 17:
            {
                size_t memoryUsage = bst.calculateMemoryUsage(root,cnt);
                cout << "Total memory used by the binary tree: " << memoryUsage << " bytes" << endl;
                break;

            }

        case 18:
            {
                cout << "Enter the item to find its in-order successor: ";
                cin >> data;
                if (tree* succ = bst.inorder_successor(root, data))
                    cout << "In-order successor of " << data << " is: " << succ->data << endl;
                else
                    cout << "In-order successor does not exist.\n";
                break;
            }

        case 19:
            {
                cout << "Enter the item to find its in-order predecessor: ";
                cin >> data;
                if (tree* pred = bst.inorder_predecessor(root, data))
                    cout << "In-order predecessor of " << data << " is: " << pred->data << endl;
                else
                    cout << "In-order predecessor does not exist.\n";
                break;
            }

        case 20:
            {
                cout << "Number of leaf nodes: " << bst.count_leaf_nodes(root) << endl;
                break;
            }

        case 21:
        {
            if (root == NULL) {
                cout << "Tree is empty\n";
            } else {
                vector<int> arr;
                bst.load(root, arr);
                cout << "Tree elements in sorted order:\n";
                for (int val : arr) {
                    cout << val << " ";
                }
                cout << endl;
            }
            break;
        }

        case 22:
            {
                cout << "Total out-degree of all leaf nodes: " << bst.out_degree_of_leaves(root) << endl;
                break;
            }

        case 23:
            {
                cout << "Nodes at level 1: " << bst.count_level_1(root) << endl;
                break;
            }

        case 24:
            {
                cout << "Enter the item to search for comparisons: ";
                cin >> data;
                cout << "Comparisons made to search for " << data << ": " << bst.comparisons_to_search(root, data) << endl;
                break;
            }
        case 25:
            {
                TREE* maxNode;
                maxNode = bst.findMax(root);
                int cnt = 0;
                bst.edges(root,cnt);
                cout << "The maximum element of the the tree is " << maxNode->data << endl;
                cout << "The number of comparisons required is " << cnt-1 << endl;
                break;
            }

        case 26:
            {
                cout << "Number of external nodes: " << (bst.count_leaf_nodes(root) + 1) << endl;
                break;
            }
        case 27:
            {
                TREE* largest = bst.findLargest(root);
                int edges = bst.findEdges(root, largest, 0);

                cout << "Number of edges between root and largest element: " << edges << endl;
                break;
            }
        case 28:
                if(root)
                {
                    head = bst.duplicate_tree(root, NULL);
                    cout << "Address of duplicate of the tree " << head << endl;
                    bst.inorder(head);
                }
                else
                    cout << "TREE is empty\n";
                    break;


        case 29:
            {
                cout<<"removing duplicates from the tree\n";
                bst.removeDuplicates(root);
                cout<<"tree after removing duplicates\n";
                bst.inorder(root);
            }

        default:
            {
            cout << "Invalid choice. Exiting...\n";
            exit(0);
            }
        }
    }
    return 0;
}
