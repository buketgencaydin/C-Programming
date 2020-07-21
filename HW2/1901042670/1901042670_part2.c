/*  
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670_part1.c 
$ gcc 1901042670_part1.o -o 1901042670_part1 -lm
$ ./1901042670_part1
*/

#include <stdio.h> /* standard input/output definitions */
#include <math.h> /* mathematical declarations used for pow() and log() */

int number_length(int number); /* finds the length of the number entered by the user */
int find_digit(int number, int index); /* finds the number in the index entered by the user */

int main()
{
	int num, index; 

	printf("Enter a number (maximum 6 digits):\n");
	scanf("%d",&num);

	printf("Your number has %d digits\n\n",number_length(num));
	printf("When your number is written 100 times next to each other, which digit of this number would you like to see? :\n");
	scanf("%d",&index);

	printf(" %d.th digit of the big number sequence: %d\n",index, find_digit(num, index));

	return 0;
}
int number_length(int number)
{
	return (int)(log10((double)number) + 1);
}
int find_digit(int number, int index)
{
	int a, b, mod, length;
	double base = 10.0;

	length = number_length(number);
	
	mod = index % length; /* finds the digit which the user wants to see*/

	if(mod != 0) 
	{
		a = number / pow(base,(double)(length-mod));
		b = a % 10 ;
		return b;
  	}
   	else /* this part works when the user wants to see the last digit of the number according to the index mod length */
   	{
    		return number % 10;  
    	}
}
