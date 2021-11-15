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
        graph[i][j]['cost'] = random.uniform(1, 100)
    trafic_demand = []
    nb_demand = random.randint(1, 5)
    for i in range(0, nb_demand):
        start_node = random.randint(0, n-1)
        end_node = start_node
        while end_node == start_node:
            end_node = random.randint(0, n-1)
        trafic = random.randint(1, 1000)
        trafic_demand.append((start_node, end_node, trafic))
    return trafic_demand, graph

def gen_cyclic_graph(n):
    graph = nwx.cycle_graph(n, nwx.DiGraph())
    nwx.set_edge_attributes(graph, 0, 'capacity')
    for i, j in graph.edges:
        graph[i][j]['capacity'] = random.randint(1, 500)
        graph[i][j]['cost'] = random.uniform(1, 100)
    trafic_demand = []
    nb_demand = random.randint(1, 5)
    for i in range(0, nb_demand):
        start_node = random.randint(0, n-1)
        end_node = start_node
        while end_node == start_node:
            end_node = random.randint(0, n-1)
        trafic = random.randint(1, 1000)
        trafic_demand.append((start_node, end_node, trafic))
    return trafic_demand, graph

def gen_random_graph(n, p):
    graph = nwx.gnp_random_graph(n, p, directed=True)
    nwx.set_edge_attributes(graph, 0, 'capacity')
    for i, j in graph.edges:
        graph[i][j]['capacity'] = random.randint(1, 500)
        graph[i][j]['cost'] = random.uniform(1, 100)
    trafic_demand = []
    nb_demand = random.randint(1, 5)
    for i in range(0, nb_demand):
        start_node = random.randint(0, n-1)
        end_node = start_node
        while end_node == start_node:
            end_node = random.randint(0, n-1)
        trafic = random.randint(1, 1000)
        trafic_demand.append((start_node, end_node, trafic))
    return trafic_demand, graph

def write_demand(file_name, trafic_demand):
    file = open(file_name, "x")
    file.write(f"{len(trafic_demand)}\n")
    for row in trafic_demand:
        file.write(f"{row[0]} {row[1]} {row[2]}\n")
    file.close()
    return

def main(argv):
    graph_type = argv[0]
    graph_nb_node = int(argv[1])

    file_path = f"graphs/{graph_type}_{graph_nb_node}_{dt.datetime.strftime(dt.datetime.now(), '%y%m%d_%H%M%S')}"

    if (graph_type == "complete"):
        trafic_demand, graph = gen_complete_graph(graph_nb_node)
        nwx.write_gml(graph, file_path)
        write_demand(file_path+"_demand", trafic_demand)
        return
    if (graph_type == "cyclic"):
        trafic_demand, graph = gen_cyclic_graph(graph_nb_node)
        nwx.write_gml(graph, file_path)
        write_demand(file_path+"_demand", trafic_demand)
        return
    if (graph_type == "random"):
        probability = float(argv[2])
        trafic_demand, graph = gen_random_graph(graph_nb_node, probability)
        nwx.write_gml(graph, file_path)
        write_demand(file_path+"_demand", trafic_demand)
        return
    
    print("ERROR : graph type not in (complete, cyclic, random)")
    return

if __name__ == "__main__":
   main(sys.argv[1:])