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

// Convert an integer value to string
string intToString(int val)
{
    ostringstream ss;
    ss << val;
    return ss.str();
}

// Print the arm branches (eg, /    \ ) on a line
void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue)
{
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel / 2; i++)
    {
        cout << ((i == 0) ? setw(startLen-1) : setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
        cout << setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
    }
    cout << endl;
}

// Print the branches and node (eg, ___10___ )
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

// Print the leaves only (just for the bottom row)
void printLeaves(int indentSpace, int level, int nodesInThisLevel, const deque<TreeNode*>& nodesQueue)
{
    deque<TreeNode*>::const_iterator iter = nodesQueue.begin();
    for (int i = 0; i < nodesInThisLevel; i++, iter++)
    {
        cout << ((i == 0) ? setw(indentSpace + 2) : setw(2 * level + 2)) << ((*iter) ? intToString((*iter)->key) : "");
    }
    cout << endl;
}

// Pretty formatting of a binary tree to the output stream
// level: Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace: Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)

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
