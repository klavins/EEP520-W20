Software Engineering For Embedded Applications
===

Week 4: Introduction to C++
---

**Last time:**
- abstract data types
- constructors and destructors
- naming conventions
- hiding memory allocation from the user
- getters, setters
- the DRY principle
- common array operations like push, pop, and map
- a (clunky) way)to make arrays of any type

**Today:**
- How these ideas map onto C++
- How C++ makes them easier
- How C++ may be confusingly sophisticiated

Resources
===

- Reference: [http://www.cplusplus.com/](http://www.cplusplus.com/)
- Books: [https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list](https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list)

Programming Lanaguage History
===

<img src="https://camo.githubusercontent.com/8b66ce7a30e85901be14bcc0a20510f458f8b5e3/68747470733a2f2f7261776769746875622e636f6d2f73746572656f626f6f737465722f70726f6772616d6d696e672d6c616e6775616765732d67656e65616c6f676963616c2d747265652f67682d70616765732f696d672f6469616772616d2e737667">


Language Types
===

<table style="width: 90%">
<tr>
  <td>Imperative</td>
  <td width=15%><img src="https://www.northernpublicradio.org/sites/wnij/files/styles/x_large/public/201809/hopper_edit.jpg"></td>
  <td>Grace Hopper (US Navy)</td>
  <td>Flowmatic</td>
  <td>COBOL, ...</td>
</tr>
<tr>
  <td>Functional / AI</td>
  <td><img src="https://blog.lfe.io/assets/images/posts/John-McCarthy.jpg"></td>
  <td>John McCarthy (MIT)</td>
  <td>Lisp</td>
  <td>Caml, Haskell </td>
</tr>
<tr>
  <td>Procedural</td>
  <td><img src="https://www.computerhope.com/people/pictures/john_backus.jpg"></td>
  <td>John Backus (IBM)</td>
  <td>Fortran</td>
  <td>C, C++</td> 
</tr>
<tr>
  <td>Object Oriented</td>
  <td><img src="https://history-computer.com/ModernComputer/Software/images/Dahl_and_Nygaard.jpg"></td>
  <td>Ole-Johan Dahl and Kristen Nygaard (NCC)
  </td><td>SmallTalk</td>
  <td>C++, Java </td>
</tr>
<tr>
  <td>Declarative / Logical</td>
  <td><img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/49/A-Colmerauer_web-800x423.jpg/330px-A-Colmerauer_web-800x423.jpg"></td>
  <td>Alain Colmerauer (U. Montreal)</td>
  <td>Prolog</td>
  <td>More Prolog</td>
</tr>
</table>

Most modern languages combine all of these paradigms.


Who uses C vs C++?
===

<img width=98% src="http://sogrady-media.redmonk.com/sogrady/files/2019/03/lang.rank_.119.png">

Programming Language Expressibility
===

<img src="http://dberkholz-media.redmonk.com/dberkholz/files/2013/03/expressiveness_weighted2.png">

- C++ is (perhaps) more expressive than C.
- The same algorithm should take fewer lines of code in C++ than it does in C, on average. 
- Highly expressive languages are hard to use.
- However, data suggest that the number of bugs in a program is proportional to the number of lines of code, not to the number of ideas expressed.
- Colors show popularity.

Procedural vs Object Oriented
===

<img src="https://4.bp.blogspot.com/-1ROdWNxn7v8/XBQ3W1emmmI/AAAAAAAAALU/C05s5HEb93QzB2weQXli829rK95aQpAxACLcBGAs/s1600/procedural-vs-oop-learn-java-oop.jpg" width=50%>

- A class defines an object's <u>attributes</u> and <u>methods</u>
- Inheritance shows how classes can be derived from other classes.
- The implementation is supposed to be hidden from the user.

| Good | Bad |
|------|-----|
| Code reuse | Dogmatic |
| Scalability | Requires training to code correctly |
| Easy collaboration | Some things really are just procedural |


Difficulties Scaling C projects
===

Avoiding naming collisions leads to very long function names:
```c++
    DynamicArray_set(a,1,2)  // dumb
```

Cannot associate methods with the objects they act upon
```c++
    DynamicArray_set(a,1,2)  // dumb
    a.set(1,2)               // better
    a[1] = 2                 // best!
```
Difficult to re-use or build upon code: `DoubleArray` vs `IntegerArray`, etc

Abstract data types are dealt with differently than built in types
- Built in types are:
    - Constructed when declared
    - Destructed when they go our of scope
    - Copied naturally with '='

The Rise of C++
===

<img width=20% src="https://media-bell-labs-com.s3.amazonaws.com/pages/20150220_2231/Stroustrup2-small.jpeg"><br>
Bjarne Stroustrup (Bell Labs)

Until C++, OOP was mostly academic

Stroustrup’s goal: Combine Simula and other OOP ideas with a practical language like C.

C++ History
===

1985 (while at Bell Labs and Columbia U)
- classes
- derived classes / inheritance
- strong typing
- inlining
- default arguments
- virtual functions
- function name and operator overloading
- constants
- type-safe free-store memory allocation (new/delete)
- improved type checking
- single-line comments with two forward slashes (//)

1989-1990 
- multiple inheritance
- abstract classes
- static member functions
- const member functions
- and protected members

Later
- templates
- exceptions
- namespaces
- boolean type

Recently
- Anonymous functions

C and C++ Uses
===

**C**:

- Operating systems, embedded systems, libraries, compilers, interpreters (e.g. Python), compilers (Java), intermediate languages (LLVM)

- Cars, planes, boats, phones, Linux, MATLAB, Mathematica, MySQL, ...

- The C compiler (so meta!)

**C++**:

- Big software: IE, Chrome, Firefox, Safari, Microsoft Office, OpenOffice, Outlook, Facebook, YouTube, Media Player, iPod software, MySQL, MongoDB, Windows UI, MacOS UI, Microsoft Visual Compiler, …

- Games: Doom III, Counter Strike, Sierra On-line: Birthright, Hellfire, Football Pro, Bullrider I & II, Trophy Bear, King’s Quest, Antara, Hoyle Card games suite, SWAT, Blizzard: StarCraft, StarCraft: Brood War, Diablo I, Diablo II: Lord of Destruction, Warcraft III, World of Warcraft, Starfleet Command, Invictus, Master of Orion III, CS-XII, MapleStory etc. Microsoft games, ...

- Languages: Javascript compiler, ...

Linus Torvalds on C++
===

From the invetor of Linux (written in C)

C++ is a horrible language. It's made more horrible by the fact that a lot of substandard programmers use it, to the point where it's much much easier to generate total and utter crap with it. Quite frankly, even if the choice of C were to do *nothing* but keep the C++ programmers out, that in itself would be a huge reason to use C.

I've come to the conclusion that any programmer that would prefer the project to be in C++ over C is likely a programmer that I really *would* prefer to piss off, so that he doesn't come and screw up any project I'm involved with.

This says a *lot* more about Linus than it does about C++. 

New things in C++ Covered Today
===

- References
- Auto declarations
- Namespaces
- iostream library
- Exceptions
- Classes and Objects
- Constructors and destructors
- Keywords: `new` instead of `malloc` and `delete` instead of `free`
- Operator overloading
- Templates

Resources
- Reference: [http://www.cplusplus.com/](http://www.cplusplus.com/)
- Books: [https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list](https://stackoverflow.com/questions/388242/the-definitive-c-book-guide-and-list)

References
===

Essentially an alias for a variable, references allow you to refer to the same object with a different name. Somewhat confusingly, references are declared using the `&` operation, which in C (and therefore also in C++) is the *dereference* operator. Here's an example declaration of a reference:
```c++
int x = 1;
int &y = x;
```
Note that we are defining `y` to refer to `x`. You can't just do
```c++
int &z
```
because you are not saying what `z` refers to. 

You can now do anything with `y` that you can with `x`. For example,
```c++
x = 3;
y == x; // true
y = 4;
x == y; // true
```

References are not pointers
===

- References are much safer! 
- They are not used for memory management (like pointers are)!
- There is no "reference arithmetic"
- They are just synonyms

References in Function Arguments
===

References are most useful in functions to make an argument *call by reference* instead of *call by value*. For example, the method `magnitude` defined below takes a const reference to a point. 
```c++
typedef struct {
    double x, y, z;
} Point;

double magnitude(const Point &p) {
    return sqrt(p.x*p.x + p.y*p.y + p.z*p.z);
}
```
You can use this method without caring that it is call by reference, as in:
```c++
Point p = { 0,3,4 };
ASSERT_DOUBLE_EQ(magnitude(p), 5);
```
The benefit speed. If you call by value, then the entire point structure, with its three doubles, is copied to call the function. With call by reference, only a reference is created, which is a much smaller object. Note that almost every modern scripted language, such as Python and Javascript, use call by reference for arrays, hashes, and other objects, because these objects can get quite large and copying them every time you call a function is innefficient.

Returning a Reference
===

A function can also return a reference. For example, suppose you want to compare the magnitudes of two points and return the one with a smaller magnitude. Copying all those points is a waste of time and space, so we use references instead. For example, if `smaller` is defined as
```c++
Point &smaller(Point &p, Point &q) {
    if ( magnitude(p) <= magnitude(q) ) {
        return p;
    } else {
        return q;
    }
}
```
then you can write
```c++
Point &r = smaller(p,q);
```
after which `r` will refer to the smaller of the two points. Let's say `p` is smaller. If you then do
```c++
r.x = -1;
```
you will also be setting `p.x`.

WARNING
===

Do not return a reference to a locally declared variable. Local variables are deleted from memory when the function completes, so you would be returning a reference to nothing. For example:
```c++
Point &f() {
    Point p = {1,2,3};
    Point &q = p;
    return q;
}
```
will compile just fine, but is meaningless to the point of dangerous.

Auto Declarations
===

Many languages allow you to declare variables without specifically saying what type they are. Somewhat late to the game, C++ added this feature in the 2011 specification. For example, if you have a function declared as follows, 
```c++
Point * create_point();
```
you can use auto to avoid clutter in your code:
```c++
auto p = create_point();
```

Namespaces
===

In C++ the notion of a namespace was introduced to avoid cluttering the global namespace with lots of function and type definitions. One of the main namespaces we will use is `std`, which is the namespace the standard library uses. For example, the C++ method `cout`, which is used for printing (instead of `printf`) is a method declared in the `std` namespace. To use it, you have to do use the `::` operator, which accesses the namespace.
```c++
#include <iostream>

// later ...
std::cout << "Hello world\n";
```

This may look just like added `std_` to the beginning of everything, but you can open a namespace to use its methods for the duration of a function, as in
```c++
void print_stuff() {
    using namespace std;
    cout << "First line\n";
    cout << "Second line\n";
}
```

Creating Namespaces
===

Put your library of functions and datatypes in a namespace. In this example, we avoid potential name collisions with "Point" and "mag" that may be defined some other way elsewhere.

```c++
namespace my_library {
    typedef struct {
        double x, y;
    } Point;
    int mag(Point &p) {
        return sqrt(p.x*p.x + p.y*p.y);
    }    
}
```

Then use the library

```c++
namespace {
    TEST(Examples, MyLibrary) {
        my_library::Point p = { x: 3, y: 4};
        ASSERT_NEAR(my_library::mag(p), 5, 0.00001);
    }
    TEST(Examples, Using) {
        using namespace my_library;
        Point p = { x: 3, y: 4};
        ASSERT_NEAR(mag(p), 5, 0.00001);
    }       
}
```

cout
===
By the way, `cout` is an *output stream* that sends a stream of charaters to the terminal (other streams can do to files, for example). The `<<` operator allows you to join a number of objects together to make a strea. For example,
```c++
std::cout << "The value of x is " << x << "\n";
```
Think of `<<` like a function that converts what comes after it to a string. Thus `<<(x)` should be a string representation of whatever `x` is. the `<iostream>` library defines `<<` for all the standard types, like `int` and `double`. 

If you create a new type, however, you have to define `<<` for it. 

Later in README we will show how to define `<<` for our array ADT.

Throwing Exceptions
===

One of the big difficulties in C is what to do when some exception occurs at run time. Usually, developers handle this by either returning a special value, such as NULL or -1, from a function in which an error occurred, or by setting up an error data structure inside an ADT to keep track of errors (like we did with the rpn calculator).

In C++, however, you can define exception handlers explicitly, as well as either choose to ignore exceptions (so they are passed to the function that calls you function), or handle them explicitly. Here is an example of how to throw an exception

```c++
#include <stdexcept>

double invert(int x, int y) {
    if ( x == 0 ) {
        throw std::invalid_argument("First argument cannot be zero");
    } else {
        return y/x;
    }
}
```

Catching (and Testing) Exceptions
===

This code throws an exception in some cases. The particular exception it throws has a type `std::invalid_argument`, which is an ADT defined in the `<stdexcept>` library. There are several other exceptions in the library as well, which you can read about [here](http://www.cplusplus.com/reference/stdexcept/). We will discuss defining new types of exceptions later in the class. To catch this exception, you would do something like:
```c++
try {
    invert(0,1);
    ASSERT_EQ(true,false);
} catch (std::invalid_argument e ) {
    ASSERT_STREQ(e.what(), "First argument cannot be zero");
}
```

Failing to Catch Exceptions
===

Note that if you do not catch an exception in a given function, it is passed up to the function that called it, all the way up to the operating system. For example, suppose you had another function
```c++
void show(x,y) {
    std::cout << invert(x,y) << "\n";
}
```
If whatever function calls `show` sends in a zero for the first argument, then `invert` will throw an exception. Since this exception is not handled in `show` it will be passed up the chain to whatever called show. Thus, you can do:
```c++
try {
    show(0,1);
} catch (std::invalid_argument e ) {
   // do something here
}
```
And if you do not look for any exceptions, you will end up with a runtime error.

Conveniently, Google Test will catch all exceptions and the tests that produced them as failures, print out the exception's `what` method, and proceed without crashing the whole program. To use them, just do



Standard Exceptions
===

The `<exception>` library defines some standard excptions you can use in your code.

```c++
throw std::invalid_argument("First argument cannot be zero");
```

to throw. All these exceptions define a `what()` method, which you can use when catching.

```c++
catch (std::invalid_argument e ) {
    std::cout << e.what() << "\n";
}
```

**Available Exceptions:**

<pre>
logic_error                    invalid_argument              domain_error, 
length_error                   out_of_range                  future_error(C++11)
bad_optional_access(C++17)     runtime_error                 range_error
overflow_error                 underflow_error               regex_error(C++11)
system_error(C++11)            ios_base::failure(C++11)      filesystem::filesystem_error(C++17), 
tx_exception(TM TS)            nonexistent_local_time(C++20) ambiguous_local_time(C++20), 
format_error(C++20)            bad_typeid                    bad_cast
bad_any_cast(C++17)            bad_weak_ptr(C++11)           bad_function_call(C++11)
bad_alloc                      bad_array_new_length(C++11)   bad_exception
ios_base::failure(until C++11) bad_variant_access(C++17).
</pre>

**Note:** You can also define your own exception class (more on this later in the course).

Memory Allocation in C++
===

Memory allocation in C++ is handled by the language, and not by a library of methods as with `malloc`. Two operators, `new` and `delete` handle everything. For example:
```c++
int * x = new int;
double * p = new double[10];

// later ...
delete x;
delete[] p;
```
Note that unlike `malloc`, `new` returns a pointer to a specific type of object. 

In the first case an `int` and in the second case an array of `doubles`.

You do not need to cast anything. No `void *` pointers!

The benefit is that C++ will do some type checking for you and report compile time errors that C could not. Also note that when you delete an object, you have to use the corresponding form. 

To delete a single object, use `delete` and to delete an array, use `delete[]`. 

Classes and Objects
===

C++ solves the problem of having objects own their methods with classes. A `class` is a description of an abstract data type's data structures and methods all within one `struct`-like entity. As an example of a class, we can write the array class we have been working on as follows:

```c++
class DoubleArray {

public:

    // Constructors
    DoubleArray();
    DoubleArray(double a, double b, double step);     // replaces the _range method
    DoubleArray(const DoubleArray& other);            // replaces the _copy method

    // Assignment operator
    DoubleArray& operator=(const DoubleArray& other); // new! lets you do array2 = array1;

    // Destructor
    ~DoubleArray();                        // Replaces destroy, deleting the buffer
                                           // and also deletes the array object itself.

    // Getters
    double get(int index) const;           // Notice all our methods now do not
    int size() const;                      // take a pointer to the array as the
                                           // first object. The object is implicit.
                                           // The trailing "const" in some methods says
                                           // the object will not be changed by the 
                                           // method.
    // Setters
    void set(int index, double value);

private:

    int capacity,                          // Our data goes here. It is private, meaning
        origin,                            // the user cannot access it. 
        end;

    double * buffer;

    const int INITIAL_CAPACITY = 10;       // Instead of a global #define, we use an class
                                           // defined constant, that is only available within
                                           // the class

    int index_to_offset(int index) const;  // No more static methods! These will be available
    int offset_to_index(int offset) const; // to the class, but not the user.
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);

};
```
The above essentially defines the interface to our new class. It says what methods are available and what arguments they take. It also defines some private data that only the class methods will have access to. 

Using Classes to Make Objects
===

To use the `DoubleArray` class, we would do something like:
```c++
TEST(DoubleArray, Construction) {
    DoubleArray a,             // use the default constructor
                b(0,1,0.1);    // use the range constructor
    a.set(4, 1);               // use the dot operator to access the `set` method
    ASSERT_EQ(b.get(2), 0.2);  // use the dot operator to access the `get` method
}
```
Notice that we do not have to explicitly delete `a` and `b` when we are done with them. This is because when they go out of scope, C++ will automatically call the method `~DoubleArray`, which is specially named with the `~` to let C++ know to call it whenever it needs to delete a `DoubleArray`. 

Allcating new Objects
===

On the other hand, we still need to use `delete` if we happened to use `new` to allocate a `DoubleArray`. For example,
```c++
auto a = new DoubleArray();
auto b = new DooubleArray(0,1,0.25);

// later ...
delete a, b;
```

Note that when declaring pointers to objects, you can write
```c++
auto c = new DoubleArray; // Compiles, but does not call the constructor! Bad!
```
in which case you get an object of type `DoubleArray` for which the constructor has not been called. Since in our case, the constructor allocated memory, the result of the above code is a `DoubleArray` in which the buffer is uninitialized. Which is bad!

Constructors
===

The constructor in a class is responsible for
- initializing variables
- allocating memory (if needed)
If the objects constructed do not need memory allocation, then C++ provides a default constructor, so you do not need to define one. For example, if you defined class as
```c++
class Complex {
    private:
      double re, im;
};
```
then you can simple make a new Imaginary number with
```c++
Complex x;
```

Multiple Constructors
===

You can add constructors that do different initializations. For example, the code
```c++
class Complex {
    public:
      Complex(double a, double b) : re(a), im(b) {};
      Complex(double a) : re(a), im(0) {};
    private:
      double re, im;
};
```
defines two new constructors. They the C++ initialization syntax to initialize the `re` and `im` fields. The first is equivalent to
```c++
Complex(double a, double b) {
    re = a;
    im = b;
}
```
so there is nothing magical about the syntax. Notice that the two constructors have the same name. C++ can tell the difference between them by what arguments are passed. In fact, there is a third constructor, the default constructor, which takes no arguments (as before). Thus, you can write:
```c++
  Complex w, x(), y(1,2), z(3);
```
and C++ will know which constructor to use. 

Memory Allocation in Constructors
===

If memory needs to be allocated, you must at least override the default constructor (the one that takes no arguments). In the `DoubleArray` class we defined the constructor:
```c++
DoubleArray();
```
which we implement in `dynamic_array.cc` with
```c++
DoubleArray::DoubleArray() {                     // Note the namespace :: operator
    buffer = new double[INITIAL_CAPACITY]();     // We use new instead of calloc
    capacity = INITIAL_CAPACITY;                 // Note that we can refer to member variables
    origin = capacity / 2;                       // like buffer, capacity, origin, and end
    end = origin;                                // implicitly. C++ knows what we mean.
}
```
Note that the contructor does not explictly return a value. In fact, it is called after an object is created either in a variable declaration or when using `new`.

A Range Constructor
===

The other constructors can build on this code, without having to do everything again, by using the initialization syntax to initialize the object being constructed using the default constructor (the one with no arguments), and then adding more to the object in the body of the function.
```c++
DoubleArray::DoubleArray(double a, double b, double step) : DoubleArray() {
    int i = 0;
    for ( double x=a; x<=b; x += step ) {
        set(i, x);
        i+=1;
    }
}
```

Operator Overloading
===

To declare a binary operator, such as `==`, we do:
```c++
bool operator==(const DoubleArray& a, const DoubleArray& b) {
    if ( a.size() != b.size() ) {
        return false;
    }
    for(int i=0; i<a.size(); i++) {
        if ( a.get(i) != b.get(i) ) {
            return false;
        }
    }
    return true;
}

bool operator!=(const DoubleArray& a, const DoubleArray& b) {
    return !(a==b);
}
```

You can now use ASSERT_EQ with arrays.

```c++
TEST(DoubleArray, Equality) {
    DoubleArray a(0,1,0.1), b(0,1,0.1), c(1,2,0.1);
    ASSERT_EQ(a, b);
    ASSERT_NE(a,c);                
}  
```

For more details, see [here](https://en.cppreference.com/w/cpp/language/operators).

Assignment
===

To support syntax like the following
```c++
  DoubleArray x(0,1,0.1), y;
  y = x;
```
C++ needs to know what it means to assign one `DoubleArray` to have the value of another. What we want `=` to mean is
- delete the buffer in y
- allocate a new buffer in y
- copy the contents of the buffer in x to the buffer in y
- initialize origin, end, etc.

Overloading "=", a.k.a. the Assignment Operator
===

```c++
DoubleArray& DoubleArray::operator=(const DoubleArray& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new double[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.get(i));
        }
    }
    return *this;
}
```
Think of this code as defining a method called `=` that would be called with `set y to be =(x)` (psuedocode). 
This method uses the keyword `this`, which refers to the object being operated on. In our C array class, we passed a pointer (usually called `da`) to the object as the first argument to every function. In C++ the pointer is implicit, but can be access if needed with `this`. In the above code, `this` refers to the assignee (the left hand side of `y=x`) and `other` refers to the object being copied. Thus, the first line checks that these two are not the same (if they are, there is nothing to do -- although you could leave this out and truely make a copy).

Also note that the method accesses the private members of `other`, which is okay because this is a class method. 

Returning Referenes
===

Finally, notice that the method returns a reference to the result of the copy. This is actually not needed to assign the left hand side (that's done in the body of the method), but is needed because an expression like `y=x` itself has a value, which should be a reference to `y`. This is so you can do things like
```c++
y = x = z;
```
which is equivalent to 
```c++
y = (x = z);
```
Returning a reference to `*this` is called *method chaining*.

The Copy Constructor
===

Using the assignment operator, we can define another constructor, called the copy constructor, as follows:
```c++
DoubleArray::DoubleArray(const DoubleArray& other) : DoubleArray() {
    *this = other;
}
```
It is quite common for these two methods to be intertwined thusly.

This would be used as in
```c++
DoubleArray x;
x.set(0,3.14); // etc
DoubleArray y(x); // sets y to be a copy of x.
```

The Destructor
===

The destructor is responsible for deallocating memory. 

If none of your constructors allocate memory, then *you do not need a destructor*. 

However, if any constructors do allocate memory, then you have to have one. For ``DoubleArray` we just write
```c++
DoubleArray::~DoubleArray() {
    delete[] buffer;
}
```
Now, whenever a `DoubleArray` goes out of scope, its destructor is called. It is also called whenever `delete` is called on a `DoubleArray` made with `new`. 

Getters and Setters
===

The getters are straightforward. Notice that we can throw an exception instead of a runtime error when exceptions occur.
```c++
double DoubleArray::get(int index) const {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    if ( index >= size() ) {
        return 0;
    } else {
        return buffer[index_to_offset(index)];
    }
}

void DoubleArray::set(int index, double value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value;
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}
```

Templates
===

The `DoubleArray` class has the same issues as our C `DynamicArray` ADT did: it only contains doubles. However, C++ provides a powerful way to make new objects that refer to arbitrary types. The approach uses `templates`.

Here is an example of function definition that uses a template to compare two objects:

```c++
template<typename T>
int compare(const T& x, const T& y) {
    if ( x < y ) {
        return -1;
    } else if ( y < x ) {
        return 1;
    } else {
        return 0;
    }
}
```
As long as `<` is defined for the the type `T`, then this template can be used. For example, 
```c++
int c = compare(1.0, 2.0)
```
works. 

Comparisons for Defined Classes
===

```c++
Complex x(1,2), y(3,4);
int c = compare(x,y);
```
will give the error:
```bash
error: no match for 'operator<' (operand types are 'const {anonymous}::Complex' and 'const {anonymous}::Complex')
```

However, if you defined `<` for complex numbers as follows:
```c++
bool operator<(const Complex& a, const Complex& b) {
    return a.magnitude() < b.magnitude();
} 
```
Then `compare` will work just fine.

Templates for the Array Class
===

To apply templates to our array class, we have to replace references to `double` with a type name:
```c++
template <typename ElementType>                      // ElementType is the type variable
class TypedArray {

public:

    TypedArray();
    TypedArray(const TypedArray& other);             

    // Copy constructor
    TypedArray& operator=(const TypedArray& other);

    // Destructor
    ~TypedArray();

    // Getters
    ElementType &get(int index);
    ElementType &safe_get(int index) const;         // This is new. See below.
    int size() const;

    // Setters
    void set(int index, ElementType value);

private:

    int capacity,
        origin,
        end;

    ElementType * buffer;   

    const int INITIAL_CAPACITY = 10;

    int index_to_offset(int index) const;
    int offset_to_index(int offset) const;
    bool out_of_buffer(int offset) const;
    void extend_buffer(void);    

};
```

Using Templated Classes
===

With this definition of array, we can make arrays of anything. 
```c++
TypedArray<Point> b;
b.set(0, Point(1,2,3));
b.set(1, Point(2,3,4));
b.set(20, Point(3,4,5));
double r = b.get(20).x;
```
Or, for an even nicer example, using arrays of arrays of doubles, we can make a matrix:
```c++
TypedArray<TypedArray<double>> m;

for (int i=0; i<30; i++) {
    for (int j=0; j<30; j++) {
        m.get(i).set(j,0.5*i*j);
    }
}
```

Where to put Template Methods
===

<span style="background: yellow; padding: 10px">Template methods need to appear in header files.</span>

This is because the compiler can only compile things like `TypedArray<int>` and not arbitrary typed arrays. Thus, any file that uses a templated class needs to include all the templated methods, and not just the class definition, because compiling it will require instantiating the template on the specific types used in the file.

See `week_4/typed_array/typed_array.h`. 

Note that there is no `typed_array.c` file!

Memory Allocation with Arbitrary Types
===
The main difference between `DoubleArray` and `TypedArray` has to do with the buffer. For example, in the constructor, we can still use `new`, but we also have to make sure to call the constructor for whatever class `ElementType` stands for, which we do with with the parentheses at the end of the statement.
```c++
template <typename ElementType>
TypedArray<ElementType>::TypedArray() {
    buffer = new ElementType[INITIAL_CAPACITY](); // Note: Calls ElementType constructor
    capacity = INITIAL_CAPACITY;    
    origin = capacity / 2;
    end = origin;    
}
```
The same line shows up in the assignment operator, and a similar line shows up in the private method `extend_buffer`. 

Setting calls the copy constructor (if there is one)
===

With DoubleArray, setting a location in the array to a value copies the value, because that's how assignment works for `double`. 

But with arbitrary element types, assignment calls the copy constructor. 

```c++
template <typename ElementType>
void TypedArray<ElementType>::set(int index, ElementType value) {
    if (index < 0) {
        throw std::range_error("Negative index in array");
    }
    while ( out_of_buffer(index_to_offset(index) ) ) {
        extend_buffer();
    }
    buffer[index_to_offset(index)] = value; // Should call the copy 
                                            // constructor of ElementType.
    if ( index >= size() ) {
        end = index_to_offset(index+1);
    }
}
```

We can check for the right behavior in a test.

```c++
TEST(TypedArray,CopyElementsInSet2) {
    TypedArray<TypedArray<double>> m;
    TypedArray<double> x;
    x.set(0,0);
    m.set(0,x);
    x.set(0,-1);
    EXPECT_DOUBLE_EQ(m.get(0).get(0),0.0); // If set didn't make a copy
                                            // then we would expect m[0][0]
                                            // to be x[0], which we changed 
                                            // to -1.
}
```

Default Values
===

Another issue is this: In the `DoubleArray` class, we used zero as the default value when the user asked for an element outside the size of the array. To do that here, we need a "zero" for any object.

One idea is to use the default constructor of the supplied type to create a new element to return in such cases, and also to extend pad array with default values all the way up to the newly accessed index:
```c++
template <typename ElementType>
ElementType &TypedArray<ElementType>::get(int index) {
    if (index < 0) {
        throw std::range_error("Out of range index in array");
    }
    if ( index >= size() ) {
                          // User is access beyond the end of the array,
                          // so return the default value.
        ElementType x;    // A temporary value to use with set.
        set(index, x);    // `set` will create a copy of the default values.
    } 
    return buffer[index_to_offset(index)];
}
```

Get Returns a Reference
===

For the line
```c++
m.get(i).set(j,0.5*i*j);
```
to work, the call to `get` cannot copy the array at index `i` in `m`, because then we would be changing a copy of the array when we called `set` after that. Thus, `get` should return a reference. Also, note that because `get` might actually change the array, the array iteself is not guaranteed to be the same after the get.

However, we may have other methods that expect getting an element at a particular index to leave the array unchanged, for example, when copying the array. Thus, we add a new method called `safe_get`:
```c++
template <typename ElementType>
ElementType &TypedArray<ElementType>::safe_get(int index) const {
    if (index < 0 || index >= size() ) {
        throw std::range_error("Out of range index in array");
    }
    return buffer[index_to_offset(index)];
}
```
Note the extra `const` at the end of the declaration. A `const` in that position refers to `this`, that is, the object that owns the method. Since the object itself is not an argument (it is only so implicitly), C++ uses this syntax to require the method to not change the underlying array data. This is required when copying an array using the assignment operator, because the argument `other` is specified to be a const.

Using safe_get
===

An example where `safe_get` is needed is in the assignment operator. 

```c++
template <typename ElementType>
TypedArray<ElementType>& TypedArray<ElementType>::operator=(const TypedArray<ElementType>& other) {
    if ( this != &other) {
        delete[] buffer; // don't forget this or you'll get a memory leak!
        buffer = new ElementType[other.capacity]();
        capacity = other.capacity;
        origin = other.origin;
        end = origin;
        for ( int i=0; i<other.size(); i++) {
            set(i,other.safe_get(i));
        }
    }
    return *this;
}
```
In the above method, if we replace `safe_get` with just `get` we get the (extremely helpful) compile time error:
```bash
error: passing 'const TypedArray<double>' as 'this' argument of 
'ElementType& TypedArray<ElementType>::get(int) [with ElementType = double]' 
discards qualifiers [-fpermissive]
```
The term "discards qualifiers" refers to the `const` after the method declaration. The last bit is a suggestion that you compile with the `g++` flag `-fpermissive` which will let you let away with such things. However, that is a bad idea. Instead, you should try to understand what is happening and come up with a solution like we did with `safe_get`. 

Interfacing with Streams
===
To print arrays, we can overload the `<<` operator:
```c++
template <typename ElementType>
std::ostream &operator<<(std::ostream &os, TypedArray<ElementType> &array)
{
    os << '[';
    for (int i=0; i<array.size(); i++ ) {
        os << array.get(i);
        if ( i < array.size() - 1 ) {
            os << ",";
        }
    }
    os << ']';
    return os;
}
```
This method is not declared inside the class definition, since it is not owned by `TypedArray`. In any case, now we can write:
```c++
TypedArray<TypedArray<double>> m;

for (int i=0; i<3; i++) {
    for (int j=0; j<3; j++) {
        m.get(i).set(j,0.5*i*j);
    }
}

std::cout << m << "\n"; 
```
which yields
```bash
[[0,0,0],[0,0.5,1],[0,1,2]]
```
The `<<` operator is called nine times. Three times with `TypedArra<double>` arguments, and for each of those times, three more times for `double` arguments. Since the `iostream` library defines `<<` for doubles, we do not need to do that. If we had an array of array of Imaginary numbers, for example, we would need to define `<<` for them as well.

Summary
===

This week, we learned to take an abstract data type written in C and rewrite it in C++. We learned to use the C++ notions of references, namespaces, exception handlers, overloading functions and operators, classes, constructors, destructors, and templates. 

C++ has many other additions beyond what we have covered here. For example, a class can inherit all the methods of another class, but also add more methods. Classes can have "friends". You can overload all the operators. There is also an extensive "standard template library" which we will introduce next week. We will touch on a few other aspects of C++, in future lectures, but the subset of C++ we have defined here is fairly complete. 

It is important to understand that C++ is a huge, messy language with many ways to do the same thing. Some very bad programs have been written in C++ (and in pretty much ever other language). This document is meant to introduce C++ but also to introduce conventions. For example, every class you write that does memory allocation should have a default constructor, a copy constructor, an assignment operator, and a destructor. As you delve deeper into C++, study good code examples and try to use their conventions. Although it is easy to make up a new one, doing so will confuse your collaborators and possibly even you.

A good book on C++ is the "C++ Primer" by Stanley Lippman. Consider reading as much of this book as you can, especially if you expect to be writing C++ programs for your job. There is a lot more covered there than is covered in that class.

Exercises (due Friday Sunday Feb 10)
===

1. Add methods `push`, `pop`, `push_front`, and `pop_front` to the `TypedArray` class. Write your tests first. Make sure that the arguments to these functions are declared as `const`. The pop methods should throw `std::range_error` with the message "Cannot pop from an empty array".
1. Add a method

    ```c++
    TypedArray concat(const TypedArray& other);
    ```
    to the `TypedArray` class. It should return a new array that is a concatenation of the given and the argument (leaving both untouched). You should be able to do:
    ```c++
    TypedArray<int> a;
    a.set(0,0);
    a.set(1,1);
    TypedArray<int> b = a.concat(a).concat(a); // yields a new array [0,1,0,1,0,1]
                                               // Should leave a untouched.
    ```
    for example. 
1. Define a `TypedArray` method called `reverse` that reverses the array. It should change the array it is called on and return a reference to the array itself (i.e. return `*this`).
1. Define the '+' operator for the `TypedArray` class to mean concatenation. You should be able to replace the fourth line above with

    ```c++
    TypedArray<int> b = a + a + a; // yields [0,1,0,1,0,1]
    ```
1. Finish the Complex Class. You should include the following methods.
    - `double re();` -- returns the real part of the number. The actual datum storing the real part should be private.
    - `double im();` -- returns the imaginary part of the number. The actual datum storing the imaginary part should be private.
    - `Complex conjugate()` -- returns the complex conjugate of the number.
In addition, you should overload `*`, `+`, and `==` operators for your class. Note that overloading the `==` operator will make your class work with Google Test's `ASSERT_EQ` method. Don't forget to write tests first. Also, ask yourself why we don't need to overload the assigment operation `=` and why we do *not* need a destructor for this class. Finally, a hint: You should declare the overloaded binary operators in your `.h` file and implement them in your `.cc` file to avoid linker errors when compiling.

**Code Organization:**: Your `hw_4` directory should look like
```bash
  complex.h
  complex.cc
  main.cc
  Makefile
  typed_array.h
  unit_tests.cc
```
Use `unit_tests.h` for all of your tests (we'll replace it with ours later). 