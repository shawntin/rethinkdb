#ifndef __RIAK_INTERFACE_HPP__
#define __RIAK_INTERFACE_HPP__

#include "riak/structures.hpp"
#include "store_manager.hpp"
#include <boost/ptr_container/ptr_map.hpp>
#include "http/json.hpp"
#include "javascript/javascript.hpp"

#define RIAK_LIST_KEYS_BATCH_FACTOR 10

namespace riak {

namespace json = json_spirit;

class bucket_iterator_t {
private:
    store_manager_t<std::list<std::string> >::const_iterator it;

public:
    bucket_iterator_t(store_manager_t<std::list<std::string> >::const_iterator const &it) 
        : it(it)
    { }

public:
    bool operator==(bucket_iterator_t const &other) { return it == other.it; }
    bool operator!=(bucket_iterator_t const &other) { return !operator==(other); }
    bucket_iterator_t operator++() { it++; return *this; }
    bucket_iterator_t operator++(int) { it++; return *this; }
    bucket_t operator*() { return boost::get<riak_store_metadata_t>(it->second->store_metadata); }
    bucket_t *operator->() { return &boost::get<riak_store_metadata_t>(it->second->store_metadata); };
};

/* The riak_interface_t is class with all the functions needed to implement a
 * riak server, in most cases the calls are obviously isomorphic to requests
 * that can be sent to a server. A notable exception to this is link walking
 * which will make multiple calls to the interface. */

class riak_interface_t {
private:
    //store_manager_t<std::list<std::string> > *store_manager;

    //typedef boost::ptr_map<std::list<std::string>, btree_slice_t> slice_map_t;

    //slice_map_t slice_map;

    //btree_slice_t *get_slice(std::list<std::string>);
    //btree_slice_t *create_slice(std::list<std::string>);
    btree_slice_t *slice;
    std::string bucket; //TODO we may not need this
public:
    riak_interface_t(btree_slice_t *_slice)
        : slice(_slice)
    { }

private:

public:
    // Bucket operations:

    // Get a bucket by name
    //boost::optional<bucket_t> get_bucket(std::string);
    // Set the properties of a bucket
    //void set_bucket(std::string, bucket_t);
    // Get all the buckets
    //std::pair<bucket_iterator_t, bucket_iterator_t> buckets();



    // Object operations:
    
    // Get all the keys in a bucket
    object_iterator_t objects(std::string);
    // Get a single object
    const object_t get_object(std::string, std::pair<int,int> range = std::make_pair(-1, -1));
    // Store an object
    void store_object(object_t);
    // Delete an object
    bool delete_object(std::string);

    // Mapreduce operations:

    //run a mapreduce job
    //std::string mapreduce(json::mValue &) throw(JS::engine_exception);
private:
    //supporting cast for mapreduce just to make this code a bit more readable
    
    //return a vector of objects containing all of the objects linked to be
    //another vector of objects which match the link filter
    std::vector<object_t> follow_links(std::vector<object_t> const &, link_filter_t const &);
    //Apply java script map function to a vector of javascript values
    static std::vector<JS::scoped_js_value_t> js_map(JS::ctx_t &, std::string src, std::vector<JS::scoped_js_value_t>);
    //Apply a java script reduce function to a vector of javascript values
    static JS::scoped_js_value_t js_reduce(JS::ctx_t &, std::string src, std::vector<JS::scoped_js_value_t>);

public:
    //make a key (which is guarunteed to be unique)
    std::string gen_key();

private:
    JS::ctx_group_t ctx_group;

    //used to initialize the field ctx_group with riaks built in mapred
    //functions.
    static void initialize_riak_ctx(JS::ctx_t &);
};

//A few convenience functions for dealing with the javascript engine.

/* We need to hand the object_t to the javascript function is the following format:
 *
 * struct value_t {
 *     string data;
 * };
 *
 * struct input_t {
 *     [value_t] values;
 * };
 */

JS::scoped_js_value_t object_to_jsvalue(JS::ctx_t &, object_t &);


} //namespace riak

#endif
