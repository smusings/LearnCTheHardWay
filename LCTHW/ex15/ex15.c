#include <stdio.h>

int main (int argc, char *argv[]){
	
	//create two arrays
	int ages[]={23, 43, 12, 29, 2};
	char *names[]={
		"Scott Snyder", "Geoff Johns",
		"Brian Azzarello", "Grant Morrison",
		"Jeph Loeb"};
		
	//safely get the size of ages
	int count=sizeof(ages)/sizeof(int);
	int i=0;
	
	//first way using indexing
	//looping through the arrays 0=0, 1=1 and printing both
	for (i=0; i<count; i++){
		printf("%s has %d years alive.\n",
			names[i], ages[i]);
	}
		
	printf("---\n");
		
	//setup the pointers to the start of the arrays
	int *cur_age=ages;
	int **cur_name=names;
		
	//second way of using pointers
	//same as above just more complex?
	for (i=0; i<count; i++){
		printf("%s is %d years old.\n",
		*(cur_name+i), *(cur_age+i));
	}
		
	printf("---\n");
		
	//fourth way with points in a stupid complex way
	//they point at one one another without just 0/0, 1/1 
	for(cur_name=names, cur_age=ages;
		(cur_age - ages) < count;
		cur_name++, cur_age++){
			printf("%s lived  %d years so far.\n",
				*cur_name, *cur_age);
			}
				
		return 0;
}