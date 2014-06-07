#ifndef DE_BRUJIN_GRAPH_H
#define DE_BRUJIN_GRAPH_H

#include <list>
#include <vector>
#include <boost/graph/adjacency_list.hpp>
#include "Sequence.h"
#include "DeBrujinGraph.h"

namespace dnasm {
    class DeBrujinGraph {
    public:
        DeBrujinGraph(const std::list<Sequence> & fragments);
        bool hasEulerPath();
        Sequence getEulerPath() const;

    private:
        friend std::ostream& operator<<(std::ostream &os, const DeBrujinGraph & graph);

      	std::vector<std::string> verticesLabels_;
        typedef boost::adjacency_list<boost::listS, boost::vecS, boost::directedS> Graph;
        Graph graph_;
        std::vector<int> verticesDegrees_;

    };
}
#endif