/*  
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670_part2.c 
$ gcc 1901042670_part2.o -o 1901042670_part2 -lm
$ ./1901042670_part2
*/

#include <stdio.h>
#include <math.h>

int isprime(int a);

int main()
{
	int a, i;

	printf("Please enter an integer: ");
	scanf("%d",&a);

	for(i=2 ; i<a ; i++)
	{
		if(isprime(i)==1) printf("%d is a prime number\n\n",i);
		else printf("%d is not a prime number, it is dividible by %d\n\n",i,isprime(i));
	}
	return 0;
}
int isprime(int a)
{
    int x, counter=0;

    for(x=2 ; x<=sqrt((double)a) ; x++)
    {
	if(a % x == 0 )
	{
		counter++;
		return (x);
	}
     }
     if(counter == 0) return 1;
}
