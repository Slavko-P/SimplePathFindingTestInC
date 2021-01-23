#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct locations {int x, y;} location;

float distance(location *pawn, location *goal);

int main() {
	int width, length, i, j;
	location goalLocation, pawnLocation;
	char goal[] = "[G]";
	char pawn[] = "[P]";
	char tile[] = "[ ]";
	const int elemSize = sizeof(tile)+sizeof(char*);

	printf("Goal: %s\nPawn: %s\nTile: %s\n",goal ,pawn, tile);
	
	printf("Field size (width length): ");
	scanf("%d %d", &width, &length);
	
	char **Map = (char **)malloc(width*length*elemSize*sizeof(char*));
	
	for (i = 0; i < length; i++)
		for (j = 0; j < width; j++)
			*(Map + elemSize*(i*width + j)) = tile;

	
	printf("Pawn starting point (X Y): ");
	scanf("%d %d", &pawnLocation.x, &pawnLocation.y);
	printf("Goal point (X Y): ");
	scanf("%d %d", &goalLocation.x, &goalLocation.y);
	
	if (goalLocation.x > width || goalLocation.y > length || goalLocation.x < 1 || goalLocation.y < 1 ||
		pawnLocation.x > width || pawnLocation.y > length || pawnLocation.x < 1 || pawnLocation.y < 1) {
			printf("Invalid location!");
			return -1;
		} else  if (pawnLocation.x == goalLocation.x && pawnLocation.y == goalLocation.y) {
			printf("Pawn and goal can't start at same location!");
			return -1;
		}
	
	*(Map + elemSize*((pawnLocation.y-1)*width + pawnLocation.x-1)) = pawn;
	*(Map + elemSize*((goalLocation.y-1)*width + goalLocation.x-1)) = goal;
	
	for (i = 0; i < length; i++) {
		printf("\n");
		for (j = 0; j < width; j++)
			printf("%s", *(Map + elemSize*(i*width + j)));
	}
	
	printf("\nDistance: %.2f", distance(&pawnLocation, &goalLocation));
	
	free(Map);
	return 0;
}

float distance(location *pawn, location *goal) {
	return sqrt(pow(pawn->y - goal->y,2)+pow(pawn->x - goal->x,2));
}