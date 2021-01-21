#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct locations {int x, y;} location;

void printMap(char Map[][4][3]);
//void pathFind(char Map[][4][3]);
float pathToGoal(char Map[][4][3]);

int main() {
	const char pawn = '!';
	const char goal = 'G';
	const char path = '-';
	location pawnStart, goalPoint;
	
	printf("Pawn: %c\nGoal: %c\nPath: %c\n", pawn, goal, path);
	
	char Map[][4][3] = {
					{"[ ]","[ ]","[ ]","[ ]"},
					{"[ ]","[ ]","[ ]","[ ]"},
					{"[ ]","[ ]","[ ]","[ ]"},
					{"[ ]","[ ]","[ ]","[ ]"}
					};
	
	printf("Pawn starting point (X Y): ");
	scanf("%d %d", &pawnStart.x, &pawnStart.y);
	printf("Goal point (X Y): ");
	scanf("%d %d", &goalPoint.x, &goalPoint.y);
	
	if (pawnStart.x > 4 || pawnStart.y > 4 || pawnStart.x <= 0 || pawnStart.y <= 0 || 
		goalPoint.x > 4 || goalPoint.y > 4 || goalPoint.x <= 0 || goalPoint.y <= 0) {
		printf("Invalid location!");
		return -1;
	} else if (pawnStart.x == goalPoint.x && pawnStart.y == goalPoint.y) {
		printf("Pawn and goal can't start at the same point!");
		return -2;
	}
		
	Map[pawnStart.y-1][pawnStart.x-1][1] = pawn;
	Map[goalPoint.y-1][goalPoint.x-1][1] = goal;
	
	printMap(Map);	
	
	printf("Distance: %.2f", pathToGoal(Map));
	
	return 0;
}

/*void pathFind() {
	
}*/

float pathToGoal(char Map[][4][3]) {
	int i,j,u;
	location pawnLocation, goalLocation;
	
	for (i=0;i<4;i++) 
		for (j=0;j<4;j++) 
				if (Map[i][j][1] == '!') {
					pawnLocation.y = i + 1;
					pawnLocation.x = j + 1;
				} else if (Map[i][j][1] == 'G') {
					goalLocation.y = i + 1;
					goalLocation.x = j + 1;
				}
	return sqrt(pow(pawnLocation.x - goalLocation.x, 2) + pow(pawnLocation.y - goalLocation.y, 2)); 
}

void printMap(char Map[][4][3]) {
	int i,j,u;
	for (i=0;i<4;i++) {
		for (j=0;j<4;j++) 
			for (u=0;u<3;u++)
				printf("%c",Map[i][j][u]);
		printf("\n");
	}
}