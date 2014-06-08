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
        std::list<std::pair<int, int> > edges;
       for ( Sequence fragment : fragments ) {
            std::string srcVertex = fragment.subsequence(0,fragment.getLength()-1).toString();
            std::string destVertex = fragment.subsequence(1,fragment.getLength()-1).toString();
            if(uniqueVertices.count(srcVertex) == 0){
                uniqueVertices[srcVertex]=uniqueVertices.size();
            }
            if(uniqueVertices.count(destVertex) == 0){
                uniqueVertices[destVertex]=uniqueVertices.size();
            }
            edges.push_back(std::make_pair(uniqueVertices[srcVertex],uniqueVertices[destVertex]));
        }
        verticesLabels_.resize(uniqueVertices.size());
        for ( auto tmpVertex : uniqueVertices ){
            verticesLabels_[tmpVertex.second]=tmpVertex.first;
        }

        graph_ = Graph(edges.begin(), edges.end(), verticesLabels_.size());
    }

    std::ostream& operator<<(std::ostream &stream, const DeBrujinGraph & graph){
        boost::write_graphviz(stream, graph.graph_, boost::make_label_writer(&graph.verticesLabels_[0]));
        return stream;
    }

    bool DeBrujinGraph::hasEulerPath(){
        verticesDegrees_.clear();
        verticesDegrees_.resize(boost::num_vertices(graph_), 0);
        boost::graph_traits<Graph>::edge_iterator edgeItr, edgeEndItr;
        for(boost::tie(edgeItr, edgeEndItr) = boost::edges(graph_) ; edgeItr != edgeEndItr ; ++edgeItr){
            ++verticesDegrees_[boost::source(*edgeItr,graph_)];
            --verticesDegrees_[boost::target(*edgeItr,graph_)];
        }
        
        std::vector<int> component(boost::num_vertices(graph_));
        bool a = std::none_of(verticesDegrees_.begin(),verticesDegrees_.end(),[](int degree){ return degree<-1 || degree>1;});
        bool b = std::count(verticesDegrees_.begin(),verticesDegrees_.end(),-1) <= 1;
        bool c = std::count(verticesDegrees_.begin(),verticesDegrees_.end(),1) <= 1;
        int d = connected_components(graph_, boost::make_iterator_property_map(component.begin(), boost::get(boost::vertex_index, graph_)));

        return (a  &&
        b &&
        c 
         );   }

    Sequence DeBrujinGraph::getEulerPath(){
        if (verticesDegrees_.size() != boost::num_vertices(graph_)){
            throw WrongCallException("You should first check if graph has an Eulerian path.");
        }    

        boost::graph_traits<Graph>::vertex_descriptor currentVertex = 
            boost::vertex(std::distance(verticesDegrees_.begin(), std::find(verticesDegrees_.begin(), verticesDegrees_.end(), 1)), graph_);
        
        if(currentVertex==verticesLabels_.size()){
            currentVertex=0;
        }
        std::string outputSequenceString = verticesLabels_[currentVertex];
        

        while(boost::out_degree(currentVertex, graph_) > 0){
            boost::graph_traits<Graph>::out_edge_iterator edgeItr, edgeEndItr;
            for(boost::tie(edgeItr, edgeEndItr) = boost::out_edges(currentVertex, graph_); edgeItr != edgeEndItr ; ++edgeItr){
                std::vector<unsigned long> verticesGroupsIds(num_vertices(graph_), 0);
                strong_components(graph_, boost::make_iterator_property_map(verticesGroupsIds.begin(), get(boost::vertex_index, graph_), verticesGroupsIds[0]));
                if(verticesGroupsIds[currentVertex] == verticesGroupsIds[boost::target(*edgeItr,graph_)]){
                    break;
                }

            }
            if(edgeItr == edgeEndItr) {
                --edgeItr;
            }
            currentVertex = boost::target(*edgeItr, graph_);
            outputSequenceString += verticesLabels_[currentVertex].at(verticesLabels_[currentVertex].size()-1);

            boost::remove_edge(*edgeItr, graph_);
        }
        
        return Sequence(outputSequenceString);
    }

}