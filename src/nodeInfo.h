// nodeInfo.h
#pragma once
#include <iostream>
using namespace std;
class NodeInfo
{
    // name: name of file or directory
    // - path: path to file or directory (starting from root)
    // - type: file type/ null for directory
    // - child nodes: ref to left and right child nodes
public:
    string name;
    string type;
    string path;

    NodeInfo() : name(""), path(""), type("") {}
    NodeInfo(string name, string path, string type) : name(name), path(path), type(type) {}
};
