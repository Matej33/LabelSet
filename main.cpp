#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <limits>

using namespace std;

long INFINITY = numeric_limits<long>::max();

struct Edge {
    long u, v, c;
};

void LabelSetAlgo(long u, long v, long numOfVertices, const vector<Edge>& allEdges) {
    vector<pair<long, long>> t_x(numOfVertices, {INFINITY, 0});

    vector<vector<pair<long, long>>> neighbors(numOfVertices + 1);
    for (auto& edge : allEdges) {
        neighbors[edge.u].emplace_back(edge.v, edge.c);
    }

    priority_queue<pair<long, long>, vector<pair<long, long>>, greater<>> epsilons;

    t_x[u - 1].first = 0;
    epsilons.emplace(0, u);

    while (!epsilons.empty()) {
        long tr = epsilons.top().first;
        long r = epsilons.top().second;
        epsilons.pop();

        if (tr > t_x[r - 1].first) continue;

        if (r == v) break;

        for (const auto& n : neighbors[r]) {
            long j = n.first;
            long c = n.second;

            long newDist = t_x[r - 1].first + c;

            if (newDist < t_x[j - 1].first) {
                t_x[j - 1].first = newDist;
                t_x[j - 1].second = r;
                epsilons.emplace(newDist, j);
            }
        }
    }

    if (t_x[v - 1].first == INFINITY) {
        cout << "Path does not exist." << endl;
    } else {
        cout << "Shortest distance: " << t_x[v - 1].first << endl;

        vector<long> finalPath;
        for (long i = v; i != 0; i = t_x[i - 1].second) {
            finalPath.push_back(i);
        }
        reverse(finalPath.begin(), finalPath.end());

        cout << "Path:";
        for (long i : finalPath) {
            cout << i << " ";
        }
        cout << endl;
    }
}

int main() {
    string fileName = "../input.hrn";
    ifstream file(fileName);

    if (!file.is_open()) {
        cerr << "Couldn't open file: " << fileName << '\n';
        return 1;
    }

    vector<Edge> allEdges;
    long a, b, c;
    long biggestVertex = 0;

    while (file >> a >> b >> c) {
        if (max(a, b) > biggestVertex) biggestVertex = max(a, b);
        allEdges.push_back({a, b, c});
    }
    file.close();

    long start, end;
    cout << "Enter start vertex: ";
    cin >> start;
    cout << "Enter end vertex: ";
    cin >> end;

    LabelSetAlgo(start, end, biggestVertex, allEdges);

    return 0;
}