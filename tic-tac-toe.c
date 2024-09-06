#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <time.h>

const char PLAYER='X';
const char COMPUTER='O';
    
    void resetare_joc(char** board)
    {
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                board[i][j]=' ';
            }
        }
    }

    void printeaza_tabla_de_joc(char** board)
    {
        printf(" %c | %c | %c ",board[0][0],board[0][1],board[0][2]);
        printf("\n---|---|---\n");
        printf(" %c | %c | %c ",board[1][0],board[1][1],board[1][2]);
        printf("\n---|---|---\n");
        printf(" %c | %c | %c ",board[2][0],board[2][1],board[2][2]);
        printf("\n");
    }

    void printeaza_castigator(char winner)
    {
        if(winner== PLAYER)
        {
            printf("YOU WIN!");
        }
        else if(winner==COMPUTER)
        {
            printf("YOU LOSE!");
        }
        else{
            printf("IT'S A TIE");
        }
    }

    char verifica_castigatorul(char** board,int rows)
    {
        //check rows
        for(int i=0;i<3;i++)
        {
            if(board[i][0]==board[i][1] && board[i][0]==board[i][2])
            {
                return board[i][0];
            }
        }

        //check coloumns
        for(int i=0;i<3;i++)
        {
            if(board[0][i]==board[1][i] && board[0][i]==board[2][i])
            {
                return board[0][i];
            }
        }

        //check diagonals
        if(board[0][0]==board[1][1] && board[0][0]==board[2][2])
        {
            return board[1][1];
        }

        //check the second diagonal
        if(board[0][2]==board[1][1] && board[0][2]==board[2][0])
        {
            return board[0][2];
        }

        return ' ';
    }

    void playerMove(char** board)
    {
        int x;
        int y;
        do
        {
            printf("Enter row number: ");
            scanf("%d",&x);
            x--; //userul va introduce un numar de la 1-3 scadem cu 1 deoarece indexarea incepe de 0
            printf("Enter coloumn number: ");
            scanf("%d",&y);
            y--; //la fel si pentru numarul de coloane;

            if(board[x][y]!=' ')
            {
                printf("Invalid move!\n");
            }
            else
            {
                board[x][y]=PLAYER;
                break;
            }
        } while (board[x][y]!=' ');
    }
    
    int verifica_spatii_libere(char** board)
    {
        int freeSpace=9;
        for(int i=0;i<3;i++)
        {
            for(int j=0;j<3;j++)
            {
                if(board[i][j]!=' ')
                {
                    freeSpace--;
                }
            }
        }
        return freeSpace;
    }

    void computerMove(char** board)
    {
        srand(time(NULL));
        int x;
        int y;

        if(verifica_spatii_libere(board)>0)
        {
            do
            {
                x=rand()%3;
                y=rand()%3;
            } while (board[x][y] !=' ');
            board[x][y]=COMPUTER;
        }
        else
        {
            printeaza_castigator(' ');
        }
    }

int main()
{
    int rows=3;
    int cols=3;
    char** board=(char**)malloc(rows*sizeof(char*));
    if(board==NULL)
    {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for(int i=0;i<3;i++)
    {
        board[i]=(char*)malloc(cols*sizeof(char));
    }
    resetare_joc(board);
    char winner= ' ';
    
    while(winner==' ' && verifica_spatii_libere(board)!=0)
    {
        printeaza_tabla_de_joc(board);  

        playerMove(board);
        winner=verifica_castigatorul(board,rows);
        if(winner!=' ' || verifica_spatii_libere(board)==0)
        {
            break;
        }
        
        computerMove(board);
        winner=verifica_castigatorul(board,rows);
        if(winner!=' ' || verifica_spatii_libere(board)==0)
        {
            break;
        }
    }
    printeaza_tabla_de_joc(board);
    printeaza_castigator(winner);
    
    for(int i=0;i<rows;i++)
    {
        free(board[i]);
    }
    free(board);
    return 0;
}
