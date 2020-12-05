#include "NodeMap.h"

NodeMap::NodeMap()
{
	for(int x = 0; x <= 15; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			WorldNode[x][y].position.x = x * 50 + 15;
			WorldNode[x][y].position.y = y * 50 + 15;
		}
	}
}

NodeMap::~NodeMap()
{
}

void NodeMap::DrawNode(Node* node, bool selected)
{
	//static char buffer[10];
	//sprintf_s(buffer, "%.0f", node->gScore);

	//Draw the circle for the outline
	DrawCircle(node->position.x, node->position.y, 15, GREEN);
	//Draw the inner circle
	
	//Draw the text
	//DrawText(buffer, node->position.x - 10, node->position.y - 10, 15, WHITE);
}

void NodeMap::DrawGraph()
{
	for (int x = 0; x <= 15; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			DrawNode(&WorldNode[x][y]);
		}
	}
}
