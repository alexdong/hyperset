#!/usr/local/bin/thrift

namespace cpp hyperset
namespace python hyperset

service hyperset {
    i32         calc (1: list<string> query),
    i32         add  (1: string name, 2: list<i32> vals),
    i32         save (),
}
