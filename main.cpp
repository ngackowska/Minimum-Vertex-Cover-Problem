#include <iostream>
#include <vector>
#include <chrono>
#include <random>

#include "nlohmann/json.hpp"

#include "generateGraph.h"
#include "json.h"

#include "bruteForce.h"
#include "aproksymacyjny.h"
#include "genetic.h"

using json = nlohmann::json;


int main() {
    int n = 5;          // number of nodes
    double p = 0.4;     // graph density
    
    bool must_have_nodes = true;
    std::vector<int> must_nodes;


    // -------- creating adjacency matrix -------- //

    std::vector<std::vector<int>> adj_matrix;
    adj_matrix.resize(n);
    for (int i = 0; i < adj_matrix.size(); i++) {
        adj_matrix[i].resize(n);
    }

    // -------- generating graph -------- //

    std::random_device rd{};
    std::mt19937 generator{rd()};

    generateErdosRenyiGraph(n, p, adj_matrix, generator);

    must_nodes = generateMustHaveNodes(n, generator);


    // -------- saving graph to JSON -------- //


    saveAdjToJSON(adj_matrix, n, must_have_nodes, must_nodes);


    // -------- reading graph from JSON -------- //

    json data = readJSON("graph.json");

    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++) {
            adj_matrix[i][j] = (int)data[std::to_string(i)][j];
        }
    }

    must_nodes.clear();

    for (int i = 0; i < (int)data["-1"].size(); i++) {
        must_nodes.push_back((int)data["-1"][i]);
    }

    
    // ---- BRUTE FORCE --- ///

    std::cout << "\n";
    auto begin = std::chrono::high_resolution_clock::now();    

    std::vector<int> minCover = bruteForce(adj_matrix, n, must_have_nodes, must_nodes);

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " microseconds" << std::endl;

    std::cout << "\nCover from brute:\n";
    for (int i = 0; i < minCover.size(); i++) {
        std::cout << minCover[i] << " ";
    }


    // ---- APROKSYMACYJNY --- //
    
    std::vector<std::vector<int>> adj_matrix_copy;
    adj_matrix_copy.resize(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            adj_matrix_copy[i].push_back(adj_matrix[i][j]);
        }
    }

    std::cout << "\n";
    begin = std::chrono::high_resolution_clock::now();  

    std::vector<int> minCover2 = approximate(adj_matrix_copy, n, must_have_nodes, must_nodes);

    end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " microseconds" << std::endl;


    std::cout << "\nCover from approx:\n";
    for (int i = 0; i < minCover2.size(); i++) {
        std::cout << minCover2[i] << " ";
    }


    // ---- GENETYCZNY --- //

    std::cout << "\n";
    begin = std::chrono::high_resolution_clock::now();  

    std::vector<int> minCover3 = genetic(adj_matrix, n, must_have_nodes, must_nodes);

    end = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(end-begin).count() << " microseconds" << std::endl;


    std::cout << "\nCover from genetic:\n";
    for (int i = 0; i < minCover3.size(); i++) {
        std::cout << minCover3[i] << " ";
    }


    std::vector<std::vector<int>> covers;
    covers.push_back(minCover);
    covers.push_back(minCover2);
    covers.push_back(minCover3);

    std::vector<std::string> names = {"brute_force", "aproksymacyjny", "genetyczny"};

    saveCover(covers, names);

    return 0;
}
