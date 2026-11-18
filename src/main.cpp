#include "Aresta.h"
#include "Grafo.h"
#include <iostream>
#include <exception>

void print_exception(const std::exception &e)
{
    std::cerr << "exception: " << e.what() << "\n";
}

class Input
{
public:
    // network = social network
    int network_nodes;       // vertex
    int network_connections; // edges

    ~Input()
    {
    }
};

class ConnectionBetween
{
public:
    Edge *connection;
    ConnectionBetween(int a, int b, Graph *graph)
    {
        connection = new Edge(a, b);
        try
        {
            graph->insert_edge(*connection);
        }
        catch (...)
        {
            delete connection;
            connection = nullptr;
            throw;
        }
    }

    ~ConnectionBetween()
    {
        delete connection;
    }
};

int main()
{
    Input input;
    try
    {
        std::cin >> input.network_nodes >> input.network_connections;
        Graph graph(input.network_nodes);
        for (int i = 0; i < input.network_connections; i++)
        {
            int a, b;
            std::cin >> a >> b;
            [[maybe_unused]]ConnectionBetween connection(a, b, &graph);
        }
    }
    catch (const std::exception &e)
    {
        print_exception(e);
    }
    return 0;
}
