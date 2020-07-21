/*  
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670_part1.c 
$ gcc 1901042670_part1.o -o 1901042670_part1 -lm
$ ./1901042670_part1
*/

#include <stdio.h> /* standard input/output definitions */
#include <math.h> /* mathematical declarations used for sqrt() */

int draw_triangle(int side1, int side2, int side3); /* determines whether the triangle can be drawn according to the triangle inequality theorem */
void type_triangle(int side1, int side2, int side3); /* determines the type of the triangle */
int perimeter_triangle(int side1, int side2, int side3); /* finds the perimeter of the triangle */
double area_triangle(int side1, int side2, int side3, int perimeter); /* finds the area of the triangle */

int main()
{
	int perimeter, side1, side2, side3; 

	printf("The length of the first side:\n");
	scanf("%d",&side1);

	printf("The length of the second side:\n");
	scanf("%d",&side2);

	printf("The length of the third side:\n");
	scanf("%d",&side3);

	if(draw_triangle(side1, side2, side3) == 1)
	{
	    printf("\nAccording to the triangle inequality theorem, this triangle can be drawn.\n\n");

	    type_triangle(side1, side2, side3);

	    perimeter = perimeter_triangle(side1, side2, side3);

	    printf("The perimeter of the triangle:%d\n",perimeter);

	    printf("The area of the triangle:%lf\n",area_triangle(side1, side2, side3, perimeter));
				
	}
	else if(draw_triangle(side1, side2, side3) == 0)
    	{
		printf("According to the triangle inequality theorem, this triangle cannot be drawn.\n");
	}
}
int draw_triangle(int side1, int side2, int side3)
{
	/*
	  the triangle inequality theorem states that the sum of any 2 sides of a triangle 
	  must be greater than the measure of the third side
        */ 
			
	if((side1+side2) > side3 && (side2+side3) > side1 && (side1+side3) > side2) return 1;
	else return 0;
}
void type_triangle(int side1, int side2, int side3)
{
	if(side1 == side2 && side1 == side2 && side2 == side3)
	{
		printf("It is an Equilateral Triangle\n");
	}
	else if(side1 ==  side2 || side1 == side3 || side2 == side3)
	{
		printf("It is an Isosceles Triangle\n");
	}
	else printf("It is a Scalene Triangle\n");
}
int perimeter_triangle(int side1, int side2, int side3)
{
	return (side1 + side2 + side3);
}
double area_triangle(int side1, int side2, int side3, int perimeter)
{
	double p,area;
	
	p = perimeter / 2.0;
	area = sqrt(p*(p-side1)*(p-side2)*(p-side3));
	
	return area;
}


