// Sudoku Solver - Let's solve one!!

#include <stdio.h>

// Function Declarations
void InputBoard(int board[9][9]);
void PrintBoard(int board[9][9]);
int CanPlaceOrNot(int board[9][9], int row, int col, int num);
int Solving(int board[9][9]);

int CanPlaceOrNot(int board[9][9], int row, int col, int num)
{
    // Checking row
    for(int x=0;x<9;x++)
    {
        if(board[row][x]==num)
        return 0;
    }
    
    // Checking column
    for(int x=0;x<9;x++)
    {
        if(board[x][col]==num)
        return 0;
    }
    
    // Chekcing 3x3 Subgrid    
    int startRow= row-(row%3);
    int startCol= col-(col%3);
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(board[startRow+i][startCol+j]==num)
            return 0;
        }
    }
    return 1;
}


void InputBoard(int board[9][9])
{
    printf("\nEnter values of sudoko row by row(Zeroes at empty places):\n");
    for(int row=0;row<9;row++)
    {
        printf("Enter 9 values for row %d(seperated by spaces):\n", row+1);
        
        int count=0;
        while(count<9)
        {
            int value;
            int res= scanf("%d",&value); // res stores 1 if success in taking value else 0
            if(res==1 && count>=0 && count<=9)
            {
                board[row][count]=value;
                count++;
            }
            else
            {
                printf("Invalid input. Enter a valid integer between 0 to 9\n");
                while(getchar()!='\n'); //Clears invalid characters entered by the user 
            }
        }
    }
}


void PrintBoard(int board[9][9])
{
    printf("\n-----Sudoko Puzzle-----\n");
    printf("\n");
    for(int row=0;row<9;row++)
    {
        if(row%3==0 && row!=0)
        printf("---------------------\n");
        for(int col=0;col<9;col++)
        {
            if(col%3==0 && col!=0)
            printf("| ");
            printf("%d ",board[row][col]);
        }
        printf("\n");
    }
}


int Solving(int board[9][9])
{
    int isEmpty=0;
    int row, col;

    // Finding empty cell
    for(row=0;row<9;row++)
    {
        for(col=0;col<9;col++)
        {
            if(board[row][col]==0)
            {
                isEmpty=1;
                break;
            }
        }
        if(isEmpty)
            break;
    }

    // Solved when no cell is found empty
    if(!isEmpty)
        return 1;

    // Solving (trying numbers from 1 to 9)
    for(int num=1;num<=9;num++)
    {
        if(CanPlaceOrNot(board, row, col, num))
        {
            board[row][col]=num; //Temporarily assigning a number for checking further chances
            if(Solving(board)) //Checking recursively working with the given number or not(Checking all possibilities)
                return 1;
            board[row][col]=0;
        }
    }
    return 0; //Works when no number fits correctly
}


int main()
{
    int board[9][9];
    InputBoard(board);
    printf("\nGiven unsolved Sudoko Puzzle\n");
    PrintBoard(board);
    
    if(Solving(board))
    {
        printf("\nSolved Sudoko\n");
        PrintBoard(board);
    }
    else
        printf("\nGiven Sudoko can't be solved.\n");
    
    return 0;
}