# Traffic-Optimizer
"Finding the Fastest Route"

The project aimed to create a program that finds the shortest distance or driving time between two locations on a street map, optimized not only for distance but also for the shortest driving time given the current traffic conditions.

Introduction
Living in Southern California means facing the reality of having to deal with heavy traffic. Fortunately, with technology, we have easy access to information that can help. The program's main job is to discover the shortest distance or driving time between two locations. The map consists of any kind of road that a car can pass over, such as streets or freeways.

To keep the problem relatively simple, absolute directions (i.e., north, south, east, and west) are not considered by the program or reported in its output. A trip is a sequence of visits to locations on the map, and the program outputs information about the distance in miles and (sometimes) driving time of each of the segments of the trip, as well as the overall distance and (sometimes) driving time for the whole trip.

Implementation
The project utilizes a directed graph to represent the locations on the map as vertices and the stretches of road connecting locations as edges. Each stretch of road contains two pieces of information: its length in miles and the current speed of traffic traveling on it in miles per hour.

The program uses Dijkstra's algorithm, a well-known algorithm for finding the shortest path between two nodes in a graph, to calculate the shortest distance or driving time between two locations.

Conclusion
The program provides a convenient way to find the shortest distance or driving time between two locations on a street map. The use of directed graphs and Dijkstra's algorithm made the implementation of the program relatively straightforward.
