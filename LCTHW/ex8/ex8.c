#include <stdio.h>

int main(int argc, char *argv[]){
	int areas[]={10,20,30,40,50};
	char name[]="John";
	char full_name[]={'J', 'o', 'h', 'n', ' ','Y', '.', ' ', 'S', 'm', 'i', 't', 'h', '\0'};
	
	//WARNING: on some systemsyou may have to change the %ld in this code to a %u since it
	//uses unsigned ints
	printf("The size of an int: %ld\n", 
		sizeof(int));
	
	printf("The size of areas (int[]): %ld\n", 
		sizeof(areas));
	
	printf("The number of ints in areas: %ld\n", 
		sizeof(areas)/sizeof(int));
	
	printf("The first area is %d, the 2nd %d.\n", 
		areas[0], areas[1]);
	
	printf("The size of a char: %ld\n", 
		sizeof(char));
	
	printf("The size of name(char[]): %ld\n", 
		sizeof(name));
	
	printf("The number of chairs: %ld\n", 
		sizeof(name)/sizeof(char));
	
	printf("the size of full_name(char[]): %ld\n", 
		sizeof(full_name));
	
	printf("the number of chars: %ld\n", 
		sizeof(full_name)/sizeof(char));
	
	printf("name=\"%s\" and full name=\"%s\"\n",
		name, full_name);
	
	return 0;
	}
	