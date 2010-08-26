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

int32_t calc(setmap_t &setmap, string query);
void    add(setmap_t  &src, const string &name, const vector<int32_t> & values);
void    clear(setmap_t &dst, string &name);
void    save(string &filename, setmap_t & setmap);
void    load(string &filename, setmap_t &setmap);

} // namespace
#endif
