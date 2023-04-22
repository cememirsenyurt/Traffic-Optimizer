// Digraph.hpp
//
// ICS 46 Winter 2022
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <queue>
#include <iostream>

// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.


template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the predecessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // typename std::map<int,DigraphVertex<VertexInfo,EdgeInfo>>possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> map;
    unsigned int vertexNumber;
    unsigned int edgeNumber;

public:
    bool DFTr(int vertex, std::vector<int> visitedVertex) const;
};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
    : vertexNumber{0}, edgeNumber{0}
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
    : map{d.map}, vertexNumber{d.vertexNumber}, edgeNumber{d.edgeNumber}
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
    : vertexNumber{0}, edgeNumber{0}
{
    std::swap(map, d.map);
    std::swap(vertexNumber, d.vertexNumber);
    std::swap(edgeNumber, d.edgeNumber);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
    for(auto it = map.begin(); it != map.end(); ++it)
    {
        it->second.edges.clear();
    }
    vertexNumber = 0;
    edgeNumber = 0;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    if(this != &d)
    {
        map = d.map;
        vertexNumber = d.vertexNumber;
        edgeNumber = d.edgeNumber;
    }
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    std::swap(map, d.map);
    std::swap(vertexNumber, d.vertexNumber);
    std::swap(edgeNumber, d.edgeNumber);
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> verticiesVector;

    for(auto it = map.begin(); it != map.end(); ++it)
    {
        verticiesVector.push_back(it->first);
    }   
    
    return verticiesVector;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> edgesVector;

    for(auto it1 = map.begin(); it1 != map.end(); ++it1)
    {
        for(auto it2 = it1->second.edges.begin(); it2 != it1->second.edges.end(); ++it2)
        {
            std::pair<int, int> fromToPair;
            fromToPair = std::make_pair(it2->fromVertex, it2->toVertex);
            edgesVector.push_back(fromToPair);
        }
    }

    return edgesVector;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    //return std::vector<std::pair<int, int>>{};
    std::vector<std::pair<int, int>> directedEdges;
    
    if(map.count(vertex) == 0)
    {
        throw DigraphException("No appropriate vertex found!");
    }
    else
    {
        for(auto it1 = map.begin(); it1 != map.end(); ++it1)
        {
            if(it1->first != vertex)
            {
                continue;
            }
            else
            {
                for(auto it2 = it1->second.edges.begin(); it2 != it1->second.edges.end(); it2++)
                {
                    std::pair<int, int> withoutFromToPair;
                    withoutFromToPair = std::make_pair(vertex, it2->toVertex);
        
                    directedEdges.push_back(withoutFromToPair);
                }
            } 
        }
    }
    return directedEdges;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    if(map.count(vertex) == 0)
    {
        throw DigraphException("No appropriate vertex found!");
    }
    else
    {
        return map.at(vertex).vinfo;
    }
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    EdgeInfo returnEdgeInfo;
    
    if (map.count(fromVertex) == 0 ||  map.count(toVertex) == 0)
    {
        throw DigraphException("No appropriate vertex have found!");
    }    
    else
    {
        std::pair<int,int> ourVerticies;
        ourVerticies = std::make_pair(fromVertex, toVertex);

        std::vector<std::pair<int,int>> edgeVector = edges(fromVertex);
        
        if(std::find(edgeVector.begin(), edgeVector.end(), ourVerticies) == edgeVector.end())
        {
            throw DigraphException("There is no edge between them!");
        }

        for(auto it = map.at(fromVertex).edges.begin(); it != map.at(fromVertex).edges.end(); it++)
        {
            if(it->toVertex == toVertex)
            {
                returnEdgeInfo = it->einfo;
            }
        }
    }

    return returnEdgeInfo;
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    if (map.count(vertex) > 0)
    {
        throw DigraphException("This vertex is already in the graph!");
    }  
    else
    {
        DigraphVertex<VertexInfo, EdgeInfo> newVertex{vinfo};

        std::pair<int, DigraphVertex<VertexInfo, EdgeInfo>> newPair;
        newPair = std::make_pair(vertex, newVertex);
        map.insert(newPair);
    }
    vertexNumber++;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    if(map.count(fromVertex) == 0 || map.count(toVertex) == 0) 
    {
        throw DigraphException("Given verticies are not exist!");
    }
    else 
    {
        std::pair<int,int> ourVerticies;
        ourVerticies = std::make_pair(fromVertex, toVertex);
        
        std::vector<std::pair<int,int>> edgeVector = edges(fromVertex);

        if(std::find(edgeVector.begin(), edgeVector.end(), ourVerticies) != edgeVector.end())    
        {
            throw DigraphException("Edge is already in the graph");
        }
    }
    map.at(fromVertex).edges.push_back(DigraphEdge<EdgeInfo>{fromVertex,toVertex,einfo});
    edgeNumber++;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    if(map.count(vertex) == 0)
    {
        throw DigraphException("This vertex does not exist in map!");
    }

    for(auto it1 = map.begin(); it1 != map.end(); ++it1)
    {
        if(it1->first != vertex)
        {
            continue;
        }
        else
        {
            for(auto it2 = it1->second.edges.begin(); it2 != it1->second.edges.end(); it2++)
            {
                it1->second.edges.erase(it2);
            }
        }
    }
    map.erase(vertex);
    vertexNumber--;
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    if(map.count(fromVertex) == 0 || map.count(toVertex) == 0)
    {
        throw DigraphException("Either fromVertex, or toVertex does not exist in graph!");
    }
    else
    {
        std::pair<int,int> ourVerticies;
        ourVerticies = std::make_pair(fromVertex, toVertex);

        std::vector<std::pair<int,int>> edgeVector = edges(fromVertex);

        if(std::find(edgeVector.begin(), edgeVector.end(), ourVerticies) == edgeVector.end())
        {
            throw DigraphException("Edge does not exist in the graph");
        }
    }
        for(auto it = map.at(fromVertex).edges.begin(); it != map.at(fromVertex).edges.end(); it++)
        {
            if(it->toVertex == toVertex)
            {
                map.at(fromVertex).edges.erase(it);
                break;
            }
            else
            {

            }
        } 
        
    edgeNumber--;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return vertexNumber;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    return edgeNumber;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    int counter = 0;
    
    if(map.count(vertex) == 0)
    {
        throw DigraphException("The vertex is not valid!");
    }
    else
    {
        for(auto it = map.at(vertex).edges.begin(); it != map.at(vertex).edges.end(); ++it)
        {
            counter++;
        }
    }
    return counter;

}

template<typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::DFTr(int vertex, std::vector<int> visitedVertex) const
{
    for(auto it = map.at(vertex).edges.begin(); it != map.at(vertex).edges.end(); ++it)
    {
        if (std::find(visitedVertex.begin(), visitedVertex.end(), it->toVertex) == visitedVertex.end())
        {
           visitedVertex.push_back(it->toVertex);
        }
        else
        {
            vertex = it->toVertex;
            DFTr(vertex, visitedVertex);
        }
    }
    if(visitedVertex.size() == vertexNumber)
    {
       return true; 
    }
    else
    {
        return false;
    }
}

template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    bool x;
    std::vector<int> visitedVector;

    for(auto it = map.begin(); it != map.end(); ++it)
    {
        x = DFTr(it->first, visitedVector);
    }
    return x;
}

template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{ 
    std::map<int, bool> k;
    std::map<int, int> d;
    std::vector<int> predecessor;
    double inf = 9999999999;

    for(auto it = map.begin(); it != map.end(); ++it)
    {
        k[it->first] = false;
        d[it->first] = inf;
    }

    d[startVertex] = 0;
    predecessor.push_back(startVertex);
     
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push(std::make_pair(startVertex, 0));
 
    while(!pq.empty())
    {
        int minVertex = pq.top().first;
        pq.pop();

        if(k[minVertex] == false)
        {
            k[minVertex] = true;
            
            for(auto it = map.at(minVertex).edges.begin(); it != map.at(minVertex).edges.end(); ++it)
            {
                if(d[it->toVertex] < d[minVertex] + edgeWeightFunc(it->einfo))
                {
                    d[it->toVertex] = d[minVertex] + edgeWeightFunc(it->einfo);
                    predecessor.push_back(minVertex);
  
                    pq.push(std::make_pair(it->toVertex, d[it->toVertex]));
                }
            }
        }
    }
    
    std::map<int, int> returnValue;
    int j = 0;

    for(auto i = d.begin(); i != d.end(); ++i)
    {
        returnValue[i->first] = predecessor[j];
        j++;
    }

    return returnValue;
}

#endif
