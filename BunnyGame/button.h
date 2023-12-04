#include <stdbool.h>

typedef struct BUTTON {
 	char ID[50];

	int POSX;
	int POSY;

	int WIDTH;
	int HEIGH;

	int VALUE;

	int ISCOLLIDING;
} BUTTON;