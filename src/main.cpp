#include "Aresta.h"
#include "Grafo.h"
#include <iostream>
#include <exception>
#include <vector>
#include <utility>

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
    int removals;
    std::vector<std::pair<int,int>> removal_list;
    int state = 0;
    

    std::vector<std::pair<int *, int>> entries = {
        std::make_pair(&network_nodes, 0),
        std::make_pair(&network_connections, 0),

        std::make_pair(&removals, 2)};

    void ReadData(Graph *graph = nullptr)
    {
        for (auto entry : entries)
        {
            if (state != entry.second)
                continue;
            std::cin >> *(entry.first);
        }
        switch(state) {
            case 1:
                for (int i = 0; i < network_connections; i++) {
                    int a, b;
                    std::cin >> a >> b;
                    graph->insert_edge(Edge(a, b));
                }
                break;
            case 2:
                removal_list.resize(removals);
                for(int i = 0; i < removals; i++) {
                    std::cin >> removal_list[i].first;
                    std::cin >> removal_list[i].second;
                }
                break;
            default:
                break;
        };
        state++;
    }



    ~Input()
    {
    }
};


int main()
{
    Input input;
    // Leitura de network nodes e network connections
    input.ReadData();
    try
    {

        Graph graph(input.network_nodes);
        // Leitura dos dados do grafo / conexões
        input.ReadData(&graph);
        // Nesse momento lemos o O
        input.ReadData(&graph);
    }
    catch (const std::exception &e)
    {
        print_exception(e);
    }
    return 0;
}
