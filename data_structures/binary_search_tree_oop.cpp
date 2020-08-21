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

#include <iostream>
#include <memory>

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
    template <typename T>
    void insertValue(T&& value) {
        if (!rootNode) {
            rootNode = std::make_shared<Node>(value);
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
    template <typename T>
    std::shared_ptr<T> findValue(T&& target) {
        std::shared_ptr<Node> targetNode = findNodeHelper(rootNode, target);
        return std::make_shared<T>(targetNode->value);
    }

    /**
     * @brief Removes given element from the tree
     *
     * @param value Element to delete
     */
    void removeValue(T&& value) { removeNodeHelper(rootNode, value); }

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
    struct Node;  //< Node structure [value][*lNode][*rNode]

    std::shared_ptr<Node> rootNode;  //< Root node of the BST

    /**
     * @brief Helper function to insert node recursive
     *
     * @param node Root node of current sub-tree
     * @param value Value to insert into BST
     * @return Node* Pointer to root node of current sub-tree
     */
    template <typename T>
    std::shared_ptr<Node> insertHelper(std::shared_ptr<Node> node, T&& value) {
        if (!node) {
            return std::make_shared<Node>(value);
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
    std::shared_ptr<Node> findMinNodeInSubTree(std::shared_ptr<Node> node) {
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
    template <typename T>
    std::shared_ptr<Node> findNodeHelper(std::shared_ptr<Node> node,
                                         T&& target) {
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
    template <typename T>
    std::shared_ptr<Node> removeNodeHelper(std::shared_ptr<Node> node,
                                           T&& target) {
        if (!node) {
            return rootNode;
        }

        if (target < node->value) {
            node->lNode = removeNodeHelper(node->lNode, target);
        } else if (target > node->value) {
            node->rNode = removeNodeHelper(node->rNode, target);
        } else {
            std::shared_ptr<Node> temp = nullptr;

            if (!node->lNode) {
                temp = node->rNode;
                node.reset();
                return temp;
            } else if (!node->rNode) {
                temp = node->lNode;
                node.reset();
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
    void clearTreeHelper(std::shared_ptr<Node> node) {
        if (!node) {
            return;
        }

        // Delete sub-trees
        clearTreeHelper(node->lNode);
        clearTreeHelper(node->rNode);

        // Delete node
        node.reset();
    }

    /**
     * @brief Helper function to print BST inorder recursively
     *
     * @param node Root node of current sub-tree
     */
    void printInorderHelper(std::shared_ptr<Node> node) {
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
    Node(T& value) : value(value), lNode(nullptr), rNode(nullptr) {}

    T value;  //< Templated value for storing element in node

    typename std::shared_ptr<BinarySearchTree<T>::Node>
        lNode;  //< Pointer to left node

    typename std::shared_ptr<BinarySearchTree<T>::Node>
        rNode;  //< Pointer to right node
};
