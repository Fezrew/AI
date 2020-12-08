#include "NodeMap.h"
#include <algorithm>
#include <vector> 

using namespace std;

NodeMap::NodeMap()
{
	for(int x = 0; x <= 15; x++)
	{
		for (int y = 0; y <= 9; y++)
		{
			WorldNode[x][y].position.x = x * 50 + 15;
			WorldNode[x][y].position.y = y * 50 + 15;

			if (x == 2 && y == 4)
			{
				WorldNode[x][y].isWater = true;
				WorldNode[x][y].isGround = false;
			}
			else if (x == 13 && y == 4)
			{
				WorldNode[x][y].isFood = true;
				WorldNode[x][y].isGround = false;
			}
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
			else
			{
				DrawCircle(WorldNode[x][y].position.x, WorldNode[x][y].position.y, 15, GREEN);
			}
		}
	}
}

bool NodeSort(Node* i, Node* j)
{
	return (i->gScore < j->gScore);
}

vector<Node*> NodeMap::DijkstrasSearch(Node* startNode, Node* endNode)
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
		sort(openList.begin(), openList.end(), NodeSort);

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
