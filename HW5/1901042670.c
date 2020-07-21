#include <stdio.h>

void menu();
void read_news(char buffer[500], char file_path[11], int is_Only_Title);
void append_file(char* file_path, char c);
int readed_or_not(int text_num);
void readed_news();
void read_magic_numbers(char buffer_magic[10], char buffer_news[500]);
double f_func(int x);
double g_func(double f(int x), int a);

int main()
{
	menu();
	return 0;
}
void menu()
{
	char buffer[500], file_path[11], buffer_magic[10], buffer_news[500];
	int is_Only_Title, choice2, choice3, i=0;
    char choice1, choice4, read;
	
	do
	{
		printf("**********Daily Press**********\n\n");
		printf("Today's news are listed for you :\n\n");

		printf("Title of 1. news:");
		read_news(buffer,"news/1.txt",1);

		printf("Title of 2. news:");
		read_news(buffer,"news/2.txt",1);

		printf("Title of 3. news:");
		read_news(buffer,"news/3.txt",1);

		printf("Title of 4. news:");
		read_news(buffer,"news/4.txt",1);

		printf("\n\nWhat do you want to do?\n");
		printf("a.Read a new\n");
		printf("b.List the readed news\n");
		printf("c.Get decrypted information from the news\n");

		scanf(" %c",&choice1);

		switch(choice1)
		{
			case 'a':
			printf("Which news do you want to read?:");
			scanf("%d",&choice2);

			if(readed_or_not(choice2) == 1) 
			{
				printf("This new is readed. Do you want to read again? Yes(1) / No(0):\n");
				scanf("%d",&choice3);
			}

			if(readed_or_not(choice2) == 0 || choice3 == 1) /* works if user never read the text before or wants to read again  */
			{
				switch(choice2)
				{
					case 1:
					read_news(buffer, "news/1.txt", 0);
	             	append_file("readed_news_id.txt", '1');
	             	break;

	             	case 2:
					read_news(buffer, "news/2.txt", 0);
	             	append_file("readed_news_id.txt", '2');
	             	break;

	             	case 3:
					read_news(buffer, "news/3.txt", 0);
	             	append_file("readed_news_id.txt", '3');
	             	break;

	             	case 4:
					read_news(buffer, "news/4.txt", 0);
	             	append_file("readed_news_id.txt", '4');
	             	break;
	            }
			}
			break;
			
			case 'b':
			readed_news();
			break;
			
			case 'c':
			read_magic_numbers(buffer_magic, buffer_news);
			break;
		}
		printf("Do you want to continue? Yes(y)/No(n):\n");
		scanf(" %c", &choice4);

	}while(choice4 == 'y' && choice4 != 'n');

	printf("Good Bye!\n");
}
void read_news(char buffer[500], char file_path[11], int is_Only_Title)
{
	int i=0;

	FILE *fp = fopen(file_path, "r");

	if(is_Only_Title == 0) /* prints the whole text */
	{
		while(fscanf(fp, "%c", &buffer[i]) != EOF)
		{
			printf("%c", buffer[i]);
			i++;
		}
		printf("\n");
	}
	else if(is_Only_Title == 1) /* prints only the title */
	{
		fscanf(fp, "%c", &buffer[i]);
		
		while(buffer[i] != '\n')
		{
			printf("%c", buffer[i]);
			i++;
			fscanf(fp, "%c", &buffer[i]);
		}
		printf("\n");
	}
	fclose(fp);
}
int readed_or_not(int text_num)
{
	int count=0;
	char read;
    
	FILE *fp = fopen("readed_news_id.txt", "r");

	while(fscanf(fp, "%c", &read) != EOF)
	{
		if((int)read - 48 == text_num) 
		{
			count++;
		} 
	}
	if(count == 0) return 0; /* if count is 0, it means that user never read that text before */

	else return 1;
	
	fclose(fp);
}
void readed_news()
{
	char read;

	FILE *fp = fopen("readed_news_id.txt", "r");
	
	printf("\nReaded news are listed below:\n");
           
	while(fscanf(fp, "%c", &read) != EOF)
	{
		if(read != '\n')
		{
			printf("%c. new is readed\n",read);
		}
	}
	fclose(fp);
}
void append_file(char* file_path, char c)
{
	int count=0;
	char read;

	FILE *fp = fopen(file_path, "a+");

	while(fscanf(fp, "%c", &read) != EOF)
	{
		if(read == c)  count++;
	}
	if(count == 0)   /* if count is 0, it means that user never read that text before so it can be added to the list */
	{
		fprintf(fp, "%c\n", c);
	}
	fclose(fp);
}
void read_magic_numbers(char buffer_magic[10], char buffer_news[500])
{
	/*
	Each news text has a '#' sign placed at random points and a number next to it. 
	These numbers are magic numbers.
	*/
	int i=0, j=0, k, y=0;
	int dec, count=0;
	double sum=0;
	
	FILE *fp1 = fopen("news/1.txt", "r");
	FILE *fp2 = fopen("news/2.txt", "r");
	FILE *fp3 = fopen("news/3.txt", "r");
	FILE *fp4 = fopen("news/4.txt", "r");
	
	printf("Which news would you like to decrypt?:");
	scanf("%d",&dec);

	switch(dec)
	{
		case 1:
		
		while(fscanf(fp1, "%c", &buffer_news[i]) != EOF)
		{
			printf("%c", buffer_news[i]);

			if(buffer_news[i]== '#')
			{
				i++;
				fscanf(fp1, "%c", &buffer_news[i]);  /* reads a magic number */
				printf("%c", buffer_news[i]);
				buffer_magic[j]=buffer_news[i];
				j++;
			}
			i++;
		}

		printf("\n");
		printf("number of tests performed=");

		for(k=0 ; k<j ; k++)
		{
			y = g_func(f_func, (int)buffer_magic[k] - 48);
			sum += y;
		}
		printf("%.2lf",sum);  /* prints the secret number */
		printf("\n");

		fclose(fp1);

		break;

		case 2:
		
		while(fscanf(fp2, "%c", &buffer_news[i]) != EOF)
		{
			printf("%c", buffer_news[i]);

			if(buffer_news[i]== '#')
			{
				i++;
				fscanf(fp2, "%c", &buffer_news[i]);  /* reads a magic number */
				printf("%c", buffer_news[i]);
				buffer_magic[j]=buffer_news[i];
				j++;
			}
			i++;
		}
		
		printf("\n");
		printf("number of sick people=");

		for(k=0 ; k<j ; k++)
		{
			y = g_func(f_func, (int)buffer_magic[k] - 48);
			sum += y;
		}
		printf("%.2lf",sum);  /* prints the secret number */
		printf("\n");

		fclose(fp2);

		break;

		case 3:
		
		while(fscanf(fp3, "%c", &buffer_news[i]) != EOF)
		{
			printf("%c", buffer_news[i]);

			if(buffer_news[i]== '#')
			{
				i++;
				fscanf(fp3, "%c", &buffer_news[i]);  /* reads a magic number */
				printf("%c", buffer_news[i]);
				buffer_magic[j]=buffer_news[i];
				j++;
			}
			i++;
		}

		printf("\n");
		printf("number of deaths=");

		for(k=0 ; k<j ; k++)
		{
			y = g_func(f_func, (int)buffer_magic[k] - 48);
			sum += y;
		}
		printf("%.2lf",sum);  /* prints the secret number */
		printf("\n");

		fclose(fp3);

		break;

		case 4:
		
		while(fscanf(fp4, "%c", &buffer_news[i]) != EOF)
		{
			printf("%c", buffer_news[i]);

			if(buffer_news[i]== '#')
			{
				i++;
				fscanf(fp4, "%c", &buffer_news[i]);  /* reads a magic number */
				printf("%c", buffer_news[i]);
				buffer_magic[j]=buffer_news[i];
				j++;
			}
			i++;
		}

		printf("\n");
		printf("expected number of sick people=");

		for(k=0 ; k<j ; k++)
		{
			y = g_func(f_func, (int)buffer_magic[k] - 48);
			sum += y;
		}
		printf("%.2lf",sum);  /* prints the secret number */
		printf("\n");

		fclose(fp4);

		break;

	}
}
double f_func(int x)
{
	double result;

	result = x*x*x - x*x + 2;

	return result;
}

double g_func(double f_func(int x), int a)
{
	double result;
	
	result = f_func(a) * f_func(a);

	return result;
	
}

