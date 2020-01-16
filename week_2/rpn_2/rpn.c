#include "rpn.h"
#include "stdio.h"

#define INITIAL_STACK_SIZE 100

static double * stack;
static int initialized = 0;
static int top = 0;

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
  }
}

void rpn_push(double x) {
    stack[top] = x;
    top++;
}

void rpn_add() {  
    double result = stack[top-1] + stack[top-2];
    top--;
    stack[top-1] = result;
}

void rpn_negate() {
    stack[top-1] = -stack[top-1];
}

void rpn_multiply() {
    double result = stack[top-1] * stack[top-2];
    top--;
    stack[top-1] = result;  
}

double rpn_pop() { 
    double result = stack[top-1];
    top--;
    return result;
 }

RPN_ERROR rpn_error() { return OK; }

void rpn_free() {}