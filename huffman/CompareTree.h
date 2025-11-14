#pragma once
#include "INode.h"
#include "Tree.h"

struct CompareTree {
    bool operator()(const Tree *a, const Tree *b) const {
        return a->Weight() > b->Weight();
    }
};
