/*******************************************************************************
 * Name          : vertex.h
 * Author        : Brian S. Borowski
 * Version       : 1.1
 * Date          : November 17, 2014
 * Last modified : October 16, 2017
 * Description   : Struct for a vertex.
 ******************************************************************************/
#ifndef VERTEX_H_
#define VERTEX_H_

#include "types.h" // anytime it's in quotes, it's your own library
#include <cstdlib> // otherwise use the angle brackets
#include <sstream>
#include <string>

// structs are public by default (everything inside is public)
struct Vertex {
    vertex_id id, predecessor_id;
    uint_t distance;

    // constructor is explicit. because:
    // func(Vertex v)
    // func(12) - first creates a Vertex with a 12 inside, then
    // passes this vertex into the constructor. this is dumb. this
    // is why it should always be explicit
    explicit Vertex() : id{0}, predecessor_id{0}, distance{0} { }

    explicit Vertex(uint_t id) :
        id{id}, predecessor_id{0}, distance{0} { }

    explicit Vertex(uint_t id, uint_t predecessor_id, uint_t distance) :
        id{id}, predecessor_id{predecessor_id}, distance{distance} { }

    std::string to_string() const {
        std::ostringstream oss;
        oss << "[" << id << ", " << distance;
        if (predecessor_id == 0) {
            oss << ", NULL]";
        } else {
            oss << ", " << predecessor_id << "]";
        }
        return oss.str();
    }

    friend std::ostream& operator<<(
                std::ostream &os, const Vertex &vertex) {
        os << vertex.to_string();
        os.flush();
        return os;
    }
};

struct distance_comparator {
    bool operator() (const Vertex *a, const Vertex *b) {
        return a->distance > b->distance;
    }
};

#endif
