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
            if (left->weight() > right->weight()) std::swap(left, right);
            int combinedWeight = left->weight() + right->weight();
            _root = new InternalNode(left, right, combinedWeight);
        }

        INode *root() const {return _root;}
        int Weight() const {return _root->weight();}

    private:
        INode* _root;
};
