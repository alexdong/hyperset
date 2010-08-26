#include <stdio.h>
#include <map>
#include <set>
#include <stack>
#include <vector>
#include <string>

#include <iostream>
#include <fstream>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include "core.h"

namespace hyperset {

void save(const string &filename, const setmap_t &setmap) {
    /**
     * save the `setmap` to `filename` as a plain text file. 
     *
     * The format is space separated with each line representing
     * each set. The first is the set name and the rest are the numbers. 
     */
    ofstream fout(filename.c_str());
    foreach(const setmap_t::value_type &pair, setmap) {
        fout << pair.first << " ";
        foreach(const int32_t value, pair.second) {
            fout << value << " ";
        }
        fout << endl;
    }
    fout.close();
}

void load(const string &filename, setmap_t &setmap) {
    string line, name;
    vector<string> tokens;
    vector<string>::const_iterator itr;
    ifstream fin(filename.c_str());

    // now, read line by line with each one a set
    while(getline(fin, line)) {
        tokens.clear();
        boost::split(tokens, line, boost::is_from_range(' ', ' '));

        // first field is always the set name
        name = tokens[0];

        // rest are the numbers
        itr = tokens.begin(); ++itr;
        for(; itr != tokens.end(); ++itr) {
            if(!itr->length()) continue;
            setmap[name].insert(atoi(itr->c_str()));
        }
    }
    fin.close();
}

void clear(setmap_t &src,
        const string &name) {
    // Return no update if we can't find the set given the `name`
    if(src.find(name) == src.end()) return;

    src[name].clear();
}

void add(setmap_t  &src,
        const string &name,
        const vector<int32_t> & values) {
    // Return no update if we can't find the set given the `name`
    if(src.find(name) == src.end()) return;

    BOOST_FOREACH(int32_t val, values) {
        src[name].insert(val);
    }
}

} // namespace
