Software Engineering For Embedded Applications
===

Week 9: Projects, Networking, Project
---

Projects
===

Requirements
---

The goal of your project is to build up an example system the uses Elma and Enviro. The general ingredients are:

- Uses enviro, or extends enviro significantly
- A new, public Github repo with all the code for your project
- Well documented code, with all public methods described. See the Elma project for an example. 
- A `README.md` file, to be included on the front page of your github repo with
    - An overview with general usage information 
    - Examples, if applicable
    - Installation / setup instructions

Projects will be due Wednesday March 18 at 11:59pm. All of the above criteria will be used to grade your project, as well as the overall usability of the code. To submit your project, just submit the github URL for your repo on canvas so we can clone your project and run it.

Project Options
===

Below is a list of suggestions for your project that build upon HW7. However, anything similar to the ideas below are fine. You could, for example, create a video game, or a more realistic simulation of an actual robot, etc.

1. Extend or improve the maze environment example. For example, use more complicated mazes. Generate random mazes. Build a map of the environment and navigate within it.
1. Extend or improve the blocks sweeping example. For example, have blocks disappear once deposited in a specific place. Make new blocks periodically. Use more varied sizes and shapes. Have robots collaborate. Include ostacles in the environment.
1. Extend or improve the example in which a robot moves around the arena with robots following it. Create a longer train of robots. Create flocking behaviors, and so on. 

Internet Protocols
===

IP
--

The "Internet Protocols" suite of protocols for communicating among computers on the internet. Raw addresses such as 127.23.4.1 for the basis of how computers find each other via routers and routing tables. IP includes other protocols such as UDP and TCP.

UDP
---

UDP stands for "User Datagram Protocol". It is used for low latency commucation of byte packets and messages between devices on an ethernet and/or the Internet. Messages sent with UDP arrive in order, but are not guaranteed to be delivered. Information such as real time voice and video are common applications. 

TCP
---

TCP stands for "Transmission Control Protocol". It is used for everything else. Messages are broken into packets and sent from one computer to another via routers. Acknowledgments of packet delivery are sent back to the sender. Each packet may take a different route. Failures occur due to over-taxed routers, and result in packets being resent. The rate at which packets are sent is adjusted according to the packet loss rate: every time a packet is lost, the packet send rate is cut in half. Every time a packet is not lost, the rate is incremented by a small amount (up to some limit). 

Web Protocols
===

HTTP
---

HTTP stands for "Hypertext Transfer Protocol". It sits on top of TCP, meaning that it is simply a specification of the format of the messages that are sent back and forth using TCP. It was originally devloped for serving web pages, thus the term hypertext in the name. However, it has developed into a standard for sending data of any kind -- web pages, images, movies, json data, and so on -- in a reliable way. HTTP also specifies how Internet resources are named, using "Uniform Resource Locators" such as http://www.google.com instead of raw IP address.

HTTPS
---

A secure version of HTTP that also uses the "Transport Layer Secutiry" (TLS) or "Secure Socket Layer" (SSL) to communcate. TLS and SSL sit on top of TCP, but encrypt packets before sending them. HTTPS can be either "simple", in which the server publishes a public key, or "mutual" in which case both sides publish public keys. Servers must additionally register with a trusted third party "certificate authority" to prevent spoofing of the service. 

Clients and Servers
===

- *Server*: An http server is a program that listens for incoming messages on a "port". Ports are just numbers the operating system uses to direct incomping IP traffic. For example, http usually runs on port 80, https on port 443, telnet on 23, ssh on 22, etc. Servers receive requests for data and "serve" the result. An example of an http server is the Apache Server. But you can make your own http server with a few lines of code.

- *Clients*: An http client is a program that connects to a server (or multiple servers), to request data or to upload data to a server. An example of a client is your web browser. But a robot in a factory or a satillite could also be clients. 

- *Request Format*: Requests are text strings that include
    - A request line, like "GET /klavins/ECEP520 HTTP/1.1" which says to get a particular file or resource from the server.
    - Any number of request header fields (key value pairs). For example, you might add "User-Agent: Elma" so the server knows what kind of client is connecting.
    - An empty line.
    - An optional request body, where you might put data for an upload, etc., encoded as text

- *Response Format*: Responses are similar and include
    - A status, like "HTTP/1.1 200 OK" or "HTTP/1.1 404 Not found"
    - Any numbner of response headers, for example "content-type: json"
    - A blank line
    - A message body encoded as text

Enviro Architecture
===
The command `esm start` starts an off the shelf web server on port 80. When you navigate to `http://localhost`, the web server returns the enviro web page, which includes a set of javascript program written using the React javascript library. In this case, your web browser is the client, and the web server (running in the container) is the server. 

Once the browser receives the web page, it runs the javascript program, which is then another client. It talks directly to the `enviro` server over port 8765. The enviro server erturns information about the configuration of the simulation, and the positions of all the agents. 

Get Requests
===

A GET request looks like 
    ```
    GET /klavins/ECEP520 HTTP/1.1
    User-Agent: chrome
    ```
    an is used to request a datum with a simple name that can be specified in a path. For example, the one in the previous sentence asks ther server running at github.com to send back the main HTML page for our class' repository.

Enviro responds to two get requests

```
http://localhost:8765/config
http://localhost:8765/state
```

Post Requests
===
A POST request might look like like 
```
POST /save HTTP/1.1
User-Agent: Elma
content-type: json

{
    "x": 123.4,
    "y": 234.5,
    "type": "screen_click"
}
```

Enviro responds to one POST request

```
http://localhost:8765/event
```

with a body of the form show above, for example.

Other Requests
===

HTTP also defines PUT, DELETE, and PATCH, which together form the basis of what is called a Restful interface. Rest stands for "Representational State Transfer". For now, GET and POST are sufficient for most purposes, with specific actions like "delete" defined either in the url path or in a JSON message body.

Web Sockets
===

The WebSocket API is an advanced technology that makes it possible to open a two-way interactive communication session between the user's browser and a server. With this API, you can send messages to a server and receive event-driven responses without having to poll the server for a reply. 

Enviro uses the `uWebSockets` library for its communication between the client and server.

The Curl Client
===

An incredibly useful tool installed on pretty much any unix like environment (including our docker pages) is `curl`. Curl allows you to send get and post requests to servers. For example, to do a simple GET request, do
```bash
curl https://www.google.com
```
will return the httmp for Google's main page.

You can also do a POST request, as in 
```bash
curl -d '{ "x": 123, "y": 234, "temperature": 41.2 }' -X POST localhost:8080/save
```
which we will use in an example below.

More interestingly, you can use Google's data API to get all sorts of interesting data. For example, see [here](https://cloud.google.com/vision/docs/using-curl). Note, charges apply. Other data services at Amazon, NOAA, Github, etc. are similar.

Talking to Enviro
===

With enviro running, try 
```
curl localhost:8765/config
```
or
```
curl -d '{ "type": "screen_click",  "x": 10, "y": 20 }' -X POST localhost:8765/event
```

Using HTTP 
===

One option for HTTP in C++ is [httplib](https://github.com/yhirose/cpp-httplib)

C and C++ provide low level access to UDP and TCP with the 'socket' library. An example of low level socket programming can be found [here](https://www.geeksforgeeks.org/socket-programming-cc/). It is a good place to start if you are developing a new protocol on top of TCP or UDP. But for communicating with HTTP, it is too low level, as it does not handle the request and response formats above, and does not know anything about GET and POST.

There are a myriad of libraries for dealing with HTTP in C++. A nice one that has a clean interface is called `cpp-httplib`. I have made a branch of this library and started to hack it a bit for use with Elma [here](https://github.com/klavins/cpp-httplib). In particular, I have added an exception class and started to add exception throws to the library, which uses return values to denote errors instead of exceptions (a very old C idea).

Examples of how to use cpp-httplib to make a simple server and client are [here](https://github.com/klavins/cpp-httplib).

A Simple Database Server
===

As an example of what a server might do in an embedded systems or robotics setting, consider a scenario where a number of robots are exploring or surveying an area. Say they each have temperature sensors. To get a global picture of how the temperature is changing over space and time, the robots could upload their coordinates and the temperature to a server. To provide this service this, we will make a server that responds to two types of request. 

- A POST request of the form `{ "x": 123, "y": 234, "temperature": 41.2 }` sent to the route `/save`
- A GET request to routes of the form `/find/42` that, in this case, returns the 42nd temperature reading

A simple database like data structue is defined as follows:
```c++
std::map<int, // id
    std::tuple<
       int,      // timestamp
       double,   // x position
       double,   // y position
       double    // temperature
    >
> database;
```
Responding to POST Requests
===

To respond to the POST requests, we 
- Parse the JSON request (returning an error if it is malformed)
- Update the database
- Respond to the client with information about what was done

In code, this looks like
```c++
svr.Post("/save", [&](const Request& req, Response& res) { 

    json request, result;

    try {
        request = json::parse(req.body);
    } catch(json::exception e) {
        result["result"] = "error";
        result["message"] = e.what();
        res.set_content(result.dump(), "json");
        return;
    }

    database[next_id] = std::make_tuple(
        unix_timestamp(),
        request["x"].is_number() ? (double) request["x"] : 0,
        request["y"].is_number() ? (double) request["y"] : 0,          
        request["temperature"].is_number() ? (double) request["temperature"] : 0
    );

    result["result"] = "ok";
    result["id"] = next_id++;
    res.set_content(result.dump(), "json");

});
```

Responding to GET Requests
===

To respond to GET requests, we look up the id in the database, and return the resulting tuple in json.
```c++
svr.Get(R"(/find/(\d+))", [&](const Request& req, Response& res) {
    auto id = std::stoi(req.matches[1].str());
    json result;
    if ( database.find(id) != database.end() ) {
        result = { 
            { "result", "ok" },
            { "id", id },
            { "timestamp", std::get<0>(database[id]) },
            { "x", std::get<1>(database[id]) },
            { "y", std::get<2>(database[id]) },
            { "temperature", std::get<3>(database[id]) }                                      
        };
    } else {
        result["result"] = "error";
        result["message"] = "not found";
    }
    res.set_content(result.dump(), "json");
});
```

Using the Server
===

To test the server, we'll map the port 8080 in the docker container to the port 80 on the host, by restarting the docker container with
```bash
docker run -p 8080:8080/tcp -v $PWD:/source -it klavins/ecep520:cppenv-http bash
```
Note that the new Dockerfile also includes a directive to expose 8080 to the host with `EXPOSE 8080`. 

Next, do `make bin/temperature_server` in the examples directory and then run `bin/temperature_server`. This will tie up the terminal, so you'll need another terminal to test it. If you have a Mac, you can just open a terminal and run
```bash
curl -d '{ "x": 123, "y": 234, "temperature": 41.2 }' -X POST localhost:8080/save
```
or
```c++
curl localhost:8080/find/1
```

Adding HTTP to Elma
===

THIS IS FOR YOUR INFORMATION ONLY. ENVIRO DOES NOT USE THIS AND THERE IS NO HOMEWORK ON THIS. 

It is tempting to add cpp-httplib directly to Elma and allow processes to use the `Get` method it provides for Clients directory. However, doing so raises two issues:
- The `Get` method of cpp-httplib blocks. That is, until the data is sent from the client to the server and back, nothing happens in the client program. Depending on how long this takes, it will block all other processes' `update` methods.
- We don't want the callback function for `Get` to run at arbitrary times (like in the middle of an update), but rather at a specified time in the main loop, like just before all processes are updated.
- We might decide to swap out cpp-httplib later, so we should define our own interface to http for Elma so that the backend can be easily changed later.

The third issue is easily solved by creating a new class. But the first two issues requires some new concepts.

Threads
===

When you want multiple things to happen at once in C or C++, such as updating processes and waiting for a TCP response, you use [std::thread](http://www.cplusplus.com/reference/thread/thread/). Use `#include <thread>`. Here is an example:
```c++
void do_something(int x, int y) {
    // suppose this takes a while
    // and we don't need the result
}

int main() {

  std::thread t1(do_something, 1, 2); 
  std::thread t2(do_something, 1, 2); 

  t1.detach();
  t2.detach();

  // continue on doing something else
  // note: if the main function ends, it will
  // stop the threads, even if they haven't
  // completed.

  return 0;

}
```

Waiting
===

You can also wait for the threads to complete, as with
```c++
int main() {

  std::thread t1(do_something, 1, 2); 
  std::thread t2(do_something, 1, 2); 

  // continue on doing stuff

  t1.join();
  t2.join();

  return 0;

}
```
In general, use `detach` if you don't intend to `join` them later. 

Race Conditions
===

One issue with threaded code is the possibility of *race conditions*, in which two or more processes access the same data structures in different orders depending on timing. Here is an example:
```c++
char buffer[301];
int index = 0;

void print_block (int n, char c) {
    for (int i=0; i<n; ++i) { 
    buffer[index] = c;
    index++;
    std::this_thread::sleep_for(std::chrono::milliseconds(rand()%5));
    }
}

TEST(RACE,CONDITIONS) {

    buffer[300] = 0;
    std::thread t1 (print_block,150,'*');
    std::thread t2 (print_block,150,'$');
    t1.join();
    t2.join();
    auto desired_result = std::string(150,'*') + std::string(150,'$');
    ASSERT_STREQ(desired_result.c_str(), buffer);

}
```
Running this test may sometimes work, but more often than not you will get an failed test report:
```
Expected equality of these values:
  desired_result.c_str()
    Which is: "*************************************************$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$"
  buffer
    Which is: "*$$**$$$*$$$**$*$$*$$*$*$$$*$$$**$*$*$$*$*$$**$*$$$$**$*$$*$$$****$*$*$$**$$*$***$$*$*$*$*$$$*$**$*$$$**"
```

Enviro Race Condition Possibilities
===

Enviro runs two threads. The first is the manager, which continuously updates all process. The second is the 8765 server, which retursn state information and receives event notifications.

What sort of data structures do you think both of these threads have to access?

Mutual Exclusion
===

To fix race conditions, we use a `mutex` (use `#include <mutex>`), which is a mutual exclusion lock. When a thread locks a mutex, it will be allowed to contiune with what it is doing without being interrupted until it unlocks the mutex. The fix for the above code is
```c++
std::mutex mtx;
char buffer[301];
int index = 0;

void print_block (int n, char c) {
    mtx.lock();
    for (int i=0; i<n; ++i) { 
    buffer[index] = c;
    index++;
    std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    mtx.unlock();
}
```
which enables the test to pass.

A Client Class for Elma
===
For our Client class, we  provde a similar interface to cpp-httplib, but with different behavior:
- Get requests  look like
    ```c++
    Client& get(std::string url, std::function<void(json&)> handler);
    ```

    We  pass the entire URL and not specifiy the host and path separately.
    We  expect a JSON result from the server, which our implementation will parse and supply to the handler.
- Our client's `get` method will be **non-blocking** so that it doesn't block the `Manager` main loop.
- The `get` method is run in a thread that does the following:
    - Parse the result. 
    - Put it and a reference to the handler into a list of responses
- The `Manager` dispatches all new responses to their handlers each time through the main loop.

Example
===

THIS IS FOR YOUR INFORMATION ONLY. ENVIRO DOES NOT USE THIS AND THERE IS NO HOMEWORK ON THIS. 

```c++
class GetTester : public Process {
    public:
    GetTester() : Process("Get Tester") {}
    void init() {}
    void start() {
        got_response = false;
        http_get("https://api.github.com/repos/klavins/ecep520", [this](json& response) {
            got_response = true;
        });
    }
    void update() {}
    void stop() {
        ASSERT_EQ(true,got_response);
    }
    bool got_response;
};

TEST(Client,ProcessInterface) {
    Manager m;
    GetTester p;
    m.schedule(p,1_ms)
        .init()
        .run(1_s);
}
```

Enviro New Features Coming Soon
===

Definitely
---
- Documentation
- get_x, get_y, get_angle instead of chipmunk
- Return identity with distance
- Respond to keyboard events
- Have an omni directional robot
- Other modes of control (path following, for example)
- Have non-physical objects (like buttons)
- Have invisible, non-physical objects (like a game controller that keeps the score or responds to collision events)
- The ability to dynamically spawn new and delete agents on the fly

Maybe
---
- Change size or appearance of agents
- Change the center of the view and possibly the magnification
- Allow multiple users logged in from different clients
- Add words and other decorations

Brainstorm
===

Now that you have worked with `enviro` for a week and have learned a bit about how it works, discuss
- What you might do with your project.
- What are some features you might need or like to have in enviro.