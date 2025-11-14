#pragma once

class INode {
    public:
        virtual ~INode() = default;
        virtual bool isLeaf() = 0;
        virtual int weight() = 0;
};