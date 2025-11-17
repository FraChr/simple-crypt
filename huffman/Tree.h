#pragma once
#include "INode.h"
#include "InternalNode.h"
#include "LeafNode.h"

class Tree {
    public:
        Tree(char element, int weight) {
            _root = new LeafNode(element, weight);
        }

        Tree(INode *left, INode *right) {
            if (left->Weight() > right->Weight()) std::swap(left, right);
            int combinedWeight = left->Weight() + right->Weight();
            _root = new InternalNode(left, right, combinedWeight);
        }

        INode *root() const {return _root;}
        int Weight() const {return _root->Weight();}

    private:
        INode* _root;
};
