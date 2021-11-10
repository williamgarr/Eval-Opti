#!/usr/bin/python

# complete_graph(n[, create_using])
# cycle_graph(n, nwx.DiGraph())
# gnp_random_graph(n, %, directed=True)
# notebook extension : .ipynb

import networkx as nwx
import sys, random
import datetime as dt

from networkx.generators import directed

def write_graph(graph, path):
    nwx.write_gml(graph, path)

def gen_complete_graph(n):
    graph = nwx.complete_graph(n, nwx.DiGraph())
    nwx.set_edge_attributes(graph, 0, 'capacity')
    for i, j in graph.edges:
        graph[i][j]['capacity'] = random.randint(1, 500)
    return graph

def gen_cyclic_graph(n):
    graph = nwx.cycle_graph(n, nwx.DiGraph())
    nwx.set_edge_attributes(graph, 0, 'capacity')
    for i, j in graph.edges:
        graph[i][j]['capacity'] = random.randint(1, 500)
    return graph

def gen_random_graph(n, p):
    graph = nwx.gnp_random_graph(n, p, directed=True)
    nwx.set_edge_attributes(graph, 0, 'capacity')
    for i, j in graph.edges:
        graph[i][j]['capacity'] = random.randint(1, 500)
    return graph

def main(argv):
    graph_type = argv[0]
    graph_nb_node = int(argv[1])

    file_path = f"graphs/{graph_type}_{graph_nb_node}_{dt.datetime.strftime(dt.datetime.now(), '%y%m%d_%H%M%S')}"

    if (graph_type == "complete"):
        graph = gen_complete_graph(graph_nb_node)
        nwx.write_gml(graph, file_path)
        return
    if (graph_type == "cyclic"):
        graph = gen_cyclic_graph(graph_nb_node)
        nwx.write_gml(graph, file_path)
        return
    if (graph_type == "random"):
        probability = float(argv[2])
        graph = gen_random_graph(graph_nb_node, probability)
        nwx.write_gml(graph, file_path)
        return
    
    print("ERROR : graph type not in (complete, cyclic, random)")
    return

if __name__ == "__main__":
   main(sys.argv[1:])