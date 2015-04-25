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
 TreeNode* BinaryTree::lookup(int)
 
 Function Description: 
 This function takes a value to search for as a parameter and calls the recursive lookup function below, starting from the root of the tree. It recurs down the tree, choosing the left or right branch by comparing the target value to the node passed in the traversal. Returns node if found and NULL if not found.
 
 Example: 
 BinaryTree tree;
 tree.lookup(8);
 
 Precondition: 
 The parameter is an integer value
 
 Post condition:
 The tree is unchanged. The return value is NULL if the value is not found, otherwise returns the pointer to the node with the given value.
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
 TreeNode* BinaryTree::insert(int)
 
 Function Description:
 This method takes the value to insert as a parameter and calls the recursive insert function to add the value to the tree. If the tree is empty, the function creates a new node and adds it to the tree as the root. Otherwise, the function recurs down each subtree in search of where to add the new value. Returns a pointer to the new node.
 
 Example: 
 BinaryTree tree;
 tree.insert(8);
 
 Precondition: 
 The parameter is an integer value.
 
 Post Condition: 
 The new node is inserted into the tree. Returns a pointer to the new node.
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
 void BinaryTree::deleteNode(int);
 
 Function Description:
 This function calls the lookup function to ensure the value being deleted is in the tree. It returns NULL if not found, otherwise it calls the deleteNode function which evaluates three cases: the node to be deleted has one child (left or right), no children, or two children. The function adjusts the parent and children pointers to re-adjust the tree.
 
 Example:
 BinaryTree tree;
 tree.deleteNode(8);
 
 Precondition: 
 The parameter is an integer
 
 Post Condition: 
 The node is deleted and the pointers are adjusted to reflect the new tree. Returns NULL if the node is not found.
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
 void BinaryTree::deleteAll();
 
 Function Description:
 This function 
 
 Example:
 BinaryTree tree;
 tree.deleteAll();
 
 Precondition: 
 None
 
 Post Condition: 
 The nodes are deleted and the tree is empty. The root is set to NULL in either case.
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
 int BinaryTree::size();
 
 Function Description:
 This function returns the call to the size function and recurs down the tree to compute the size. The function returns NULL if the tree is empty, otherwise it returns the integer size.
 
 Example:
 BinaryTree tree;
 tree.size();
 
 Precondition:
 None
 
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
 int BinaryTree::maxDepth();
 
 Function Description:
 This function returns the call to the recursive maxDepth function starting from the root of the tree. Returns the integer value for the maximum depth once it compares the length of the subtrees, otherwise it returns NULL if the tree is empty.
 
 Example:
 BinaryTree tree;
 tree.maxDepth();
 
 Precondition:
 None
 
 Post Condition:
 The tree is unchanged. Returns the maximum height of the tree once found. Otherwise, returns NULL if the tree is empty.
 
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
 int BinaryTree::minValue();
 
 Function Description:
 This function returns the call to the minimum value function that starts from the root and recurs down the left subtree in search of the leftmost leaf. Returns the smallest value when found. If the tree is empty, the function returns 0.
 
 Example:
 BinaryTree tree;
 tree.minValue();
 
 Precondition:
 None
 
 Post Condition:
 The smallest value found is returned, otherwise the function returns 0.
 */

int BinaryTree::minValue()
{
    return minValue(root);
}

int BinaryTree::minValue(TreeNode* node)

{
    TreeNode* current = node;
    if (current == NULL)
        return 0;
    
    while (current->left != NULL)
    {
        current = current->left;
    }
    
    return(current->key);
}

/*
 Function Prototype:
 int BinaryTree::maxValue();
 
 Function Description:
 This function returns the call to the maxValue function starting from the root of the tree and recurring down the right subtree in search of the rightmost leaf. Returns 0 if the node is NULL, otherwise returns the value of the rightmost leaf.
 
 Example:
 BinaryTree tree;
 tree.maxValue();
 
 Precondition:
 None
 
 Post Condition:
 The largest value found is returned. Otherwise, the function returns 0 if the tree is empty.
 */

int BinaryTree::maxValue()
{
    return maxValue(root);
}

int BinaryTree::maxValue(TreeNode* node)
{
    
    TreeNode* current = node;
    if (current == NULL)
        return 0;
    
    // loop down to find the rightmost leaf
    
    while (current->right != NULL)
    {
        current = current->right;
    }
    
    return(current->key);
}

/*
 Function Prototype:
 void BinaryTree::printPostOrder();
 
 Function Description:
 This function prints the statement and then calls the recursive function printPostOrder to recur down each of the subtrees and print them bottoms up. If the tree is empty, the function returns. Otherwise, it prints the bottoms up traversal with a space between the values.
 
 Example:
 BinaryTree tree;
 tree.printPostOrder();
 
 Precondition:
 None
 
 Post Condition:
 The keys are printed with a space between them if the tree is not empty. Otherwise it returns.
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
 void BinaryTree::printPreOrder();
 
 Function Description:
 This function prints the cout statement and then calls the recursive printPreOrder function starting from the root and recurring down each subtree, printing them first from the left and then from the right. Returns if the tree is empty.
 
 Example:
 BinaryTree tree;
 tree.printPreOrder();
 
 Precondition:
 None
 
 Post Condition:
 The nodes are printed from the top down with a space between them. Otherwise the function returns.
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
 void BinaryTree::printInOrder();
 
 Function Description:
 This function prints the cout statement and then calls the printInOrder function starting from the root and recurring down the left subtree and then the right to print the values in the tree in order. Returns if the tree is empty.
 
 Example:
 BinaryTree tree;
 tree.printInOrder();
 
 Precondition:
 None
 
 Post Condition:
 The values are printed in order. Otherwise the function returns if there are no nodes in the tree.
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

/*
 Function Prototype:
 void BinaryTree::prettyPrint();
 
 Function Description:
 This function calls the printPretty function starting from the root and going to the maximum depth of the tree, leaving 1 level between them and making 0 spaces between the values.
 
 Precondition:
 
 Post Condition:
 The tree is printed according to the specified spaces and height.
 */

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
 The parameter is an integer
 
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
 void BinaryTree::mirror();
 
 Function Description:
 The function returns the call to the recursive mirror function. Starting from the root, the function recurs down each subtree and then adjusts the pointers to mirror the tree. If the tree is empty, the function returns.
 
 Example:
 BinaryTree tree;
 tree.mirror();
 
 Precondition:
 None
 
 Post Condition:
 The function mirrors the tree. Returns if the tree is empty.
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
 The function returns the recursive doubleTree function which recurs down each subtree, duplicates each node, and adds it as the left child of the original node. The pointers are adjusted to double the tree. Returns if the tree is empty.
 
 Example:
 BinaryTree tree;
 tree.doubleTree();
 
 Precondition:
 None
 
 Post Condition:
 The tree is doubled. Returns if the tree is empty.
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
 bool BinaryTree::isBST();
 
 Function Description:
 This function returns the call to the isBST function starting from the root of the tree and checking each node to ensure that the max of the left is less than the parent node and that the max of the right is greater than the parent node. If both cases are true, the function returns true. Otherwise it returns false. If the tree is empty, the function also returns true.
 
 Example:
 BinaryTree tree;
 tree.isBST();
 
 Precondition:
 None
 
 Post Condition:
 The tree is unchanged and the function returns true if the tree is valid. Otherwise, it returns false.
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

