#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct Hospital
    {
        char* name;
        char citiesServed[3];
    }; 

char cities[6] = { 'A', 'B', 'C', 'D', 'E', 'F'};
char locations[4][3] = { {'A', 'B', 'C'}, {'A', 'C', 'D'}, {'B', 'F'}, {'C', 'E', 'F'} };
    
int count;
int counter;
int comb;

int numPathsHome(int street, int avenue);
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4]);
int control_records(char _cities[6], char city_records[6]);
void control_current(char city_records[6], char current_city);
void mix_cards(char faces[13][10], char suits[4][10]);

int main()
{
	int opt, cho;
	int street, avenue, num;
	int numHospitals, x, i, j;

    struct Hospital results[4];

	char faces[13][10]={"Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten", "Jack", "Queen", "King"};
    char suits[4][10]={"Hearts", "Diamonds", "Clubs", "Spades"};

	do
	{
		printf("1- Execute Part1\n");
		printf("2- Execute Part2\n");
		printf("3- Execute Part3\n");
		printf("4- Exit\n\n");
		printf("What do you want to do ?\n");
		scanf("%d",&opt);

		switch(opt)
		{
			case 1:
				do
				{
				printf("Enter the street number: ");
				scanf("%d", &street);
				printf("street:%d\n",street);

				printf("Enter the avenue number: ");
				scanf("%d", &avenue);
				printf("avenue:%d\n",avenue);

				if(street<1 || avenue<1)
				{
					printf("\nInvalid number! Please enter positive numbers.\n\n");
				}
			}while(street<1 || avenue<1);

				num = numPathsHome(street, avenue);

				printf("Number of optimal paths to take back home: %d\n\n", num);
			break;

			case 2:
				do
				{
					printf("Enter the maximum number of hospitals that can be constructed:");
			    	scanf("%d",&numHospitals);

			    	if((numHospitals<1 || numHospitals>4)) 
			    	{
			    		printf("\nInvalid hospital number! Please enter a number between 1 and 4.\n\n");
			    	}
				}while(numHospitals<1 || numHospitals>4);
				

			    x = canOfferCovidCoverage(cities, locations, numHospitals, results);

			    if(x==1)
			    {
			        printf("\nYes, can offer health care to all!\n");

			        for(i=0 ; i<numHospitals ; i++)
			        {
			            printf("Hospital - %d\n",i+1);

			            printf("Hospital locations: ");

			            for(j=0 ; j<3 ; j++)
			            {
			                printf("%c",results[i].citiesServed[j]);
			            }
			            printf("\n");
			        }
			    }
			    else
			    {
			        printf("No, some cities are not covered\n");
			    }
			    printf("\n");
			    count=0;
				counter=0;
				comb=0;

			break;

			case 3:
				do
			    {
			        mix_cards(faces, suits);
			        printf("\n\nEnter 1 for mix the cards or 0 for exit: ");
			        scanf("%d",&cho);
			    }while(cho==1);
			break;

			case 4:
			break;

			default:
			printf("Invalid option! Please try again.\n\n");
		}

	}while(opt != 4);

	return 0;
}
int numPathsHome(int street, int avenue)
{
	if(street==1 || avenue==1)
	{
		return 1;
	}
	else
	{
		return numPathsHome(street-1, avenue) + numPathsHome(street, avenue-1);
	}
}
void mix_cards(char faces[13][10], char suits[4][10])
{
    int f, s, flag, count=0;
    int record[13][4]={0};
    char deck[52][20]={'\0'};

    struct card
    {
        const char *face;
        const char *suit;
    };

    struct card new;

    srand(time(NULL));
    do
    {
        do
        {
            flag=0;

            f = rand() % 13;
            s = rand() % 4;

            if(record[f][s] == 1) flag++; 

        }while(flag==1);

        record[f][s]=1;

        new.face=faces[f];
        new.suit=suits[s];

        if(count % 2 != 0) printf("%10s of %s\n", new.face, new.suit);
        else printf("%7s of %s\t",new.face, new.suit);

        count++;
        
    } while(count != 52);
    
}
int canOfferCovidCoverage(char _cities[6], char _locations[4][3], int _numHospitals, struct Hospital results[4])
{
	/*
		for example:
			if _numHospitals=2, function will check Hospital 1 and 2 
														Hospital 2 and 3
															Hospital 3 and 4 recursively by increasing the _locations pointer

	*/
    int i, j, k=comb-1 ;
    char city_records[6];

    if(counter==6)
    {
        for(i = 0 ; i<_numHospitals ; i++)
        {
            for(j=0 ; j<3 ; j++)
            {  
                results[i].citiesServed[j] = locations[k][j];
            }
            k++;
        }
    	return 1;
    }
    else if(comb<5) // if maximum combination number isn't reached
    {
			for(i=0 ; i<_numHospitals ; i++)
	        {
	            for(j=0 ; j<3 ; j++) 
	            {
	                control_current(city_records, _locations[i][j]);
	                control_records(_cities, city_records);
	            }
	            counter=count;
	        }
        comb++;
        count=0;
       
        return canOfferCovidCoverage(_cities, _locations+1, _numHospitals, results);
    }
    return 0;
}
int control_records(char _cities[6], char city_records[6])
{
    int i, j, flag=0;

    for(i=0 ; i<6 ; i++)
    {
        for(j=0 ; j<6 ; j++)
        {
            if(_cities[i]==city_records[j]) flag++;
        }
    }
	if(flag == 6) return 1;
    else return 0;
}
void control_current(char city_records[6], char current_city)
{
    int i, flag=0;

    for(i=0 ; i<6 ; i++)
    {   
        if(current_city == city_records[i]) flag++;
        
    }
    if(flag == 0 && current_city>='A' && current_city<='F')
    {
        city_records[count]=current_city;
        count++;
    }

    
}