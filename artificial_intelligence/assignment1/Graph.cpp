#include "Graph.h"
#include "Vertex.h"
#include "Edge.h"
#include "RandomGenerator.h"

Graph::Graph()
{
}


Graph::~Graph()
{
	for (auto it : _vertexMap)
		delete it.second;
}

void Graph::addVertex(const int &vertKey, const float &xPos, const float &yPos)
{
	if (_vertexMap.find(vertKey) == _vertexMap.end()) {
		_vertexMap.insert(std::make_pair(vertKey, new Vertex(vertKey,xPos,yPos)));
		_edgeList.insert(std::make_pair(vertKey, std::list<Edge*>()));
	}
}

void Graph::addEdge(const int &fromVert, const int &toVert, const int &weight)
{
	if (_vertexMap.find(fromVert) != _vertexMap.end() && _vertexMap.find(toVert) != _vertexMap.end()) {
		//_vertexMap[toVert]->addEdge(fromVert, weight);
		//_vertexMap[fromVert]->addEdge(toVert, weight);
		_edgeList[fromVert].push_back(new Edge(fromVert, toVert, weight));
		_edgeList[toVert].push_back(new Edge(toVert, fromVert, weight));
	}
}

Vertex *Graph::getRandomVertex(const int &notKey)
{
	Vertex *returnVertex = nullptr;
	int retries = 0;
	std::map<int, Vertex*>::const_iterator iterator;

	do
	{
		iterator = _vertexMap.begin();
		std::advance(iterator, RandomGenerator::random(0, _vertexMap.size()-1));
		if (iterator != _vertexMap.end()) {
			returnVertex = iterator->second;
		}

	} while (returnVertex == nullptr && retries < 10 && returnVertex->getKey() == notKey);

	return returnVertex;
}

Vertex *Graph::getVertex(const int &vertKey) 
{
	return _vertexMap[vertKey];
}


int Graph::numVertexes()
{
	return (int)_vertexMap.size();
}