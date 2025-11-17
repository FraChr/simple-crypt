#pragma once
#include <queue>

#include "CompareTree.h"
#include "Tree.h"

static Tree* buildTree(std::priority_queue<Tree*, std::vector<Tree*>, CompareTree> &pq) {

    while (pq.size() > 1) {
        Tree* left = pq.top(); pq.pop();
        Tree* right = pq.top(); pq.pop();

        Tree* combined = new Tree(left->root(), right->root());
        delete left;
        delete right;
        pq.push(combined);
    }
    return pq.top();
};
