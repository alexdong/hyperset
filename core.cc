#include <algorithm>
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

#include <glog/logging.h>

#include "core.h"

namespace hyperset {

void _get_set_vector(setmap_t &setmap, string &name, 
        stack<vector<int32_t> > &set_stack, 
        vector<int32_t> &current) {
    /**
     * Get the data for the current set into a vector. 
     * If the `name` is a '$', read the set data from the stack, 
     * Otherwise, copy the data from the `setmap` into new vector.
     */
    if(name == "$") {
        current = set_stack.top();
        set_stack.pop(); 
    } else {
        current.reserve(setmap[name].size());
        copy(setmap[name].begin(), setmap[name].end(),
                back_inserter(current));
    }
}

int32_t calc(setmap_t &setmap, string query) {
    /**
     * Execute query over the setmap.  
     * The query is something like 
     * union scr:0 scr:20; union geo:1 $
     */

    // Break a query into sub queries
    vector<string> subqueries;
    boost::split(subqueries, query, boost::is_any_of(string(";")));
    LOG(INFO) << "Processing query: " << query;

    vector<int32_t> current, next, result;
    stack<vector<int32_t> > set_stack;

    // Process each sub-query
    foreach(string & subquery, subqueries) {
        VLOG(1) << "Current sub query: " << subquery;
        current.clear(); next.clear(); result.clear(); 

        // Break up the sub-queries into [op, *operand]
        vector<string> tokens;
        boost::algorithm::trim(subquery);
        boost::split(tokens, subquery, boost::is_space());
        string &op = tokens[0]; 

        // Set operate the first two sets into `current`, then use 
        // `current` to perform further operations with other sets. 
        _get_set_vector(setmap, tokens[1], set_stack, current);
        for(unsigned int idx = 2; idx < tokens.size(); ++idx) {
            _get_set_vector(setmap, tokens[idx], set_stack, next);

            if(op == "union") {
                set_union(current.begin(), current.end(), 
                        next.begin(), next.end(),
                        back_inserter(result));
            } else {  // if(tokens[0] == "intersect")        
                set_intersection(current.begin(), current.end(), 
                        next.begin(), next.end(),
                        back_inserter(result));
            }
            VLOG(2) << op << " " << current.size() << " " << next.size()
                << "  => " << result.size();

            current.clear(); current.reserve(result.size());
            copy(result.begin(), result.end(), back_inserter(current));
            result.clear(); next.clear();
        }

        // push the current set result onto the stack and move on 
        // to the next `SetOp` operation set.
        VLOG(1) << "Current SetOp result length: " << current.size();
        set_stack.push(current);
        VLOG(1) << "Stack.size(): " << set_stack.size();
    } // foreach

    current = set_stack.top();
    return current.size();
}

void save(string &filename, setmap_t &setmap) {
    /**
     * save the `setmap` to `filename` as a plain text file. 
     *
     * The format is space separated with each line representing
     * each set. The first is the set name and the rest are the numbers. 
     */
    ofstream fout(filename.c_str());
    foreach(setmap_t::value_type &pair, setmap) {
        fout << pair.first << " ";
        foreach(int32_t value, pair.second) {
            fout << value << " ";
        }
        fout << endl;
    }
    fout.close();
    LOG(INFO) << "Saved " << setmap.size() << " sets";
}

void load(string &filename, setmap_t &setmap) {
    string line, name;
    vector<string> tokens;
    vector<string>::const_iterator itr;
    ifstream fin(filename.c_str());

    // now, read line by line with each one a set
    while(getline(fin, line)) {
        tokens.clear();
        boost::split(tokens, line, boost::is_space());

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
    LOG(INFO) << "Loaded " << setmap.size() << " sets";
}

void add(setmap_t  &src, const string &name, const vector<int32_t> & values) {
    BOOST_FOREACH(int32_t val, values) {
        src[name].insert(val);
    }
    LOG(INFO) << "Added " << values.size() << " values to set: " << name;
    LOG(INFO) << "Set current size: " << src[name].size();
}

} // namespace
