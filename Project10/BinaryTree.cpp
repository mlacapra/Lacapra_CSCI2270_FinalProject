//
//  Final Project
//
//  Created by Margherita Lacapra on 4/19/15
//  Copyright (c) 2015 Margherita Lacapra. All rights reserved.
//

#include "BinaryTree.h"
#include <iostream>
#include <iomanip>

using namespace std;

BinaryTree::BinaryTree()
{
    root = NULL;
}

BinaryTree::~BinaryTree()
{
    if (root != NULL)
        deleteNode(root);
}

/*
 Given a binary tree, return true if a node
 with the target data is found in the tree. Recurs
 down the tree, chooses the left or right
 branch by comparing the target to each node.
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
 Give a binary search tree and a number, inserts a new node
 with the given number in the correct place in the tree.
 Returns the new root pointer which the caller should
 then use (the standard trick to avoid using reference
 parameters).
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
 Compute the number of nodes in a tree.
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
 Compute the "maxDepth" of a tree -- the number of nodes along
 the longest path from the root node down to the farthest leaf node.
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
 Write a C++ function to check whether the given tree is Binary Search Tree. The function takes one argument:
 the tree node. It returns True if the tree is a valid BST. Otherwise, it returns false.
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
 Given a binary tree, print its
 nodes according to the "bottom-up"
 postorder traversal.
*/

void BinaryTree::printPostOrder()
{
    cout << "Print PostOrder: ";
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
    
    // first recur on both subtrees
    printPreOrder(node->left);
    printPreOrder(node->right);
}

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
    cout << node->key << " ";
}

/*
 Write a C++ function to check if a tree has a root-to-leaf path such that adding up all the values along the path equals the given sum. The function takes two arguments, tree node and the sum being searched for. Return true if such path can be found. Otherwise, return false.
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
 Write a C++ function which does the following operation:
 For each node in a binary search tree, create a new duplicate node, and insert the duplicate as the left child of the original node.
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
 A function that returns True if two trees are structurally identical.(they are made of nodes with the same values arranged in the same way.) The function takes two arguments: treenode of tree1 and treenode of tree2. It should return True if the trees are identical. Otherwise, return False.
*/

bool BinaryTree::sameTree(BinaryTree* otherTree)
{
    return sameTree(root, otherTree->getRoot());
}

bool BinaryTree::sameTree(TreeNode* a, TreeNode* b)
{
    
    // 1. both empty -> true
    if (a == NULL && b == NULL)
        return true;
    
    // 2. both non-empty -> compare them
    if (a != NULL && b != NULL)
    {
        return
        (
         a->key == b->key &&
         
         sameTree(a->left, b->left) &&
         
         sameTree(a->right, b->right)
         
         );
    }
    
    // 3. one empty, one not -> false
    return false;
}

/*
 For the key values 1...numKeys, how many structurally unique
 binary search trees are possible that store those keys.
 Strategy: consider that each value could be the root.
 Recursively find the size of the left and right subtrees.
*/

int BinaryTree::countTrees(int numKeys)
{
    return countTrees(root, numKeys);
}

int BinaryTree::countTrees(TreeNode* node, int numKeys)
{
    
    if (numKeys <= 1)
        return(1);
    
    // there will be one value at the root, with whatever remains
    // on the left and right each forming their own subtrees.
    // Iterate through all the values that could be the root...
    int sum = 0;
    int left, right, root;
    
    for (root = 1; root <= numKeys; root++)
    {
        left = countTrees(root - 1);
        right = countTrees(numKeys - root);
    
        // number of possible trees with this root == left*right
        sum += left*right;
    }
    return(sum);
}

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

