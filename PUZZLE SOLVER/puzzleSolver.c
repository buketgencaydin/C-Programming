#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRLEN 256

typedef struct
{
    char *word; // word and corresponding hint
    char *clue; 
    int x; // Starting x and y positions
    int y; 
    char direction; // H for horizontal, V for vertical
    int f; // solved or not
} Word_t;

Word_t* loadTextFile(FILE* myFile, int nrWords);
void displayBoard(int rows, int cols, char** myBoard);
int isBoardFilled(int rows, int cols, char** myBoard);
char** createArray(int rows, int cols);
int findIndex(int arr[], int size, int val);
void playGame(char** myBoard, int nrWords, Word_t *words, int x, int y, int countToFinish);
char** updateBoard(char** myBoard, Word_t *words, int solve);
int checkInputValidity(char* input, Word_t *words, int nrWords);

int main()
{
    char** board; // a dynamic array of board 
    FILE* myFile; // file pointer to the file
    int rows, cols, nrWords; // number of rows, columns and words
    Word_t *words; // a dynamic array of Word_t type

    char fileName[STRLEN]; 
    char puzzleInfo[STRLEN];

    printf("\nPUZZLE GAME\n\n");

    printf("Enter name of the text file: ");
    scanf("%s", fileName);    

    myFile = fopen(fileName, "r");
    if (myFile == NULL)
    {
        perror("Error opening file: ");
        return 0;
    }

    fgets(puzzleInfo, STRLEN, myFile);
    sscanf(puzzleInfo, "%d %d %d", &rows, &cols, &nrWords);
    printf("Game is %d rows x %d cols with %d words\n", rows, cols, nrWords); 

    words = (Word_t*)malloc(nrWords * sizeof(Word_t));    
    words = loadTextFile(myFile, nrWords);  
    board = createArray(rows, cols);
    playGame(board, nrWords, words, rows, cols, 0); 

    fclose(myFile);   
    free(board);
    free(words); 

    return 0;
}
Word_t* loadTextFile(FILE* myFile, int nrWords)
{    
    Word_t *temp = (Word_t *)malloc(nrWords * sizeof(Word_t));    
    char tempWord[STRLEN];   
    char tempClue[STRLEN];    
    char str[STRLEN];

    for(int i=0 ; i<nrWords ; i++)
    {
        fgets(str, STRLEN, myFile);
        sscanf(str, "%c %d %d %s %[^\n]", &temp[i].direction, &temp[i].x, &temp[i].y,  tempWord, tempClue); 

        temp[i].word = (char *)malloc(strlen(tempWord) + 1);   
        temp[i].clue = (char *)malloc(strlen(tempClue) + 1);        
        strcpy(temp[i].word, tempWord);        
        strcpy(temp[i].clue, tempClue);    
        temp[i].f = 0; 
    }      
    printf("Words and clues are read!\n");   
    
    return temp;
}
void displayBoard(int rows, int cols, char** myBoard)
{    
    printf("\n\t ");    
    for(int i=1 ; i<=cols ; i++)    
        printf(" %d ",i);    
    printf("\n\t ");  

    for(int i=0 ; i<cols ; i++)    
        printf(" --");    
    printf("\n");    

    for(int i=0 ; i<cols ; i++)    
    {        
        printf("%d\t|", i+1);        
        for(int j=0 ; j<rows ; j++)        
            printf(" %c ", myBoard[i][j]);              
        printf("\n");    
    }    
    printf("\t");  

    for(int i=0 ; i<rows ; i++)        
        printf("***");    
    printf("\n\n");
}
int isBoardFilled(int rows, int cols, char** myBoard)
{    
    for(int i = 0 ; i < rows ; i++)    
    {        
        for(int j = 0 ; j < cols ; j++)        
        {            
            if(myBoard[i][j] == '_') return 0;            
        }    
    }    
    return 1;
}
char** createArray(int rows, int cols)
{   
    char** board = (char**)malloc(rows * sizeof(char*));  
  
    for(int i = 0; i < rows; i++)
    {   
        board[i] = (char*)malloc(cols * sizeof(char));     
        for(int j=0 ; j<cols ; j++) 
            board[i][j] = '#';           
    }  
    return board;
}
int findIndex(int arr[], int size, int val)
{
    for(int i=0 ; i<size ; i++)
    {
        if(arr[i] == val)
            return 1;
    }
    return 0;
}
void playGame(char** myBoard, int nrWords, Word_t *words, int x, int y, int countToFinish)
{    
    int count = 0; 
    int gameOver = countToFinish;

    while(count < nrWords) 
        updateBoard(myBoard, words, count++);    

    printf("Current puzzle:\n");    
    displayBoard(x, y, myBoard);   

    while(!isBoardFilled(x, y, myBoard) && gameOver < nrWords)    
    {        
        printf("Ask for hint:\n#  Direction   row     col\n---------------------------\n");        
        count = 0;

        while(count < nrWords) 
        {
            if(!words[count++].f)
            {
                if(words[count-1].direction == 'H')
                    printf("%d: Horizontal\t%d\t%d\n", count, words[count-1].x, words[count-1].y);               
                else if(words[count-1].direction == 'V')
                    printf("%d: Vertical\t%d\t%d\n", count, words[count-1].x, words[count-1].y);                  
            } 
        }       
        char input[STRLEN];
        int num;	
        do        
        {            
            printf("\nEnter -1 to exit\nWhich word to solve next?: ");         
            scanf("%s", input);
            num = checkInputValidity(input, words, nrWords);              
        }while(num == 0);     

        printf("Current hint: %s\n", words[num-1].clue);        
        printf("Enter your solution: ");

        char solution[STRLEN];        
        scanf(" %s", solution);	

        if(!strcasecmp(words[num-1].word, solution))        
        {            
            printf("\nCorrect!\n\n"); 
            gameOver++;            
            words[num-1].f = 1;            
            updateBoard(myBoard, words, num-1);                
        }        
        else
            printf("WRONG ANSWER\n"); 

        printf("Current puzzle:\n");           
        displayBoard(x, y, myBoard);           
        
        if(isBoardFilled(x, y, myBoard))        
        {            
            printf("Congratulations! You beat the puzzle!\n\n");            
            return;  
        }    
    }
}
char** updateBoard(char** myBoard, Word_t *words, int solve)
{   
    int temp = 0;    

    if(words[solve].f == 1)   
    {   if(words[solve].direction == 'H')        
        {            
            for(int i=0 ; i<strlen(words[solve].word) ; i++)                
                myBoard[words[solve].x-1][i + words[solve].y-1] = words[solve].word[temp++];        
        }
        else if(words[solve].direction == 'V')        
        {           
            for(int i=0 ; i < strlen(words[solve].word) ; i++)                
                myBoard[i+words[solve].x-1][words[solve].y-1] = words[solve].word[temp++];       
        }    
    }
    else
    {   if(words[solve].direction=='H')        
        {
            for(int i=0 ; i<strlen(words[solve].word) ; i++)               
                myBoard[words[solve].x-1][i + words[solve].y-1] = '_';        
        }
        else if(words[solve].direction=='V')        
        {            
            for(int i=0 ; i<strlen(words[solve].word) ; i++)               
                myBoard[i+words[solve].x-1][words[solve].y-1]='_';        
        } 
    }    
    return myBoard;
}
int checkInputValidity(char* input, Word_t* words, int nrWords)
{
    int num = atoi(input);
    
    if(num == -1) exit(0); 

    if (num == 0 && input[0] != '0')
    {
        printf("Input is not an integer");
        return 0;
    }   
    if(num < 1 || num > nrWords)
    {
        printf("Input is not in range");
        return 0;
    }
    if(words[num-1].f == 1)
    {
        printf("That word has been solved before");
        return 0;
    }  
    return num;              
}

