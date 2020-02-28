Software Engineering For Embedded Applications
===

Week 8: Mobile Robot Control
---

Last week we learned:
- Events and event handlers (`emit` and `watch`)
- Finite state machines
- JSON

This week, we apply our skills to building robot control systems using a new multi-robot simulation environment, called ENVIRO, build on top of ELMA.

Introducing ENVIRO
===

ENVIRO is a multi robot simulation environment with the following features:
- Robot behaviors are defined with C++ *plugins* containing ELMA processes
- Robots can be controlled with simple methods, like `track_velocity` or `apply_force`
- Robot can use range sensors to sense the environment
- Inanimate objects and static objects (like walls) can be added to the environment
- JSON configuration files are used to define the environment

New Concepts
===

- Robot Motion Control
- Shared Object Libraries
- Multiple Inheritance
- Client/Server Architectures

Docker Container with Enviro
===

To start a Docker container with ENVIRO pre-loaded into it, do:

```bash
docker run -p80:80 -p8765:8765 -v $PWD:/source -it klavins/enviro:alpha bash
esm start
```

The above commands do the following:

- The `-p80:80 option maps *port* 80 from the Docker container to ports on your host computer. This should allow you to go to 
    > http://localhost
    with your web browser and see the ENVIRO client. It should say "Error: Failed to fetch. Is the server running?" at this point. 

- The `-p8765:8765` option allows the ENVIRO client to communicate with the `enviro` server (not yet running) via a *WebSocket*.

- The command `esm start` uses the <u>e</u>nviro <u>s</u>etup <u>m</u>anager to start a web server from which your browser can access the ENVRIO client. 

Creating a Project
===

To create a new project, use `esm` as follows:

```bash
mkdir my_project
cd my_project
esm init
```

This will create the following directories and files
```
Makefile
config.json
defs/
    README.md
lib/
    README.md
src/
    Makefile
```

Make the project and start the enviro sever as follows.
```bash
make
enviro
```

Then navigate to `http://localhost` you should see a rectangular walled area. 

You can press `Ctrl-C` to stop the enviro server. 

Adding a Robot
===

To add a robot to your project, you have to create some new files and edit the `config.json` file. First, do
```bash
esm generate MyRobot
```

This will create the files
```
defs/
  my_robot.json         // Defines the shape, mass, and other parameters of the robot
src/ 
  my_robot.h            // Contains classes inheriting from elma::Process that define the behavior
  my_robot.cc           // Contains the implementation of the classes in my_robot.h
```

To compile the robot code, do
```
make
```

This will make the file `lib/my_robot.so`, which is a **shared object file** containing the compiled code for your robot.

Using the Robot
===

To place the robot into the simulation, change the `agents` entry in `config.json` to
```json
"agents": [    
    {
        "definition": "defs/my_robot.json",
        "style": { "fill": "lightgreen", "stroke": "black" },
        "position": {
            "x": 0, 
            "y": 0, 
            "theta": 0
        }
    }        
]
```
Now you should be able to run
```bash
enviro
```
and see a green square in the environment. That's your robot!

Press `Ctrl-C` to stop enviro.

Change the Look of Your Robot
===

Edit the file `defs/my_robot.json` to change what the robot looks like. For example, we can give it a gripper. 

```json
{
    "name": "MyRobot",
    "type": "dynamic",
    "description": "A Robot with a (static) gripper",
    "shape": [
        { "x": -10, "y": 10 },
        { "x": 10, "y": 10 },
        { "x": 10, "y": 2 },
        { "x": 12, "y": 2 },
        { "x": 12, "y": 6 },
        { "x": 16, "y": 6 },
        { "x": 16, "y": 4 },
        { "x": 14, "y": 4 },
        { "x": 14, "y": -4},
        { "x": 16, "y": -4 },
        { "x": 16, "y": -6 },
        { "x": 12, "y": -6 },
        { "x": 12, "y": -2 },
        { "x": 10, "y": -2 },
        { "x": 10, "y": -10 },
        { "x": -10, "y": -10 },
        { "x": -9, "y": 0 }
    ],
    "friction": {
      "collision": 5,
      "linear": 40,
      "rotational": 600
    },
    "sensors": [],
    "mass": 1,    
    "controller": "lib/my_robot.so"
}
```

Start `enviro` to reload the simulation. 

Press `Ctrl-C` to stop the simulation.

Make the Robot Move
===

Edit the file `src/my_robot.h` and change the `update` method in the `MyRobotController` class to
```c++
void update() {
    track_velocity(10,0.15);
}
```

The `track_velocity(v,omega)` method attempts to make the robot move at `v` units per second in the direction it is pointing while rotating at `omega` radians per second. It is implemented as a proortional controller, where the force and torque applied to the robot are

> -K<sub>L</sub> ( v<sub>actual</sub> - v )

> -K<sub>R</sub> ( w<sub>actual</sub> - w )

Since the actual speed and angular velocity are changing over time, we have to run this command in the `update` function of the robot controller so that it can continuously adjust the force and toque applied to the robot. 

Rebuild the project and run:
```bash
make
enviro
```

You should see your robot moving around in circles.

Press `Ctrl-C` to stop the simulation.

Add More Robots
===

Edit `config.json` and add several more MyRobot entries to the `agents` list. Do this by copying the one that's there, but make sure to change the initial positions (and possibly angles) so that the robots are not initialized to be all on top of each other. For example, try putting four robots in the locations (100,0), (-100, 0), (0, 100), and (0,-100). 

Rebuild the project and run:
```bash
make
enviro
```

You should see more robots.

Press `Ctrl-C` to stop the simulation.

Add Some Blocks
===

First, create a new agent type
```bash
esm generate Block
```

Then add some blocks to the `agents` list in `config.json`. These should look something like
```json
{
    "definition": "defs/block.json",
    "style": { "fill": "orange", "stroke": "black" },
    "position": {
        "x": 50, 
        "y": 0, 
        "theta": 0
    }
}      
```

By default, new agents will have no friction with the environment, so they will move around as though on ice. To damp this movement with the friction parameters in `defs/block.json`, change the `update` method in `src/block.h` to
```c++
void update() {
    damp_movement();
}
```

Rebuild the project and run:
```bash
make
enviro
```

You should see some orange blocks being pushed around by the robots.

Press `Ctrl-C` to stop the simulation.

In Class Work
===

Now you try the above steps.

Enviro Architecture
===

Enviro is built on top of Elma. You define processes and state machines just like you would with elma, but also add some interfacing to the enviro simulator.

<img src='https://raw.githubusercontent.com/klavins/EEP520-W20/master/week_8/images/enviro-architecture.png' width=80%>

Shared Object Libraries
===

The issue: The ENVIRO code is a few thousand lines long. We don't want to have to recompile it every time we add a new agent type. Somehow we need to compile agent code into object code and then link it **dynamically** into ENVIRO. 

To do this, we compile each `src/my_robot.cc` file into a `lib/my_robot.so` file -- a shared object file. In a shared object file, the addresses of all data and functions are stored relative to some starting point. When a running executable dynamically links a shared object file, it resolves those relative addresses into actual addresses. 

The Makefile comples shared object files using g++ as in
```bash
g++ -std=c++17 -Wno-psabi -ggdb  -shared -fPIC -I /usr/local/src/enviro/server/include -I /usr/local/src/Chipmunk2D/include/chipmunk  my_robot.cc -o ../lib/my_robot.so
```
Note the `-shared` flag. 

Linking a Shared Object Library
===

When Enviro runs, it loads the shared object files stated in `defs/my_robot.json` using the `dlopen` function. 
```c++
Agent * Agent::create_from_specification(json spec, World& world) {
    auto file = spec["definition"]["controller"].get<std::string>();
    auto handle = dlopen(file.c_str() , RTLD_LAZY);
    if (!handle) {
        std::cerr << "Error: " << file << "\n";
        throw std::runtime_error(dlerror());
    }
    auto create_agent = AGENT_CREATE_TYPE dlsym(handle, "create_agent");
    auto agent_ptr = (Agent*) create_agent(spec, world); 
    agent_ptr->set_destroyer(AGENT_DESTROY_TYPE dlsym(handle, "destroy_agent"));
    return agent_ptr;
}
```
It then looks for methods called `create_agent` and `destroy_agent` in the loaded library. These are defined in your `my_robot.h` file via the line
```c++
DECLARE_INTERFACE(MyRobot)
```
which is a macro that defines those functions for your agent:
```c++
#define DECLARE_INTERFACE(__CLASS_NAME__)                                         \
extern "C" __CLASS_NAME__* create_agent(json spec, enviro::World& world) {        \
    return new __CLASS_NAME__(spec, world);                                       \
}                                                                                 \
extern "C" void destroy_agent( __CLASS_NAME__* object ) {                         \
    delete object;                                                                \
}
```
Fortunately, you don't have to worry to much about all of this, as it is all handled for you.

The Agent Class
===

In `src/my_robot.h`, the `MyRobot` class is defined as follows:

```c++
class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
    }
    private:
    MyRobotController c;
};
```
Behind the scenes, classes that inherit from `Agent` will set up the physics of the agent, and coordiate various other activites with the manager. 

This class is also a container for processes. You could add more if you would like, so that it looks like:
```c++
class MyRobot : public Agent {
    public:
    MyRobot(json spec, World& world) : Agent(spec, world) {
        add_process(c);
        add_process(p);
    }
    private:
    MyRobotController c;
    MyOtherProces p;
};
```

Agent Processes
===

The `MyRobotController` class is defined as follows:
```c++
class MyRobotController : public Process, public AgentInterface {
    public:
    MyRobotController() : Process(), AgentInterface() {}
    void init() {}
    void start() {}
    void update() {
        track_velocity(10,0.15);
    }
    void stop() {}
};
```
Note that it inherits from `Process`, so everything you know about Elma processes applies. 

It also inherits from `AgentInterface`, which provides methods like `track_velocity`. Inheriting from two different classes is called ***multiple inheritance***. 

Multiple Inheritance
===

Here is a simple example of multiple inheritance:
```c++
#include <iostream>

class A {
    public:
    int f(int x) { return x+1; }
};

class B {
    public:
    int g(int x) { return 2*x; }
};

class C : public A, public B {
    public:
    int h(int x) { return x/2; }
};

int main(void) {

    C c;

    std::cout << c.f(1) << ","
              << c.g(1) << ","
              << c.h(1) << "\n";

}
```

Thus, 
```c++
class MyRobotController : public Process, public AgentInterface { 
    ...
}
```
allows `MyRobotController` objects to access methods in both the `Process` class and the `AgentInterface` class.

The Agent Interface
===

The `AgentInterface` class allows classes that derive from it to use the following methods:
```c++
// State
cpVect position();
cpVect velocity();
cpFloat angle();
cpFloat angular_velocity();

// Id
int id();

// Actuators
void apply_force(double thrust, double torque);
void track_velocity(double linear_velocity, double angular_velocity, 
                    double kL=10, double kR=200);
void damp_movement();  
void move_toward(double x, double y, double vF=10, double vR=200);
void teleport(double x, double y, double theta);

// Sensors
double sensor_value(int index);
std::vector<double> sensor_values();
```
For these methods to be available to a `Process/AgentInterface` object `c`, you **must** call
```c++
add_process(c)
```
from within the `Agent` constructor. 

For example, try replacing `track_velocity` with something like `move_toward(0,0)` in the `MyRobot` class. 

Client Events
===

When you click on something in the ENVIRO client, an event is sent back to ENVIRO server. These events are one of the following:

- ***screen_click*** events with values of the form

    ```json
    {
        "x": 123,
        "y": 234
    }
    ```
    where the x,y values are the position in the client where the mouse was clicked.

- ***agent_click*** events with values of the form

    ```json
    {
        "x": 12,
        "y": 23,
        "id": 3
    }
    ```
    In this case, the x,y position is the position on the agent where the mouse was clicked, and the `id` is an integer identifying the agent.

Using Click Events
===
Here is an example of how to use the click events. First, make a new project

```bash
cd ..        
mkdir chaser
cd chaser
esm init
esm generate Chaser
esm generate Target
```

Change `defs/chaser.json` so that it uses the `MyRobot` shape from the previous example.

Add a chaser and a target to `config.json`. 

Test with `enviro` to see if you get a robot and a block.

Watch for Click Events
===

In `src/target.h`, you can make the target watch and respond to click events as follows:
```c++
class TargetController : public Process, public AgentInterface {

    public:
    TargetController() : Process(), AgentInterface() {}

    void init() {
        watch("screen_click", [this](Event e) {
            teleport(e.value()["x"], e.value()["y"], 0);
            emit(Event("goal_change", { 
                { "x", e.value()["x"] }, 
                { "y", e.value()["y"] } 
            }));
        });
    }

    void start() {}
    void update(){
        damp_movement();
    }
    void stop() {}

};
```
When the user clicks on the screen, the `Target` agent moves to that location, and emits a `goal_change` event, which we will respond to in a minute.

Compile this code and test to see the target move.

Chase the Target
===

To get the robot to move, change the `ChaserController` to 
```c++
class ChaserController : public Process, public AgentInterface {

    public:
    ChaserController() : Process(), AgentInterface() {}

    void init() {
        goal_x = 0;
        goal_y = 0;
        watch("goal_change", [this](Event e) {
            goal_x = e.value()["x"];
            goal_y = e.value()["y"];
        });
    }
    void start() {}
    void update() {
        move_toward(goal_x, goal_y);
    }
    void stop() {}

    double goal_x, goal_y;

};
```

In Class Work
===

Try the above example.

State Machines
===

You can use finite state machines in ENVIRO code as well. As an example, let's build a robot controller that has two states

- MoveForward
- Rotate

and that switches between the two states and random times. 

First, we'll need a new project
```c++
cd ..
mkdir wanderer
cd wanderer
esm init
esm generate Wanderer
```

Changing the Controller to a State Machine
===

In the `WandererController` class, change the base class from `Process` to `StateMachine`:
```c++
class WandererController : public StateMachine, public AgentInterface {
  public:
  WandererController() : StateMachine() {
      ...
```

Switching at Random Times
===

To emit events that will eventually cause the state to change, we can override the `WandererController::update()` method with something like
```c++
void update() {
    if ( rand() % 100 <= 5 ) {
        emit(Event("tick"));
    }   
    StateMachine::update();
}
```
This condition in the `if` statement is true only about 5% of the time, so only occasiinally ticks. The last line in the update function ensures that the superclass, `StateMachine`, has a chance to run its `update` method as well.

The States
===

We then create states
```c++
    class MovingForward : public State, public AgentInterface {
        void entry(const Event& e) {}
        void during() {}
        void exit(const Event& e) {}
    };

    class Rotating : public State, public AgentInterface {
        void entry(const Event& e) {}
        void during() {}
        void exit(const Event& e) {}
    };
```
and add them to the state machine via instance variables.
```c++
    class WandererController : public StateMachine, public AgentInterface {
        // rest of code not shown
        MovingForward moving_forward;
        Rotating rotating;
    };
```

The Transitions
===

The initial state and transitions are added to the constructor:
```c++
WandererController() : StateMachine() {
    set_initial(moving_forward);
    add_transition("tick", moving_forward, rotating);
    add_transition("tick", rotating, moving_forward);
}
```

Adding Movement
===

In the `MovingForward` state, we move forward:
```c++
void during() { 
    track_velocity(10, 0); 
}
```
and in the `Rotating` state, we rotate
```c++
void during() {
    track_velocity(0,1);
}
```

Compiling and running this code should show a robot wandering around the arena. 

In Class Work
===

1) Make a wanderer. 

2) Make multiple wanderers. This is a little tricky because you need a separately named "tick" event for each robot (By default, sent to any process watching them, in any agent). 

Sensors
===

You can add a range sensor to a wanderer by modifyin `defs/wanderer.json`:
```json
"sensors": [
    { 
        "type": "range",
        "location": { "x": 16, "y": 0 },
        "direction": 0
    }
]
```

This will create a range sensor, like a laser range finder, sticking out of the front of the robot (angle 0). You can then access the value of the sensor using
```c++
double v = sensor_value(0);
```

Updating the Wanderers
===

The wandering robot gets stuck a lot. One way to fix this is to change the state functions to something like:
```c++
class MovingForward : public State, public AgentInterface {
    public:
    void entry(const Event& e) {}
    void during() { 
        track_velocity(4,0); // Go forward
        if ( sensor_value(0) < 40 ) {
            emit(Event("ping"));
        }            
    }
    void exit(const Event& e) {}
};

class Rotating : public State, public AgentInterface {
    public:
    void entry() {}
    void during() { 
        track_velocity(0,2); // Rotate
        if ( sensor_value(0) > 140 ) {
            emit(Event("ping"));
        }
    }
    void exit(const Event& e) {}      
};
```
In the `WandererController` constructor you would then have
```c++
add_transition("ping", moving_forward, rotating);
add_transition("ping", rotating, moving_forward);
```

Exercises
===

This week, you do not need to run tests. Just build a project that implements <u>one</u> of the following behaviors. We will clone your repo into a `klavins/enviro:alpha` image and run
```bash
esm start
enviro
```
to see to what extend you got the behavior to work. You are, of course, welcome to try more than one problem.

1. Using static elements, create a maze like environment. Put a robot at the start and have it explore until it finds the end of the maze. Use range sensors, wall following behaviors, and perhaps some kind of memory of where the robot has been.
1. Place a grid of about 20 blocks all over the arena. Create two robots each of which attemts to sweep the blocks to their respective sides of the field. You may want to change the shape of the robot from what we used in class so that it can better push blocks around.
1. Make a robot that moves around the arena in long, looping path. Call this robot the `Leader`. Create a `Follower` robot that uses a range finder to stay a respectful distance behind the leader. See if you can add more `Follower` robots to create a train of robots. 