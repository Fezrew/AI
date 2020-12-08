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
		bool isWater = false;
		bool isFood = false;
		bool isGround = true;
		Vector2 position;

		float gScore;
		Node* previous;

		std::vector<Edge> connections;
	};

	NodeMap();
	~NodeMap();
	Node WorldNode[16][10];
	vector<Node*> DijkstrasSearch(Node* startNode, Node* endNode);

	void DrawGraph();
};

