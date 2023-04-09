
# 运行GreedyFAS算法
g++ GreedyFAS.cpp data_structure/Graph.cpp data_structure/AdjacencyList.cpp -std=c++11 && ./a.out

# 运行SortFAS算法
g++ SortFAS.cpp data_structure/Graph.cpp data_structure/AdjacencyList.cpp -std=c++11 && ./a.out

# 运行PageRankFAS算法
g++ PageRankFAS.cpp data_structure/Graph.cpp data_structure/AdjacencyList.cpp -o pagerankfas -std=c++11 && ./pagerankfas