//
//  YNode.hpp
//  range-tree
//
//  Created by Yang Du on 9/13/20.
//  Copyright © 2020 Yang Du. All rights reserved.
//

#ifndef YNode_hpp
#define YNode_hpp

#include <stdio.h>

struct Point {
    double x;
    double y;
};

class YNode {
public:
    YNode* left = nullptr;
    YNode* right = nullptr;
    Point p;
};


#endif /* YNode_hpp */
