#include "gtest/gtest.h"
#include "extrema.h"

namespace {

    class ExtremaTester : public Process {


        // This process will be used to send data to the "link" channel
        // so that an Extrema process can be tested. It sends the 
        // sequence, 0.1, -0.2, 0.3, -0.4, ... to the channel.

        public:

        ExtremaTester(std::string name) : Process(name), x(0.1) {}

        void init() {}
        void start() {}
        void update() {
            channel("link").send(x);
            if ( x > 0 ) {
                max = x;
            } else {
                min = x;
            }
            x = -2*x;
        }
        void stop() {}

        double x, min, max;

    };
    
    TEST(Extrema,FindsExtrema) {

      // This test runs an Extrema process and an ExtremaTester
      // together for 20 ms, and then checks that the two processes
      // agree on what the min and max were. 

      Manager m;
      Extrema extrema("Min max finder");
      ExtremaTester tester("Tester");
      Channel link("link");

      m.schedule(tester, 1_ms) 
       .schedule(extrema, 1_ms) 
       .add_channel(link)
       .init() 
       .run(20_ms); 

      ASSERT_DOUBLE_EQ(tester.max, extrema.max());
      ASSERT_DOUBLE_EQ(tester.min, extrema.min());

    }

    TEST(Extrema,Exceptions) {

        // This tests makes sure an Extrema process throws
        // an error if its min() and max() getters are used
        // before it has seen any data.

        Extrema extrema("Min max finder"); 

        try {
          extrema.min();
          FAIL();
        } catch ( std::runtime_error e ) {
          ASSERT_STREQ(e.what(), "Extrema process has no data");
        }

        try {
          extrema.max();
          FAIL();
        } catch ( std::runtime_error e ) {
          ASSERT_STREQ(e.what(), "Extrema process has no data");
        }

    }

}