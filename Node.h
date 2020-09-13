//
//  Node.h
//  fractional-cascading
//
//  Created by Yang Du on 8/26/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <vector>
#include <algorithm>
#include "YNode.h"

using namespace std;



class Node {
public:
    YNode* yroot = nullptr;
    double val;
    Node* left = nullptr;
    Node* right = nullptr;
    bool isLeaf = false;
    Point p; // only meaningful at leaf
    void build_helper(vector<Point> v); // v is sorted by x
    YNode* builtYTree(vector<Point> w); // w is sorted by y
};


#endif /* Node_h */
