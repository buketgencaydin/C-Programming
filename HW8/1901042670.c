/*
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670.c 
$ -o 1901042670.o 1901042670 -lm
$ ./1901042670 
*/
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define ARRAY_SIZE 500
#define N 8

void menu();
void menu2();
void generate_hofstadters_sequence (int *arr, int n);
int find_max (int arr[], int index, int max_value);
int sum_array (int arr[]);
double std_array (int arr[], double *mean, int n, int index);
void install_pipes(int visited[N][N], int x, int y, int orientation,int counter);
char* remove_duplicates(char* str);

int main()
{
	menu();
	return 0;
}
void menu()
{
	int op;
	char str[101];
	int x=0,y=0,orientation=2;

	int visited[N][N]={0};
	visited[0][0]=1;
	int counter=0;


	do
	{
		printf("\n\nWelcome to Homework 8, please choose one of the parts to continue\n");
		printf("------------------------\n");
		printf("1) Execute Part 1\n");
		printf("2) Execute Part 2\n");
		printf("3) Execute Part 3\n");
		printf("4) Exit\n\n");

		scanf("%d",&op);

		switch(op)
		{
			case 1:
				menu2();
			break;

			case 2:
				install_pipes(visited, x,y,orientation,counter);

			break;

			case 3:
				printf("Please enter a string(maximum 100 characters) :");
				scanf(" %100[^\n]", str);

				remove_duplicates(str);

				printf("\nDuplicated characters in the string were removed.\n");

				printf("New string : %s\n",str);
			break;

		}
	
	}while(op != 4);
}
void menu2()
{
	int op, n, index,  max_value;
	double mean,x;
	int arr[ARRAY_SIZE];
	int result;
	
	do
	{
		printf("\nPlease make your choice:\n");
		printf(" ------------------\n");
		printf(" 1) Fill Array\n");
		printf(" 2) Find Biggest Number\n");
		printf(" 3) Calculate Sum\n");
		printf(" 4) Calculate Standart Deviation\n");
		printf(" 5) Exit\n\n");

		scanf("%d",&op);

		switch(op)
		{
			case 1:
				printf("Enter an integer:");
				scanf("%d", &n);

				arr[0]=1;
				arr[1]=1;
				generate_hofstadters_sequence (arr, n);
			break;

			case 2:
				index = n-1;
				max_value = arr[0];

				result = find_max (arr, index, max_value);
				printf("Biggest number in the array : %d\n",result);
			break;

			case 3:
				result = sum_array (arr);
				printf("Sum of items in the array :%d\n",result);
				
				arr[0]=1;
				arr[1]=1;
			break;

			case 4:
				index = 0;
				
				x = std_array (arr, &mean, 0, index);
				printf("Mean of the array : %lf\n",mean);
				printf("Standard deviation of the array : %lf\n",x);
				arr[1]=1;
				arr[0]=1;
				mean=0;
			break;
		}

	}while(op != 5);
}
void generate_hofstadters_sequence (int *arr, int n) 
{
	/* 
		HOFSTADTERS SEQUENCE
		--------------------
		Q(n) = Q(n - Q(n-1)) + Q(n - Q(n-2))
		Q(1) = Q(2) = 1 
	*/

	int index=arr[0]+1;

	if(arr[0]==500)
	{
		arr[0]=1;
	}
	else
	{
		if(arr[0]<n-1)
		{
			arr[index] = arr[index-arr[index-1]] + arr[index-arr[index-2]];
			
		}
		else
		{
			arr[index]=0;
		}
		arr[0]++;
		generate_hofstadters_sequence(arr,n);
		
	}
}
int find_max (int arr[], int index, int max_value)
{
	if(index==0)
	{
		return max_value;
	}
	else
	{
		if(arr[index] > max_value)
		{
			max_value=arr[index];
		}

		return find_max(arr, index-1, max_value);
	}
}
int sum_array (int arr[])
{
	if(arr[0] == 0)
	{
		return 0;
	}
	else
	{
		return arr[0] + sum_array(arr+1);
	}
}
double std_array (int arr[], double *mean, int n, int index)
{
	if(arr[n]==0 || n==500)
	{
		*mean /= n;
	}
	else
	{
		*mean += arr[n];
	
		return std_array(arr,mean, n+1, index);
	}
	if(arr[index]==0 || index==500)
	{
		*mean *= n;
		return 0;
	}
	else
	{
		if(index != 0)
		{
			*mean *= n;	
		}
		double x = (double)arr[index] - *mean;
		
	return sqrt(pow(x,2.0)/ (n-1) + pow((std_array(arr, mean, n, index+1)),2.0)) ;
	} 
}
void install_pipes(int visited[N][N], int x, int y, int orientation,int counter)
{
	int i,j;
	int count=1;

	/* I COULDN'T FIGURE OUT HOW TO DO IT.
		I SAW MY MAXIMUM ORIENTATION IS 62.
		  SO I DID IT THIS WAY.
		   SORRY...
	*/
	if(orientation==62)
	{
		printf("\n\n");
		for(int i=0; i<N; i++)
		{
			for(int j=0; j<N; j++)
			{
				printf("%d\t",visited[i][j]);
			}
			printf("\n\n");
		}
	}

	else
	{
		if(count==1)
		{
			if(x+2<8 && y+1<8 && visited[x+2][y+1]==0 )
			{
				x += 2;
				y += 1;
				visited[x][y]=orientation;
				orientation++;
				
				install_pipes(visited, x, y, orientation,counter);

				x -= 2;
				y -= 1;

				orientation--;
				visited[x][y]=0;
			}
			count++;
		}
		if(count==2)
		{
			if(x+1<8 && y-2>=0 && visited[x+1][y-2]==0)
			{
				x += 1;
				y -= 2;
				visited[x][y]=orientation;
				orientation++;
				
				install_pipes(visited, x, y, orientation,counter);

				x -= 1;
				y += 2;
				visited[x][y]=0;
				orientation--;
			}
			count++;
		}
		if(count==3)
		{
			if(x-2>=0 && y-1>=0 && visited[x-2][y-1]==0)
			{
				x -= 2;
				y -= 1;
				visited[x][y]=orientation;
				orientation++;
				
				install_pipes(visited, x, y, orientation,counter);

				x += 2;
				y += 1;
				visited[x][y]=0;
				orientation--;
			}
			count++;
		}
		if(count==4)
		{
			if(x-1>=0 && y+2<8 && visited[x-1][y+2]==0)
			{
				
				x -= 1;
				y += 2;
				visited[x][y]=orientation;
				orientation++;
			
				install_pipes(visited, x, y, orientation,counter);

				x += 1;
				y -= 2;
				visited[x][y]=0;
				orientation--;
			}
			count++;
		}
		if(count==5)
		{
			if(x+1<8 && y+2<8 && visited[x+1][y+2]==0)
			{
				x += 1;
				y += 2;
				visited[x][y]=orientation;
				orientation++;

				install_pipes(visited, x, y, orientation,counter);
					
				x -= 1;
				y -= 2;
				visited[x][y]=0;
				orientation--;
				}
			count++;
		}
		if(count==6)
		{
			if(x+2<8 && y-1>=0 && visited[x+2][y-1]==0)
			{
				x += 2;
				y -= 1;
				visited[x][y]=orientation;
				orientation++;
			
				install_pipes(visited, x, y, orientation,counter);
				
				x -= 2;
				y += 1;
				visited[x][y]=0;
				orientation--;
			}
			count++;
		}
		if(count==7)
		{
			if(x-1>=0 && y-2>=0 && visited[x-1][y-2]==0)
			{
				x -= 1;
				y -= 2;
				visited[x][y]=orientation;
				orientation++;
				
				install_pipes(visited, x, y, orientation,counter);

				x += 1;
				y += 2;
				visited[x][y]=0;
				orientation--;
			}
			count++;
		}
		if(count==8)
		{
			if(x-2>=0 && y+1<8 && visited[x-2][y+1]==0)
			{
				x -= 2;
				y += 1;
				visited[x][y]=orientation;
				orientation++;
			
				install_pipes(visited, x, y, orientation,counter);

				x += 2;
				y -= 1;
				visited[x][y]=0;
				orientation--;
			}
			count++;
		}
	}
}
char* remove_duplicates (char* str)
{
	if(str[0] == '\0')
	{
		return str;
	}
	else
	{
		if(str[0] == str[1])
		{
			for(int i=0 ; str[i] != '\0' ; i++)
			{
				str[i]= str[i+1];
			}
			return remove_duplicates(str);
		}
		else
		{
			return remove_duplicates(str+1);
		}
	}

}