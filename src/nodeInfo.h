#pragma once
#include <iostream>
using namespace std;
class NodeInfo
{
public:
    string name;
    string type;
    string path;

    NodeInfo() : name(""), path(""), type("") {}
    NodeInfo(string name, string path, string type) : name(name), path(path), type(type) {}
};
