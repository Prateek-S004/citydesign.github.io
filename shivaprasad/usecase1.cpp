#include <bits/stdc++.h>
using namespace std;

#define INF INT_MAX / 2

class Dijkstra {
public:
    int vertices;
    vector<int> dist, path, vis;
    int src, dest;
    vector<vector<int>> cost;
    vector<vector<int>> lookup;

    void read(const string &filename) {
        cost.resize(vertices, vector<int>(vertices, INF));
        lookup.resize(vertices, vector<int>(vertices, INF));
        for (int i = 0; i < vertices; i++) {
            cost[i][i] = 0;
        }

        ifstream file(filename);
        int u, v;
        double w;
        while (file >> u >> v >> w) {
            cost[u-1][v-1] = w;
            cost[v-1][u-1] = w;
        }
    }

    void init() {
        vis.resize(vertices, 0);
        dist.resize(vertices, INF);
        path.resize(vertices);
    }

    void shortest_path() {
        if (lookup[src][dest] != INF) {
            cout << "Path already calculated. Using lookup table.\n";
            print_path_from_lookup();
            return;
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, src});
        dist[src] = 0;
        path[src] = src;

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            for (int v = 0; v < vertices; v++) {
                if (cost[u][v] != INF && dist[v] > dist[u] + cost[u][v]) {
                    dist[v] = dist[u] + cost[u][v];
                    path[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        lookup[src][dest] = dist[dest];
    }

    void print_path_from_lookup() {
        vector<int> route;
        int node = dest;
        while (node != src) {
            route.push_back(node + 1);
            node = path[node];
        }
        route.push_back(src + 1);

        cout << "Path: ";
        for (int i = route.size() - 1; i >= 0; i--) {
            cout << route[i];
            if (i > 0) cout << " -> ";
        }

        cout << "\nTotal distance: " << lookup[src][dest] << " km\n";
        double costAmount = lookup[src][dest] * 2.5;
        cout << "Total cost: " << costAmount << " RS\n";
        double avgSpeed = 80.0;
        double timeWithoutTraffic = lookup[src][dest] / avgSpeed;
        double timeWithTraffic = timeWithoutTraffic + (rand() % 5 + 1) * (route.size() - 1) / 60.0;

        cout << "Estimated time without traffic: " << timeWithoutTraffic * 60 << " minutes\n";
        cout << "Estimated time with traffic: " << timeWithTraffic * 60 << " minutes\n";
    }

    void print_path() {
        vector<int> route;
        int node = dest;
        while (node != src) {
            route.push_back(node + 1);
            node = path[node];
        }
        route.push_back(src + 1);

        cout << "Path: ";
        for (int i = route.size() - 1; i >= 0; i--) {
            cout << route[i];
            if (i > 0) cout << " -> ";
        }

        cout << "\nTotal distance: " << dist[dest] << " km\n";
        double costAmount = dist[dest] * 2.5;
        cout << "Total cost: " << costAmount << " RS\n";
        double avgSpeed = 80.0;
        double timeWithoutTraffic = dist[dest] / avgSpeed;
        double timeWithTraffic = timeWithoutTraffic + (rand() % 5 + 1) * (route.size() - 1) / 60.0;

        cout << "Estimated time without traffic: " << timeWithoutTraffic * 60 << " minutes\n";
        cout << "Estimated time with traffic: " << timeWithTraffic * 60 << " minutes\n";
    }

    void handle_queries() {
        char choice;
        do {
            cout << "Enter the source station (1-based index): ";
            cin >> src;
            cout << "Enter the destination station (1-based index): ";
            cin >> dest;

            src--;
            dest--;

            dist.assign(vertices, INF);
            fill(vis.begin(), vis.end(), 0);

            shortest_path();
            if (lookup[src][dest] != INF) {
                print_path_from_lookup();
            } else {
                print_path();
            }

            cout << "Do you want to continue? (c to continue, e to exit): ";
            cin >> choice;
        } while (choice == 'c' || choice == 'C');
    }
};

int main() {
    //ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
    srand(time(0));

    Dijkstra d;
    // cout << "Enter the number of vertices (stations): ";
    // cin >> d.vertices;
    d.vertices = 19;

    string filename = "edges.txt";
    d.read(filename);

    d.init();
    d.handle_queries();

    return 0;
}
