//  Driver File
//  binarySearchTree
//
//  Created by Margherita Lacapra on 2/24/15.
//  Copyright (c) 2015 Margherita Lacapra. All rights reserved.

#include <iostream>
#include <fstream>
#include "BinaryTree.h"

using namespace std;

//Main menu
void mainMenu()
{   cout << endl << "======Main Menu=====" << endl;
    cout << "1. Tree Functions" << endl;
    cout << "2. Tree Information" << endl;
    cout << "3. Tree Operations" << endl;
    cout << "4. Print Tree" << endl;
    cout << "5. Reset Tree" << endl;
    cout << "6. Delete Tree" << endl;
    cout << "7. Quit" << endl;
}

//Functions menu - Contains all functions that can be performed on the tree
void functionsMenu(BinaryTree& tree)
{
    string inputLine;
    int secondChoice = 0;
    
    while (secondChoice != 4)
    {
        cout << endl << "=====Tree Functions=====" << endl;
        cout << "1. Insert a value" << endl;
        cout << "2. Lookup a value" << endl;
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
                break;
        }
    }
}

//Information menu - Contains information about the tree
void informationMenu(BinaryTree& tree)
{
    string inputLine;
    int secondChoice = 0;

    while (secondChoice != 6)
    {
    
        cout << endl <<"=====Tree Information=====" << endl;
        cout << "1. Tree Size" << endl;
        cout << "2. Max Depth " << endl;
        cout << "3. Min Value" << endl;
        cout << "4. Max Value" << endl;
        cout << "5. Valid Tree" << endl;
        cout << "6. Main Menu" << endl;
        
        getline(cin, inputLine);
        secondChoice = stoi(inputLine);
        
        switch (secondChoice)
        {
            case 1:
                cout << "Tree size: " << tree.size() << endl;
                break;
            case 2:
                cout << "Max depth: " << tree.maxDepth() << endl;
                break;
            case 3:
                cout << "Min value: " << tree.minValue() << endl;
                break;
            case 4:
                cout << "Max value: " << tree.maxValue() << endl;
                break;
            case 5:
                if (tree.isBST())
                    cout << "The tree is valid" << endl;
                else
                    cout << "The tree is not valid." << endl;
                break;
            case 6:
                break;
        }
    }
}

//Operations menu - Contains operations you can perform with an existing tree.
void operationsMenu(BinaryTree& tree)
{
    string inputLine;
    int secondChoice = 0;
    
    while (secondChoice != 4)
    {
        cout << endl << "=====Tree Operations=====" << endl;
        cout << "1. Double Tree" << endl;
        cout << "2. Mirror Tree" << endl;
        cout << "3. Find Path Sum" << endl;
        cout << "4. Main Menu" << endl;
        
        getline(cin, inputLine);
        secondChoice = stoi(inputLine);
        
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
                if (tree.hasPathSum(stoi(inputLine)))
                    cout << "The answer is yes." << endl;
                else
                    cout << "The answer is no." << endl;
                break;
            case 4:
                break;
        }
    }
}

//Allows the user to pick the preferred method of displaying the contents of the tree
void printingMenu(BinaryTree& tree)
{
    string inputLine;
    int secondChoice = 0;
    
    while (secondChoice != 5)
    {
        cout << endl << "=====Print the Tree=====" << endl;
        cout << "1. Postorder Traversal" << endl;
        cout << "2. Preorder Traversal" << endl;
        cout << "3. In Order Traversal" << endl;
        cout << "4. Pretty Print" << endl;
        cout << "5. Main Menu" << endl;
        
        getline(cin, inputLine);
        secondChoice = stoi(inputLine);
        
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
                break;
        }
    }
}

//Loads the tree data from a file and loads the tree
void loadFileData(BinaryTree& tree, const char* filename)
{
    string line;
    int value;
    ifstream myfile;
    myfile.open(filename);
    
    if (!myfile.is_open())
    {
        cout << "File not found." << endl;
        return;
    }
    
    while (!myfile.eof())
    {
        myfile >> value;
        tree.insert(value);
    }
    myfile.close();
}

int main(int argc, const char* argv[]) {
    int mainChoice = 0;
    
    BinaryTree tree; // creates the tree
    
    if (argc != 2) // checks for the correct number of arguments
    {
        cout << "Invalid number of arguments." << endl;
        return 1;
    }
    
    loadFileData(tree, argv[1]); // loads the tree with the information from the file
    
    while (mainChoice != 7) // contains calls to each separate menu
    {
        mainMenu();
        
        string inputLine;
        getline(cin, inputLine);
        mainChoice = stoi(inputLine);
        
        switch (mainChoice)
        {
            case 1:
                functionsMenu(tree);
                break;
            case 2:
                informationMenu(tree);
                break;
            case 3:
                operationsMenu(tree);
                break;
            case 4:
                printingMenu(tree);
                break;
            case 5:
                tree.deleteAll();
                loadFileData(tree, argv[1]);
                break;
            case 6:
                tree.deleteAll();
                break;
            case 7:
                cout << "Goodbye!" << endl;
                break;
        }
    }
    return 0;
}
