// directoryTree.h
#pragma once
#include "node.h"
#include <string>
#include <queue>
class DirectoryTree
{
private:
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

    void AddRemoveFiles(Node *&temp)
    {
        int flag = 1;
        Node *prev = temp;

        while (flag == 1)
        {
            temp = prev;

            // Check if there's a left child (folder)
            if (temp->Left == NULL)
            {
                string name, type, path;
                cout << "Enter name of Folder to create in " << temp->Info->path << ": ";
                cin >> name;
                path = temp->Info->path + "/" + name;
                cout << "Enter type of Folder to create in " << temp->Info->path << ": ";
                cin >> type;

                // Check if the folder already exists
                if (temp->Right != NULL && temp->Right->Info->name == name)
                {
                    // Folder already exists, move to that folder
                    temp = temp->Right;
                }
                else
                {
                    // Create a new folder
                    temp->Left = new Node(new NodeInfo(name, path, type));
                    temp = temp->Left;
                }
            }
            else
            {
                // do you want to add a file in Patient A or create a new folder for Patient B?
                cout << "Do you want to add files in any folder in existing directory or create a new folder in: " << prev->Info->path << " (1/0): ";
                int subFlag;
                cin >> subFlag;

                if (subFlag == 1)
                {
                    cout<<"Enter name of Folder in which you want to add files: ";
                    string folderName;
                    cin>>folderName;

                    //check is any folder of this name exists in this directory
                    if(temp->Left->Info->name == folderName)
                    {
                        temp = temp->Left;
                    }
                    else
                    {
                        cout<<"No folder of this name exists in this directory."<<endl;
                    }

                    string name, type, path;
                    cout << "Enter name of File to create in " << temp->Info->path << ": ";
                    cin >> name;
                    path = temp->Info->path + "/" + name;
                    cout << "Enter type of File to create in " << temp->Info->path << ": ";
                    cin >> type;

                    // Check if the file already exists
                        // Create a new file
                        temp->Right = new Node(new NodeInfo(name, path, type));
                        temp = temp->Right;
                }
                else
                {
                    string name, type, path;
                    cout << "Enter name of Folder to create in " << temp->Info->path << ": ";
                    cin >> name;
                    path = temp->Info->path + "/" + name;
                    cout << "Enter type of Folder to create in " << temp->Info->path << ": ";
                    cin >> type;

                    // Check if the folder already exists
                    if (temp->Left != NULL && temp->Left->Info->name == name)
                    {
                        // Folder already exists, move to that folder
                        temp = temp->Left;
                    }
                    else
                    {
                        // Create a new folder
                        temp->Left = new Node(new NodeInfo(name, path, type));
                        temp = temp->Left;
                    }
                }
            }

            cout << "Add more Files/Folders? (1/0): ";
            cin >> flag;
        }
    }

    // void AddRemoveFiles(Node *&temp)
    // {
    //     int flag = 1;
    //     Node *prev = temp;
    //     while (flag == 1)
    //     {
    //         temp = prev;
    //         // yaha se add/remove hone start honge
            
    //         if (temp->Left == NULL)
    //         {
    //             string name, type, path;
    //             cout << "Enter name of Folder to create in " << temp->Info->path << ": ";
    //             cin >> name;
    //             path = temp->Info->path + "/" + name;
    //             cout << "Enter type of Folder to create in " << temp->Info->path << ": ";
    //             cin >> type;
    //             // patients ki files add hongi
    //             temp->Left = new Node(new NodeInfo(name, path, type));
    //             temp = temp->Left;
    //         }
    //         else
    //         {
    //             // do you want to add a file in Patient A or create a new folder for Patient B?
    //             cout<<"Do you want to add files in "<< temp->Info->name<< " directory or create a new folder in "<< prev->Info->path<< " directory? (1/0): ";
    //             int subFlag;
    //             cin>>subFlag;
    //             if(subFlag == 1)
    //             {
    //                 string name, type, path;
    //                 cout << "Enter name of File to create in " << temp->Info->path << ": ";
    //                 cin >> name;
    //                 path = temp->Info->path + "/" + name;
    //                 cout << "Enter type of File to create in " << temp->Info->path << ": ";
    //                 cin >> type;
                    
    //                 temp->Right = new Node(new NodeInfo(name, path, type));
    //                 temp = temp->Right;
    //             }
    //             else
    //             {
    //                 string name, type, path;
    //                 cout << "Enter name of Folder to create in " << temp->Info->path << ": ";
    //                 cin >> name;
    //                 path = temp->Info->path + "/" + name;
    //                 cout << "Enter type of Folder to create in " << temp->Info->path << ": ";
    //                 cin >> type;

    //                 temp->Left = new Node(new NodeInfo(name, path, type));
    //                 temp = temp->Left;
    //             }

    //         }

    //         cout << "Add more Files/Folders? (1/0): ";
    //         cin >> flag;
    //     }
    // }

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

            // Check if the path is valid
            if (temp->Info->name == path)
            {
                // found at root
                counter++;
            }
            // Check if there's a left or right child
            else if (temp->Left->Info->name == path)
            {
                temp = temp->Left; // Move to the left child
                counter++;
            }
            else if (temp->Right->Info->name == path)
            {
                temp = temp->Right; // Move to the right child
                counter++;
            }
            else
            {
                // Invalid path
                cout << "Invalid path." << endl;
            }

            cout << "Add more path? (1/0): ";
            cin >> flag;
        }
        // temp: last node in path

        Node *callingTemp = temp;
        AddRemoveFiles(temp);
    }

    void DisplayLevelOrderRightChildren()
    {
        if (root == nullptr)
        {
            cout << "Tree is empty." << endl;
            return;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty())
        {
            int levelSize = q.size();

            for (int i = 0; i < levelSize; ++i)
            {
                Node *current = q.front();
                q.pop();

                // Print the current node's information
                cout << current->Info->name << " (" << current->Info->type << ") ";

                // Enqueue right child if it exists
                if (current->Right != nullptr)
                    q.push(current->Right);
            }

            // Move to the next level
            cout << endl;
        }
    }
    };
