#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define GAME_NUM 2000
#define NAME_LEN 100
#define GENRE_NUM 20
#define PLATFORM_NUM 20

int overlap_control(char array[100][20], char* element, int flag, int* ind); /* controls whether the element is already in the array or not */

int main()
{
	char names[GAME_NUM][NAME_LEN];
	char genres[GENRE_NUM][20];
	char platforms[PLATFORM_NUM][20];
	char temp[200];
	char ch;
	int size=0; 
	int i=0, j=0, k=0, line=0, flag1=0, flag2=0, count=0;
	float game_data[GAME_NUM][7];
	int op, year, time, index, ind;
	float sum=0, avg=0;
	int g[12],p[10];

	FILE *fp = fopen("Video_Games.txt", "r");

	do{
		fscanf(fp, "%c", &ch); /* since the first line of the text includes data types(name, genre, platform etc.) it needs to be skipped */
	}while(ch!= '\n');


	do{
		fgets(temp,200,fp); /* saves a line into temp[] array from the text file */

		char* name = strtok(temp, ",");
		strcpy(names[line],name);

		char* genre = strtok(NULL, ",");
		if(overlap_control(genres, genre, flag1, &ind) == 0)
		{
			strcpy(genres[flag1],genre);
			game_data[line][0] = flag1; 
			flag1++;
		}
		else
		{
			game_data[line][0] = ind; 
		}

		char* platform = strtok(NULL, ",");

		if(overlap_control(platforms, platform, flag2, &ind) == 0)
		{
			strcpy(platforms[flag2],platform);
			game_data[line][1] = flag2; 
			flag2++;
		}
		else
		{	
			game_data[line][1] = ind; 
		}
		
		char* year_of_release = strtok(NULL, ",");
		game_data[line][2] = strtof(year_of_release,NULL);

		char* na_sales = strtok(NULL, ",");
		game_data[line][3] = strtof(na_sales,NULL);
		
		char* eu_sales = strtok(NULL, ",");
		game_data[line][4] = strtof(eu_sales,NULL);

		char* global_sales = strtok(NULL, ",");

		if(strcmp(global_sales,"not_available") == 0)
		{
			game_data[line][5]= -1.0;
		}
		else
		{
			game_data[line][5] = strtof(global_sales,NULL);
		}
		
		char* user_score = strtok(NULL, ",");
		game_data[line][6] = strtof(user_score,NULL);

		line++;


	}while(!feof(fp));

	do
	{
		printf("0: List of the Genres\n");
		printf("1: List of the Platforms\n");
		printf("2: List of the Games Through the Years\n");
		printf("3: All Informations of a Single Game\n");
		printf("4: Average of the User Scores\n");
		printf("5: Geographical Information of a Single Game\n");
		printf("6: Frequence of the Genres\n");
		printf("7: Frequence of the Platforms\n");
		printf("8: Exit\n\n");

		printf("Please select an operation: ");
		scanf("%d",&op);

		printf("\n");

		switch(op)
		{
			case 0:
				for(i=0 ; i<flag1 ; i++)
				{
					printf("%s\n",genres[i]);
				}
			break;

			case 1:
				for(i=0 ; i<flag2 ; i++)
				{
					printf("%s\n",platforms[i]);
				}
			break;

			case 2:
				do
				{
					printf("Enter a year:\n");
					scanf("%d",&year);
					
					printf("Until (0) or Since (1)  %d: ",year);
					scanf("%d",&time);
					
					printf("\n");

					if(time == 0)
					{
						for(i=0 ; i<2000 ; i++)
						{
							if(game_data[i][2] < year)
							{
								printf("%s\n",names[i]);
								count++;
							}
						}
					}
					else
					{
						for(i=0 ; i<2000 ; i++)
						{
							if(game_data[i][2] > year)
							{
								printf("%s\n",names[i]);
								count++;
							}
						}
					}

					if(count==0) printf("TRY AGAIN.\n\n");

			    }while(count == 0);
			    count=0;

			break;

			case 3:
				do
				{
					printf("Please enter the name of the game:\n");
					scanf("%s",temp);

					i=0;
					index=-1;

					/* finds the index of the game in the names array */
					do
					{
						if(strcmp(temp,names[i]) == 0) 
							{
								index=i;
							}
						i++;

					}while(strcmp(temp,names[i-1]) != 0 && i != 2000);

					if(index==-1)
					{
						printf("%s is not in the database, try again.\n\n",temp);
					}

					else
					{
						printf("Name:            %s\n", names[index]);
						printf("Genre            %s\n", genres[(int)game_data[index][0]]);
						printf("Platform:        %s\n", platforms[(int)game_data[index][1]]);
						printf("Year:            %.0f\n", game_data[index][2]);
						printf("Sales In NA:     %.6f\n", game_data[index][3]);
						printf("Sales In EU:     %.6f\n", game_data[index][4]);

						if(game_data[index][5] == -1)
						{
							printf("Total Sales:     Not Available\n");
						}
						else
						{
							printf("Total Sales:     %.6f\n" ,game_data[index][5]);
						}
						printf("User Score:      %.6f\n", game_data[index][6]);
					 }
				}while(index == -1);
			break;
			case 4:
				for(i=0 ; i<2000 ; i++)
				{
					sum += game_data[i][6];
				}
				avg = sum / 2000.0;

				printf("Average: %.6f\n",avg);
			break;

			case 5: /* finds and prints either the game was more populer in NA or EU according to the sales */
				do
				{
					printf("Please enter the name of the game:\n");
					scanf("%s",temp);

					i=0;
					index=- 1;

					/* finds the index of the game in the names array */
					do
					{
						if(strcmp(temp,names[i]) == 0) 
							{
								index=i;
							}
						i++;

					}while(strcmp(temp,names[i-1]) != 0 && i !=2000);

					if(index==-1)
					{
						printf("%s is not in the database, try again.\n\n",temp);
					}

					else
					{
						if(game_data[index][3] > game_data[index][4])
						{
							printf("This game was more popular in North America.\n");
						}
						else if(game_data[index][3] < game_data[index][4])
						{
							printf("This game was more popular in Europe.\n");
						}
						else
						{
							printf("This game had same popularity in North America and Europe.\n");
						}
					}
				}while(index == -1);
			break;

			case 6:  
				for(i=0 ; i<2000 ; i++)  /* loop for finding the frequence of every genre */
				{
					if(game_data[i][0] == 0.0) g[0]++;
					if(game_data[i][0] == 1.0) g[1]++;
					if(game_data[i][0] == 2.0) g[2]++;
					if(game_data[i][0] == 3.0) g[3]++;
					if(game_data[i][0] == 4.0) g[4]++;
					if(game_data[i][0] == 5.0) g[5]++;
					if(game_data[i][0] == 6.0) g[6]++;
					if(game_data[i][0] == 7.0) g[7]++;
					if(game_data[i][0] == 8.0) g[8]++;
					if(game_data[i][0] == 9.0) g[9]++;
					if(game_data[i][0] == 10.0) g[10]++;
					if(game_data[i][0] == 11.0) g[11]++;
				}
				for(i=0 ; i<flag1 ; i++)
				{
					printf("%-14s  %d\n",genres[i],g[i]);
				}
			break;
			case 7:
				for(i=0 ; i<2000 ; i++) /* loop for finding the frequence of every platform */
					{
						if(game_data[i][1] == 0.0) p[0]++;
						if(game_data[i][1] == 1.0) p[1]++;
						if(game_data[i][1] == 2.0) p[2]++;
						if(game_data[i][1] == 3.0) p[3]++;
						if(game_data[i][1] == 4.0) p[4]++;
						if(game_data[i][1] == 5.0) p[5]++;
						if(game_data[i][1] == 6.0) p[6]++;
						if(game_data[i][1] == 7.0) p[7]++;
						if(game_data[i][1] == 8.0) p[8]++;
						if(game_data[i][1] == 9.0) p[9]++;
					}
					for(i=0 ; i<flag2 ; i++)
					{
						printf("%-6s  %d\n",platforms[i],p[i]);
					}
			break;
			case 8:  /* Exit situation */
			break;

			default: /* Invalid entry situation */
			printf("TRY AGAIN.");
		}
		printf("\n\n");
	}while(op != 8);
	return 0;
}
int overlap_control(char array[100][20], char* element, int flag, int* ind)
{
	int i, count=0;

	for(i=0 ; i<flag ; i++)
	{
		if(strcmp(array[i],element) == 0) 
			{
				count=1;
				*ind=i;
			}
	}
	return count;
}




 