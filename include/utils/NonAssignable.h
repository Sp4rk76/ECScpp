//
// Created by Sp4rk on 15-09-17.
//

#ifndef CES_NONASSIGNABLE_H
#define CES_NONASSIGNABLE_H

class NonAssignable {
public:
    NonAssignable(NonAssignable const&) = delete;
    NonAssignable& operator=(NonAssignable const&) = delete;
    NonAssignable() {}
};

#endif //CES_NONASSIGNABLE_H
