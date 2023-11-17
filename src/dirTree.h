// directoryTree.h
#pragma once
#include "node.h"
#include <string>
#include <queue>
class DirectoryTree
{
public:
    Node *root;

public:
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

    // DirectoryTree()
    // {
    //     // default tree structure
    //     root = new Node();
    //     root->Left = new Node();
    //     root->Right = new Node();
    //     root->Left->Left = new Node();
    //     root->Left->Right = new Node();
    //     root->Right->Left = new Node();
    //     root->Right->Right = new Node();

    //     root->Info->name = "root";
    //     root->Info->path = "root";
    //     root->Info->type = "root";

    //     root->Left->Info->name = "PatientsData";
    //     root->Left->Info->path = "root/PatientsData";
    //     root->Left->Info->type = "mainDirectory";

    //     root->Right->Info->name = "Logs";
    //     root->Right->Info->path = "root/Logs";
    //     root->Right->Info->type = "mainDirectory";

    //     root->Left->Left->Info->name = "PatientsHome";
    //     root->Left->Left->Info->path = "root/PatientsData/PatientsHome";
    //     root->Left->Left->Info->type = "PatientsHome_Directory";

    //     root->Left->Right->Info->name = "PatientsList.txt";
    //     root->Left->Right->Info->path = "root/PatientsData/PatientsList.txt";
    //     root->Left->Right->Info->type = "PatientsList_Directory";

    //     // Hardcoded inputs
    //     // Create folders
    //     root->Left->Left->Left = new Node(new NodeInfo("Patient-A", "root/PatientsData/PatientsHome/Patient-A", "folder"));
    //     root->Left->Left->Right = new Node(new NodeInfo("Patient-C", "root/PatientsData/PatientsHome/Patient-A/Patient-C", "folder"));
    //     root->Left->Left->Right->Right = new Node(new NodeInfo("Patient-B", "root/PatientsData/PatientsHome/Patient-B", "folder"));

    //     // Create files in Patient-A
    //     root->Left->Left->Left->Right = new Node(new NodeInfo("report-1.pdf", "root/PatientsData/PatientsHome/Patient-A/report-1.pdf", ".pdf"));
    //     root->Left->Left->Left->Right->Right = new Node(new NodeInfo("report-2.pdf", "root/PatientsData/PatientsHome/Patient-A/report-2.pdf", ".pdf"));

    //     // Create files in Patient-C
    //     root->Left->Left->Right->Right->Right = new Node(new NodeInfo("report-3.pdf", "root/PatientsData/PatientsHome/Patient-A/Patient-C/report-3.pdf", ".pdf"));

    //     // Create files in Patient-B
    //     root->Left->Left->Right->Right->Right->Right = new Node(new NodeInfo("report-4.pdf", "root/PatientsData/PatientsHome/Patient-B/report-4.pdf", ".pdf"));
    //     root->Left->Left->Right->Right->Right->Right->Right = new Node(new NodeInfo("report-5.pdf", "root/PatientsData/PatientsHome/Patient-B/report-5.pdf", ".pdf"));
    //     root->Left->Left->Right->Right->Right->Right->Right->Right = new Node(new NodeInfo("report-6.pdf", "root/PatientsData/PatientsHome/Patient-B/report-6.pdf", ".pdf"));
    // }

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
            cin >> choice;

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

        return foundInRight;
    }

    void Create()
    {
        Node *temp = root;
        string path;
        int flag = 1;
        int counter = 0;

        while (flag == 1)
        {
            cout << "Enter path: ";
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
                cout << "Invalid path. Please try again." << endl;
                continue;
            }

            counter++;

            cout << "Add more path? (1/0): ";
            cin >> flag;
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
        Node* destinationNode, *sourceNode;
        
        cout<<"Enter destination folder: ";
        cin>>destination;
        destinationNode = findNode(root, destination);
        if (destinationNode == nullptr)
        {
            cout << "Folder not found." << endl;
            return;
        }

        cout<<"Enter source folder: ";
        cin>>source;
        sourceNode = findNode(root, source);
        if (sourceNode == nullptr)
        {
            cout << "Folder not found." << endl;
            return;
        }

        // mow merging the files of source folder into destination folder
        Node* filetraverse = sourceNode->Right;
        while (filetraverse != nullptr)
        {
            // traverse to the end of the right of destination folder
            Node* temp = destinationNode;
            while (temp->Right != nullptr)
            {
                temp = temp->Right;
            }

            // add the file to the end of the right of destination folder
            temp->Right = new Node(new NodeInfo(filetraverse->Info->name, filetraverse->Info->path, filetraverse->Info->type));

            filetraverse = filetraverse->Right;
        }
        // now deleting the source folder from the main node
        Node* temp = sourceNode;
        sourceNode = sourceNode->Left;
        delete temp;

        // ask user if he wants to keep the name of destination folder or change it
        cout<<"Do you want to keep the name of destination folder or change it? (1/0): ";
        int choice;
        cin>>choice;
        if (choice == 0)
        {
            cout<<"Enter new name of destination folder: ";
            cin>>destination;
            destinationNode->Info->name = destination;
            cout<<"Folder name changed successfully."<<endl;
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

        // Delete the file
        Node *temp = fileNode->Right;
        fileNode->Right = temp->Right;
        delete temp;
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
        cout<<"Folder found: "<< folderNode->Info->name<<endl;

        // Delete the folder directly if it's right and left nodes are null
        if (folderNode->Left == nullptr && folderNode->Right == nullptr)
        {
            cout<<"Deleting folder directly."<<endl;
            Node* temp = folderNode;
            folderNode = folderNode->Left;
            delete temp;
            return;
        }

        if(folderNode->Left == nullptr && folderNode->Right != nullptr)
        {
            // folder has files so ask to merge these files with another folder
            cout<<"Folder has files. Do you want to merge these files with another folder? (1/0): ";
            int choice;
            cin>>choice;
            if (choice == 1)
            {
                string destinationFolder;
                cout<<"Enter destination folder: ";
                cin>>destinationFolder;
                Node* destinationNode = findNode(root, destinationFolder);
                if (destinationNode == nullptr)
                {
                    cout << "Folder not found." << endl;
                    return;
                }

                // mow merging the files of source folder into destination folder
                Node* filetraverse = folderNode->Right;
                while (filetraverse != nullptr)
                {
                    // traverse to the end of the right of destination folder
                    Node* temp = destinationNode;
                    while (temp->Right != nullptr)
                    {
                        temp = temp->Right;
                    }

                    // add the file to the end of the right of destination folder
                    temp->Right = new Node(new NodeInfo(filetraverse->Info->name, filetraverse->Info->path, filetraverse->Info->type));

                    filetraverse = filetraverse->Right;
                }
            }
            // delete the folder directly
            cout<<"Deleting folder directly."<<endl;
            Node* temp = folderNode;
            folderNode = folderNode->Left;
            delete temp;
            return;
        }

        if (folderNode->Left != nullptr && folderNode->Right != nullptr)
        {
            // Folder has another folder in its left and files in its right
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

            // Find the parent folder of the current folder
            Node *parentFolder = FindNodewithBack(root, folderNode->Info->path);

            if (parentFolder != nullptr)
            {
                // Merge files to the chosen destination
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

    void Display()
    {
        Node* temp = findNode(root, "PatientsHome");
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

};
