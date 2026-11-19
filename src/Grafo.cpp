#include "Grafo.h"
#include <stdexcept>
#include <string>
#include <iostream>
#include <set>
#include <stack>
#include <queue>
#include <algorithm>

Graph::Graph(int num_vertices)
{
    if (num_vertices <= 0)
    {
        throw std::runtime_error("Error in constructor Graph(int): the number of "
                                 "vertices " +
                                 std::to_string(num_vertices) + " is invalid!");
    }

    num_vertices_ = num_vertices;
    num_edges_ = 0;

    adj_matrix_.resize(num_vertices);
    for (int i = 0; i < num_vertices; i++)
    {
        adj_matrix_[i].resize(num_vertices, 0);
    }
}

Graph::~Graph()
{
    adj_matrix_.clear();
}

int Graph::num_vertices()
{
    return num_vertices_;
}

int Graph::num_edges()
{
    return num_edges_;
}

bool Graph::has_edge(Edge e)
{
    if (adj_matrix_[e.v1][e.v2] != 0)
    {
        return true;
    }
    return false;
}

void Graph::insert_edge(Edge e)
{
    validate_edge(e);

    if (!has_edge(e) && (e.v1 != e.v2))
    {
        adj_matrix_[e.v1][e.v2] = 1;
        adj_matrix_[e.v2][e.v1] = 1;

        num_edges_++;
    }
}

void Graph::remove_edge(Edge e)
{
    validate_edge(e);

    if (has_edge(e))
    {
        adj_matrix_[e.v1][e.v2] = 0;
        adj_matrix_[e.v2][e.v1] = 0;

        num_edges_--;
    }
}

void Graph::print()
{
    for (int v = 0; v < num_vertices_; v++)
    {
        std::cout << v << ":";
        for (int u = 0; u < num_vertices_; u++)
        {
            if (adj_matrix_[v][u] != 0)
            {
                std::cout << " " << u;
            }
        }
        std::cout << "\n";
    }
}

void Graph::validate_vertex(int v)
{
    if ((v < 0) || (v >= num_vertices_))
    {
        throw std::runtime_error("Invalid vertex index: " + std::to_string(v));
    }
}

void Graph::validate_edge(Edge e)
{
    validate_vertex(e.v1);
    validate_vertex(e.v2);
}

bool Graph::is_walk(std::vector<int> &vertex_sequence)
{
    if (vertex_sequence.size() == 0)
    {
        throw std::runtime_error("Error in operation eh_passeio(vector<int> &): the"
                                 " vertex sequence is empty");
    }

    for (int i = 1; i < ((int)vertex_sequence.size()); i++)
    {
        if (adj_matrix_[vertex_sequence[i - 1]][vertex_sequence[i]] == 0)
        {
            return false;
        }
    }

    return true;
}

bool Graph::is_path(std::vector<int> &vertex_sequence)
{
    if (vertex_sequence.size() == 0)
    {
        throw std::runtime_error("Error in operation eh_caminho(vector<int> &): the"
                                 " vertex sequence is empty");
    }

    std::vector<int> visited(num_vertices_);

    visited[vertex_sequence[0]] = 1;
    for (int i = 1; i < ((int)vertex_sequence.size()); i++)
    {
        if ((visited[vertex_sequence[i]] != 0) ||
            (adj_matrix_[vertex_sequence[i - 1]][vertex_sequence[i]] == 0))
        {
            return false;
        }

        visited[vertex_sequence[i]] = 1;
    }

    return true;
}

std::vector<int> Graph::breadth_first_search(int origin, std::set<int> &outer_marked)
{
    std::vector<int> graph;
    std::set<int> visited;
    visited.emplace(origin);
    std::queue<int> to_visit;
    to_visit.emplace(origin);
    graph.push_back(origin);
    while (!to_visit.empty())
    {
        int node = to_visit.front();
        for (int neighbour = 0; neighbour < this->num_vertices_; neighbour++)
        {
            int is_edge = this->adj_matrix_[node][neighbour];
            if (is_edge != 0 && visited.count(neighbour) == 0)
            {
                to_visit.push(neighbour);
                visited.emplace(neighbour);
                graph.push_back(neighbour);
            }
        }
        to_visit.pop();
    }
    return graph;
}

int Graph::vertice_max_grau_nao_marcado(std::set<int> marked_set)
{
    // degrau mais alto | indice mais baixo se necessario
    std::pair<int, int> chosen_vertex = {-1, -1};

    for (int vertex = 0; vertex < num_vertices(); vertex++)
    {
        if (marked_set.count(vertex) > 0)
            continue;
        int degree = 0;

        for (int edge = 0; edge < num_vertices(); edge++)
        {
            if (adj_matrix_[vertex][edge] != 0 && marked_set.count(edge) == 0)
            {
                degree++;
            }
        }
        if (degree > chosen_vertex.first)
        {
            // o caso de haver um igual e maior nunca vai substituir o valor
            chosen_vertex.first = degree;
            chosen_vertex.second = vertex;
        }
    }
    return chosen_vertex.second;
}

std::vector<int> Graph::influenciadores_a_contratar()
{
    std::set<int> vertices;
    std::vector<int> influencers;
    while(vertices.size() != num_vertices_) {
        int non_marked = vertice_max_grau_nao_marcado(vertices);
        if(non_marked == -1) break;
        
        influencers.push_back(non_marked);
        vertices.emplace(non_marked);
        for (int edge = 0; edge < num_vertices(); edge++)
        {
            if (adj_matrix_[non_marked][edge] != 0 && vertices.count(edge) == 0)
            {
                vertices.emplace(edge);
            }
        }
    }
    std::sort(influencers.begin(), influencers.end());
    return influencers;
}