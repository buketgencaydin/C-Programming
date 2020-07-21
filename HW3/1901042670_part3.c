#include <stdio.h>

int andop(int a, int b);
int is_binary(int a);
int find_length(int a);
int power(int base, int num);

int main()
{
	int a, b, div ,len_a=0, len_b=0, bin_a, bin_b, count=0;
	
	do
        {
		printf("First integer: ");
		scanf("%d",&a);

		printf("Second integer: ");
		scanf("%d",&b);

		len_a = find_length(a);
		len_b = find_length(b);

        	if(len_a != len_b) printf("Integers should have the same length, please enter 2 new integers.\n");

		bin_a = is_binary(a);
		bin_b = is_binary(b);

		if((bin_a != 1) || (bin_b != 1)) printf("Integers should be binary, please enter 2 new integers.\n");
	} while((len_a != len_b) || (bin_a !=1) || (bin_b !=1));

        printf("%d AND %d = %d\n",a,b,andop(a, b));
    
        return 0;
}
int find_length(int a)
{
	int div, len_a=0;
	div=a;

	while(div != 0) 
	{
		div /= 10;
		len_a++;
	}
	return len_a;
}
int is_binary(int a)
{
	int x=0;
	while(a > 0)
	{
		x = a % 10;
		if((x == 0) || (x == 1)) a /= 10;
		else return 0;
        }
	return 1;
}
int andop(int a, int b)
{
	int x, y, num, sum=0, count=0, result=0;
	int base=10;

	x = a % 10;
	y = b % 10;

	sum = x + y;

	if(sum == 2 )
	{
		num = 1;
		result = 1;
	}
	else num = 0;
	count++;

	a /= 10;
	b /= 10;

	while(a != 0 )
	{
		x = a % 10;
		y = b % 10;

		sum = x + y;

		if(sum == 2 )
		{
			num = 1;
			result += power(base,count);
		}
		else num = 0;
		count++;

       		a /= 10;
	    	b /= 10;
    	}
   	return result;
}
int power(int base, int num)
{
	int i=1, pow=1;

	while(i<=num)
	{
		pow *= base;
		i++;
	}
	return pow;
}



