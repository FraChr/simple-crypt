#pragma once
#include <queue>

#include "CompareTree.h"
#include "Tree.h"

static Tree* buildTree(std::priority_queue<Tree*, std::vector<Tree*>, CompareTree> &pq) {

    while (pq.size() > 1) {
        Tree* l = pq.top(); pq.pop();
        Tree* r = pq.top(); pq.pop();
        /*Tree* combined(l->root(), r->root());*/
        Tree* combined = new Tree(l->root(), r->root());
        pq.push(combined);
    }
    return pq.top();
};
