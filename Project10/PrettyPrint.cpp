#include <fstream>
#include <iostream>
#include <deque>
#include <iomanip>
#include <sstream>
#include <string>
#include <Math.h>
#include "BinaryTree.h"

/*This implementation has been derived from the article "How to Pretty Print a Binary Tree" by 1337c0d3r
  http://articles.leetcode.com/2010/09/how-to-pretty-print-binary-tree.html
*/

using namespace std;

/*
 Function prototype:
 string intToString(int);
 
 Function Definition:
 This function takes an integer as a parameter and type casts it into a string. Returns the string.
 
 Example:
 int intToString(8);
 
 Precondition:
 The parameter is an integer
 
 Post Condition:
 The integer is type casted into a string and returned.
 */

string intToString(int val)
{
    ostringstream ss;
    ss << val;
    return ss.str();
}

/*
 Function Prototype:
 void printBranches(int, int, int, int, const deque<TreeNode*>);
 
 Function definition:
 Print the arm branches (eg, /    \ ) on a line using the deque data structure to store the values for the branches, space between the nodes, the start length, and the nodes in the level.
 
 Example:
 printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, const deque<TreeNode*>& nodesQueue);
 
 Pre condition:
 None
 
 Post condition:
 The branches are printed with the corresponding spaces
 */

void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue)
{
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++)
    {
        cout << ((i == 0) ? setw(startLen - 1) : setw(nodeSpaceLen - 2)) << "" << ((*iter++) ? "/" : " ");
        cout << setw(2 * branchLen + 2) << "" << ((*iter++) ? "\\" : " ");
    }
    cout << endl;
}

/*
 Function Prototype:
 void printNodes(int, int, int, int, const deque<TreeNode*>);
 
 Function Definition:
 Prints branches and the node in the middle. Creates a deque to store the nodes and the spaces accordingly.
 
 Example:
 printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
 
 Precondition:
 None
 
 Post Condition:
 The branches are printed with the corresponding spaces and the node.
 */

void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue)
{
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++)
    {
        cout << ((i == 0) ? setw(startLen) : setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left) ? setfill('_') : setfill(' '));
        cout << setw(branchLen+2) << ((*iter) ? intToString((*iter)->key) : "");
        cout << ((*iter && (*iter)->right) ? setfill('_') : setfill(' ')) << setw(branchLen) << "" << setfill(' ');
    }
    cout << endl;
}

/*
 Function Prototype:
 void printLeaves(int, int, int, const deque<TreeNode*>);
 
 Function Definition:
 Prints the leaves of the tree (the bottom row of the tree) with the corresponding spaces and stores this in a deque to access the values from either end.
 
 Example:
 printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue);
 
 Precondition:
 None
 
 Post Condition:
 The leaves of the tree are printed with the corresponding spaces
 */

void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue)
{
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++)
    {
        cout << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? intToString((*iter)->key) : "");
    }
    cout << endl;
}

/*
 Function Prototype:
 void printPretty(TreeNode*, int, int, int);
 
 Function Description:
 This function calls the printBranches, printLeaves, and printNodes functions to output the tree. Prints the corresponding tree.
 
 Example:
 printPretty(root, maxDepth, 1, 0);
 
 Precondition:
 None
 
 Post Condition:
 The tree is printed with the leaves, branches, and nodes in the right places starting from the root and going all the way to the maximum depth of the tree.
 */

void printPretty(TreeNode* root, int height, int level, int indentSpace)
{
    int nodesInThisLevel = 1;
    int branchLen = 2 * ((int)pow(2.0, height) - 1) - (3 - level) * (int)pow(2.0, height - 1);
    int nodeSpaceLen = 2 + (level + 1) * (int)pow(2.0, height);
    int startLen = branchLen + (3 - level) + indentSpace;
    
    deque<TreeNode*> nodesQueue;
    nodesQueue.push_back(root);
    for (int i = 1; i < height; i++)
    {
        printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
        branchLen = branchLen/2 - 1;
        nodeSpaceLen = nodeSpaceLen/2 + 1;
        startLen = branchLen + (3 - level) + indentSpace;
        printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
        
        for (int j = 0; j < nodesInThisLevel; j++)
        {
            TreeNode* currentNode = nodesQueue.front();
            nodesQueue.pop_front();
            if (currentNode)
            {
                nodesQueue.push_back(currentNode->left);
                nodesQueue.push_back(currentNode->right);
            }
            else
            {
                nodesQueue.push_back(NULL);
                nodesQueue.push_back(NULL);
            }
        }
        nodesInThisLevel *= 2;
    }
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue);
    printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue);
}
