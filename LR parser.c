#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <ctype.h>

#define MAXLINE 255 //setting input length to 255

int main(int argc, char* argv[])
{
    char input[MAXLINE];    //input string
    char output[MAXLINE];   //output string
    char stack[MAXLINE];    //stack string
    int temp = 0;           //temp int
    int accept = 0;         //if the string is accepted
    int pushing = 0;        //bool if pushing onto stack
    int error = 0;          //bool if error or string not accepted
    int tableEntry = 0;     //keeps track table entry

    int x = 0;  //x cord for table
    int y = 0;  //y cord for table

    //  Action Table reference
    // -1 = null 
    //  0 = accept
    //  1 = S4
    //  2 = S5
    //  3 = S6
    //  4 = S7
    //  5 = S8
    //  6 = S9
    //  7 = S15
    //  8 = R1
    //  9 = R2
    //  10 = R3
    //  11 = R4
    //  12 = R5
    //  13 = R6
    //  14 = R7
    //  15 = R8

    int actionTable[16][8] =
    {
    //i | + | - | * | / | ( | ) | $ |
    { 2 ,-1 ,-1 ,-1 ,-1 , 1 ,-1 ,-1 },  //0
    {-1 , 3 , 4 ,-1 ,-1 ,-1 ,-1 , 0 },  //1
    {-1 ,10 ,10 , 5 , 6 ,-1 ,10 ,10 },  //2
    {-1 ,13 ,13 ,13 ,13 ,-1 ,13 ,13 },  //3
    { 2 ,-1 ,-1 ,-1 ,-1 , 1 ,-1 ,-1 },  //4
    {-1 ,15 ,15 ,15 ,15 ,-1 ,15 ,15 },  //5
    { 2 ,-1 ,-1 ,-1 ,-1 , 1 ,-1 ,-1 },  //6
    { 2 ,-1 ,-1 ,-1 ,-1 , 1 ,-1 ,-1 },  //7
    { 2 ,-1 ,-1 ,-1 ,-1 , 1 ,-1 ,-1 },  //8
    { 2 ,-1 ,-1 ,-1 ,-1 , 1 ,-1 ,-1 },  //9
    {-1 , 3 , 4 ,-1 ,-1 ,-1 , 7 ,-1 },  //10
    {-1 , 8 , 8 , 5 , 6 ,-1 , 8 , 8 },  //11
    {-1 , 9 , 9 , 5 , 6 ,-1 , 9 , 9 },  //12
    {-1 ,11 ,11 ,11 ,11 ,-1 ,11 ,11 },  //13
    {-1 ,12 ,12 ,12 ,12 ,-1 ,12 ,12 },  //14
    {-1 ,14 ,14 ,14 ,14 ,-1 ,14 ,14 },  //15
    };

    int gotoTable[16][3] =
    {
    //E | T | F |
    { 1 , 2 , 3},  //0
    {-1 ,-1 ,-1},  //1
    {-1 ,-1 ,-1},  //2
    {-1 ,-1 ,-1},  //3
    {10 , 2 , 3},  //4
    {-1 ,-1 ,-1},  //5
    {-1 ,11 , 3},  //6
    {-1 ,12 , 3},  //7
    {-1 ,-1 ,13},  //8
    {-1 ,-1 ,14},  //9
    {-1 ,-1 ,-1},  //10
    {-1 ,-1 ,-1},  //11
    {-1 ,-1 ,-1},  //12
    {-1 ,-1 ,-1},  //13
    {-1 ,-1 ,-1},  //14
    {-1 ,-1 ,-1},  //15
    };

    //input
    printf("Enter an input string:\n");
    gets(input);
    printf("\nstack \t\t input\n");

    //initalize stack
    stack[0] = '0';
    printf("%s \t\t %s\n", stack, input);

    for(int i = 0; i < strlen(input); i++)
    {
        pushing = 1;
        while(pushing && !(error))
        {
            //x cord
            switch (input[i])
            {
            case 'i': x = 0; 
                break;
            case '+': x = 1; 
                break;
            case '-': x = 2; 
                break;
            case '*': x = 3; 
                break;
            case '/': x = 4; 
                break;
            case '(': x = 5; 
                break;
            case ')': x = 6; 
                break;
            case '$': x = 7; 
                break;
            default:
                error = 1;
            }

            //y cord
            y = (stack[strlen(stack) - 1] - '0');
            if(stack[strlen(stack) - 2] == '1')
            {
                y = 10 + y;
            }

            //table
            tableEntry = actionTable[y][x];
            switch (tableEntry)
            {
            case 0:  // accept
                accept = 1;
                break;

            case 1:  // S4
            case 2:  // S5
            case 3:  // S6
            case 4:  // S7
            case 5:  // S8
            case 6:  // S9
                temp = strlen(stack);
                stack[temp] = input[i]; //push onto stack
                input[i] = ' ';         //delete from input
                stack[temp + 1] = '3' + tableEntry; //pushes S# onto stack
                stack[temp + 2] = '\0';
                pushing = 0;
                break;

            case 7:  // S15 
                temp = strlen(stack);
                stack[temp] = input[i]; //push onto stack
                input[i] = ' ';         //delete from input
                stack[temp + 1] = '1';
                stack[temp + 2] = '5';
                stack[temp + 3] = '\0';
                pushing = 0;
                break;

            case 8:  // R1
            case 9:  // R2 
                temp = strlen(stack) - 1;
                while(stack[temp] != 'E')
                {
                    //pop elements off until E
                    stack[temp] = '\0';
                    temp--;
                };
                x = 0;  //goto table for E
                break;

            case 10:  // R3
                temp = strlen(stack) - 1;
                while(stack[temp] != 'T')
                {
                    //pop elements off until T
                    stack[temp] = '\0';
                    temp--;
                };

                stack[temp] = 'E'; // production E -> T
                x = 0;  //goto table for E
                break;

            case 11:  // R4
            case 12:  // R5
                temp = strlen(stack) - 1;
                while(stack[temp] != 'T')
                {
                    //pop elements off until T
                    stack[temp] = '\0';
                    temp--;
                };
                x = 1;  //goto table for T
                break;

            case 13:  // R6
                temp = strlen(stack) - 1;
                while(stack[temp] != 'F')
                {
                    //pop elements off until F
                    stack[temp] = '\0';
                    temp--;
                };

                stack[temp] = 'T'; // production T -> F
                x = 1;  //goto table for T
                break;
            
            case 14:  // R7
                temp = strlen(stack) - 1;
                while(stack[temp] != '(')
                {
                    //pop elements off until (
                    stack[temp] = '\0';
                    temp--;
                };

                stack[temp] = 'F'; // production F -> (E)
                x = 2;  //goto table for F
                break;

            case 15:  // R8
                temp = strlen(stack) - 1;
                while(stack[temp] != 'i')
                {
                    //pop elements off until i
                    stack[temp] = '\0';
                    temp--;
                };

                stack[temp] = 'F'; // production F -> i
                x = 2;  //goto table for F
                break;

            default:
                error = 1;
            }//end switch

            //goto table look up for reduce actions
            if(tableEntry > 7)
            {
                temp = strlen(stack);
                y = (stack[temp - 2] - '0');
                if(stack[temp - 3] == '1')
                {
                    y = y + 10;
                }
                if(gotoTable[y][x] > 9)
                {
                    stack[temp] = '1';
                    stack[temp + 1] = '0' + (gotoTable[y][x] % 10);
                    stack[temp + 2] = '\0';
                }
                else
                {
                    stack[temp] = '0' + gotoTable[y][x];
                    stack[temp + 1] = '\0';
                }
                pushing = 1;    //sets while loop to run again since not pushing input onto stack
            }

            //early break for accept or error
            if(accept || error)
            {
                break;
            }

            //print stack and input
            if(strlen(stack) < 7)
            {
                printf("%s \t\t %s\n", stack, input);
            }
            else
            {
                printf("%s \t %s\n", stack, input);
            }
        }//end while

    }//end for

    //if string accepted
    if(accept)
    {
        printf("\nString accepted\n");
    }
    else
    {
        printf("\nString not accepted\n");
    }

    system("pause");
    return 0;
}