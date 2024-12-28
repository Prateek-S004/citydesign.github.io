#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <map>
#include <string>
#include <sstream>

using namespace std;

#define inf INT_MAX / 2

class Dijkstra {
public:
    int V; // Number of vertices
    vector<int> dis, p, vis; // Distance, parent, and visited arrays
    int s, r, cnt = 0; // Source, current vertex, and counter (not used)
    vector<vector<int>> c; // Adjacency matrix (cost matrix)
    map<string, int> n_i; // Map building names to indices
    map<int, string> i_n; // Map indices to building names

    void readFromFile(const string& filename) {
        ifstream file(filename);
        string line;

        while (getline(file, line)) {
            istringstream ss(line);
            string source, destination;
            int weight;

            if (line.empty() || line[0] == '#') continue; 

            getline(ss, source, ',');
            getline(ss, destination, ',');
            ss >> weight;

            if (n_i.find(source) == n_i.end()) {
                n_i[source] = V;
                i_n[V] = source;
                V++;
                c.resize(V);
                for (int j = 0; j < V; ++j) {
                    c[j].resize(V, inf);
                }
            }
            if (n_i.find(destination) == n_i.end()) {
                n_i[destination] = V;
                i_n[V] = destination;
                V++;
                c.resize(V);
                for (int j = 0; j < V; ++j) {
                    c[j].resize(V, inf);
                }
            }

            c[n_i[source]][n_i[destination]] = weight;
            c[n_i[destination]][n_i[source]] = weight; // Assuming undirected graph
        }

        file.close();
    }

    void init() {
        vis.resize(V);
        fill(vis.begin(), vis.end(), 0);

        cout << "Enter the source building: ";
        string source_name;
        cin >> source_name;

        if (n_i.find(source_name) == n_i.end()) {
            cout << "Error: Source building not found." << endl;
            return;
        }

        s = n_i[source_name];
        vis[s] = 1;

        p.resize(V);
        dis.resize(V);

        for (int i = 0; i < V; i++) {
            p[i] = s;
            dis[i] = c[s][i];
        }
        r = s;
    }

    void find_min() {
        int mi = 0;

        for (int i = 0; i < V; i++) {
            if (vis[i] == 0) {
                if (dis[mi] > dis[i]) mi = i;
            }
        }

        r = mi;
        vis[r] = 1;

        for (int i = 0; i < V; i++) {
            if (vis[i] == 0) {
                if (dis[i] > dis[r] + c[r][i] && dis[r] < inf) {
                    p[i] = r;
                    dis[i] = dis[r] + c[r][i];
                }
            }
        }
    }

    void print_path(int x) {
        vector<int> ans;
        ans.push_back(x);
        for (int i = 0; i < V; i++) {
            ans.push_back(p[ans.back()]);
            if (ans.back() == s)
                break;
        }

        for (int i = ans.size() - 1; i > 0; i--) cout << i_n[ans[i]] << "->";
        cout << i_n[ans.front()];

        cout << "\ttotal cost: " << dis[x] << endl;
    }

    void show_reach() {
        cout << "Reachable Buildings from " << i_n[s] << ":\n";
        for (int i = 0; i < V; i++) {
            if (dis[i] != inf) {
                cout << i_n[i] << " (Distance: " << dis[i] << ")\n";
            }
        }
    }
};

int main() {
    Dijkstra d;
    d.readFromFile("city_map.txt");

    d.init();
    for (int i = 0; i < d.V - 1; i++) d.find_min();

    d.show_reach();

    cout << "\nShortest Paths:\n";
    for (int i = 0; i < d.V; i++) {
        if (i != d.s) {
            cout << "To " << d.i_n[i] << ": ";
            d.print_path(i);
        }
    }

    return 0;
}
