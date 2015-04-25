//
//  Final Project
//
//  Created by Margherita Lacapra on 4/19/15
//  Copyright (c) 2015 Margherita Lacapra. All rights reserved.
//

#include "BinaryTree.h"
#include "PrettyPrint.h"
#include <iostream>
#include <iomanip>

using namespace std;

//Constructor
BinaryTree::BinaryTree()
{
    root = NULL;
}

//Destructor
BinaryTree::~BinaryTree()
{
    if (root != NULL)
        deleteAll(root);
}

/*
 Function Prototype:
 TreeNode* BinaryTree::lookup(struct node, int)
 
 Function Description: 
 This function takes a node and the value to search for as parameters and recurs down the tree, choosing the left or right branch by comparing the target value to each node passed in the traversal. Returns the node if found and NULL if not found.
 
 Example: 
 BinaryTree tree;
 tree.lookup(root, 8);
 
 Precondition: 
 The root is not empty and the value passed in the function is the value being searched for in the tree.
 
 Post condition:
 Recurs down the subtrees in search of the value. If found, the function returns the node.
 */

TreeNode* BinaryTree::lookup(int value)
{
    return lookup(root, value);
}

TreeNode* BinaryTree::lookup(TreeNode* node, int value)
{
    // 1. Base case == empty tree
    // in that case, the target is not found so return false
    if (node == NULL)
    {
        return NULL;
    }
    else {
        // 2. see if found here
        if (value == node->key)
            return node;
        else {
            // 3. otherwise recur down the correct subtree
            if (value < node->key) return(lookup(node->left, value));
            else return(lookup(node->right, value));
        }
    }
}

/*
 Function Prototype:
 TreeNoe* BinaryTree::insert(struct node, int);
 
 Function Description:
 This method inserts a given value into the tree. If the tree is empty, the function creates a new node and adds it to the tree. Otherwise, the function recurs down each subtree in search of where to add the new value. Returns the unchanged node once inserted as a way to avoid using reference parameters.
 
 Example: 
 BinaryTree tree;
 tree.insert(root, 8);
 
 Precondition: 
 If the tree is empty, the node becomes the root. Otherwise it is added into the tree.
 
 Post Condition: 
 The tree contains the new node added appropriately and its pointers are updated to reflect the new addition
 */

void BinaryTree::insert(int data)
{
    root = insert(root, data);
}

TreeNode* BinaryTree::insert(TreeNode* node, int data)
{
    // 1. If the tree is empty, return a new, single node
    if (node == NULL)
    {
        TreeNode* node = new TreeNode(data);
        return node;
    }
    else {
        // 2. Otherwise, recur down the tree
        if (data <= node->key) {
            node->left = insert(node->left, data);
            node->left->parent = node;
        }else {
            node->right = insert(node->right, data);
            node->right->parent = node;
        }
        
        return(node); // return the (unchanged) node pointer
    }
}

/*
 Function Prototype:
 void BinaryTree::deleteNode(struct node);
 
 Function Description:
 This function handles three case: the node has no childre, the node has one child (left or right), or the node has two children.
 
 Example:
 BinaryTree tree;
 tree.deleteNode(8);
 
 Precondition: 
 The node to be deleted is in the tree
 
 Post Condition: 
 The node is deleted and the pointers are adjusted to reflect the new tree
 */

void BinaryTree::deleteNode(int value)
{
    TreeNode* node = lookup(value);
    if (node == NULL)
        cout << "Not found." << endl;
    else
        deleteNode(node);
}

void BinaryTree::deleteNode(TreeNode* node)
{
    
    /* if the node to be deleted has no children */
    if (node->left == NULL && node->right == NULL)
    {
        if (node->parent->left == node)
            node->parent->left = NULL;
        else
            node->parent->right = NULL;
        delete node;
    } else if (node->right == NULL)
    {
        /* if the node to be deleted has only leftChild */
        
        if (node->parent->left == node)
            node->parent->left = node->left;
        else
            node->parent->right = node->left;
        
        delete node;
    } else if (node->left == NULL)
    {
        /* if the node to be deleted has only rightChild */
        if (node->parent->left == node)
            node->parent->left = node->right;
        else
            node->parent->right = node->right;
        
        delete node;
    } else if (node->left != NULL && node->right != NULL)
    {
        /* if the node to be deleted has two children */
        // Start on the right sub-tree
        TreeNode * replacementNode = node->right;
        
        // search for the smallest left child
        while (replacementNode->left != NULL)
        {
            replacementNode = replacementNode->left;
        }
        
        // Swap in the info from the replacement to this node we are "deleting"
        node->key = replacementNode->key;
        
        // If the replacement node has a right child, update the parent
        if (replacementNode->right != NULL)
            replacementNode->right->parent = replacementNode->parent;
        
        // If the replacement node is a left child
        if (replacementNode->parent->left == replacementNode)
            replacementNode->parent->left = replacementNode->right;
        // If it is a right child
        else
            replacementNode->parent->right = replacementNode->right;
        
        // Delete the node
        delete replacementNode;
    }
}

/*
 Function Prototype:
 void BinaryTree::deleteAll(struct node);
 
 Function Description:
 This function recurs down each subtree and deletes each node
 
 Example:
 BinaryTree tree;
 tree.deleteAll(root);
 
 Precondition: 
 There is at least one node in the tree
 
 Post Condition: 
 The nodes are deleted and the tree is empty. The root is set to NULL
 */

void BinaryTree::deleteAll()
{
   if (root != NULL)
       deleteAll(root);
    root = NULL;
}

void BinaryTree::deleteAll(TreeNode* node)
{
    if (node->left)
        deleteAll(node->left);
    if (node->right)
        deleteAll(node->right);
    delete node;
}

/*
 Function Prototype:
 int BinaryTree::size(struct node);
 
 Function Description:
 This function computes the number of nodes in the tree. Returns the number of nodes in the tree if successful, and 0 if the tree is empty.
 
 Example:
 BinaryTree tree;
 tree.size(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 Function recursively calls itself and sums the root to the number of nodes found in each subtree
 */

int BinaryTree::size()
{
    return size(root);
}

int BinaryTree::size(TreeNode* node)
{
    if (node == NULL)
        return 0;
    
    return(size(node->left) + 1 + size(node->right));
}

/*
 Function Prototype:
 int BinaryTree::maxDepth(struct node);
 
 Function Description:
 This function computes the number of nodes along the longest path from the root node to the farthest leaf node and returns an integer value which is the maximum height of the tree
 
 Example:
 BinaryTree tree;
 tree.maxDepth(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 The heights of each subtree are computed and the function returns the larger one of the two, adding 1 to represent the root
 
 */

int BinaryTree::maxDepth()
{
    return maxDepth(root);
}

int BinaryTree::maxDepth(TreeNode* node)
{
    if (node == NULL)
        return 0;

    // compute the depth of each subtree
    int lDepth = maxDepth(node->left);
    int rDepth = maxDepth(node->right);
    
    // use the larger one
    if (lDepth > rDepth)
        return(lDepth+1);
    
    return(rDepth+1);
    
}

/*
 Function Prototype:
 int BinaryTree::minValue(struct node);
 
 Function Description:
 This function recurs down the left subtree in search of the smallest value. When found, it returns the value
 
 Example:
 BinaryTree tree;
 tree.minValue(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 The smallest value found is returned
 */

int BinaryTree::minValue()
{
    return minValue(root);
}

int BinaryTree::minValue(TreeNode* node)

{
    TreeNode* current = node;
    // loop down to find the leftmost leaf
    
    while (current->left != NULL)
    {
        current = current->left;
    }
    
    return(current->key);
}

/*
 Function Prototype:
 int BinaryTree::maxValue(struct node);
 
 Function Description:
 This function recurs down the right subtrees starting from the root in search of the largest value. When found, the function returns that value
 
 Example:
 BinaryTree tree;
 tree.maxValue(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 The largest value found is returned
 */

int BinaryTree::maxValue()
{
    return maxValue(root);
}

int BinaryTree::maxValue(TreeNode* node)
{
    
    TreeNode* current = node;
    
    // loop down to find the rightmost leaf
    
    while (current->right != NULL)
        
    {
        current = current->right;
    }
    
    return(current->key);
}

/*
 Function Prototype:
 void BinaryTree::printPostOrder(struct node);
 
 Function Description:
 This function prints the tree nodes in a bottom-up postorder traversal
 
 Example:
 BinaryTree tree;
 tree.printPostOrder(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 The function recurs down both subtrees and then prints the nodes with a space between them
 */

void BinaryTree::printPostOrder()
{
    cout << "Print Post Order: ";
    printPostOrder(root);
    cout << endl;
}

void BinaryTree::printPostOrder(TreeNode* node)
{
    if (node == NULL)
        return;
    
    // first recur on both subtrees
    printPostOrder(node->left);
    printPostOrder(node->right);
    
    // then deal with the node
    cout << node->key << " ";
}

/*
 Function Prototype:
 void BinaryTree::printPreOrder(struct node);
 
 Function Description:
 This function recurs down both subtrees and prints the nodes from the top down
 
 Example:
 BinaryTree tree;
 tree.printPreOrder(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 The nodes are printed from the top down with a space between them
 */

void BinaryTree::printPreOrder()
{
    cout << "Print Pre Order: ";
    printPreOrder(root);
    cout << endl;
}

void BinaryTree::printPreOrder(TreeNode* node)
{
    if (node == NULL)
        return;
    
    cout << node->key << " ";

    printPreOrder(node->left);
    printPreOrder(node->right);
}

/*
 Function Prototype:
 void BinaryTree::printInOrder(struct node);
 
 Function Description:
 This function prints the nodes in order starting from the left and then going on the right
 
 Example:
 BinaryTree tree;
 tree.printInOrder(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 The nodes are printed in numerical order starting with the left and then recurring down the right
 */

void BinaryTree::printInOrder()
{
    cout << "Print In Order: ";
    printInOrder(root);
    cout << endl;
}

void BinaryTree::printInOrder(TreeNode* node)
{
    if (node == NULL)
        return;
    
    // first recur on both subtrees
    printInOrder(node->left);
    cout << node->key << " ";
    printInOrder(node->right);
}

void BinaryTree::prettyPrint()
{
    printPretty(root, maxDepth(), 1, 0);
}

/*
 Function Prototype:
 bool BinaryTree::hasPathSum(int);
 
 Function Description:
 This function takes a sum to be searched for and checks if the tree has a root-to-leaf path that makes the sum once all the values along it are added up. Returns true if the path is found, otherwise it returns false.
 
 Example:
 BinaryTree tree;
 tree.hasPathSum(76);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 If the sum is equal to the value being searched for, the function returns true. Otherwise it returns false
*/

bool BinaryTree::hasPathSum(int sum)
{
    return hasPathSum(root, sum);
}

bool BinaryTree::hasPathSum(TreeNode* node, int sum)
{
    if (node)
        return hasPathSum(node->left, sum - node->key) || hasPathSum(node->right, sum - node->key);
    
    if (sum == 0)
        return true;
    else
        return false;
}

/*
 Function Prototype:
 void BinaryTree::mirror(struct node);
 
 Function Description:
 This function mirrors the tree
 
 Example:
 BinaryTree tree;
 tree.mirror(root);
 
 Precondition:
 There are nodes in the tree
 
 Post Condition:
 The function recurs down each subtree and then swaps the pointers accordingly to mirror the tree
 */

void BinaryTree::mirror()
{
    return mirror(root);
}

void BinaryTree::mirror(TreeNode* node)
{
    if (node == NULL)
        return;

    TreeNode* temp;
        
    // do the subtrees
    mirror(node->left);
    mirror(node->right);
        
    // swap the pointers in this node
    temp = node->left;
    node->left = node->right;
    node->right = temp;
}

/*
 Function Prototype:
 void BinaryTree::doubleTree(struct node);
 
 Function Description:
 For each node in the tree, the function creates a duplicate node and inserts it as the left child of the original node
 
 Example:
 BinaryTree tree;
 tree.doubleTree(root);
 
 Precondition:
 The tree is not empty
 
 Post Condition:
 The node is duplicated and the pointers are adjusted to make the new node the left child of the original
 */

void BinaryTree::doubleTree()
{
    return doubleTree(root);
}

void BinaryTree::doubleTree(TreeNode* node)
{
    TreeNode* oldLeft;
    
    if (node == NULL)
        return;
    
    // do the subtrees
    
    doubleTree(node->left);
    doubleTree(node->right);
    
    // duplicate this node to its left
    oldLeft = node->left;
    
    TreeNode* newNode = new TreeNode(node->key);
    
    node->left = newNode;
    
    node->left->left = oldLeft;
}

/*
 Function Prototype:
 bool BinaryTree::isBST(struct node);
 
 Function Description:
 This function takes the root as a parameter and checks to see if the tree is a balanced Binary Search Tree
 
 Example:
 BinaryTree tree;
 tree.isBST(root);
 
 Precondition:
 The tree is not empty
 
 Post Condition:
 All of the leftChildren are less than the parent and the rightChildren are greater than the parent
 */

bool BinaryTree::isBST()
{
    return isBST(root);
}

bool BinaryTree::isBST(TreeNode* node)

{
    if (node == NULL)
        return(true);
    
    // false if the max of the left is > than us
    
    if (node->left != NULL && maxValue(node->left) > node->key)
        return(false);
    
    // false if the min of the right is <= than us
    
    if (node->right != NULL && minValue(node->right) <= node->key)
        return(false);
    
    // false if, recursively, the left or right is not a BST
    
    if (!isBST(node->left) || !isBST(node->right))
        return(false);
    
    // passing all that, it's a BST
    return(true);
}

