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
    cout << "3. Tree Operations" << endl;
    cout << "4. Print the Tree" << endl;
    cout << "5. Reset the Tree" << endl;
    cout << "6. Delete All Entries" << endl;
    cout << "7. Quit" << endl;
}

void functionsMenu()
{
    cout << "=====Tree Functions=====" << endl;
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
            secondChoice = 4;
            break;
    }
}

void informationMenu()
{
    cout << "=====Tree Information=====" << endl;
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
            secondChoice = 6;
            break;
    }
}

void operationsMenu()
{
    cout << "=====Tree Operations=====" << endl;
    cout << "1. Double Tree" << endl;
    cout << "2. Mirror Tree" << endl;
    cout << "3. Count Trees" << endl;
    cout << "4. Find Path Sum" << endl;
    cout << "5. Main Menu" << endl;
    
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
            secondChoice = 5;
            break;
    }
}

void printingMenu()
{
    cout << "=====Print the Tree=====" << endl;
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
            secondChoice = 5;
            break;
    }
}

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
    int secondChoice = 0;
    
    BinaryTree tree;
    
    if (argc != 2)
    {
        cout << "Invalid number of arguments." << endl;
        return 1;
    }
    
    loadFileData(tree, argv[1]);
    
    while (mainChoice != 7)
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
                    functionsMenu();
                }
                secondChoice = 0;
                break;
            case 2:
                while (secondChoice != 6)
                {
                    informationMenu();
                }
                secondChoice = 0;
                break;
            case 3:
                while (secondChoice != 5)
                {
                    operationsMenu();
                }
                secondChoice = 0;
                break;
                
            case 4:
                while (secondChoice != 5)
                {
                    printingMenu();
                }
                secondChoice = 0;
                break;
            case 5:
                //delete all
                loadFileData(tree, argv[1]);
                secondChoice = 0;
                break;
            case 6:
                //delete all
                secondChoice = 0;
                break;
            case 7:
                cout << "Goodbye!" << endl;
                break;
        }
    }
    return 0;
}
