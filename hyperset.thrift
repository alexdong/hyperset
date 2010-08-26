#!/usr/local/bin/thrift

namespace cpp hyperset
namespace python hyperset

service hyperset {
    i32         calc (1: string query),
    void        add  (1: string name, 2: list<i32> vals),
    void        save (),
}
