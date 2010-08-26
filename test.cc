#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE hyperset

#include <boost/test/unit_test.hpp>
#include "core.h"

using namespace std;
using namespace hyperset;

/**
 * LOAD/SAVE 
 */
BOOST_AUTO_TEST_CASE(save_and_load_test) {
    setmap_t sm1, sm2;
    sm1["scr:20"].insert(100056);
    sm1["scr:20"].insert(100086);
    sm1["geo:1"].insert(100056);
    sm1["geo:1"].insert(200063);
    sm1["geo:2"].insert(200060);

    string filename = "data.txt";
    save(filename, sm1);
    load(filename, sm2);

    BOOST_CHECK_EQUAL(2, sm2["geo:1"].size());
    BOOST_CHECK_EQUAL(1, sm2["geo:2"].size());
    BOOST_CHECK_EQUAL(2, sm2["scr:20"].size());
}

BOOST_AUTO_TEST_CASE(integration_test) {
    // ['union', 'scr:0', 'scr:20']
    setmap_t setmap;
    string filename = "test.data";
    load(filename, setmap);

    BOOST_CHECK_EQUAL(9, calc(setmap, 
                "union scr:0 scr:20"));
    BOOST_CHECK_EQUAL(10, calc(setmap,
                "union scr:0 scr:20 scr:30"));
    BOOST_CHECK_EQUAL(10, calc(setmap,
                "union scr:0 scr:20 scr:30 geo:1"));
    BOOST_CHECK_EQUAL(0, calc(setmap,
                "intersect scr:0 scr:20"));
    BOOST_CHECK_EQUAL(4, calc(setmap,
                "intersect scr:0 geo:1"));
    BOOST_CHECK_EQUAL(2, calc(setmap,
                "intersect scr:0 geo:1 date:1667"));
    BOOST_CHECK_EQUAL(8, calc(setmap,
                "union scr:0 scr:20; union geo:1 geo:2; union date:1667 date:1668 date:1669 date:1690; intersect $ $ $"));
}
