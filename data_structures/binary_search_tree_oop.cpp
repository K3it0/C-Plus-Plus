/**
 * @file binary_search_tree_oop.cpp
 * @brief Binary Search Tree Data Structure
 *
 * @details Binary Search Tree is a node-based binary tree data structure which
 * has the following properties:
 *
 * + The left subtree of a node contains only nodes with keys lesser than the
 *   node’s key.
 * + The right subtree of a node contains only nodes with keys greater
 *   than the node’s key.
 * + The left and right subtree each must also be a binary
 *   search tree.
 *
 * Reference used:
 * [GeeksforGeeks]https://www.geeksforgeeks.org/binary-search-tree-data-structure/
 *
 * @author [K3it0](https://github.com/K3it0)
 */

/**
 * @brief Binary Search Tree (BST) Class implementation with basic methods
 *
 * @tparam T Type to store in BST
 */
template <typename T>
class BinarySearchTree {
 public:
    /**
     * @brief Construct a new Binary Search Tree object
     *
     */
    BinarySearchTree() : rootNode(nullptr) {}

    /**
     * @brief Destroy the Binary Search Tree object
     *
     */
    virtual ~BinarySearchTree() { clear(); }

    /**
     * @brief Inserts a value in tree
     *
     * @param value value to insert
     */
    void insertValue(const T& value) {
        if (!rootNode) {
            rootNode = new Node(value);
            return;
        }

        insertHelper(rootNode, value);
        return;
    }

    /**
     * @brief Searches a given element in the tree and returns pointer to it
     *
     * @param target Element to search for
     * @return T* Pointer to found element
     */
    T* findValue(const T& target) {
        Node* targetNode = findNodeHelper(rootNode, target);
        return &(targetNode->value);
    }

    /**
     * @brief Removes given element from the tree
     *
     * @param value Element to delete
     */
    void removeValue(const T& value) { removeNodeHelper(rootNode, value); }

    /**
     * @brief Prints BST inorder
     *
     */
    void printInorder() { printInorderHelper(rootNode); }

    /**
     * @brief clears BST
     *
     */
    void clear() {
        clearTreeHelper(rootNode);
        rootNode = nullptr;
    }

 private:
    struct Node;

    /**
     * @brief Root node of the BST
     *
     */
    Node* rootNode;

    /**
     * @brief Helper function to insert node recursive
     *
     * @param node Root node of current sub-tree
     * @param value Value to insert into BST
     * @return Node* Pointer to root node of current sub-tree
     */
    Node* insertHelper(Node* node, const T& value) {
        if (!node) {
            return new Node(value);
        }

        if (value > node->value) {
            node->rNode = insertHelper(node->rNode, value);
        } else if (value < node->value) {
            node->lNode = insertHelper(node->lNode, value);
        }

        return node;
    }

    /**
     * @brief Finds minimal element in sub-tree
     *
     * @param node Root node for sub-tree to search in
     * @return Node* Minimum node in sub-tree
     */
    Node* findMinNodeInSubTree(Node* node) {
        if (!node->lNode) {
            return node;
        }

        return findMinNodeInSubTree(node->lNode);
    }

    /**
     * @brief Helper function to find node with target value recursive
     *
     * @param node Root node of current sub-tree
     * @param target Value to find in BST
     * @return Node* Pointer to node with target value
     */
    Node* findNodeHelper(Node* node, const T& target) {
        if (!node || node->value == target) {
            return node;
        }

        if (target > node->value) {
            return findNodeHelper(node->rNode, target);
        }

        return findNodeHelper(node->lNode, target);
    }

    /**
     * @brief Helper function to remove node recursively
     *
     * @param node Root node of current sub-tree
     * @param target Value to remove from BST
     * @return Node* Pointer to new root node in sub-tree
     */
    Node* removeNodeHelper(Node* node, const T& target) {
        if (!node) {
            return rootNode;
        }

        if (target < node->value) {
            node->lNode = removeNodeHelper(node->lNode, target);
        } else if (target > node->value) {
            node->rNode = removeNodeHelper(node->rNode, target);
        } else {
            Node* temp = nullptr;

            if (!node->lNode) {
                temp = node->rNode;
                delete node;
                return temp;
            } else if (!node->rNode) {
                temp = node->lNode;
                delete node;
                return temp;
            }

            temp = findMinNodeInSubTree(node->rNode);

            node->value = temp->value;

            node->rNode = removeNodeHelper(node->rNode, temp->value);
        }
        return node;
    }

    /**
     * @brief  Helper function to clear BST recursively
     *
     * @param node Root node of current sub-tree
     */
    void clearTreeHelper(Node* node) {
        if (!node) {
            return;
        }

        // Delete sub-trees
        clearTreeHelper(node->lNode);
        clearTreeHelper(node->rNode);

        // Delete node
        delete node;
        node = nullptr;
    }

    /**
     * @brief Helper function to print BST inorder recursively
     *
     * @param node Root node of current sub-tree
     */
    void printInorderHelper(Node* node) {
        if (node) {
            printInorderHelper(node->lNode);
            std::cout << node->value << std::endl;
            printInorderHelper(node->rNode);
        }
    }
};

/**
 * @brief Node structure [value][*lNode][*rNode]
 *
 * @tparam T Type to store in node
 */
template <typename T>
struct BinarySearchTree<T>::Node {
    /**
     * @brief Construct a new node object
     *
     * @param value Templated value to store in node
     */
    Node(const T& value) : value(value) {}

    /**
     * @brief Templated value for storing element in node
     *
     */
    T value;

    /**
     * @brief Pointer to left node
     *
     */
    typename BinarySearchTree<T>::Node* lNode = nullptr;

    /**
     * @brief Pointer to right node
     *
     */
    typename BinarySearchTree<T>::Node* rNode = nullptr;
};
