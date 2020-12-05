#pragma once
#include "raylib.h"
#include <vector>
#include <algorithm>

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
		Vector2 position;

		float gScore;
		Node* previous;

		std::vector<Edge> connections;
	};

	NodeMap();
	~NodeMap();
	Node WorldNode[16][10];

	void DrawNode(Node* node, bool selected = false);
	void DrawGraph();
};

