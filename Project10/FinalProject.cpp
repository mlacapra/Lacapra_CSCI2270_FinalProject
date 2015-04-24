//
//  main.cpp
//  binarySearchTree
//
//  Created by Margherita Lacapra on 2/24/15.
//  Copyright (c) 2015 Margherita Lacapra. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "BinaryTree.h"

using namespace std;


void displayMenu()
{
    cout << "======Main Menu=====" << endl;
    cout << "1. Tree Functions" << endl;
    cout << "2. Tree Information" << endl;
    cout << "3. Print the Tree" << endl;
    cout << "4. Quit" << endl;
}

int main(int argc, const char* argv[]) {
    int mainChoice = 0;
    int secondChoice = 0;
    
    BinaryTree tree;
    
    tree.insert(8);
    tree.insert(5);
    tree.insert(10);
    tree.insert(4);
    tree.insert(6);
    tree.insert(11);
    tree.insert(12);
    
    while (mainChoice != 4)
    {
        displayMenu();
        
        string inputLine;
        getline(cin, inputLine);
        mainChoice = stoi(inputLine);
        
        switch (mainChoice)
        {
            case 1:
                
                while (secondChoice != 4)
                {
                    cout << "=====Tree Functions=====" << endl;
                    cout << "1. Lookup a value" << endl;
                    cout << "2. Insert a value" << endl;
                    cout << "3. Delete a value" << endl;
                    cout << "4. Main Menu" << endl;
                    
                    getline(cin, inputLine);
                    secondChoice = stoi(inputLine);
                
                    switch (secondChoice)
                    {
                        case 1:
                            cout << "Insert value:" << endl;
                            getline(cin, inputLine);
                            tree.insert(stoi(inputLine));
                            break;
                        case 2:
                        {
                            cout << "Lookup value:" << endl;
                            getline(cin, inputLine);
                            tree.lookup(stoi(inputLine));
                            TreeNode* node = tree.lookup(stoi(inputLine));
                            if (node == NULL)
                                cout << "Value not found." << endl;
                            else
                                cout << "Value found! " << node->key << endl;
                        }
                            break;
                        case 3:
                            cout << "Delete value:" << endl;
                            getline(cin, inputLine);
                            tree.deleteNode(stoi(inputLine));
                            break;
                        case 4:
                            secondChoice = 0;
                            break;
                    }
                break;
                }
            
            case 2:
             while (secondChoice != 11)
             {
                 cout << "=====Tree Information=====" << endl;
                 cout << "1. Tree Size" << endl;
                 cout << "2. Max Depth " << endl;
                 cout << "3. Min Value" << endl;
                 cout << "4. Max Value" << endl;
                 cout << "5. Valid Tree" << endl;
                 cout << "6. Main Menu" << endl;
                 
                 switch (secondChoice)
                 {
                     case 1:
                         cout << "Tree size:" << tree.size() << endl;
                         break;
                     case 2:
                         cout << "Max depth:" << tree.maxDepth() << endl;
                         break;
                     case 3:
                         tree.minValue();
                         break;
                     case 4:
                         tree.maxValue();
                         break;
                     case 5:
                         tree.isBST();
                         break;
                     case 6:
                         secondChoice = 0;
                         break;
                 }
             }
            
                break;
                
            case 3:
                while (secondChoice != 5)
                {
                    cout << "=====Print the Tree=====" << endl;
                    cout << "1. Postorder Traversal" << endl;
                    cout << "2. Preorder Traversal" << endl;
                    cout << "3. In Order Traversal" << endl;
                    cout << "4. Pretty Print" << endl;
                    cout << "5. Main Menu" << endl;
                    
                    switch (secondChoice)
                    {
                        case 1:
                            tree.printPostOrder();
                            break;
                        case 2:
                            tree.printPreOrder();
                            break;
                        case 3:
                            tree.printInOrder();
                            break;
                        case 4:
                            tree.prettyPrint();
                            break;
                        case 5:
                            secondChoice = 0;
                            break;
                    }
                }
                break;
            case 4:
            {
                while (secondChoice != 5)
                {
                    cout << "=====Tree Operations=====" << endl;
                    cout << "1. Double Tree" << endl;
                    cout << "2. Mirror Tree" << endl;
                    cout << "3. Count Trees" << endl;
                    cout << "4. Find Path Sum" << endl;
                    cout << "5. Main Menu" << endl;
                    
                    switch (secondChoice)
                    {
                        case 1:
                            tree.doubleTree();
                            cout << "Doubled Tree: " << endl;
                            tree.prettyPrint();
                            break;
                        case 2:
                            tree.mirror();
                            cout << "Mirrored Tree: " << endl;
                            tree.prettyPrint();
                            break;
                        case 3:
                            cout << "Enter value:" << endl;
                            getline(cin, inputLine);
                            cout << "Number of possible trees:" << tree.countTrees(stoi(inputLine)) << endl;
                            break;
                        case 4:
                            cout << "Enter value:" << endl;
                            getline(cin, inputLine);
                            if (tree.hasPathSum(stoi(inputLine)))
                                cout << "The answer is yes." << endl;
                            else
                                cout << "The answer is no." << endl;
                            break;
                        case 5:
                            secondChoice = 0;
                            break;
                    }
                }
            }
            case 5:
                cout << "Goodbye!" << endl;
                break;
        }
        
    }
    return 0;
}
