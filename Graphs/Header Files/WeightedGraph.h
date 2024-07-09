//
//  WeightedWeightedGraph.h
//  Practice
//   S really this will print out the vertex, weight, accoridnlgy using ASCII Art 
//  Created by Gunnar Beck on 7/9/24.
//

#ifndef GRAPH_PRINTER_H
#define GRAPH_PRINTER_H

#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include <string>
#include <unordered_map>
#include <utility> // For std::pair
#include <sstream> // For std::stringstream

using namespace std;

class WeightedGraph {
public:
    void printGraph(const vector<list<pair<int, int>>>& adj) const {
        cout << "Graph adjacency list:" << endl;
        for (int v = 0; v < adj.size(); ++v) {
            cout << v << " -> ";
            for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
                cout << "(" << it->first << ", " << it->second << ") ";
            }
            cout << endl;
        }
        cout << endl;

        cout << "Graph edges using ASCII art:" << endl;
        renderGraph(adj);
    }

private:
    void renderGraph(const vector<list<pair<int, int>>>& adj) const {
        const int RADIUS = 10;
        const int DIAMETER = 2 * RADIUS + 1;
        vector<string> graphLines(DIAMETER, string(DIAMETER * 2, ' '));
        int size = adj.size();

        unordered_map<int, pair<int, int>> positions;
        for (int i = 0; i < size; ++i) {
            double angle = 2.0 * M_PI * i / size;
            int x = RADIUS + static_cast<int>(RADIUS * cos(angle));
            int y = RADIUS + static_cast<int>(RADIUS * sin(angle));
            positions[i] = {x, y};
        }

        for (int v = 0; v < size; ++v) {
            auto [x, y] = positions[v];
            graphLines[y][x * 2] = 'O';
            graphLines[y][x * 2 + 1] = '0' + v;
        }

        for (int v = 0; v < size; ++v) {
            for (auto [w, weight] : adj[v]) {
                drawArrow(graphLines, positions[v], positions[w], weight);
            }
        }

        for (const auto& line : graphLines) {
            cout << line << endl;
        }
    }

    void drawArrow(vector<string>& graphLines, pair<int, int> from, pair<int, int> to, int weight) const {
        int x1 = from.first, y1 = from.second;
        int x2 = to.first, y2 = to.second;

        int dx = abs(x2 - x1), dy = abs(y2 - y1);
        int sx = x1 < x2 ? 1 : -1;
        int sy = y1 < y2 ? 1 : -1;
        int err = dx - dy;

        while (true) {
            if (x1 == x2 && y1 == y2) break;
            int e2 = err * 2;
            if (e2 > -dy) {
                err -= dy;
                x1 += sx;
            }
            if (e2 < dx) {
                err += dx;
                y1 += sy;
            }
            if (x1 != x2 || y1 != y2) graphLines[y1][x1 * 2] = '-';
        }
        graphLines[y2][x2 * 2] = '>';
        placeWeight(graphLines, from, to, weight);
    }

    void placeWeight(vector<string>& graphLines, pair<int, int> from, pair<int, int> to, int weight) const {
        int x1 = from.first, y1 = from.second;
        int x2 = to.first, y2 = to.second;
        int mx = (x1 + x2) / 2;
        int my = (y1 + y2) / 2;
        stringstream ss;
        ss << weight;
        string weightStr = ss.str();
        for (int i = 0; i < weightStr.size(); ++i) {
            graphLines[my][mx * 2 + i] = weightStr[i];
        }
    }
};

#endif // GRAPH_PRINTER_H
