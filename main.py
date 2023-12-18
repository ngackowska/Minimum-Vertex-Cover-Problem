import networkx as nx
import matplotlib.pyplot as plt
from networkx.readwrite import json_graph
import scipy as sp
import numpy as np
import json
import random
import math

must_have_nodes = True
n = 5
p = 0.4

# Creating random graph #####################

# G= nx.erdos_renyi_graph(n, p)

# A = nx.adjacency_matrix(G)
# data = A.todense().tolist()


# to JSON ##################################

# data_dict = {}

# if (must_have_nodes):
#     must_nodes = []
#     must_nodes_count = random.randint(1, int(math.ceil(0.2*n)))
#     for i in range(must_nodes_count+1):
#         random_node = random.randint(0,n)
#         while (random_node in must_nodes):
#             random_node = random.randint(0,n)
#         must_nodes.append(random_node)

#     data_dict[-1] = must_nodes


# for i in range(len(data)):
#     data_dict[i] = data[i]



# with open('graph_test.json', 'w', encoding='utf-8') as f:
#     json.dump(data_dict, f, ensure_ascii=False, indent=4)



# Opening JSON file (loading graph) #########################

with open('graph.json') as f:
    data = json.load(f)

must_nodes = data['-1']
del data['-1']

# Opening JSON file for covers #########################
with open('covers.json') as f:
    data_covers = json.load(f)

cover = data_covers['genetyczny']  # picking algorithm (aproksymacyjny, brute_force, genetyczny)

# print(data)

# Graph ########################
G = nx.Graph()

color_map = []

for i in data:
    print(i)
    if int(i) in cover:
        if int(i) in must_nodes:
            color_map.append("red")
        else:
            color_map.append("green")
    else:
        color_map.append("gray")

    G.add_node(i)

for i in data:
    for j in range(int(i),len(data[i])):
        if data[i][j] == 1:
            G.add_edge(i,str(j))


# Showing graph #####################
nx.draw(G, with_labels=True, node_color=color_map)
plt.show()
