#include <stdio.h>

int main(int argc, char *argv[]){
	
	int distance=100;
	float power=2.345f;
	double super_power=56789.4532;
	char initial='Y';
	char first_name[]="John";
	char last_name[]="Smith";
	
	printf("You are %d miles away.\n", distance);
	printf("You have %f levels of power.\n", power);
	printf("You have %f awesome super powers.\n", super_power);
	printf("I have an initial %c.\n", initial);
	printf("I have a first initial %s.\n", first_name);
	printf("I have a last initial %s.\n", last_name);
	printf("My full initials are: %s. %c. %s. \n", 
	first_name, initial, last_name);
	
	return 0;
}