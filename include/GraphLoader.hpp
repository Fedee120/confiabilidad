#ifndef GRAPHLOADER_HPP
#define GRAPHLOADER_HPP

#include "graph.hpp"
#include <string>

class GraphLoader {
public:
    static Graph loadGraphFromCSV(const std::string& filepath);
};

#endif // GRAPHLOADER_HPP
