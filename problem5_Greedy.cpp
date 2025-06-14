#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <limits>
using namespace std;

constexpr  double INF = numeric_limits< double>::max();

struct Road {
   int city1;
   int city2;
   double length;
};

string decimalToBinary(  double n) {
   if (n == 0) return "0";
   string binary;
   while (n > 0) {
       binary = (fmod (n , 2 )== 0 ? "0" : "1") + binary;
       n = floor(n / 2);
   }
   return binary;
}

// Function to find the minimum distances between all pairs of cities using Floyd-Warshall
 double findMinimumDistances(int n, vector<Road> &roads) {
   vector<vector< double>> dist(n + 1, vector< double>(n + 1, INF));

   for (int i = 1; i <= n; ++i) {
       dist[i][i] = 0;
   }

   // Fill the initial distances from roads
   for (auto &[city1, city2, length] : roads) {
       dist[city1][city2] = min(dist[city1][city2], length);
       dist[city2][city1] = min(dist[city2][city1], length); // It's an undirected graph
   }

   // Run Floyd-Warshall to compute shortest paths between all pairs of cities
   for (int k = 1; k <= n; ++k) {
       for (int i = 1; i <= n; ++i) {
           for (int j = 1; j <= n; ++j) {
               // Check for overflow before updating the distance
               if (dist[i][k] != INF && dist[k][j] != INF) {
                   if (dist[i][j] > dist[i][k] + dist[k][j]) {
                       dist[i][j] = dist[i][k] + dist[k][j];
                   }
               }
           }
       }
   }

   // Calculate the total minimum distance by summing all shortest paths
   double totalDistance = 0;
   for (int i = 1; i <= n; ++i) {
       for (int j = i + 1; j <= n; ++j) {
           if (dist[i][j] != INF) {
               totalDistance += dist[i][j];
           }
       }
   }

   return totalDistance;
}

int main() {
   int n, m;
   cin >> n >> m;

   vector<Road> roads(m);
   for (int i = 0; i < m; ++i) {
       int a, b, c;
       cin >> a >> b >> c;
       double C = pow(2, c);
       roads[i] = {a, b, C};
   }

   const  double totalDistance = findMinimumDistances(n, roads);
   string binaryResult = decimalToBinary(totalDistance);
   cout << binaryResult << endl;

   return 0;
}
