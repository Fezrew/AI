#include "NodeMap.h"
#include <algorithm>
#include <vector> 
#include <raylib.h>

using namespace std;

NodeMap::NodeMap()
{
	for (int x = 0; x <= 15; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			WorldNode[x][y].position.x = (int)x * 50 + 15;
			WorldNode[x][y].position.y = (int)y * 50 + 15;

			WorldNode[x][y].isWater = false;
			WorldNode[x][y].isFood = false;
			WorldNode[x][y].isGround = true;

			if (x == 2 && y == 4)
			{
				WorldNode[x][y].isWater = true;
				WorldNode[x][y].isFood = false;
				WorldNode[x][y].isGround = false;
			}
			else if (x == 13 && y == 4)
			{
				WorldNode[x][y].isFood = true;
				WorldNode[x][y].isWater = false;
				WorldNode[x][y].isGround = false;
			}
			else if (x == 7 && (y > 2 && y < 8) || (x == 1 || x == 2 || x == 3 || x == 12 || x == 13 || x == 14) && (y == 3 || y == 5) || (x == 3 || x == 12) && y == 4)
			{
				WorldNode[x][y].isGround = false;
				WorldNode[x][y].isWater = false;
				WorldNode[x][y].isFood = false;
			}
#pragma region Creating edges


			//Up-left connections
			if (x != 0 && y != 0)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x - 1][y - 1], 1.4 });
				}
			}
			//Upwards connections
			if (y != 0)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x][y - 1], 1 });
				}
			}
			//Up-right connections
			if (x != 15 && y != 0)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x + 1][y - 1], 1.4 });
				}
			}
			//Right connections
			if (x != 15)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x + 1][y], 1 });
				}
			}
			//Down-right connections
			if (x != 15 && y != 9)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x + 1][y + 1], 1.4 });
				}
			}
			//Downwards connections
			if (y != 9)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x][y + 1], 1 });
				}
			}
			//Down-Left connections
			if (x != 0 && y != 9)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x - 1][y + 1], 1.4 });
				}
			}
			//Left connections
			if (x != 0)
			{
				if (WorldNode[x][y].isGround)
				{
					WorldNode[x][y].connections.push_back(Edge{ &WorldNode[x - 1][y], 1 });
				}
			}
#pragma endregion
		}
	}
}

NodeMap::~NodeMap()
{
}

void NodeMap::DrawGraph()
{
	for (int x = 0; x <= 15; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			if (WorldNode[x][y].isWater)
			{
				DrawCircle(WorldNode[x][y].position.x, WorldNode[x][y].position.y, 15, DARKBLUE);
			}
			else if (WorldNode[x][y].isFood)
			{
				DrawCircle(WorldNode[x][y].position.x, WorldNode[x][y].position.y, 15, ORANGE);
			}
			else if (!WorldNode[x][y].isFood && !WorldNode[x][y].isWater && !WorldNode[x][y].isGround)
			{
				DrawCircle(WorldNode[x][y].position.x, WorldNode[x][y].position.y, 15, BLACK);
			}

			if (IsKeyDown(KEY_D))
			{
				if (WorldNode[x][y].isGround)
				{
					DrawCircle(WorldNode[x][y].position.x, WorldNode[x][y].position.y, 15, GREEN);
				}

				//For each Edge in this node's connections
				for (Edge e : WorldNode[x][y].connections)
				{
					//Draw the Edge
					DrawLine(WorldNode[x][y].position.x, WorldNode[x][y].position.y, e.target->position.x, e.target->position.y, BLACK);
				}
			}
		}
	}
}

#pragma region Pathfinding

bool NodeMap::NodeSort(const Node* i, const Node* j)
{
	return (i->gScore < j->gScore);
}

vector<NodeMap::Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
{
	//Validate the input
	if (startNode == nullptr || endNode == nullptr)
	{
		return vector<Node*>();
	}

	if (startNode == endNode)
	{
		vector<Node*> singleNodePath;
		singleNodePath.push_back(startNode);
		return singleNodePath;
	}

	//Initialize the starting node
	startNode->gScore = 0;
	startNode->previous = nullptr;

	//Create our temporary lists for storing nodes
	vector<Node*> openList;
	vector<Node*> closedList;

	//Add the starting node to openList
	openList.push_back(startNode);

	while (!openList.empty())
	{
		//Sort openList based on gScore using the function created above
		sort(openList.begin(), openList.end(), NodeMap::NodeSort);

		//Set the current node to the first node in the openList
		Node* currentNode = openList.front();
		//Remove currentNode from openList
		openList.erase(openList.begin());
		//Add currentNode to closedList
		closedList.push_back(currentNode);

		//If the destination node was added to the closed list,
		//the shortest path has been found
		if (currentNode == endNode)
		{
			break;
		}

		//For each Edge e in currentNode's connections
		for (Edge e : currentNode->connections)
		{
			//If the target node is in the closedList, ignore it
			if (find(closedList.begin(), closedList.end(), e.target) != closedList.end()) {
				continue;
			}
			//If the target node is not in the openList, update it
			if (find(openList.begin(), openList.end(), e.target) == openList.end()) {
				//Calculate the target node's G Score
				e.target->gScore = currentNode->gScore + e.cost;
				//Set the target node's previous to currentNode
				e.target->previous = currentNode;
				//Find the earliest point we should insert the node
				//to the list to keep it sorted
				auto insertionPos = openList.end();
				for (auto i = openList.begin(); i != openList.end(); i++) {
					if (e.target->gScore < (*i)->gScore) {
						insertionPos = i;
						break;
					}
				}
				//Insert the node at the appropriate position
				openList.insert(insertionPos, e.target);
			}
			//Otherwise the target node IS in the open list
			else {
				//Compare the new G Score to the old one before updating
				if (currentNode->gScore + e.cost < e.target->gScore) {
					//Calculate the target node's G Score
					e.target->gScore = currentNode->gScore + e.cost;
					//Set the target node's previous to currentNode
					e.target->previous = currentNode;
				}
			}
		}
	}

	//Create path in reverse from endNode to startNode
	vector<Node*> path;
	Node* currentNode = endNode;

	while (currentNode != nullptr)
	{
		//Add the current node to the beginning of the path
		path.insert(path.begin(), currentNode);
		//Go to the previous node
		currentNode = currentNode->previous;
	}

	return path;
}
#pragma endregion
