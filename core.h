#ifndef HYPERSET_H
#define HYPERSET_H

#include <string>
#include <set>
#include <map>
#include <boost/foreach.hpp>
#include "hyperset.h"
#include "hyperset_types.h"

using namespace std;

namespace hyperset {

#define foreach                         BOOST_FOREACH
typedef map<std::string, std::set<int32_t> > setmap_t;

void    calc(const setmap_t  &src, const vector<SetOp> & ops, 
        set<int32_t> & result);

void    clear(setmap_t &dst, const string &name);

void    add(const setmap_t  &src,
        const string &name,
        const vector<int32_t> & values);

void    save(const string &filename, const setmap_t & setmap);
void    load(const string &filename, setmap_t &setmap);

} // namespace
#endif
