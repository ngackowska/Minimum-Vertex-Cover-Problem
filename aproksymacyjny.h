#include <vector>

int checkCover(std::vector<std::vector<int>> &adj_matrix, int n) {

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (adj_matrix[i][j] != 0) {
                return 1;
            }
        }
    }

    return 0;

}

std::vector<int> approximate(std::vector<std::vector<int>> &adj_matrix, int n, bool must_have_nodes, std::vector<int> must_nodes) {
    std::vector<bool> visited(n, false);    // vector for checking if given vertice was already visited
    std::vector<int> minimalCover;

    // if there are vertices that have to be in the cover -> delete edges for them first
    if (must_have_nodes) {
        for (int must = 0; must < must_nodes.size(); must++) {
            if (!visited[must_nodes[must]]) {
                visited[must_nodes[must]] = true;
                minimalCover.push_back(must_nodes[must]);

                for (int v = 0; v < n; v++) {
                    if (adj_matrix[must_nodes[must]][v] == 1 && !visited[v]) {
                        visited[v] = true;
                        minimalCover.push_back(v);

                        for (int j = 0; j < n; j++) {
                            adj_matrix[must_nodes[must]][j] = 0;
                            adj_matrix[v][j] = 0;
                            adj_matrix[j][must_nodes[must]] = 0;
                            adj_matrix[j][v] = 0;
                        }

                        if (!checkCover(adj_matrix, n)) {
                            return minimalCover;
                        }
                    }
                }
            }
        }
    }

    for (int u = 0; u < n; u++) {
        if (!visited[u]) {
            visited[u] = true;
            minimalCover.push_back(u);

            for (int v = 0; v < n; v++) {
                if (adj_matrix[u][v] == 1 && !visited[v]) {
                    visited[v] = true;
                    minimalCover.push_back(v);

                    for (int j = 0; j < n; j++) {
                        adj_matrix[u][j] = 0;
                        adj_matrix[v][j] = 0;
                        adj_matrix[j][u] = 0;
                        adj_matrix[j][v] = 0;
                    }

                    if (!checkCover(adj_matrix, n)) {
                        return minimalCover;
                    }
                }
            }
        }
    }
}

