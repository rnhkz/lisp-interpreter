#include <stdio.h>
#include <math.h>

//Structure Declaration
typedef struct
{
	float x;
	float y;
} point;

//Function Declaration
int add_together(int x, int y)
{
	int result = x + y;
	return result;
}

int main (int argc, char **argv)
{
	//Declare int
	int i;
	//Declare with set value
	int j = 10;	
	
	printf("j = %d", j);

	//Using the declared function
	int added = add_together(j, 18);
	
	printf("%d + 18 =  %d\n", j, added);	
	
	//Using the declared structure
	point p;
	p.x = 0.1;
	p.y = 10.0;
	float length = sqrt(p.x * p.x + p.y * p.y);

	printf("X: %f Y: %f\n", p.x, p.y);
	printf("Length: %f\n", length);
	
	//Conditionals
	int x = 10;
	if (x > 10 && x < 100) {
		puts("x is greater than 10, but less than 100.");
	} else {
		puts("x is less than 11 or greater than 100.");
	}

	//Loops
	puts("While loop execution:");
	
	i = 10;
	while (i > 0) {
		puts("Loop Iteration");
		i = i - 1;
	}
	
	puts("For loop execution:");	
	
	for (int i = 0; i < 10; i++) {
		puts("Loop Iteration");
	}

	return 0;
}
