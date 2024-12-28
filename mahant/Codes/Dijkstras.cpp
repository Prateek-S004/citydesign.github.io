#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <vector>
#include <cctype>
#include <string>
#include <algorithm>
using namespace std;

class Dijistras{
    public:
        vector<int> V, vis, dist, path;
        vector<vector<int>> cost_matrix;
        int n, src, relax_e, cnt = 0;

        void read_input();
        void initialize();
        void dijistra_algo();
        void display(int x);


};

void Dijistras::read_input(){
    cout << "Enter number of vertices : ";
    cin >> n;
    for(int i = 0 ; i < n ; i++){
        V.push_back(i);
    }
    cost_matrix.resize(n, vector<int>(n));
    cout << "Enter the cost matrix : " << endl;
    for(int i = 0 ; i < n ; i++){
        for(int j = 0 ; j < n ; j++){
            cin >> cost_matrix[i][j];
        }
    }
}

void Dijistras::initialize(){
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

void Dijistras::dijistra_algo(){
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
            if(dist[i] > dist[relax_e] + cost_matrix[relax_e][i] && dist[relax_e] < 999){
                path[i] = relax_e;
                dist[i] = dist[relax_e] + cost_matrix[relax_e][i];
            }
        }
    }
}

void Dijistras::display(int x){
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
    Dijistras D;
    D.read_input();
    D.initialize();

    for(int i = 0; i < D.n - 1; i++){
        D.dijistra_algo();
    }

    for(int i = 0; i < D.n - 1; i++ ){
        D.display(i);
    }
    return 0;
}
