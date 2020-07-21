#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ROW 20
#define COLUMN 20
#define WORD_LEN  20
#define WORD_NUM  10

char random_character(); /* returns a random character between 'a' and 'z' */
int random_direction(int row, int column, int word_len); /* returns an integer between 0 and 7 that represents the one of the 8 directions */
int control_intersection(int row, int column, int direction, int word_len, char board[ROW][COLUMN]);
void fill_board(int row, int column, int direction, int word_len,char board[ROW][COLUMN],char word[WORD_LEN]);
void print_board(char board[ROW][COLUMN]); /* prints the 20x20 puzzle board */
int control_directions(int row_user, int column_user, char word_user[WORD_LEN],char coor[10][10][20], char board[ROW][COLUMN]);        
void make_list_uppercase(char random_words[WORD_NUM][WORD_LEN], char word_user[WORD_LEN]);

int main()
{
	char board[ROW][COLUMN];
	char random_words[WORD_NUM][WORD_LEN];
	int i, j, k=0, c, words_number[10], len, word_len;
	int column, row,direction,flag=0;
	char word[WORD_LEN];
	int column_user;
	char row_user;
	char word_user[WORD_LEN];
	char coor[10][10][20]; /* three dimensional array for saving the words with coordinates e.g. coor[3][5] = "number" */
	char str[20]; 
	char wordk[WORD_LEN];
	int line[10], count=0, line_num,control=0;

	for(i=0 ; i<20 ; i++)
	{
		for(j=0 ; j<20 ; j++)
		{
			board[i][j] = '-'; 
		}
	}
	
	FILE *fp = fopen("words.txt", "r");
	srand(time(NULL));
    
    for (i = 0; i < WORD_NUM; i++) 
    {
        do
        {
            flag = 0 ;
            
            rewind(fp); /* sets the file position to the beginning of the file */
            
            line_num = rand() % 100 + 1; /* gives a random number between [1,100] */

            for(int k = 0 ; k < count; k++)
            {
                if(line_num==line[k]) flag++; /* checks whether the given line_num is chosen before or not */
            }
            
        }while(flag != 0);

        line[i] = line_num;
        count++;

       for (int j = 0; j < line[i]; j++) 
        {
            fgets(wordk, sizeof wordk, fp);
        }
        strcpy(random_words[i], wordk);
        len = strlen(random_words[i]);

        if(line[i] != 100) random_words[i][len-2]='\0';
        else random_words[i][len]='\0';
    }
	fclose(fp);

	for(i=0 ; i<10 ; i++)
		{
			do
			{
				row = rand() % 20;
				column = rand() % 20;
				direction = random_direction(row, column, strlen(random_words[i]));
				control= control_intersection(row, column, direction, strlen(random_words[i]), board);


				if(control==0) /* there is no intersection */
				{
					strcpy(word,random_words[i]);
					strcpy(coor[row][column],random_words[i]); /* saves the words according to their coordinates */

					fill_board(row, column, direction, strlen(random_words[i]), board, word); 
				}
			}while(control == 1);
		}
	
	/* fills the empty places with random characters */
	for(i=0 ; i<20 ; i++)
	{
		for(j=0 ; j<20 ; j++)
		{
			if(board[i][j] == '-')
			{
				board[i][j]=random_character(); 
			}
			
		}
	}
	printf("\n\n");

	i=0;
	control=0;

	while(i<10)
	{
		printf("\n");
		printf("WORD LIST\n---------\n");
		

		for(int i=0; i<10 ; ++i)
		{
			printf("%s\n",random_words[i]);
				
		}
		printf("\n");

		print_board(board);
		printf("\nPlease enter the coordinate and word or Exit for exiting\n");
			
		scanf(" %19[^\n]",str);

		if(strcmp(str,"Exit") == 0) exit(0);

		sscanf(str,"%c%d%s",&row_user,&column_user,word_user);

		row_user -= 65;
			
		control=control_directions(row_user, column_user, word_user, coor,board);
			

		if(control==0)
		{
			printf("\nWRONG GUESS PLEASE TRY AGAIN\n");
		}
		else if(control==1)
		{
			i++;
			make_list_uppercase(random_words,word_user);
		}
	}

	printf("\nWORD LIST\n---------\n");
		
	for(int i=0; i<10 ; ++i)
	{
		printf("%s\n",random_words[i]);
	}
	printf("\n");

	print_board(board);

	printf("\nYOU FOUND ALL THE WORDS, CONGRATULATIONS\n");
		
	return 0;
}
char random_character() /* returns a random character between 'a' and 'z' */
{
    char random_c;
	
	do{
	   random_c = 1 + rand() % 'z' ;
	}while(random_c < 'a');

    return random_c;
}
int random_direction(int row, int column, int word_len)
{
	int direction, flag=0;

		/*
		  direction is a random integer between 0 and 7.
		  These 8 integers represent 8 directions :
		  East, West, North, South, Northwest, Southwest, Northeast and Southeast. 
		*/
	
		while(flag == 0)
		{
			direction = rand() % 8; 
			
			switch(direction)
			{
				case 0: //East
					if((20-column)>word_len)
					{
						direction=0;
						flag++;
					}
					break;
				case 1: //West
					if(column > word_len-2)
					{
						direction=1;
						flag++;
					}
					break;
				case 2: //North
					if(row > word_len-2)
					{
						direction=2;
						flag++;
					}
					break;
				case 3: //South
					if((20-row) > word_len)
					{
						direction=3;
						flag++;
					}
					break;
				case 4: //Northwest
					if((row > word_len-2) && (column > word_len-2))
					{
						direction=4;
						flag++;
					}
					break;
				case 5: //Northeast
					if((row > word_len-2) && (20-column > word_len))
					{
						direction=5;
						flag++;
					}
					break;
				case 6: //Southwest
					if(column > word_len-2 && 20-row>word_len)
					{
						direction=6;
						flag++;
					}
					break;
				case 7: //Southeast
					if(20-column>word_len && 20-row>word_len)
					{
						direction=7;
						flag++;
					}
					break;
			}
		}
		return direction;
}
int control_intersection(int row, int column, int direction, int word_len, char board[ROW][COLUMN])
{
	int i, j;
	int flag = 0;

	i=row;
	j=column;

	switch(direction)
	{
		case 0: //East
			for(j;j<column+word_len;j++)
			{
				if(board[i][j] != '-') flag = 1;
			}
			break;
		case 1: //West
			for(j;j>column-word_len;j--)
			{
				if(board[i][j] != '-') flag = 1;
			}
			break;
		case 2: //North
			for(i;i>row-word_len;i--)
			{
				if(board[i][j]!= '-') flag = 1;
			}
			break;
		case 3: //South
			for(i;i<row+word_len;i++)
			{
				if(board[i][j]!= '-') flag = 1;
			}
			break;
		case 4: //Northwest
			for(i;i>row-word_len;i--)
			{
				if(board[i][j]!= '-') flag = 1;
				j--;
			}
			break;
		case 5: //Northeast
			for(i;i>row-word_len;i--)
			{
				if(board[i][j]!= '-') flag = 1;
				j++;
			}
			break;
		case 6: //Southwest
			for(i;i<row+word_len;i++)
			{
				if(board[i][j]!= '-') flag = 1;
				j--;
			}
			break;
		case 7: //Southeast
			for(i;i<row+word_len;i++)
			{
				if(board[i][j]!= '-') flag = 1;
				j++;
			}
			break;
	}
	return flag;
}
void fill_board(int row, int column, int direction, int word_len,char board[ROW][COLUMN],char word[WORD_LEN])
{
	int i, j, k=0;
	
	i=row;
	j=column;

	switch(direction)
	{
		case 0: //East
			for(j;j<column+word_len; j++)
			{
				board[i][j]=word[k];
				k++;
			}
			break;
		case 1: //West
			for(j;j>column-word_len; j--)
			{
				board[i][j]=word[k];
				k++;
			}
			break;
		case 2: //North
			for(i;i>row-word_len; i--)
			{
				board[i][j]=word[k];
				k++;
			}
			break;
		case 3: //South
			for(i;i<row+word_len;i++)
			{
				board[i][j]=word[k];
				k++;
			}
			break;
		case 4: //Northwest
			for(i;i>row-word_len;i--)
			{
				board[i][j]=word[k];
				k++;
				j--;
			}
			break;
		case 5: //Northeast
			for(i;i>row-word_len;i--)
			{
				board[i][j]=word[k];
				k++;
				j++;
			}
			break;
		case 6: //Southwest
			for(i;i<row+word_len;i++)
			{
				board[i][j]=word[k];
				k++;
				j--;
			}
			break;
		case 7: //Southeast
			for(i;i<row+word_len;i++)
			{
				board[i][j]=word[k];
				k++;
				j++;
			}
		break;
	}
}
void print_board(char board[ROW][COLUMN]) /* prints the 20x20 puzzle board */
{
	int i, j;
	
	for(i=0 ; i<20 ; i++)
	{
		if(i<10) printf("   %d",i);
		else printf("  %d",i);
	}
	printf("\n\n");
	for(i=0 ; i<20 ; i++)
	{
		printf("%c- ",i+65);

		for(j=0; j<20 ; j++)
		{
			printf("%c   ",board[i][j]);
		}
		printf("\n\n");	
	}
}
int control_directions(int row_user, int column_user, char word_user[WORD_LEN], char coor[10][10][20], char board[ROW][COLUMN]) 
{
	int flag, i, j, k;

	int word_len = strlen(coor[row_user][column_user]);

	int len = strlen(word_user);

	/********************************EAST*****************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(j; j<column_user+word_len;j++) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
	}
	
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		for(j=column_user;j<column_user+word_len;j++)
		{
			board[i][j]=board[i][j]-32;
		}
		return 1;
	}
	/*********************************WEST****************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(j; j>column_user-word_len;j--) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
	}
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		for(j=column_user; j>column_user-word_len;j--)
		{
			board[i][j]=board[i][j]-32;
		}
		return 1;
	}
	/*******************************NORTH*****************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(i;i>row_user-word_len;i--) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
	}
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		for(i=row_user; i>row_user-word_len;i--)
		{
			board[i][j]=board[i][j]-32;
		}
		return 1;
	}
	/********************************SOUTH****************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(i;i<row_user+word_len;i++) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
	}
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		for(i=row_user; i<row_user+word_len;i++)
		{
			board[i][j]=board[i][j]-32;
		}
		return 1;
	}
	/*****************************NORTHWEST***************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(i; i>row_user-word_len;i--) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
		j--;
	}
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		j=column_user;
		for(i=row_user; i>row_user-word_len;i--)
		{
			board[i][j]=board[i][j]-32;
			j--;
		}
		return 1;
	}
	/*******************************NORTHEAST*************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(i;i>row_user-word_len;i--) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
		j++;
	}
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		j=column_user;

		for(i=row_user-column_user; i>row_user-word_len;i--)
		{
			board[i][j]=board[i][j]-32;
			j++;
		}
		return 1;
	}
	/*******************************SOUTHWEST**************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(i; i<row_user+word_len;i++) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
		j--;
	}
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		j=column_user;
		for(i=row_user; i<row_user+word_len;i++)
		{
			board[i][j]=board[i][j]-32;
			j--;
		}
		return 1;
	}
	/*******************************SOUTHEAST*************************************/
	i=row_user;
	j=column_user;
	k=0;
	flag=0;

	for(i; i<row_user+word_len;i++) 
	{
		if(board[i][j]==word_user[k]) flag++;
		k++;
		j++;
	}
	if(flag==word_len && !strcmp(word_user,coor[row_user][column_user]))
	{
		j=column_user;

		for(i=row_user; i<row_user+word_len;i++)
		{
			board[i][j]=board[i][j]-32;
			j++;
		}
		return 1;
	}
	return 0;
}
void make_list_uppercase(char random_words[WORD_NUM][WORD_LEN], char word_user[WORD_LEN])
{
	int i, j;

	for(i=0 ; i<10; ++i)
	{
		if(strcmp(random_words[i],word_user)==0)
			{
				for(j=0 ; j<strlen(random_words[i]); j++)
				{
					random_words[i][j] -= 32;
				}
			}
	}
}
