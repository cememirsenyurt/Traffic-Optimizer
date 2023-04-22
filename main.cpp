// main.cpp
//
// ICS 46 Winter 2022
// Project #5: Rock and Roll Stops the Traffic
//
// This is the program's main() function, which is the entry point for your
// console user interface.
#include <iostream>
#include <string>
#include "InputReader.hpp"
#include "RoadMapReader.hpp"
#include "RoadMapWriter.hpp"
#include "RoadSegment.hpp"
#include "TripMetric.hpp"
#include "Trip.hpp"
#include "TripReader.hpp"
#include "Digraph.hpp"

struct properties
{
    int vertex;
    std::string name;
    RoadSegment information;
};

int main()
{
    InputReader inR = InputReader(std::cin);    //readLine() // readIntLine()
    RoadMapReader rM;                           // knows how to read RoadMap
    RoadMap roadMap = rM.readRoadMap(inR);;     // <name, RoadSegment>
    //RoadSegment travel;
    std::vector<Trip> trip;                     // start Vertex, endVertex, metric
    TripReader tR;
    trip = tR.readTrips(inR);                   //read the trip
    
    std::map<int, int> dijkstraMap;
    for(auto iter = trip.begin(); iter != trip.end(); ++iter)
    {
        std::vector<properties> roadTripVector;
        
        if(iter->metric == TripMetric::Time)
        {
            dijkstraMap = roadMap.findShortestPaths(iter->startVertex, [](RoadSegment roadSegment){return roadSegment.milesPerHour/ roadSegment.miles;});
        }
        else
        {
            dijkstraMap = roadMap.findShortestPaths(iter->startVertex, [](RoadSegment roadSegment){return roadSegment.miles;});
        }

        int last = iter->endVertex;
        properties end = properties{last, roadMap.vertexInfo(last), roadMap.edgeInfo(dijkstraMap[last], last)};
        roadTripVector.push_back(end);
        double distance = end.information.miles;
        
        while(last != iter->startVertex)
        {
            int temp = last;
            last = dijkstraMap[last];
            roadTripVector.push_back(properties{last, roadMap.vertexInfo(last), roadMap.edgeInfo(last, temp)});
                        
            if (last != iter->startVertex)
            {
                distance += roadMap.edgeInfo(last, temp).miles;
            }
        }

        if (iter->metric == TripMetric::Time)
        {
            std::cout << "Shortest driving time from " << roadMap.vertexInfo(roadTripVector.back().vertex)<< 
                " to " << roadMap.vertexInfo(roadTripVector.front().vertex)<<std::endl;
        }
        else
        {
            std::cout << "Shortest distance from "<< roadMap.vertexInfo(roadTripVector.back().vertex)<<
                " to "<<roadMap.vertexInfo(roadTripVector.front().vertex)<<std::endl;
        }
    }

    return 0;
}

