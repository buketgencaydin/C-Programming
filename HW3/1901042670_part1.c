#include <stdio.h>

int sum(int n, int flag);
int mult(int n, int flag);

int main()
{
	int n, op, flag, i, last;

	printf("Enter an integer: ");
	scanf("%d",&n);

    printf("Please enter '0' for sum, '1' for multiplication\n");
	scanf("%d",&op);

	switch(op)
	{
		case 0:
		printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
	    scanf("%d",&flag);

		    switch(flag)
		    {
		    	case 0:
		    	for(i=2 ; i<=n ; i++)
			    {
					if(i % 2 == 0)
					{
						if((n % 2 == 0 && i != n ) || (n % 2 == 1 && i != (n-1)))
						{
							printf("%d + ",i);
						}
						else
						{
							printf("%d = %d\n",i,sum(i, flag));
						}
					}
				}
				break;

		    	case 1:
		    	for(i=1 ; i<=n ; i++)
			    {
					if(i % 2 != 0)
					{
						if((n % 2 == 0 && i != n-1 ) || (n % 2 == 1 && i != n))
						{
							printf("%d + ",i);
						}
						else
						{
							printf("%d = %d\n",i,sum(i, flag));
						}
					}
				}
		    	break;

		    	default:
		    	printf("Invalid value for odd/even selection.\n");
		    }
			
		break;

		case 1:
		printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
	    scanf("%d",&flag);

		    switch(flag)
		    {
		    	case 0:
		    	for(i=2 ; i<=n ; i++)
			    {
					if(i % 2 == 0)
					{
						if((n % 2 == 0 && i != n ) || (n % 2 == 1 && i != (n-1)))
						{
							printf("%d * ",i);
						}
						else
						{
							printf("%d = %d\n",i,mult(i, flag));
						}
					}
				}
		    	break;

		    	case 1:
		    	for(i=1 ; i<=n ; i++)
			    {
					if(i % 2 != 0)
					{
						if((n % 2 == 0 && i != n-1 ) || (n % 2 == 1 && i != n))
						{
							printf("%d * ",i);
						}
						else
						{
							printf("%d = %d\n",i,mult(i, flag));
						}
					}
				}
		    	break;

		    	default:
		    	printf("Invalid value for odd/even selection.\n");
		    }
			
		break;

		default:
		printf("Please enter '0' to work on even numbers, '1' to work on odd numbers\n");
		scanf("%d",&flag);

		printf("Unsupported operation.\n");

	}

	return 0;
}


int sum(int n, int flag)
{
	int i, sum=0;

	if(flag == 0)
	{
		for(i=2 ; i<=n ; i++)
		{
			if(i % 2 == 0)
			{
				sum += i;
			}
		}
	}
	else if(flag == 1)
	{
		for(i=1 ; i<=n ; i++)
		{
			if(i % 2 != 0)
			{
				sum += i;
			}
	    }
	}

	return (sum);
}


int mult(int n, int flag)
{
	int i, mult=1;

	if(flag == 0)
	{
		for(i=2 ; i<=n ; i++)
		{
			if(i % 2 == 0)
			{
				
				mult *= i;
			}
		}
}
	else if(flag == 1)
	{
		for(i=1 ; i<=n ; i++)
		{
			if(i % 2 != 0)
			{
				mult *= i;
			}
		}
    }

	return (mult);
}