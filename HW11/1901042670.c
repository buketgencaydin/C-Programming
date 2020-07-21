/*
Since math.h library was used in the code, compile and run procedure need to be done like below :
$ gcc -c 1901042670.c 
$ -o 1901042670.o 1901042670 -lm
$ ./1901042670 
*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct node
{
	int data;
	struct node *next;
}nodes;

typedef struct 
{
	int n1,n2;
}diff;

int * read_array(char *filename, int *arr_size);
float * stats_array(int *arr, int *arr_size);
nodes * read_linkedlist(char *filename, int *list_size);
float * stats_linkedlist(nodes *ptr );
diff *generate_sequence(int *arr, nodes *ptr, int *seq_size);
diff * find_difference(int *arr, nodes *ptr);

int main()
{
	char *filename = "list.txt";
    int *arr;
    int arr_size=0, list_size=0;
    int byte_arr, byte_list;
    nodes *head;
	float *stats_a;
    float *stats_l; 
	clock_t t; 
	double time_taken1=0,time_taken2=0,time_taken3=0,time_taken4=0;
	int opt;

	do
	{
		printf("1 - Execute Part 1\n");
		printf("2 - Execute Part 2\n");
		scanf("%d",&opt);

		if(opt==1)
		{
			t = clock(); arr = read_array(filename, &arr_size); t = clock() - t; time_taken1 += ((double)t)/CLOCKS_PER_SEC;
			arr_size=0; 
			t = clock(); head = read_linkedlist(filename, &list_size); t = clock() - t; time_taken3 += ((double)t)/CLOCKS_PER_SEC; 
			list_size=0;
			t = clock(); arr = read_array(filename, &arr_size); t = clock() - t; time_taken1 += ((double)t)/CLOCKS_PER_SEC;
			arr_size=0;
			t = clock(); arr = read_array(filename, &arr_size); t = clock() - t; time_taken1 += ((double)t)/CLOCKS_PER_SEC;
			arr_size=0;
			t = clock(); head = read_linkedlist(filename, &list_size); t = clock() - t; time_taken3 += ((double)t)/CLOCKS_PER_SEC; 
			list_size=0;
			t = clock(); arr = read_array(filename, &arr_size); t = clock() - t; time_taken1 += ((double)t)/CLOCKS_PER_SEC;
			t = clock(); head = read_linkedlist(filename, &list_size); t = clock() - t; time_taken3 += ((double)t)/CLOCKS_PER_SEC; 
			list_size=0;
			t = clock(); head = read_linkedlist(filename, &list_size); t = clock() - t; time_taken3 += ((double)t)/CLOCKS_PER_SEC; 

			printf("\n-----------read_array()-----------\n");
			printf("Average time taken to execute is %f seconds\n", time_taken1/4.0); 
		    printf("The total memory in bytes required the dynamic array is %d\n\n", arr_size * 4);

			printf("----------read_linkedlist()----------\n");
		    printf("Average time taken to execute is %f seconds\n", time_taken3/4.0); 
			printf("The total memory in bytes required the linked listed is %d\n\n",list_size * 8);

			t = clock(); stats_a = stats_array(arr, &arr_size); t = clock() - t; time_taken2 += ((double)t)/CLOCKS_PER_SEC;
			t = clock(); stats_l = stats_linkedlist(head); t = clock() - t; time_taken4 += ((double)t)/CLOCKS_PER_SEC;
			t = clock(); stats_l = stats_linkedlist(head); t = clock() - t; time_taken4 += ((double)t)/CLOCKS_PER_SEC;
			t = clock(); stats_a = stats_array(arr, &arr_size); t = clock() - t; time_taken2 += ((double)t)/CLOCKS_PER_SEC;
			t = clock(); stats_a = stats_array(arr, &arr_size); t = clock() - t; time_taken2 += ((double)t)/CLOCKS_PER_SEC;
			t = clock(); stats_l = stats_linkedlist(head); t = clock() - t; time_taken4 += ((double)t)/CLOCKS_PER_SEC;
			t = clock(); stats_l = stats_linkedlist(head); t = clock() - t; time_taken4 += ((double)t)/CLOCKS_PER_SEC; 
			t = clock(); stats_a = stats_array(arr, &arr_size); t = clock() - t; time_taken2 += ((double)t)/CLOCKS_PER_SEC;
				
			printf("-------------stats_array()-------------\n");
		    printf("Average time taken to execute is %f seconds\n", time_taken2/4.0);
		    printf("MIN:%.3f\nMAX:%.3f\nMEAN:%.3f\nSTD:%.3f\n\n",stats_a[0],stats_a[1], stats_a[2], stats_a[3]); 

			printf("-----------stats_linkedlist()-----------\n");
		    printf("Average time taken to execute is %f seconds\n", time_taken4/4.0); 
		    printf("MIN:%.3f\nMAX:%.3f\nMEAN:%.3f\nSTD:%.3f\n\n",stats_a[0],stats_a[1], stats_a[2], stats_a[3]); 
		}
		else if(opt==2)
	    {
	    	int count=0, x;
			int num, error;
			nodes *cp; // current pointer
			nodes *pp; // previous pointer
			nodes *h; // head pointer
			diff *array;
			int *seq;

			seq = (int*)calloc(1, sizeof(int)); 

			srand(time(NULL));

			while(count != 60) // integer sequence will include 60 numbers
		    {
	    		num = rand() % 1000;
		    	error = rand() % 40;

		    	/*****************ARRAY PART*****************/
		        
		        seq = realloc(seq, ((count)+2) * sizeof(int));
				if(error == 19) seq[count]=num-1;
				else if(error == 5) seq[count]=num+1;
				else seq[count]=num;

		    	/***********LINKED LIST PART***********/
		        
		        nodes *cp = (nodes *)malloc(sizeof(nodes));
		        	
				if((count)==0) h = cp;
		        else  pp -> next = cp;

				if(error == 1) cp -> data = num+1;
				else if(error == 11) cp -> data = num-1;
				else cp -> data = num;
		        pp = cp;

		        count++;
		    }
		    pp -> next = NULL;
		   	
		   	array = find_difference(seq, h);

		    printf("\nDynamic Array : {%d",seq[0]);
			for(int j=1 ; j<60 ; j++)
			{
				printf(",%d",seq[j]);
			}
			printf("}\n\n");

			printf("Linked List   : {%d",h->data);
			h=h->next;
		    while(h!=NULL)
			{
				printf(",%d",h->data);
				h = h->next;
			}
			printf("}\n\n");

			printf("\nWRONG ENTRIES\n");
		    printf("-------------\n");

		    for(int i=0 ; array[i].n1 != -1 ; i++)
		    {
		    	printf("%d -> n1:%d n2:%d\n",i+1,array[i].n1,array[i].n2);
		    }
	    }
	    else printf("\nInvalid option. Please try again!\n\n");

	}while(opt != 1 && opt != 2);
	
	return 0;
}
int * read_array(char *filename, int *arr_size)
{
 	int *arr;
    int num;
	
	FILE *fp = fopen(filename,"r");
	
	arr = (int *)calloc(1, sizeof(int));
    
    while(fscanf(fp, "%d,", &num) != EOF)
    {
    	arr = realloc(arr, ((*arr_size)+2) * sizeof(int));
		arr[*arr_size]=num;
        (*arr_size)++;
    }

    fclose(fp);
   
	return arr;
}
float * stats_array(int *arr, int *arr_size)
{
	int i;

	float *stats = (float*)calloc(4, sizeof(float));
	/*
		stats[0]=min
		stats[1]=max;
		stats[2]=mean;
		stats[3]=std deviation
	*/
	stats[0] = stats[1] = arr[0];
	stats[2] = stats[3] =  0;

	for(i=0 ; i<((*arr_size)) ; i++)
	{
		if(arr[i] < stats[0]) stats[0]=arr[i];
		if(arr[i] > stats[1]) stats[1]=arr[i];
		stats[2] += (float)arr[i];		
	}
	stats[2] /= (float)(*arr_size);
	
	for(i=0 ; i<((*arr_size)) ; i++)
	{
		stats[3] += ((float)arr[i] - stats[2]) * ((float)arr[i] - stats[2]);		
	}
	stats[3] = sqrt((double)stats[3] / (double)((*arr_size)-1));
	
	return stats;
}
nodes * read_linkedlist(char *filename, int *list_size)
{
	FILE *fp = fopen(filename, "r");

	nodes *cp; // current pointer
	nodes *pp; // previous pointer
	nodes *head; // head pointer

	int num=0;

	while(fscanf(fp, "%d,", &num)!= EOF)
    {
        nodes *cp = (nodes *)malloc(sizeof(nodes));
        	
        if((*list_size)==0) head = cp;
        else  pp -> next = cp;

		cp -> data = num;
        (*list_size)++;
        pp = cp;
    }
    pp -> next = NULL;

    fclose(fp);

    return head;
}
float * stats_linkedlist(nodes *ptr)
{
	int i,count=0;
	nodes *head = ptr;

	float *stats = (float*)calloc(4, sizeof(float));
	/*
		stats[0]=min
		stats[1]=max;
		stats[2]=mean;
		stats[3]=std deviation
	*/
	stats[0] = stats[1] = ptr->data;
	stats[2] = stats[3] =  0;

	while(ptr != NULL)
	{
		if(ptr->data < stats[0]) stats[0] = ptr->data;
		if(ptr->data > stats[1]) stats[1] = ptr->data;
		stats[2] += (float)(ptr->data);
		ptr = ptr->next;
		count++;
	}
	stats[2] /= (float)(count);

	ptr = head;

	while(ptr != NULL)
	{
		stats[3] += ((float)(ptr->data) - stats[2]) * ((float)(ptr->data) - stats[2]);	
		ptr = ptr->next;
	}
	stats[3] = sqrt((double)stats[3] / (double)((count)-1));
	
	return stats;
}
diff * find_difference(int *arr, nodes *ptr)
{
	int i,count=0;

	diff *array = (diff*)calloc(1, sizeof(diff));

	for(i=0 ; ptr!=NULL ; i++)
	{
		if(arr[i] != ptr->data)
		{
			if(count != 0) array = realloc(array, (count+1) * sizeof(diff));

			array[count].n1 = arr[i];
			array[count].n2 = ptr->data;
			count++;
		}
		ptr = ptr->next;
	}
	array[count].n1 = -1; // end of the array

	return array;
}
