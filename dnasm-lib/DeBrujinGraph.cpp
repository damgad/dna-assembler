#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <set>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/graphviz.hpp>
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/strong_components.hpp>

#include "Sequence.h"
#include "DeBrujinGraph.h"
#include "Exceptions.h"

namespace dnasm {
      
    DeBrujinGraph::DeBrujinGraph(const std::list<Sequence> & fragments){
        std::unordered_map<std::string, int> uniqueVertices;
        std::set<std::pair<int, int> > edges;
       for ( Sequence fragment : fragments ) {
            std::string srcVertex = fragment.subsequence(0,fragment.getLength()-1).toString();
            std::string destVertex = fragment.subsequence(1,fragment.getLength()-1).toString();
            if(uniqueVertices.count(srcVertex) == 0){
                uniqueVertices[srcVertex]=uniqueVertices.size();
            }
            if(uniqueVertices.count(destVertex) == 0){
                uniqueVertices[destVertex]=uniqueVertices.size();
            }
            edges.insert(std::make_pair(uniqueVertices[srcVertex],uniqueVertices[destVertex]));
        }
        verticesLabels_.resize(uniqueVertices.size());
        for ( auto tmpVertex : uniqueVertices ){
            verticesLabels_[tmpVertex.second]=tmpVertex.first;
        }

        graph_ = Graph(edges.begin(), edges.end(), verticesLabels_.size());
    }

    std::ostream& operator<<(std::ostream &stream, const DeBrujinGraph & graph){
        std::vector<std::string> vertices = graph.verticesLabels_;

        boost::write_graphviz(stream, graph.graph_, boost::make_label_writer(&vertices[0]));
        return stream;
    }

    bool DeBrujinGraph::hasEulerPath(){

        std::vector<int> degrees(boost::num_vertices(graph_), 0);
        verticesDegrees_ = degrees;
        boost::graph_traits<Graph>::edge_iterator edgeItr, edgeEndItr;
        for(boost::tie(edgeItr, edgeEndItr) = boost::edges(graph_) ; edgeItr != edgeEndItr ; ++edgeItr){
            ++verticesDegrees_[boost::source(*edgeItr,graph_)];
            --verticesDegrees_[boost::target(*edgeItr,graph_)];
        }
        
        std::vector<int> component(boost::num_vertices(graph_));

        int a =connected_components(graph_, boost::make_iterator_property_map(component.begin(), boost::get(boost::vertex_index, graph_)));
        
        return ( std::none_of(degrees.begin(),degrees.end(),[](int degree){ return degree<-1 || degree>1;}) &&
        std::count(degrees.begin(),degrees.end(),-1) <= 1 &&
        std::count(degrees.begin(),degrees.end(),1) <= 1 &&
        connected_components(graph_, boost::make_iterator_property_map(component.begin(), boost::get(boost::vertex_index, graph_))) == 1);
    }

    Sequence DeBrujinGraph::getEulerPath() const{

        throw NotImplementedYetException("Computing Euler path is not implemented yet.");

        if (verticesDegrees_.size() != boost::num_vertices(graph_)){
            throw WrongCallException("You should first check if graph has an Eulerian path.");
        }
        boost::graph_traits<Graph>::vertex_iterator vertexItr, vertexEndItr;
        for(boost::tie(vertexItr, vertexEndItr) = boost::vertices(graph_); vertexItr != vertexEndItr; ++vertexItr){
            if(verticesDegrees_[*vertexItr] == -1){
                //end
            }
            if(verticesDegrees_[*vertexItr] == 1){
                //start
            }
        }
        return Sequence("ALA");
    }

}