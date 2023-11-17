// node.h
#pragma once
#include "nodeInfo.h"
class Node
{
public:
    NodeInfo *Info;
    Node *Left;  // Left child node.
    Node *Right; // Right child node.

    Node()
    {
        Info = new NodeInfo();
        Left = nullptr;
        Right = nullptr;
    
    }

    Node(NodeInfo *info)
    {
        Info = info;
        Left = nullptr;
        Right = nullptr;
    }

    ~Node()
    {
        delete Info;
        delete Left;
        delete Right;
    }
};