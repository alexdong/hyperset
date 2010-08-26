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

/**
 * MAIN TEST CODES 
 */
void _load_test(setmap_t &setmap) {
    string filename = "test.data";
    load(filename, setmap);
}

BOOST_AUTO_TEST_CASE(single_union_for_two) {
    // ('union', ['scr:0', 'scr:20'])
    setmap_t setmap;
    _load_test(setmap);

    vector<SetOp> ops;
    SetOp op1; op1.op = "union"; 
    op1.sets.push_back("scr:0"); op1.sets.push_back("scr:1");
    ops.push_back(op1);

    BOOST_CHECK_EQUAL(9, calc(setmap, ops));
}

BOOST_AUTO_TEST_CASE(single_union_for_three) {
    // ('union', ['scr:0', 'scr:20', 'scr:30])
    setmap_t setmap;
    _load_test(setmap);

    vector<SetOp> ops;
    SetOp op1; op1.op = "union"; 
    op1.sets.push_back("scr:0"); op1.sets.push_back("scr:1"); 
    op1.sets.push_back("scr:30");
    ops.push_back(op1);

    BOOST_CHECK_EQUAL(10, calc(setmap, ops));
}

BOOST_AUTO_TEST_CASE(single_union_for_four) {
    // ('union', ['scr:0', 'scr:20', 'scr:30', 'geo:1'])
    setmap_t setmap;
    _load_test(setmap);

    vector<SetOp> ops;
    SetOp op1; op1.op = "union"; 
    op1.sets.push_back("scr:0"); op1.sets.push_back("scr:1");
    op1.sets.push_back("scr:30"); op1.sets.push_back("geo:1");
    ops.push_back(op1);

    BOOST_CHECK_EQUAL(10, calc(setmap, ops));
}

BOOST_AUTO_TEST_CASE(single_intersect_for_two) {
    // ('intersect', ['scr:0', 'scr:20'])
    setmap_t setmap;
    _load_test(setmap);

    vector<SetOp> ops;
    SetOp op1; op1.op = "intersect"; 
    op1.sets.push_back("scr:0"); op1.sets.push_back("scr:1");
    ops.push_back(op1);

    BOOST_CHECK_EQUAL(0, calc(setmap, ops));
}

BOOST_AUTO_TEST_CASE(single_intersect_for_two_with_result) {
    // ('intersect', ['scr:0', 'geo:1'])
    setmap_t setmap;
    _load_test(setmap);

    vector<SetOp> ops;
    SetOp op1; op1.op = "intersect"; 
    op1.sets.push_back("scr:0"); op1.sets.push_back("geo:1");
    ops.push_back(op1);

    BOOST_CHECK_EQUAL(4, calc(setmap, ops));
}

BOOST_AUTO_TEST_CASE(single_intersect_for_three) {
    // ('intersect', ['scr:0', 'geo:1', 'date:1667'])
    setmap_t setmap;
    _load_test(setmap);

    vector<SetOp> ops;
    SetOp op1; op1.op = "intersect"; 
    op1.sets.push_back("scr:0"); op1.sets.push_back("geo:1"); 
    op1.sets.push_back("date:1667");
    ops.push_back(op1);

    BOOST_CHECK_EQUAL(1, calc(setmap, ops));
}


BOOST_AUTO_TEST_CASE(integration_test) {
    // ('union', ['scr:0', 'scr:20'])
    // ('union', ['geo:1', 'geo:2'])
    // ('union', ['date:1667', 'date:1668', 'date:1669', 'date:1670'])
    // ('intersect', ['$', '$', '$'])
    setmap_t setmap;
    _load_test(setmap);

    vector<SetOp> ops;
    SetOp op1; op1.op = "union"; 
    op1.sets.push_back("scr:0"); op1.sets.push_back("scr:20"); 
    ops.push_back(op1);

    SetOp op2; op2.op = "union"; 
    op2.sets.push_back("geo:2"); op2.sets.push_back("geo:1"); 
    ops.push_back(op2);

    SetOp op3; op3.op = "union"; 
    op3.sets.push_back("scr:0"); op3.sets.push_back("scr:20"); 
    ops.push_back(op3);

    SetOp op4; op4.op = "intersect"; 
    op4.sets.push_back("scr:0"); op4.sets.push_back("scr:20"); 
    ops.push_back(op4);

    BOOST_CHECK_EQUAL(9, calc(setmap, ops));
}
