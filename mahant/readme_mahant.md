use case 1: Smart EV stations

Algorithm: [Dijkstra's algorithm](Codes/Dijkstras.cpp)
Need: Finding shortest path from source node.
inputs: Directed graph, where nodes are EV stations and weight is distance between them. Data: [city_num.txt](Codes/city_num.txt)
output: Dijkstra's algorithm can efficiently determine the shortest paths between charging stations, 
        allowing EV drivers to minimize the time spent traveling between charging stops.

use case 2: Security in Airports and Harbor

Algorithm: [BFSS(Brute Force String Search)](Codes/BFSS.cpp)
Need: Checking if individual's PAN number is Valid or not.
assumption: We assume there are 200 PAN numbers which are valid, open [PAN_num.txt](Codes/PAN_num.txt) for all 200 numbers.
inputs: PAN number, whose format is AAAAANNNNA (A - alphabet A to Z, N - number 0 to 9).
output: Apply BFSS and check whether PAN number matches with the contents of [PAN_num.txt](Codes/PAN_num.txt)

use case 3: Network Tower Deployment

Algorithm: [Kruskal's algorithm](Codes/Kruskals.spp)
Need: Proper placing of network tower infrastruct for high speed connectivity.
assumption: Coverage of Network tower is 3 - 12 kms of radius.
inputs: Undirected Graph, where nodes are position of towers and weights represent distance between them.
output: MST(minimum spanning tree). Data: [city_area.txt](Code/city_area.txt)
