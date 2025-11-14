#pragma once
#include "INode.h"

class LeafNode : public INode {
    public:
        LeafNode(const char element, const int weight) : _element(element), _weight(weight) {};
        char value() const {return _element;}
        int weight() override {return _weight;}
        bool isLeaf() override {return true;}
    private:
        char _element;
        int _weight;
};
