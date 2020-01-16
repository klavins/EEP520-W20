#include <stdio.h>
#include <math.h>

#include "rpn.h"

#define INITIAL_STACK_SIZE 100

static double * stack;
static int initialized = 0;
static int top = 0;
static RPN_ERROR error = OK;

void rpn_show() {
    printf("--->\n");
    for ( int i=0; i<top; i++ ) {
        printf("  %lf\n", stack[i]);
    }
    printf("<---\n");
}

void rpn_init() {
  if ( ! initialized ) {
      stack = (double *) calloc(INITIAL_STACK_SIZE, sizeof(double));
      initialized = 1;
      top = 0;
      error = OK;
  }
}

void rpn_push(double x) {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else {
        stack[top] = x;
        top++;
    }
}

void rpn_add() {  
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else {    
        double x = stack[top-1]+stack[top-2];
        if ( x == INFINITY ) {
            error = OVERFLOW_ERROR;
        } 
        top--;
        stack[top-1] = x;
    }
}

void rpn_negate() {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 1 ) {
        error = UNARY_ERROR;
    } else {    
      stack[top-1] = -stack[top-1];
    }
}

void rpn_multiply() {
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
    } else if ( top < 2 ) {
        error = BINARY_ERROR;
    } else {    
        double x = stack[top-1]*stack[top-2];
        if ( x == INFINITY || x == -INFINITY ) {
            error = OVERFLOW_ERROR;
        } 
        top--;
        stack[top-1] = x;
    }
}

double rpn_pop() { 
    if ( !initialized ) {
        error = NOT_INITIALIZED_ERROR;
        return 0;
    } else if ( top == 0 ) {
        error = POP_ERROR;
        return 0;        
    } else {
        double result = stack[top-1];
        top--;
        return result;
    }
 }

RPN_ERROR rpn_error() { return error; }

void rpn_free() {
    if ( initialized ) {
        free(stack);
        initialized = 0;
    }
    error = OK;
}