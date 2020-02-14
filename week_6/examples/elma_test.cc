#include "gtest/gtest.h"
#include "elma/elma.h"

namespace {

    using namespace elma;

    class DoNothing : public Process {
      public:
        DoNothing(std::string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() {}
        void stop() {}
    };   
    
    TEST(Elma,Basics) {

      Manager m;
      DoNothing p("Do Nothing");

      m.schedule(p, 1_ms)    // process updates every 1ms
        .init()              // initialize all processes
        .run(10_ms);         // run for 1s

    }

    class MyProcess : public elma::Process {
      public:
        MyProcess(std::string name) : Process(name) {}
        void init() {}
        void start() {}
        void update() { 
          std::cout << name() << ": " 
                    << milli_time()
                    << "ms\n";
        }
        void stop() {}
    };    

    TEST(Elma,NumUpdates) {
        Manager m;
        MyProcess p("A"), q("B");

        m.schedule(p, 1_ms)
         .schedule(q, 5_ms)
         .init()
         .run(11_ms);

        ASSERT_EQ(p.num_updates(), 10);
        ASSERT_EQ(q.num_updates(), 2);      
    }

}