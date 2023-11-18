#pragma once
#include "nodeInfo.h"
#include <limits>
class Node
{
public:
    NodeInfo *Info;
    Node *Left;
    Node *Right;

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