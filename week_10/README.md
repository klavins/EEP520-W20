Projects
===

Week 10: Projects and Enviro 
---

Project Rubric
===

Goal: Be creative. Make a fun, engaging, and or informative simulation or game. 

Projects are due Wednesday March 18 at 11:59pm.

| Points | Description |
|-----|-----|
| 5   | Uses enviro, or extends enviro in some way.  |
| 5   | Code is well documented. Each method and class should have inline comments say what it does. See [here](https://github.com/klavinslab/elma) for an example.  |
| 5   | Project is shared with as a new Github Repository.  |
| 5   | Repo has a licence file (e.g. the [mit licence](https://opensource.org/licenses/MIT) |
| 5   | Repo has a README.md file |
| 10  | README has an overview of what the goal of the project is |
| 10  | README has a description of key challenges and how they were addressed |
| 10  | README describes how to install and run the code (assuming the user has docker installed) |
| 10  | README describes how to run and/or use the project |
| 5   | README acknowedges all sources of information or code used |
| 20  | Project compiles |
| 20  | Project runs without crashing. Occasional crashes will not result in partial deductions.  |
| 20  | Project shows a substantial behavior |
| 20  | Behavior is mostly bug free |
|----|----|
| Total | 150 |

Note: Homeworks 1-7 are each worth 1/9th of your grade. And the project is worth 2/9ths of the grade. 

Enviro Examples
===

Examples in the [enviro github repo](https://github.com/klavinslab/enviro): 

- ***avoiders***: Illustrates sensors, multiple copies of the same agent, decorations, and labels. 

- ***new_agent_test***: A simple demonstration of dynamically creating a new agent.

- ***platformer***: Turns off rotations and demonstrates how to simulate gravity, jumping, and left/right movement. Uses sensors, collision handlers, and keyboard events.  

- ***teleporter***: Move an agent to an arbitrary location. Reponds to keyboard events.

- ***wanderers***: Simpler version of avoiders demo.

- ***multiuser***: Demonstrates how to have multiple players all logged in with separate web browsers. Also shows non-interactive and invisible elements.  
- ***omni***: Shows a few omni-directional agents moving and teleporting.

- ***virus***: Demonstrates agent creation, and removal. Uses collision handlers and attachment constraints. 

Documentation
===

See the [README](https://github.com/klavinslab/enviro).

Button Clicks
===

In `config.json`

> `buttons`<br>
> A list of buttons to show in the top right of the front end user interface. These should have the form
> ```json
> {
>     "name": "name",
>     "label": "Displayed Name",
>     "style": { "background": "white", "border-color": "black" }
> }
> ```

Your events:

> Name: `button_click`<br>
> Sent when a user clicks on a button. The buttons need to be defined in `config.json`. <br>
> Value: An object with the a `name` field that matches the name field used in `config.json`. 

Keyboard Events
===

> Name: `keydown`<br>
> Sent when a user presses a key down.<br>
> Value: An object with a `key` field, which is the character pressed, as well as the following boolean fields
> ```
> ctrlKey
> shiftKey
> altKey
> metaKey
> ```
> &#x2469; New in 1.0.

> Name: `keyup`<br>
> Sent when a user release a key.<br>
> Value: Same as for `keydown`. 
> &#x2469; New in 1.0.

Keyboard Example
===

```c++
void init() {
    watch("keydown", [&](Event &e) {
        auto k = e.value()["key"].get<std::string>();
        if ( k == "w" ) {
                f = magnitude;              
        } else if ( k == "s" ) {
                f = -magnitude;  
        } else if ( k == "a" ) {
                tau = -magnitude;
        } else if ( k == "d" ) {
                tau = magnitude;
        } 
    });        
    watch("keyup", [&](Event &e) {
        auto k = e.value()["key"].get<std::string>();
        if ( k == "w" || k == "s" ) {
                f = 0;               
        } else if ( k == "a" ) {
                tau = 0;
        } else if ( k == "d" ) {
                tau = 0;
        } 
    });
}
void update() {
    apply_force(f,tau);
}
double f, tau;
double const magnitude = 200;
```

Omni Directional Robots
===

In `defs/your_robot.json` use

- "shape": "omni"
- "radius": 123

New methods:

- `void omni_apply_force(double fx, double fy)`
- `void omni_track_velocity(double vx, double vy, double k=10)` 
- `void omni_damp_movement()`
- `void omni_move_toward(double x, double y, double v=1)`

See `examples/omni`.

Collisions
===

`void notice_collisions_with(const std::string agent_type, std::function<void(Event&)> handler)`

Runs the handler function upon collisions with agents of the given agent type. 
The `agent_type` string is the name used in `defs/*.json` files. 
These should usually be set up in the `init` function of a process, as follows:
```c++
void init() {
    notice_collisions_with("Robot", [&](Event &e) {
        int other_robot_id = e.value()["id"];
        Agent& other_robot = find_agent(other_robot_id); 
        // etc.
    });
}
```
The value associated with the event `e` is a json object with a single key, `id`, which is the id of the other agent. 

`void ignore_collisions_with(const std::string agent_type)`

Stop noticing collisions with agents of the given type. 

Attaching
===

`void attach_to(Agent &other_agent)` 

Create a constraint that attaches the calling agent to the `other_agent`. 
For example, after the call
```c++
Agent& other_robot = find_agent(other_robot_id); 
attach_to(other_robot);
```
the two agents center's will be constrained to remain at the same distance from each other. 

Agent Management
===

`Agent& find_agent(int id)`

Given an agent's id, returns a reference to the agent. Note: ***do not*** assign the return value of this function to a normal 
variable, because when it goes out of scope, the agent's destructor will be called. Instead, assign it to a reference, as in
```c++
Agent& other_agent = find_agent(other_agent_id;
```

`bool agent_exists(int id)` 

Returns true or false depending on whether an agent with the given id still exists (i.e. is being managed by enviro). 
Agents may cease to exist if `remove_agent()` is called. 

`void remove_agent(int id)`
Removes the agent with the given id from the simulation. Also calls it's desctructor, so think of it as remove and delete. 

`Agent& add_agent(const std::string name, double x, double y, double theta, const json style)` <br>
Add's a new agent to the simulation with the given name at the given position and orientation.
Note that an agent with this type should have been mentioned in `config.json` so enviro knows about it. 
The style argument determines the agent's style, just as in the configuration file. 
Any valid svg styling will work. For example:
```c++
Agent& v = add_agent("Block", 0, 0, 0, {{"fill": "bllue"},{"stroke": "black"}});
```

The Virus Example
===

Go to `examples/virus`

Sensor Reflection Types

`std::string sensor_reflection_type(int index)`

This method returns the name of object type the sensor of the specificed index is seeing. The index refers to the position in the sensor list in the agent's JSON definition. 

std::vector<std::string> sensor_values()`
This method returns a list of all the sensor reflection types, in the same order as the sensors appear in the agent's JSON definition.

Decorations and Labels
===

`void decorate(const std::string svg)`

Add an aribtrary svg element to the agent's rendering method on the client side. 
The svg element will be transformed and rotated to the agent's coordinate system. 
For example, to place a red dot in the middle of the agent do:
```c++
decorate("<circle x='-5' y='5' r='5' style='fill: red'></circle>");
```
To clear the decoration later, simple call
```c++
decorate("");
```

`void label(const string str, double x, double y )` 

Add a textual label to the agent's icon. The x and y values are relative to the origin of the agent's coordinate system. 

`void clear_label()` 

Clear the label associated with the agent. 

Preventing Rotation
===

`void prevent_rotation()`

Prevents the agent from rotating. Probably best to call in the init function. Good for platformer type movement. Technically sets the moment of inertia to infinity. 

`void allow_rotation()`

Allows the agent to rotate, setting the moment of inertia to the default number (based on the mass and shape of the agent). 

See `examples/platformer`.

New Agent Types
===

In the `defs/*.json` definitions, the type field can now be:

- "dynamic": the agent will move, have mass, etc. 
- "static": the agent will not move but will still be something other agents will collide with (i.e. like a wall).
- "noninteractive": The agent will not by simulated with any physics. Other agents will pass through it.
- "invisible": The agent is noninteractive and invisible. It can be used to run background processes not associated with visible elements. 

The Client ID
===

Event Name: `connection`

Sent when a new client attaches to the enviro server.

Value: An object with a string valued `id` field that should be unique to the client that has connected.

Note: this ID will be sent with all other events as well.

Example: Spawn new Player for Each Connection
===

```c++
class CoordinatorController : public Process, public AgentInterface {

    public:
    CoordinatorController() : Process(), AgentInterface() {}

    void init() {
        watch("connection", [&](Event e) {
            Agent& a = add_agent("Guy", 0, y, 0, {{"fill","gray"},{"stroke","black"}});
            a.set_client_id(e.value()["id"]);
            y += 50;
        });
    }
    void start() {}
    void update() {}
    void stop() {}

    double y = -150;

};
```

Example: Filter Keyboard Events by Connection
===

In `guy.h`:

```c++
watch("keyup", [&](Event &e) {
    if ( e.value()["id"] == get_client_id() ) { // FILTER CLIENT!
        auto k = e.value()["key"].get<std::string>();
        if ( k == " " ) {
            firing = false;
        } else if ( k == "w" || k == "s" ) {
            f = 0;               
        } else if ( k == "a" ) {
            tau = 0;
        } else if ( k == "d" ) {
            tau = 0;
        } 
    }
});
```

Muiltiple Players
===

See `examples/multiuser`

That's It
===

I hope you learned:
- Some C
- Abstract data types and classes
- Memory management
- C++
    - Classes

Thank You!
===

I had fun teaching the course and meeting all of you!

Sorry for grading hiccups! This are being resolved!

Have fun with the project!

Keep Calm and Carry On
===

Please stay safe, but also try to maintain as normal of schedule as you can.

We can adapt to life and work with a pandemic! 

Someday you'll tell you grandkids about it!

<img src="https://upload.wikimedia.org/wikipedia/commons/6/6f/Keep-calm-and-carry-on-scan.jpg" height=50%>






