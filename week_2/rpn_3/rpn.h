#ifndef RPN_H
#define RPN_H

#include <stdlib.h>

typedef enum {
    OK, 
    NOT_INITIALIZED_ERROR, 
    POP_ERROR, 
    UNARY_ERROR, 
    BINARY_ERROR, 
    OVERFLOW_ERROR
} RPN_ERROR;

void rpn_init();
void rpn_push(double x);
void rpn_add();
void rpn_negate();
void rpn_multiply();
double rpn_pop();
RPN_ERROR rpn_error();
void rpn_free();

#endif