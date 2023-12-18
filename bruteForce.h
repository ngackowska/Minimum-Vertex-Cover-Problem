#include <cmath>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> generateSubsets(int n) {
    std::vector<int> vertices;
    for (int i = 0; i < n; i++) {
        vertices.push_back(i);
    }

    int subsetsCount = pow(2,n);
    std::vector<std::vector<int>> subsets;

    subsets.resize(subsetsCount);
    for (int i = 0; i < (1 << n); i++) {
        subsets[i].resize(n);
        for (int j = 0; j < n; j++) {
            if ((i & (1 << j)) != 0) {
                subsets[i][j] = vertices[j];
            } else {
                subsets[i][j] = -1;
            }
        }

    }

    return subsets;
}


int checkCover(std::vector<std::vector<int>> &adj_matrix, std::vector<std::vector<int>> &subsetMatrix, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj_matrix[i][j] != subsetMatrix[i][j]) {
                return 1;
            }
        }
    }

    return 0;
}


std::vector<std::vector<int>> changeSubsets(std::vector<std::vector<int>> subsets, std::vector<int> must_nodes) {
    std::vector<std::vector<int>> new_subsets;

    bool theyAre;
    for (int subset = 0; subset < subsets.size(); subset++) {
        bool theyAre = true;
        for (int must = 0; must < must_nodes.size(); must++) {
            if (std::find(subsets[subset].begin(), subsets[subset].end(), must_nodes[must]) == subsets[subset].end()) {
                theyAre = false;
                break;
            }
        }
        if (theyAre) {
            new_subsets.push_back(subsets[subset]);
        }   
    }

    return new_subsets;
}


std::vector<int> bruteForce(std::vector<std::vector<int>> &adj_matrix, int n, bool must_have_nodes, std::vector<int> must_nodes) {

    std::vector<std::vector<int>> subsets;
    subsets = generateSubsets(n);

    if (must_have_nodes) {      // if there are vertices that have to be in the vertex cover
        subsets = changeSubsets(subsets, must_nodes);
    }

    // seting all vertices as minimal vertex cover
    std::vector<int> minimalCover;
    for (int i = 0; i < n; i++) {
        minimalCover.push_back(i);
    }

    int verticesCount = 0;

    // iterating through subsets
    for (int subset = 1; subset < subsets.size()-1; subset++) {
        std::vector<std::vector<int>> subsetMatrix;
        subsetMatrix.resize(n);
        for (int v = 0; v < n; v++) {
            subsetMatrix[v].resize(n);
        }

        // iterating through vertices
        for (int v = 0; v < n; v++) {
            
            if (subsets[subset][v] != -1) {  
                 verticesCount++;
                for (int x = 0; x < n; x++) {
                    int val = adj_matrix[v][x];
                    subsetMatrix[v][x] = val;
                    subsetMatrix[x][v] = val;
                }
            }
        }

        // checking if this subset is a vertex cover
        if (checkCover(adj_matrix, subsetMatrix, n) == 0) {
            if (verticesCount < minimalCover.size()) {                  
                minimalCover.clear();
                for (int x = 0; x < subsets[subset].size(); x++) {
                    if (subsets[subset][x] != -1) {
                        minimalCover.push_back(subsets[subset][x]);
                    }
                }
            }
        }

        verticesCount = 0;
    }

    return minimalCover;
}