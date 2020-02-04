#include "db.h"
#include "gtest/gtest.h"

namespace {
    
    TEST(DB,Basics) {

        DB db;

        db.insert("earth", 1, 1)            
          .insert("mars", 0.11, 1.524)
          .insert("moon", 0.012, 1)
          .insert("exoplanet one", 1, 1054.4)
          .insert("jupiter", 318, 5.2);

        ASSERT_EQ(NAME(db.find(0)), "earth");

        auto rows = db.where([](DB::Row row) { return  MASS(row) < 1; }); 

        ASSERT_EQ(rows.size(), 2);

        try {
            db.drop(2)                        
              .find(2);  
            FAIL();
        } catch ( runtime_error e ) {
            ASSERT_STREQ(e.what(), "Could not find an entry with the given key");
        }     

    }

}