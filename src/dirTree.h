// directoryTree.h
#pragma once
#include "node.h"
#include <string>
#include <queue>
#include <fstream>
#include <string.h>
#include <sstream>
class DirectoryTree
{
public:
    Node *root;

    DirectoryTree()
    {
        // default tree structure
        root = new Node();
        root->Left = new Node();
        root->Right = new Node();
        root->Left->Left = new Node();
        root->Left->Right = new Node();
        root->Right->Left = new Node();
        root->Right->Right = new Node();

        root->Info->name = "root";
        root->Info->path = "root";
        root->Info->type = "root";

        root->Left->Info->name = "PatientsData";
        root->Left->Info->path = "root/PatientsData";
        root->Left->Info->type = "mainDirectory";

        root->Right->Info->name = "Logs";
        root->Right->Info->path = "root/Logs";
        root->Right->Info->type = "mainDirectory";

        root->Left->Left->Info->name = "PatientsHome";
        root->Left->Left->Info->path = "root/PatientsData/PatientsHome";
        root->Left->Left->Info->type = "PatientsHome_Directory";

        root->Left->Right->Info->name = "PatientsList.txt";
        root->Left->Right->Info->path = "root/PatientsData/PatientsList.txt";
        root->Left->Right->Info->type = "PatientsList_Directory";

        root->Right->Left->Info->name = "LogsHome";
        root->Right->Left->Info->path = "root/Logs/LogsHome";
        root->Right->Left->Info->type = "LogsHome_Directory";

        root->Right->Right->Info->name = "LogsReport.pdf";
        root->Right->Right->Info->path = "root/Logs/LogsReport.pdf";
        root->Right->Right->Info->type = "LogsReport_Directory";
    }

    void Add(Node *&temp)
    {
        char flag = 'y';
        Node *prev = temp;

        // Check if PatientsHome is empty or has no folders
        if (temp->Left == nullptr)
        {
            // Create a new folder in PatientsHome
            string name, type, path;
            cout << "Enter folder name to create in " << temp->Info->path << ": ";
            cin >> name;
            path = temp->Info->path + "/" + name;
            type = "folder";

            temp->Left = new Node(new NodeInfo(name, path, type));
            temp = temp->Left;
        }

        while (flag == 'y')
        {
            temp = prev;

            // Ask the user if they want to create a new folder or add files to an existing folder
            cout << "\nDo you want to create a new folder (1) or add files to an existing folder (0): ";
            int choice;

            while (true)
            {
                if (cin >> choice && (choice == 0 || choice == 1))
                {
                    break;
                }
                else
                {
                    cout << "Invalid input. Please enter 1 or 0: ";
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }
            }

            if (choice == 1)
            {
                // Create a new folder
                string name, type, path;
                cout << "Enter name of folder to create in " << temp->Info->path << ": ";
                cin >> name;
                path = temp->Info->path + "/" + name;
                type = "folder";

                // Traverse to the end of the left and put the folder there
                Node *folderNode = temp;
                while (folderNode->Left != nullptr)
                {
                    folderNode = folderNode->Left;
                }
                folderNode->Left = new Node(new NodeInfo(name, path, type));
                temp = folderNode->Left;
            }
            else
            {
                // Adding files to an existing folder
                cout << "Enter name of folder to add files in " << temp->Info->path << ": ";
                string folderName;
                cin >> folderName;

                // Check if the folder already exists
                Node *foundFolder = FindFolder(temp, folderName);

                if (foundFolder != nullptr)
                {
                    temp = foundFolder;
                }
                else
                {
                    cout << "Folder doesn't exist. Creating a new one." << endl;
                    // Create a new folder
                    string type = "folder";
                    string path = temp->Info->path + "/" + folderName;
                    temp->Left = new Node(new NodeInfo(folderName, path, type));
                    temp = temp->Left;
                }
            }

            // Create a new file inside the current folder
            string fileName, fileType, filePath;
            cout << "Enter name of file to create in " << temp->Info->path << ": ";
            cin >> fileName;
            fileType = ".pdf"; // You can modify this based on your needs
            filePath = temp->Info->path + "/" + fileName + fileType;

            // Check if the file already exists
            Node *foundFile = FindFile(temp, fileName);

            if (foundFile != nullptr)
            {
                cout << "File already exists. Please enter a new file name." << endl;
            }
            else
            {
                // File doesn't exist, create a new one
                // Traverse to the end of the right and put the file there
                Node *fileNode = temp;
                while (fileNode->Right != nullptr)
                {
                    fileNode = fileNode->Right;
                }
                fileNode->Right = new Node(new NodeInfo(fileName, filePath, fileType));
                temp = fileNode->Right;
            }

            cout << "Add more files/folders? (y/n): ";
            cin >> flag;
        }
    }

    Node *FindFolder(Node *temp, const string &folderName)
    {
        if (temp == nullptr)
        {
            return nullptr;
        }

        if (temp->Info->name == folderName)
        {
            return temp;
        }

        Node *foundInLeft = FindFolder(temp->Left, folderName);
        Node *foundInRight = FindFolder(temp->Right, folderName);

        return foundInLeft ? foundInLeft : foundInRight;
    }

    Node *FindFile(Node *temp, const string &fileName)
    {
        if (temp == nullptr)
        {
            return nullptr;
        }

        if (temp->Info->name == fileName)
        {
            return temp;
        }


        Node *foundInRight = FindFile(temp->Right, fileName);
        Node* foundInLeft = FindFile(temp->Left, fileName);

        return foundInRight ? foundInRight : foundInLeft;
    }

    void Create()
    {
        Node *temp = root;
        string path;
        int flag = 1;
        int counter = 0;

        while (flag == 1)
        {
            cout << "\nEnter path: ";
            cin >> path;

            bool validPath = false;

            // Check if the path is valid
            if (temp->Info->name == path)
            {
                // found at root
                validPath = true;
            }
            // Check if there's a left or right child
            else if (temp->Left != nullptr && temp->Left->Info->name == path)
            {
                temp = temp->Left; // Move to the left child
                validPath = true;
            }
            else if (temp->Right != nullptr && temp->Right->Info->name == path)
            {
                temp = temp->Right; // Move to the right child
                validPath = true;
            }

            if (!validPath)
            {
                // Invalid path
                cout << "\nInvalid path. Please try again." << endl;
                continue;
            }

            counter++;

            cout << "\nPath accepted. Current position: " << temp->Info->path << endl;

            // Ask for more path
            cout << "Add more path? (1/0): ";
            while (!(cin >> flag) || (flag != 0 && flag != 1))
            {
                // Reset cin's error state and clear the input buffer
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                cout << "\nInvalid input. Please enter 1/0: ";
            }
        }

        // temp: last node in path
        Add(temp);
    }

    Node* findNode(Node* current, string nodeName)
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        if (current->Info->name == nodeName)
        {
            return current;
        }

        Node* foundInLeft = findNode(current->Left, nodeName);
        Node* foundInRight = findNode(current->Right, nodeName);

        return foundInLeft ? foundInLeft : foundInRight;
    }

    Node* FindNodewithBack(Node* current, string nodeName)
    {
        if (current == nullptr)
        {
            return nullptr;
        }

        if (current->Left != nullptr && current->Left->Info->name == nodeName)
        {
            return current;
        }

        if (current->Right != nullptr && current->Right->Info->name == nodeName)
        {
            return current;
        }

        Node* foundInLeft = FindNodewithBack(current->Left, nodeName);
        Node* foundInRight = FindNodewithBack(current->Right, nodeName);

        return foundInLeft ? foundInLeft : foundInRight;
    }

    void Merge()
    {
        string destination, source;
        Node *destinationNode, *sourceNode;

        cout << "\nEnter destination folder: ";
        cin >> destination;
        destinationNode = findNode(root, destination);
        if (destinationNode == nullptr)
        {
            cout << "\nError: Destination folder not found." << endl;
            return;
        }

        cout << "\nEnter source folder: ";
        cin >> source;
        sourceNode = findNode(root, source);
        if (sourceNode == nullptr)
        {
            cout << "\nError: Source folder not found." << endl;
            return;
        }

        // Merging the files of the source folder into the destination folder
        Node *filetraverse = sourceNode->Right;
        while (filetraverse != nullptr)
        {
            // Traverse to the end of the right of the destination folder
            Node *temp = destinationNode;
            while (temp->Right != nullptr)
            {
                temp = temp->Right;
            }

            // Add the file to the end of the right of the destination folder
            temp->Right = new Node(new NodeInfo(filetraverse->Info->name, filetraverse->Info->path, filetraverse->Info->type));

            filetraverse = filetraverse->Right;
        }

        // Deleting the source folder from the main node
        Node *temp = sourceNode;
        sourceNode = sourceNode->Left;
        delete temp;

        // Ask the user if they want to keep the name of the destination folder or change it
        cout << "\nDo you want to keep the name of the destination folder or change it? (1/0): ";
        int choice;
        cin >> choice;
        if (choice == 0)
        {
            cout << "\nEnter new name of the destination folder: ";
            cin >> destination;
            destinationNode->Info->name = destination;
            cout << "Folder name changed successfully." << endl;
        }
    }

    void DeleteFile()
    {
        string name;
        cout << "Enter name of file to delete: ";
        cin >> name;

        Node *fileNode = FindNodewithBack(root, name);

        if (fileNode == nullptr)
        {
            cout << "File not found." << endl;
            return;
        }

        // Check if the file has a right child
        if (fileNode->Right != nullptr)
        {
            // Delete the file
            Node *temp = fileNode->Right;
            fileNode->Right = temp->Right;
            delete temp;
            cout << "File deleted successfully." << endl;
        }
        else
        {
            cout << "Folder does not have any content to delete." << endl;
        }
    }

    void DeleteFolder()
    {
        string name;
        cout << "Enter name of folder to delete: ";
        cin >> name;

        Node *folderNode = FindFolder(root, name);

        if (folderNode == nullptr)
        {
            cout << "Folder not found." << endl;
            return;
        }

        // Delete the folder directly if it has no left or right child
        if (folderNode->Left == nullptr && folderNode->Right == nullptr)
        {
            cout << "Deleting folder directly." << endl;
            Node *temp = folderNode;
            folderNode = folderNode->Left;
            delete temp;
            return;
        }

        // Attempt to merge files if the folder has files
        if (folderNode->Left == nullptr && folderNode->Right != nullptr)
        {
            // Folder has files, ask to merge these files with another folder
            cout << "Folder has files. Do you want to merge these files with another folder? (1/0): ";
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                string destinationFolder;
                cout << "Enter destination folder: ";
                cin >> destinationFolder;
                Node *destinationNode = findNode(root, destinationFolder);
                if (destinationNode == nullptr)
                {
                    cout << "Destination folder not found." << endl;
                    return;
                }

                // Merge the files of the source folder into the destination folder
                Node *fileTraverse = folderNode->Right;
                while (fileTraverse != nullptr)
                {
                    // Traverse to the end of the right of the destination folder
                    Node *temp = destinationNode;
                    while (temp->Right != nullptr)
                    {
                        temp = temp->Right;
                    }

                    // Add the file to the end of the right of the destination folder
                    temp->Right = new Node(new NodeInfo(fileTraverse->Info->name, fileTraverse->Info->path, fileTraverse->Info->type));

                    fileTraverse = fileTraverse->Right;
                }
            }

            // Delete the folder directly
            cout << "Deleting folder directly." << endl;
            Node *temp = folderNode;
            folderNode = folderNode->Left;
            delete temp;
            return;
        }

        // Attempt to merge files and folders if the folder has both
        if (folderNode->Left != nullptr && folderNode->Right != nullptr)
        {
            cout << "Folder contains both folders and files." << endl;

            // Ask the user where to merge the files
            string destination;
            cout << "Enter the destination folder where you want to merge the files: ";
            cin >> destination;

            // Search for the destination folder in the tree
            Node *destinationNode = FindFolder(root, destination);

            if (destinationNode == nullptr)
            {
                cout << "Destination folder not found. Aborting operation." << endl;
                return;
            }
            cout << "Destination folder found: " << destinationNode->Info->name << endl;

            // Find the parent folder of the current folder
            Node *parentFolder = FindNodewithBack(root, folderNode->Info->name);

            if (parentFolder != nullptr)
            {
                // Merge files to the chosen destination
                Node *currentFile = folderNode->Right;
                while (currentFile != nullptr)
                {
                    // Create a copy of the current file node
                    Node *newFile = new Node(new NodeInfo(currentFile->Info->name, currentFile->Info->path, currentFile->Info->type));

                    // Attach the copied file node to the destination node
                    if (destinationNode->Right == nullptr)
                    {
                        destinationNode->Right = newFile;
                    }
                    else
                    {
                        // Find the last node in the right subtree of the destination node
                        Node *lastNode = destinationNode->Right;
                        while (lastNode->Right != nullptr)
                        {
                            lastNode = lastNode->Right;
                        }

                        lastNode->Right = newFile;
                    }

                    // Move to the next file node
                    currentFile = currentFile->Right;
                }

                // Connect the left child (another folder) to the parent folder
                if (parentFolder->Left == folderNode)
                {
                    parentFolder->Left = folderNode->Left;
                }
                else if (parentFolder->Right == folderNode)
                {
                    parentFolder->Right = folderNode->Left;
                }

                // After merging, delete the folder
                Node *nodeToDelete = FindNodewithBack(root, folderNode->Info->name);
                if (nodeToDelete != nullptr)
                {
                    Node *temp = nodeToDelete->Left;
                    nodeToDelete->Left = nodeToDelete->Left->Left;
                    delete temp;
                }

                cout << "Folder merged and deleted successfully." << endl;
            }
            else
            {
                cout << "Error: Parent folder not found." << endl;
            }
        }
    }

    void Search()
    {
        // Take the file name from the user and print its path if found
        // Ask the user if they want to search for a directory
        // If yes, then print the path of the directory; otherwise, print not found

        string name;
        cout << "Enter name of File/Folder to search: ";
        cin >> name;

        Node *fileNode = findNode(root, name);

        if (fileNode == nullptr)
        {
            cout << "File not found." << endl;
            return;
        }

        // Print its path by going to its parent node until the root node
        // Combine the whole path in a string with / in between
        Node *temp = fileNode;
        string path = fileNode->Info->name;

        while (temp != nullptr)
        {
            temp = FindNodewithBack(root, temp->Info->name);

            if (temp != nullptr)
            {
                path = temp->Info->name + "/" + path;
            }
        }

        cout << "Path of file/folder: " << path << endl;

        // Ask the user if they want to search for a directory
        cout << "Do you want to search for a directory? (1/0): ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            // Check if the found node is a directory
            if (fileNode->Left != nullptr)
            {
                // Print the path of the directory
                cout << "Path of directory: " << path << endl;
            }
            else
            {
                cout << "No directory found for the given name." << endl;
            }
        }
    }

    void Copy_Move()
    {
        string name, destination;
        cout << "Enter name of File to copy/move: ";
        cin >> name;

        Node *fileNode = findNode(root, name);

        if (fileNode == nullptr)
        {
            cout << "File not found." << endl;
            return;
        }

        cout << "Enter destination folder: ";
        cin >> destination;

        Node *destinationNode = findNode(root, destination);

        if (destinationNode == nullptr)
        {
            cout << "Destination folder not found." << endl;
            return;
        }

        cout << "Do you want to copy or move the file? (1/0): ";
        int choice;
        cin >> choice;

        if (choice == 1)
        {
            // Copy the file
            Node *temp = destinationNode;
            while (temp->Right != nullptr)
            {
                temp = temp->Right;
            }

            temp->Right = new Node(new NodeInfo(fileNode->Info->name, fileNode->Info->path, fileNode->Info->type));
        }
        else
        {
            // Move the file
            Node *temp = destinationNode;
            while (temp->Right != nullptr)
            {
                temp = temp->Right;
            }

            temp->Right = new Node(new NodeInfo(fileNode->Info->name, fileNode->Info->path, fileNode->Info->type));

            // remove the file from it's original location
            Node *fileParent = FindNodewithBack(root, fileNode->Info->name);
            if (fileParent != nullptr)
            {
                Node *temp = fileParent->Right;
                fileParent->Right = fileParent->Right->Right;
                delete temp;
            }

            cout << "File moved successfully." << endl;
            
            // check if the folder from which the file was moved is empty, if yes, ask user to delete it
            if (fileParent->Right == nullptr)
            {
                cout << "Folder is empty. Do you want to delete it? (1/0): ";
                int choice;
                cin >> choice;

                if (choice == 1)
                {
                    Node *parent = FindNodewithBack(root, fileParent->Info->name);

                    if (parent != nullptr)
                    {
                        // Connect the parent's left or right to the folder's left (can be nullptr)
                        if (parent->Left == fileParent)
                        {
                            parent->Left = fileParent->Left;
                        }
                        else if (parent->Right == fileParent)
                        {
                            parent->Right = fileParent->Left;
                        }

                        // Delete the empty folder
                        delete fileParent;

                        cout << "Folder deleted successfully." << endl;
                    }
                }
            }
        }
    }

    Node *FindParentAtDepth(Node *node, int targetDepth, int currentDepth = 0)
    {
        if (node == nullptr)
            return nullptr;

        if (currentDepth == targetDepth)
        {
            // If the target depth is reached, return the parent of this node
            return node;
        }

        // Recursively search in left and right subtrees
        Node *leftResult = FindParentAtDepth(node->Left, targetDepth, currentDepth + 1);
        Node *rightResult = FindParentAtDepth(node->Right, targetDepth, currentDepth);

        // Return the first non-null result
        return leftResult ? leftResult : rightResult;
    }

    // Add these two member functions to your DirectoryTree class:

    void ExportToFileHelper(Node *node, ofstream &file, int depth = 0)
    {
        if (node == nullptr)
            return;

        file << string(depth, '\t') << node->Info->name << "," << node->Info->path << "," << node->Info->type << endl;

        // Recursively export left and right subtrees
        ExportToFileHelper(node->Left, file, depth + 1);
        ExportToFileHelper(node->Right, file, depth);
    }

    void ExportToFile()
    {
        ofstream file("tree.txt");

        if (!file.is_open())
        {
            cout << "Unable to open file." << endl;
            return;
        }

        ExportToFileHelper(root, file);

        file.close();
    }

    void ImportFromFile()
    {
        ifstream file("tree.txt");

        if (!file.is_open())
        {
            cout << "Unable to open file." << endl;
            return;
        }

        // Clear the existing tree
        DestroyTree(root);
        root = nullptr;

        string line;
        while (getline(file, line))
        {
            string name, path, type;
            stringstream ss(line);
            getline(ss, name, ',');
            getline(ss, path, ',');
            getline(ss, type);

            // Count the number of tabs to determine the depth of the node
            int depth = 0;
            while (ss.peek() == '\t')
            {
                ss.get();
                ++depth;
            }

            Node *newNode = new Node(new NodeInfo(name, path, type));

            if (depth == 0)
            {
                // Root node
                root = newNode;
            }
            else
            {
                // Find the parent node at the correct depth
                Node *parentNode = FindParentAtDepth(root, depth - 1);

                // Add the new node to the left or right based on its depth
                if (parentNode != nullptr)
                {
                    if (parentNode->Left == nullptr)
                        parentNode->Left = newNode;
                    else
                        parentNode->Right = newNode;
                }
            }
        }

        file.close();
    }


    void Display()
    {
        Node* temp = findNode(root, "root");
        if (temp == nullptr)
        {
            cout << "Folder not found." << endl;
            return;
        }

        Node* foldertraverse = temp;

        while(foldertraverse != nullptr)
        {
            cout << foldertraverse->Info->name << " ";

            Node *filetraverse = foldertraverse->Right;
            while (filetraverse != nullptr)
            {
                cout << filetraverse->Info->name << " ";
                filetraverse = filetraverse->Right;
            }
            cout << endl;

            foldertraverse = foldertraverse->Left;
        }
    }

    void DestroyTree(Node *node)
    {
        if (node == nullptr)
            return;

        // Recursively destroy left and right subtrees
        DestroyTree(node->Left);
        DestroyTree(node->Right);

        // Delete the current node
        delete node;
    }
};
