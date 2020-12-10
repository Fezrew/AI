#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>

using namespace std;

class NodeMap
{
public:
	struct Node;

	struct Edge
	{
		Node* target;
		float cost;
	};

	struct Node
	{
		bool isWater;
		bool isFood;
		bool isGround;
		Vector2 position;

		float gScore = 0;
		Node* previous;

		vector<Edge> connections;
	};

	NodeMap();
	~NodeMap();
	Node WorldNode[16][10];

	static bool NodeSort(const Node* i, const Node* j);
	vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);

	void DrawGraph();
};

