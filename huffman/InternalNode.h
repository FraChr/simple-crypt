#pragma once
#include "LeafNode.h"

class InternalNode : public INode {
public:
    InternalNode(INode *left, INode *right, const int weight)
        : _weight(weight), _left(left), _right(right) {
    };

    INode *left() { return _left; }
    INode *right() { return _right; }
    int weight() override { return _weight; }
    bool isLeaf() override { return false; }

private:
    int _weight;
    INode *_left;
    INode *_right;
};
