#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE hyperset

#include <boost/test/unit_test.hpp>
#include "core.h"

using namespace std;
using namespace hyperset;

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
