//
// Created by Sp4rk on 16-09-17.
//

#ifndef CES_EXAMPLEBASE_H
#define CES_EXAMPLEBASE_H

#include <iostream>

class ExampleBase
{
public:
    void print(const std::string& input) const;

    virtual void showExample() = 0;
};

#endif //CES_EXAMPLEBASE_H
