#!/usr/local/bin/thrift

namespace cpp hyperset
namespace python hyperset

// Input data structures
struct SetOp {
    1: string op,
    2: list<string> sets,
}

service hyperset {
    set<i32>    calc (1: list<SetOp> query),
    i32         count(1: list<SetOp> query),
    i32         add  (1: string name, 2: list<i32> vals),
    i32         save (),
}
