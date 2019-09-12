#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <time.h>

int verify(int v[], int n, int x) {
	int i;
	//Try to find x in the array, if found return 1, else return 0
	for(i = 0; i < n; i++) {
		if(v[i] == x) {
			return 1;
		}
	}
	return 0;
}

char * preprocess(char t[]) {
	int len = strlen(t);
	
	if(len > 1) {
		t[len - 1] = '\0';	
	}
	return t;
}

int main(int argc, char* argv[]) {
	
	//Path 
	char dir[100];
	//Quantity of musics to play.
	int n;
	//Command to execute in batch file
	
	//Variables to pass from a text file to the array;
	int index = 0;
	char ** tempBuffer;
	
	//Variables to create the playlist...
	char ** playlist;
	int *numberV;
	
	//Auxiliar variables
	int i, j, k, random;
	
	char command[1000] = "dir /b /s ";
	FILE *ptr;
	
	//To execute by terminal
	if(argc > 1) {
	
		//Too many parameters...
		if(argc > 3) 
			exit(1);
		else if(argc == 2) {
			strcpy(dir, "C:\\Users\\sawada19941\\Music");
			n = atoi(argv[1]);
		}else {
			strcpy(dir, argv[1]);
			n = atoi(argv[2]);
		}	
	}else {
		printf("Please select the path: ");
		scanf("%[^\n]s", dir);
	
		printf("Number of random musics to play: ");
		scanf("%d",&n);	
	}
	
	//Verify if the number is valid...
	if(n <= 0) {
		printf("\nInvalid number...");
		getch();
		exit(0);
	}
	
	//Concatenates the dir to the buffer
	strcat(command, dir);
	strcat(command, " > ");
	strcat(command, dir);
	strcat(command, "\\temp.txt");
	
	//Execute the command.
	system(command);
	//Clear the buffer
	memset(command, '\0', sizeof(command));
	
	strcpy(command, dir);
	strcat(command, "\\temp.txt");
	
	ptr = fopen(command, "r");
	
	//Verify if the path exists...
	if(ptr == NULL) {
		printf("\nFailed to locate path...");
		getch();
		exit(0);
	}
	
	//Clear the buffer
	memset(command, '\0', sizeof(command));
	
	//Allocates the array...
	tempBuffer = (char **) malloc(50000);
		
	//Stores in the array...
	while(!feof(ptr)) {
		fgets(command, 1000, ptr);
		//Alocattes a new String in the array.
		tempBuffer[index] = (char *) malloc(1000);
		//Copy the content of the buffer to the array.
		strcpy(tempBuffer[index], preprocess(command));
		index++;
	}
	
	//If the number of numbers wanted is bigger than the current number
	//It will show all the musics.
	if(n > index)
		n = index;
	
	
	//Generates the random seed.
	srand(time(NULL));
	
	//Generate the playlist
	playlist = (char **) malloc(10000);
	numberV = (int*) malloc(n * sizeof(int));
	
	j = 0;
	k = 0;
	
	for(i = 0; i < n; i++) {
		//Calculates random until 
		do {
			random = rand() % index;	
		}while(verify(numberV, n, random));
		//Add the previous number to the array...
		numberV[k++] = random;
		
		
		//Allocates and stores the random directory to the playlist
		playlist[j] = (char *) malloc(1000);
		strcpy(playlist[j], "\"");
		strcat(playlist[j], tempBuffer[random]);
		strcat(playlist[j], "\"");
		j++;
	}
	
	for(i = 0; i < n; i++) {
		printf("%s\n", playlist[i]);
	}
	
	for(i = 0; i < n; i++) {
		printf("Adding %d\n", i);
		system(playlist[i]);
		system("cls");
	}
	
	return 0;
	
}
