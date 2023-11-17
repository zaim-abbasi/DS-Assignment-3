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

        if (temp->Left != nullptr && temp->Left->Info->name == folderName)
        {
            return temp->Left;
        }

        Node *foundInLeft = FindFolder(temp->Left, folderName);
        // Node *foundInRight = FindFolder(temp->Right, folderName);

        return foundInLeft; // ? foundInLeft : foundInRight;
    }

    Node *FindFile(Node *temp, const string &fileName)
    {
        if (temp == nullptr)
        {
            return nullptr;
        }

        // Node *foundInLeft = FindFile(temp->Left, fileName);
        Node *foundInRight = FindFile(temp->Right, fileName);

        return foundInRight; // ? foundInLeft : foundInRight;
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
