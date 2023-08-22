#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#define N 10 // Maximum number of cities

int graph[N][N];
bool visited[N];
int minCost = INT_MAX;
int bestPath[N];
int currentPath[N];
int numCities;

void branchAndBound(int currCity, int depth, int cost) {
    if (depth == numCities) {
        if (cost + graph[currCity][0] < minCost) {
            minCost = cost + graph[currCity][0];
            for (int i = 0; i < numCities; i++) {
                bestPath[i] = currentPath[i];
            }
        }
        return;
    }

    visited[currCity] = true;
    for (int i = 0; i < numCities; i++) {
        if (!visited[i]) {
            currentPath[depth] = i;
            branchAndBound(i, depth + 1, cost + graph[currCity][i]);
        }
    }
    visited[currCity] = false;
}

int main() {
    printf("Enter the number of cities (max %d): ", N);
    scanf("%d", &numCities);

    printf("Enter the cost matrix:\n");
    for (int i = 0; i < numCities; i++) {
        for (int j = 0; j < numCities; j++) {
            scanf("%d", &graph[i][j]);
        }
    }

    currentPath[0] = 0; // Start from the first city
    branchAndBound(0, 1, 0);

    printf("Minimum cost of traveling salesman problem: %d\n", minCost);
    printf("Path taken: ");
    for (int i = 0; i < numCities; i++) {
        printf("%d ", bestPath[i]);
    }
    printf("0\n"); // Return to the starting city
    return 0;
}