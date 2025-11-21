#pragma once

class INode {
public:
    virtual ~INode() = default;

    virtual bool isLeaf() = 0;

    virtual int Weight() = 0;
};