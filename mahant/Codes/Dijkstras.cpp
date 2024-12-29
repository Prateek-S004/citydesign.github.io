// Algorithm: Dijkstra's algorithm
// Need:      Finding shortest path from source node.
// inputs:    Directed graph, where nodes are EV stations and weight is distance between them. Data: city_num.txt
// output:    Dijkstra's algorithm can efficiently determine the shortest paths between charging stations,
//            allowing EV drivers to minimize the time spent traveling between charging stops.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

class Dijkstra{
    public:
        vector<int> V, vis, path;
        vector<float> dist;
        vector<vector<float>> cost_matrix;
        int n = 18, src, relax_e, cnt = 0;
        // compile time initializing number of vertices = 18
        void read_input();
        void initialize();
        void dijistra_algo();
        void display(int x);
};

void Dijkstra::read_input(){
    for(int i = 0 ; i < n ; i++){
        V.push_back(i);
    }

    cost_matrix.resize(n);
    for(int i = 0; i < n; i++){
        vector<float> temp(n);
        fill(temp.begin(), temp.end(), 999.9);
        
        cost_matrix[i] = temp;            
        cost_matrix[i][i] = 0.0;
    }

    ifstream file("city_num.txt");
    if(!file){
        cout << "File not found." << endl;
    }
    int u, v;
    float w;
    while(file >> u >> v >> w){
        cost_matrix[u][v] = w;
    }
    file.close();
}

void Dijkstra::initialize(){
    cout << "Enter source : ";
    cin >> src;

    dist.resize(n);
    for(int i = 0 ; i < n ; i++){
        dist[i] = cost_matrix[src][i];
    }

    path.resize(n);
    for(int i = 0 ; i < n ; i++){
        path[i] = src;
    }

    vis.resize(n);
    for(int i = 0 ; i < n ; i++){
        vis.push_back(0);
    }
    vis[src] = 1;

    relax_e = src;
}

void Dijkstra::dijistra_algo(){
    int min_dist_index = 0;
    for(int i = 1 ; i < n ; i++){
        if(vis[i] == 0){
            if(dist[min_dist_index] > dist[i]){
                min_dist_index = i;
            }
        }
    }

    relax_e = min_dist_index;
    vis[relax_e] = 1;

    for(int i = 0; i < n ; i++){
        if(vis[i] == 0){
            // dist[not visited] = min(dist[not visited], dist[relaxed edge] + cost_matrix[relaxed edge][not visited])
            if(dist[i] > dist[relax_e] + cost_matrix[relax_e][i] && dist[relax_e] < 999.9){
                path[i] = relax_e;
                dist[i] = dist[relax_e] + cost_matrix[relax_e][i];
            }
        }
    }
}

void Dijkstra::display(int x){
    vector<int> ans;
    ans.push_back(x);

    for(int i = 0; i < n; i++){
        ans.push_back(path[ans.back()]);
        if(ans.back() == src)
        break;
    }
    for(int i = ans.size() - 1; i > 0; i--){
        cout << ans[i] << "->";
    }
    cout << ans.front();
    
    cout << "\ttotal cost: " << dist[x];
    cout << endl;
}

int main(){
    Dijkstra D;
    D.read_input();
    D.initialize();

    for(int i = 0; i < D.n ; i++){
        D.dijistra_algo();
    }

    for(int i = 0; i < D.n ; i++ ){
        D.display(i);
    }
    return 0;
}
