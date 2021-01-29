#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include <math.h>

using namespace std;

struct node {
	bool isObstacle = false;
	bool wasVisited = false;
	float GlobalGoal = INFINITY;
	float LocalGoal = INFINITY;
	int x;
	int y;
	vector<node*> Neighbours;
	node *parent = nullptr;
	char icon[4] = "[ ]";
};

struct location {int x,y;};

void printMap(const node *Nodes, const int MapHeight, const int MapWidth) {
	for (int x = 0; x < MapWidth; x++) {
		for (int y = 0; y < MapHeight; y++)
			cout << Nodes[y * MapWidth + x].icon;
		cout << endl;
	}
}

float distance(location *a, location *b) {
	//cout << "a->y:" << a->y << " b->y:" << b->y << endl;
	//cout << "b->y:" << b->y << " b->x:" << b->x << endl;
	return sqrtf(pow(a->y - b->y,2)+pow(a->x - b->x,2));
} 

void SolveAStar(node *Nodes, location pawn,  location goal, int MapWidth) {
	node *StartingNode = &Nodes[pawn.y*MapWidth + pawn.x];
	node *CurrentNode = StartingNode;
	node *EndNode = &Nodes[goal.y*MapWidth + goal.x];
	
	StartingNode->LocalGoal = 0.0f;
	StartingNode->GlobalGoal = distance(StartingNode, EndNode);
	
	list<node*> NotTestedNodes;
	NotTestedNodes.push_back(StartingNode);
	
	while (!NotTestedNodes.empty() && CurrentNode != EndNode) {
		NotTestedNodes.sort([](const node* lhs, const node* rhs){return lhs->GlobalGoal < rhs->GlobalGoal;});
		
		while (!NotTestedNodes.empty() && NotTestedNodes.front()->wasVisited)
			NotTestedNodes.pop_front();
		
		if (NotTestedNodes.empty())
			break;
		
		CurrentNode = NotTestedNodes.front();
		CurrentNode->wasVisited = true;
		
		for (auto ThisNeighbour : CurrentNode->Neighbours) {
			if (!ThisNeighbour->wasVisited && !ThisNeighbour->isObstacle)	
				NotTestedNodes.push_back(ThisNeighbour);
			
			float PossiblyLowerGoal = CurrentNode->LocalGoal + distance(CurrentNode, ThisNeighbour);
			
			cout << distance(CurrentNode, ThisNeighbour) << " " << CurrentNode->y << " " << CurrentNode->x << " " << ThisNeighbour->y << " " << ThisNeighbour->x << endl;
			//cout << sqrtf(pow(CurrentNode->y - ThisNeighbour->y,2) + pow(CurrentNode->x - ThisNeighbour->x,2)) << endl;
			
			if (PossiblyLowerGoal < ThisNeighbour->LocalGoal) {
				ThisNeighbour->parent = CurrentNode;
				ThisNeighbour->LocalGoal = PossiblyLowerGoal;
				ThisNeighbour->GlobalGoal += distance(ThisNeighbour, EndNode);
			}
		}
	}
	
	if (EndNode != nullptr) {
		node *point = EndNode;
		while (point->parent != nullptr) {
			if (point != EndNode)
				Nodes[(point->y-1)*MapWidth + point->x-1].icon[1] = '-';
			point = point->parent;
		}
	}
}

int main() {
	int MapWidth, MapHeight;
	location PawnLocation, GoalLocation;
	
	cout << "Input map size (width height): ";
	scanf("%d %d", &MapWidth, &MapHeight);
	
	node *Nodes = new node[MapHeight * MapWidth];
	if (Nodes == nullptr) {
		cout << "Not enough space!";
		return -1;
	}
	
	cout << "Input pawn starting position (x y): ";
	scanf("%d %d", &PawnLocation.x, &PawnLocation.y);
	
	if (PawnLocation.x > MapWidth || PawnLocation.x < 1 || PawnLocation.y > MapHeight || PawnLocation.y < 1) {
		cout << "Invalid location!";
		return -1;
	}
	
	cout << "Input goal starting position (x y): ";
	scanf("%d %d", &GoalLocation.x, &GoalLocation.y);
	
	if (GoalLocation.x > MapWidth || GoalLocation.x < 1 || GoalLocation.y > MapHeight || GoalLocation.y < 1) {
		cout << "Invalid location!";
		return -1;
	} else if (GoalLocation.x == PawnLocation.x && GoalLocation.y == PawnLocation.y) {
		cout << "Goal and pawn can't have the same location!";
		return -1;
	}
	
	for (int x = 0; x < MapWidth; x++)
		for (int y = 0; y < MapHeight; y++) {
			Nodes[y*MapWidth + x].x = x;
			Nodes[y*MapWidth + x].y = y;
		}
	
	for (int x = 0; x < MapWidth; x++)
		for (int y = 0; y < MapHeight; y++) {
			if(y>0)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y - 1) * MapWidth + (x + 0)]); //Up
			if(y<MapHeight-1)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y + 1) * MapWidth + (x + 0)]); //Down
			if (x>0)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y + 0) * MapWidth + (x - 1)]); //Left
			if(x<MapWidth-1)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y + 0) * MapWidth + (x + 1)]); //Right
			
			if (y>0 && x>0)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y - 1) * MapWidth + (x - 1)]); //Up-Left
			if (y<MapHeight-1 && x>0)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y + 1) * MapWidth + (x - 1)]); //Down-Left
			if (y>0 && x<MapWidth-1)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y - 1) * MapWidth + (x + 1)]); //Up-Right
				if (y<MapHeight - 1 && x<MapWidth-1)
				Nodes[y*MapWidth + x].Neighbours.push_back(&Nodes[(y + 1) * MapWidth + (x + 1)]); //Down-Right
		}
	
	Nodes[(PawnLocation.y-1)*MapWidth + PawnLocation.x-1].icon[1] = 'P';
	Nodes[(GoalLocation.y-1)*MapWidth + GoalLocation.x-1].icon[1] = 'G';
	
	SolveAStar(Nodes, PawnLocation, GoalLocation, MapWidth);
	
	printMap(Nodes, MapHeight, MapWidth);
	printf("Starting distance: %.2f\n", distance(&PawnLocation, &GoalLocation));

	return 0;
}