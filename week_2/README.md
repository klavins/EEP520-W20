Software Engineering For Embedded Applications
===

Week 2: The C Language
---

Last week we focused on the installation and use of several development tools. The aims were to give you a solid environment in which to develop code in C and C++, as well as to make sure the class as a whole are using the same tools.

This week we review (or introduce) the C language and use our environment to make a simple application.

- Build environment revisited
- C data types
- C control structures
- Example: RPN Calculator
- Homework

Review: VS Code
===

- Use this editor to edit your source files, header files, and Makefile. 
- VS Code also includes a terminal for entering command line statements. 
  - The VS Code terminal seems to work much better with docker than the command prompt on windows.

Review: The Terminal
===

Everyone should have some kind of terminal window into which they can enter and run `git` and `docker` commands. 
- Ideally, use VS Code's terminal
- On a Mac, this is the program called `Terminal`. 
- On a PC, this is a program called `command prompt`. 
- On a PC, if you installed the Docker toolbox version of Docker, then you should use the Docker `Quickstart` shell. 
- We will call the environment that you run git and docker commands the "host environment".

Review: Command line / Linux
===

Get away from using Finder and Explorer. Use the command line!!!

Make sure you understand these basic linux commands:
- `pwd`, `cd`, `ls`, `mkdir`, `cp`, `mv`, `rm`

Make sure you know these file system abbreviations
- `.`, `..`, `/` 

When we say to run a particular command from "within" a directory X, we mean that the current directory of your command line terminal should be X. That is, `pwd` should return `X`. If not, `cd` to the directory X before running the command.

<span style="background: yellow; padding: 10px; font-weight: bold">Know how to use the linux shell!</span>

Read this: http://linuxcommand.org/index.php. This is not merely a suggestion!

Review: Git
===

Use `git` to keep track of versions of your code, to save your code to `github`, and to retrieve example code and lecture notes from the course repository.

You will put your code in a repository called `520-Assignments` under your username. When you make changes, and to submit your homework, run the following from within `520-Assigments` (or any subdirectory of `520-assignments`).
```bash
git add .
git commit -m "an informative message"
git push origin master
```

**Note:** You can run `git` from either your host environment or the container environment that you get by executing `docker run` with `bash` (see below).

Review: Course Code and Notes
===

Prof. Klavins will put example code and course notes in a repository called `EEP520-W20` under the username `klavins`. You should have cloned the `EEP520-W20` repository onto your local computer, with the command:

```bash
git clone https://github.com/klavins/EEP520-W20.git
```

**Note:** Do not run this command inside `520-Assignments` or any of its subdirectories!!!

To get the latest version, run the following `git` command from within the `ECEP520` directory in your host environment:
```bash
git pull origin master
```
which will retrieve the latest changes from github.

Review: Docker
===

You should have Docker running on your computer by now. For the next several weeks we will continue to use the `cppenv` image to start a container that has the gnu compiler tools, the Google test library, and the Doxygen API documentation tool.

Within your host environment you will execute a command like
```bash
docker run -v /path/to/ECE590:/source -it cppenv bash
```
to get a `bash` prompt that allows you to run commands within the "container environment". 

You will be initially placed the the `/source` directory onto which the `-v` option to docker will have mounted the `/path/to/ECE590` directory in your host environment. This directory and its children are the only host directories available within the container environment.

Review: `gcc` and `g++`
===

These commands are available in the container environment and are used to compile C and C++ source files into object files and executables. 

**Note:** Some of you may also have these commands available in your host environments, but will not have libraries like `gtest` installed on your host environment. So you should only use these commands in the container environment.

Review: `make`
===

This command is available in the container environment and is a way to script a bunch of long `gcc` or `g++` commands together, to compile only changed files, and to keep track of files and directories. 

You will normally just use the course Makefile and edit a few lines to tell make what files are part of your source code. We have made changes to the Makefile, by the way. You no longer need to add your source and header files, because we have changed the `HEADERS` and `SOURCES` definitions to:
```make
HEADERS     := $(wildcard *.h)
SOURCES     := $(wildcard *.c)
```

Review: gtest
===

The is a C library that is installed in the cppenv image and available to `gcc` and `g++` within the container environment. Specifically, the cppenv conatiner has the gtest include files installed in 
```bash
/usr/local/include/gtest
```
which you get by putting
```c
#include "gtest/gtest.h"
```
in your source files. The gtest shared object library (which is like a unix DLL) is located at
```bash
/usr/local/lib/libgtest.a
```
which you link when you compile with the `-lgest` option to `gcc` or `g++`. 

**Note:** Gtest is a C++ library. To use it with our C examples, we will need to compile everyting with `g++`. Thus, although C++ syntax is available to us, we will only use C for now in our code. 

The C Programming Language
===

Most of you have encountered C at some point. We will not review all of the details of C syntax. Many guides exist online and book by Kerninghan and Ritchie is an excellent source. If you are not familiar with the following concepts in C, you should review them before attempting the homework (for example [here](http://www.cplusplus.com/doc/tutorial/control/)).

- `if` statements
- `for` loops
- `while` loops
- `do` ... `while` loops
- `switch` ... `case` statements
- operators such as `*`, `+`, `-`, `%`, `||`, `&&`, `>`, `<`, `>=`, `<=`, `!`, `++`, and `--`
- the `a ? b : c` syntax for inline if statments

In this lecture, we will assume these concepts are straightforward and mainly talk about C's type system, which is the most complex aspect of C programming.

printf
===

One of the most useful functions in C is the `printf`. You can use it to format strings together with variables to print information to the shell. The declaration of `printf` is
```c
int printf ( const char * format, ... );
```
which means it takes a pointer to a (null terminated) string of characters and an optional set of arguments. The optional arguments are values that will be interpoloated into the string based on 'format specifiers', one for each type. For example,
```c
int x = 1;
double y = 2.3;
char z[] = "uw";
printf("x = %d, y = %lf, z = '%s'\n", x, y, z );
```
prints out the values of `x`, `y`, and `z` in a nicely formatted way. See the [documentation](http://www.cplusplus.com/reference/cstdio/printf) for `printf` for a list of the other format specifiers and modifiers available to `printf`.

Types in C
===

In C, every variable, function argument, and function return value needs to have a declared type. One of the basic types in C is `int`, which refers to a positive, zero, or negative integer. The following bit of code uses the `int` type to define a function that takes an `int` argument, has two local `int` variables, and returns an `int` value. 
```c
int sum(int n) {
  int i,
      s = 0;
  for (i=0; i<=n; i++) {
    s = s + i;
  }
  return s;
}
```

Scope
===

Note that when `s` is declared it is also assigned an initial value. Initializating a variable when it is declared is optional, but often a good idea. You can also write the above function like this:
```c
int sum(int n) {
  int s = 0;
  for (int i=0; i<=n; i++) {
    s = s + i;
  }
  return s;
}
```
In this case, the variable `i` is delcared within the scope of the for loop and not in the broader scope of the function. In general, you can declare local variables in any block, whether it is a function block, a `for` loop or an `if` statement. In particular, you can declare variables in google test `TEST` blocks. 
```c++
TEST(MyTest, LocalOne) {
  int x = 5;
}

TEST(MyTest, LocalTwo) {
  double x = 6.28; /* different variable than in the previous block */
}
```
The void type
===

In C, an object with type `void` has no value. Usually we use `void` to refer to functions that do not return anything, such as
```c
void say_hello() {
  printf("hello\n");
  return;
}
```
Note that you cannot declare a variable of type `void`.

Basic Types
===
The following code demonstrates most of the basic integer types in C along with some initializations showing what sorts of values they take. Note that character values such as `'a'`, `'b'` and `'c'` are shorthand for ASCII integer values, in this case `97`, `98`, and `99`. 
```c
char a = 97;             /* one byte */
unsigned char b = 'b';
signed char c = -99;
short d;                 /* two bytes */
unsigned short e;
int f;                   /* two or four bytes */
unsigned int g; 
long h;                  /* four bytes */
unsigned long i;
```
To see how many bytes a type has, you can use the `sizeof` function, as in 
```c
printf("The size of an int on this machine is %d\n", sizeof(int));
```

Float Types
===

In addition , the following floating point types are available:
```c
float x;                 /* four bytes, 6 decimal places     */
double y;                /* eight bytes, 15 decmial places   */
long double z;           /* sixteen bytes, 19 decimal places */
```
You trade storage space and speed as you increase the size of these types.

Limits
===

The minimum and maximum values of variables with these types for the particular C implemtation you are working with are noted in the `<limits.h>` header file. If you include this header in a source file, open the file with Visial Studio Code, and follow its definition, you'll see all sorts of C pre-processor macros defining limits. To use the definitions, for example, do:
```c
#include <limits.h>
#include <stdio.h>
...
printf("The minimum value of INT = %d\n", INT_MIN);
printf("The maximum value of INT = %d\n", INT_MAX);
...
```
which on an Intel machine will print out
```bash
The minimum value of INT = -2147483648
The maximum value of INT = 2147483647
```

Modifiers: `register`
===

This keyword is used to strongly suggest to the compiler that the variable should be stored in a register instead of in RAM. You would do something like this:
```c
void f(int x) {
  register int i;
  for(i=0; i<10; i++) {
    /* do something */
  }
}
```
However, most compilers know how to figure out when to use a register for a counter without the `register` keyword, so you do not almost certainly will not need to use this modifer.

Modifiers: `volotile`
===

This keyword is used to refer to locations in memory that might change do to something happening outside of the code. It prevents the compiler from assuming that a volatile variable that is assigned only once in the code will never change and subsequently optimizing it out of existence. For example, on an embedded device, if you know that location 0x5555 was a globally available register being written to by, for example, a sensor or interrupt handler, then you could do
```c
voif f() {
  volatile int * x = 0x5555; /* x is a pointer to the 
                              * location 0x5555 (see pointers
                              * below) */
  while ( *x == 0 ) {
    /* wait */
  }
  /* do something because *x changed, 
    * presumably due to some outside event */
}
```

Modifiers: `static`
===

A static variable is one that preserves its value even after it has gone out of scope. For example, compare the following two functions
```c
int f() {
  int x = 0;
  x++;
  return x;
}

int g() {
  static int x = 0; /* note: must be a literal constant,
                      *  not a computed value */
  x++;
  return x;
}
```
If you call `f` twice in a row, you will get the value `1` each time. If you call `g` twice in a row, you will get `1` the first time and `2` the second time. Thus, the function `g` is using `x` as local storage. It initializes the variable the first time it is called, but does not reinitialize it upon subsequent calls to the function.

Modifiers: `static` within a File
===

The `static` keyword is also used in a *totally different way* to declare variables and functions as local to the file in which they are defined. If a function is defined without static, as in
```c
int f(int x) {
  return x+1;
}
```
then it is globally available to your code (assuming your code includes its declaration). If a function is defined as static, then it is only available in that file:
```c
static int f(int x) {
  return x+1;
}
```
If you put this in a file called `my_source.c`, then only codw within `my_source.c` can use the function `f`. This is a way to make private functions that you do not want users of an API to access. 

Modifiers: `const`
===

This keyword is used in variable declarations to make symbols that refer to constants. For example
```c
int f() {
  const double PI = "3.14159"; 
  /* etc */
}
```
The compiler will complain if you attempt to reassign `PI` later in the code for `f`.

The use of `const` gets complicated when combined with pointers (see below). In short, you can define a constant pointer with
```c
int * const ptr;
```
and a pointer to a constant value with
```c
const int * ptr;
```

Modifiers: `const` Arguments
===

If you have a function that takes a pointer to a value and want to enforce that the function does not modify the pointed to value, then you would define the argument to the function as follows:
```c
void f(const int * p) {
  /* do things like print *p but don't
    * modify it */
}
```
The follow example will produce a compile error because the function attempts to change the value pointed to by `x`.
```c
int f ( const int * x ) {
    *x = *x + 1;
    return *x;
}    
```
Compiling this code gives the error
```bash
  error: assignment of read-only location '* x'
  *x = *x + 1;
    ^
```

Modifiers: `extern`
===

This keyword is used in certain circumstances to declare functions without defining them, and to tell the compiler to go ahead and link your code expecting that the function will be defined somewhere else. We will likely not need it, although you will see it a lot in header files we include.

Structures
===
A structure in C is like a record or dictionary in other languages. It is a way to define a new type of object to store information that belongs together. For example, you might use the following structure to keep track of the information associated with a new data type you are defining called point and then declare some points.
```c
struct point {
  double x, y, z;
};
struct point p, q;
```
You can then refer to the components of a point with the `.` notation as in `p.x` or `q.z`. If you do not name the `struct` then you can declare `p` and `q` directly, but then cannot declare more structs of the same type:
```c
struct {
  double x, y, z;
} p, q;
```

Typedef with `struct`
===

If you would like to avoid having to write `struct point` over and over, you can also make a type definition as in the following example:
```c
typedef struct point {
  double x, y, z;
} Point;
Point p, q;
```
which also delcared `p` and `q` to be of type `struct point`. 

You can initialize a struct using either of the following notations:
```c
Point p = { .x = 1.0, .y = 2.0, .z = 3.0 };
Point q = { 1.0, 2.0, 3.0 };
```
The order in which the members of the struct were declared determines the order in which the initializers should appear. 

Unions
===
A `union` is like a `struct`, but with all members using the smae memory location. A `union` allows you to use only **one** of the members of the union at the same time. For example,
```c
typedef union thing {
  int x;
  double y;
  float z;
} Thing;
Thing t;
```
In this case, the addresses in memory of `t.x`, `t.y` and `t.z` are all the same. If we replaced the above with a `struct`, they would all be different. 

Enums
===
An `enum` is a way to enumerate the possible values a variable might have. For example
```c
typedef enum status {
  IDLE, RUNNING, ERROR
} Status;
Status x = IDLE;
```
defines a variable of type `Status` whose values are either `IDLE`, `RUNNING` or `ERROR`. These values are *not* strings. They are symbols. However, in C (but not in C++), the compiler actually just uses the integers 0, 1, 2, ... internally to represent the values in an enum. Thus, you will notice that you can treat them like integers, but you should make every effort not to do so, since other compilers may use different numbers to represent an enum's values. 

Pointers
===
The most difficult aspect of C is its use of pointers, which most other higher level languages like Python or Javascript do not have. When you declare a variable, the C compiler has to store it in memory somewhere. The location in memory of the value of a variable is called its *address*. So a pointer variable is a variable whose value is an address. 

There are two operators in C that you use to change back and forth between a variable's value and its address. The first is the `&` operator, which finds a variable's address. For example,
```c
int p = 1;
printf("The value of p is %d and the address of p is %x.\n", p, &p);
```
which would print out something like:
```bash
The value of p is 1 and the address of p is e5788eac.
```
The hexadecimal number e5788eac is the physical address in memory of the first byte of the integer `p`. 

Dereferencing
===

The second operator is the `*` operator, which dereferences a pointer and is also used to declare a pointer. For example, suppose `p` and `ptr` were declared as follows:
```c
int p = 1;
int * ptr = &p;
```
then `p` is an integer and `ptr` is the address of `p` in memory. If you would like to get the value pointed to by `ptr`, then you would use the syntax `*p`. For example, 
```c
int q = *ptr; /* q is 1 */
*ptr = 2;     /* indirectly changes p to 2 */
```

Pointers to `structs`
===

One of the places pointers are used extensively in C is with pointers to structs. This is because a struct can be quite large, and passing structs around by copying everything in them is a waste of time and space. When you have a variable that is a pointer to a struct, then you use the `->` operator instead of the `.` operator, as in the following example:
```c
typedef struct {
  double x, y, z;
} Point;
Point * ptr;
ptr->x = 3;
```
Actually, `ptr->x` is really just shorthand for
```c
(*ptr).x
```
but is more preferred. 

Pointers to functions
===

You can also define pointers to functions. The syntax is tricky. For example, the following defines a function `add` and a pointer `f_ptr` to it.
```c
int add(int n, int m) {
  return n+m;
}
int (* f_ptr) (int,int);
f_ptr = add;
```
You can use this syntax to send functions to other functions as arguments. For example, the following function applies a function to a value and returns the value.
```c
int apply(int (*f) (int), int x) {
  return f(x);
}
```

Arrays
===
Arrays in C are contiguous regions of memory that contain strings of values.
Arrays can be declared with the `[]` operator as follows:
```c
int x[10];                             /* an array of 10 integers */
Point plist[20];                       /* An array of 20 Point structures */
double y[] = { 2.1, 3.2, 4.3, 5.4, };  /* Array of four doubles with initial values */
```
Arrays are zero indexed. Elements can be assigned and retrieved using the `[]` operator as well. For example,
```c
x[0] = 1;
x[1] = x[0];
plist[5] = (Point) { 3.1, 4.1, 5.9 };
y[3] = plist[5].y;
```
In the above cases, `x`, `plist` and `y` are just pointers to the beginning of the memory location for the arrays they represent. The `[]` operator is just shorthand for pointer arithmetic. Thus, the above code is equivalent to the following:
```c
*x = 1;
*(x+1) = *(x);
*(plist + 5) = (Point) { 3.1, 4.1, 5.9 };
*(y+3) = (plist+5)->y;
```

Bound Checking
===

**Warning**: Arrays in C are not bounds checked. For example, the following code may compile just fine, but in fact contains a serious error.
```c
int a[10];
a[12] = 5;
ASSERT_EQ(a[12], 5);
ASSERT_EQ(a[13], 0);
```
This compiles and runs without error in the `cppenv` container, but it is just luck. The memory locations at `a+12` and `a+13` just happen to be unused. If you do try to write to `a[1000]` or larger, you will almost certainly encounter either
- a segmentation fault, meaning that you wrote a value outside the memory reserved by the OS for your application;
- strange behavior, meaning you wrote a value to some other data structure's portion of memory.
To catch errors like this, you can use a tool called 'Address Sanitizer'. To use it, we modify the Makefile as follows
```c
CFLAGS      := -fsanitize=address -ggdb
LIB         := -lgtest -lpthread -lasan
```
Now, the code still compiles, but when you run it you get all sorts of useful error information from `asan`.

Memory Allocation
===
When you declare arrays as with the above, you know at compile time how big they should be. However, often you do not know this, and may also need to write functions that return arrays. To dynamically allocate memory in C, you use the functions `malloc` and `calloc`, which are available in `stdlib`. For example, to dynamically allocate memory for 10 doubles, you can do:
```c
double * a = (double *) malloc(10*sizeof(double));
```
or
```c
double * a = (double *) calloc(10,sizeof(double)); /* also inits array to zeros */
```
Now `a` can be used just like a normal array, with elements `a[0]`, `a[1]` and so on. Note that 'malloc' and 'calloc' return `void *` pointers, because they do not have any way of knowing what type of array you want. Thus, we have to *type cast* or *coerce* the value returned into the correct type. That is what the `(double *)` notation does.

Deallocation
===

It is important to note that if you declare a pointer and allocate memory for it in a function, then the pointer disappears when the function is complete, but the memory allocated does not. Thus, when you are done using the memory, your code must give the memory back to the operating sytem using the `free` function, also in `stdlib.h`. For example,
```c
void f() {
  int * a = (int *) calloc(1000,sizeof(int));
  /* do stuff with a */
  free(a);
}
```
This issue becomes particularly important when you use functions that allocate memory for you. For example, here is a function that joins two arrays together into a new array:
```c
int * join(const int * a, int length_a, const int * b, int length_b) {
    int * c = (int *) calloc(length_a+length_b, sizeof(int));
    for (int i=0; i<length_a; i++ ) {
        c[i] = a[i];
    }
    for (int i=0; i<length_b; i++ ) {
        c[i+length_a] = b[i];
    }
    return c;
}
```

The Allocation / Free Pattern
===

To use this function and then free the result, you might do
```c
TEST(Examples,AlocateAndFree) {
    int a[] = { 0, 1, 2 };
    int b[] = { 3, 4, 5 };
    int * c = join(a, 3, b, 3);
    for (int i=0; i<6; i++ ) {
        ASSERT_EQ(c[i], i);
    }
    free(c);
}
```
Repeated failure to free the result of `join` would result in a *memory leak*, which will eventually use up all the RAM on your computer, causing a crash. These are hard to catch. Memory leaks are in fact one of the biggest issues plaguing modern software. Modern languages have *garbage collectors* to clean up unused memory, but (a) they don't work in every case and (b) they are written in C or C++ by humans who make mistakes.

Strings are arrays of chars;
===
Strings in C are contiguous regions of one byte memory addresses whose values are usually interpreted as characters. To declare and initialize strings, you do something like:
```c
char x[] = "Hi";
char y[3] = { 'H', 'i', '\0' };
char z[3];
char z[0] = 'H';
char z[1] = 'i';
char z[2] = '\0';
```
The special character `\0` is called the **null** character and is used to terminate strings so that functions that manipulate them know when to stop.

When you declare a string within a scope, its memory is allocated for the duration of that scope. If you want a string that lasts a long time, you might have to allocate it yourself, in which case you would just treat it as an allocated array of characters.

Design Example
===

**Goal:** Write a reverse polish notation (RPN) calculator in C with functions `rpn_init`, `rpn_push`, `rpn_add`, `rpn_negate`, `rpn_multiply`, `rpn_pop`, `rpn_error`. The way an RPN calculator works is as follows.

- The `init` method creates a new array to implement the stack. It also sets an index to the top of the stack to zero. If the `init` method has been called already, then it frees the old stack and creates a new stack. It should also clear errors.
- The `rpn_push` method pushes its argument onto the stack.
- The `rpn_negate` method negates the value on the top of the stack.
- The `rpn_add` method pops the top two values off the top of the stack and pushes their product onto the stack.
- The `rpn_multiply` method pops the top two values off of the stack and pushes their product onto the stack.
- The `rpn_pop` method pops the top value off the stack and returns it. 
- The `rpn_free` method should free the memory used by the rpn, and un-initialized it.

Dealing With Errors
===

Your user's may not always treat your RPN Calculator correctly, so you should look out for runtime errors.

- The `rpn_error` method should return an enum value, either
```c
OK, NOT_INITIALIZED_ERROR, POP_ERROR, UNARY_ERROR, BINARY_ERROR, ADD_ERROR, or OVERFLOW_ERROR
```
Errors include trying to `pop` or `negate` an empty stack, trying to apply `add` or `multiply` to a stack with fewer than two values on it, or having the result of a computation be greater than the maximum value a `double` can hold. If the rpn has not been initialized before a called to one of the other operations, then rpn_error should become `NOT_INITIALIZED`. pop` should return 0 when the calculator is in an error mode.

Test Driven Development
===

To develop a library like this, we will follow the following procedure:

0. Create a directory structure
0. Put function type declarations in a header (.h) file
0. Put empty function definitions in a source file (.c)
0. Define tests that should pass
0. Keep refining the source code until all the tests pass

Directory Structure
===

Copy the template directory in week_2.

Change names from `example` to `rpn`.

Function Declarations
===

Put this code in `rpn.h`

```c
#ifndef RPN_H
#define RPN_H

#include <stdlib.h>

typedef enum {
    OK, 
    NOT_INITIALIZED_ERROR, 
    POP_ERROR, 
    NEGATE_ERROR, 
    MULT_ERROR, 
    ADD_ERROR,
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
```

Function Definitions
===

Put this code in `rpn.c`

```c
#include "rpn.h"

void rpn_init() {}
void rpn_push(double x) {}
void rpn_add() {}
void rpn_negate() {}
void rpn_multiply() {}
double rpn_pop() { return 0; }
RPN_ERROR rpn_error() { return OK; }
void rpn_free() {}
```
Basic Test File
===

```c
#include "gtest/gtest.h"
#include "rpn.h"

namespace {
    TEST(HW2,RPN) {
        rpn_init();
    }
}
```

Note that `main.c` stays the same:

```c
#include <stdio.h>
#include "gtest/gtest.h"

GTEST_API_ int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
```

Example Test
===

```c
TEST(RPN,Arithmetic {
  rpn_init();
  rpn_push(0.5);
  rpn_push(2.0);
  rpn_push(1.0);
  rpn_add();
  rpn_multiply();
  rpn_negate();
  ASSERT_EQ(rpn_pop(),-1.5);
  ASSERT_EQ(rpn_error(), OK);
  rpn_free();
```

See the `rpn_3` directory for a full set of tests. 

Developing Code
===

0. Fill in functionality, assuming user does the right thing.
0. Create tests for catching errors. 
0. Put in condition checking for errors.
0. Repeat as necessary.

See the `rpn_3` directory for a complete implementation.

Exercises Setup
===

If you are unfamiliar with C or need a refresher, you should spend a few hours reading through a good tutorial, such as [this one](https://www.tutorialspoint.com/cprogramming/index.htm).

For homework 2 you will write a set of functions that are mostly unrelated, but for convenience we will put into one source file and one header file. You will also modify the RPN example. Thus, your homework 2 directory should look like
```bash
- 520-Assignments/
  - hw_2/
    - solutions
      - main.c
      - unit_tests.c 
      - solutions.h
      - solutions.c
      - Makefile
    - rpn/
      - main.c
      - unit_tests.c 
      - rpn.h
      - rpn.c
      - Makefile    
```
In the first directory, the `unit_tests.h` file will include `solutions.h`, which should have all your function declarations in it. The implementations of those functions should be put in `solutions.c`. For the second directory, start by copying the `rpn_3` directory from the `week_2` directory within the course's code repository.

Exercises
===

1. Write a function called `running_total` that keeps track of the sum of the arguments it has been called with over time. Someting like the following test should pass.
        
        TEST(HW2,RunningTotal) {
          ASSERT_EQ(running_total(1),  1);
          ASSERT_EQ(running_total(1),  2);
          ASSERT_EQ(running_total(5),  7);
          ASSERT_EQ(running_total(-3), 4);      
        }       

1. Write a function called `reverse_in_place` which takes an array and its length and reverses it in place. Something like the following tests should pass.

        TEST(HW2,ReverseInPlace) {
            int x[] = {10,20,30,40,50};
            reverse_in_place(x,5);
            ASSERT_EQ(x[0],50);
            ASSERT_EQ(x[1],40);       
            ASSERT_EQ(x[2],30);   
            ASSERT_EQ(x[3],20);   
            ASSERT_EQ(x[4],10);                            
        }
3. Write a function called `reverse` that takes an array and its length and returns a new array that is the reverse of the given array. The function should use `calloc` to create space for the new array. A test for this might look like

        TEST(HW2,Reverse) {
            int x[] = {10,20,30,40,50};
            int * y = reverse(x,5);
            ASSERT_EQ(y[0],50);
            ASSERT_EQ(y[1],40);       
            ASSERT_EQ(y[2],30);   
            ASSERT_EQ(y[3],20);   
            ASSERT_EQ(y[4],10);  
            free(y);
        }
4. Write a function called `num_instances` that takes an array of integers, a length, and a value and returns the number of instances of that value in the array. 

        TEST(HW2,NumInstances) {
          int a[] = { 1, 1, 2, 3, 1, 4, 5, 2, 20, 5 };
          ASSERT_EQ(num_instances(a,10,1), 3);
        }
6. Write a function called `map` that takes an array of Points, its length, and a function pointer that returns a newly allocated array whose values are the values of the function argument applied to the array argument. You should put the following `typedef` in your `solutions.h` file:

        typedef struct {
          double x, y, z;
        } Point;

  Then tests like the following should pass.

        Point negate(Point p) {
          return = { -p.x, -p.y, -p.z };
        }

        TEST(HW2,PointMap) {
          Point a[] = { { 1,2,3 }, { 2,3,4 } };
          Point * b = map(a,2,negate);
          for(int i=0; i<2; i++) {
            ASSERT_EQ(b[i].x,-a[i].x);
            ASSERT_EQ(b[i].y,-a[i].y);
            ASSERT_EQ(b[i].z,-a[i].z);
          }
          free(b);
        }   
7. Extend the RPN Calculator Example with the following improvements:

  a) Add an `rpn_div()` operation that divides the second to the top element of the stack with the top element of the stack. Add a `DIVIDE_BY_ZERO_ERROR` type and check for that. Also check that the result of the division does not overflow the size of a `double`. 

  b) The stack in the example code from class has a fixed size of 100. If the user is about to exceed in a call to `push`, then you should use the `realloc` method to reallocate your array to be twice as large. See [here](https://www.tutorialspoint.com/c_standard_library/c_function_realloc.htm) for details about how to use this function.

  Write tests for these behaviors first, then develop your code.
