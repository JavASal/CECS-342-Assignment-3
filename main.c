/* Name: Javier Salamanca
   Date: 09/27/25
   Assignment #3 - Grid Area Counter using Depth First Search implemented with a linked stack.
*/

#include <stdio.h>
#include <stdlib.h>

/* Structure: Point
Represents a location in the grid that will be placed on the stack.
- pLocation: an array of 2 integers that hold the row and column of a given point
- next: a pointer to the next Point struct in the stack
*/
struct Point{
    int pLocation[2];
    struct Point *next;
};

/* Structure: Stack
Represents a Stack data structure to store Point objects in LIFO order.
- p: pointer to the top Point on the stack
*/
struct Stack{
    struct Point *p;
};

/* Function: push
Adds a new Point object to the top of the stack.
struct Stack *stack - [fill in your documentation here]
int r - used to pass the row index to be stored on the dynamically created point
int c - used to pass the column index to be stored on the dynamically created point
*/
void push(struct Stack *stack, int r, int c) {
    struct Point *temp = (struct Point*)malloc(sizeof(struct Point));
    temp->pLocation[0] = r;
    temp->pLocation[1] = c;
    temp->next = stack->p;

    stack->p = temp;
}

/* Function: pop
Removes and deallocates the Point object from the top of the stack.
struct Stack *stack - pointer to stack where item will be popped from
int *retloc - return parameter - array of 2 integers that is used to return the indices of the point that was popped from the stack
*/
void pop(struct Stack *stack, int *retloc) {
    retloc[0] = stack->p->pLocation[0];
    retloc[1] = stack->p->pLocation[1];

    struct Point *temp = stack->p;

    stack->p = stack->p->next;
    free(temp);
    temp = NULL;
}


/* Function: print_grid
Displays the contents of the grid in a matrix format.
char **grid - pointer to an array of char points that holds the grid which was read in from the grid file
int rows - passes in the integer read from the grid file that signifies the number of rows
int cols - passes in the integer read from the grid file that signifies the number of colums
*/
void print_grid(char **grid, int rows, int cols) {
    for(size_t i = 0; i < rows; ++i){
        for(size_t j = 0; j < cols; ++j){
            printf("%c", grid[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    //open file
    FILE *fptr = fopen("grid.txt", "r");
    int rows, cols;
    char **grid;
    if(fptr != NULL) {
        //get rows & cols from file
        char c;
        fscanf(fptr, "%d%d%c", &rows, &cols, &c);
        //dynamically allocate 2D array
        grid = (char **)malloc(sizeof(char *) * rows);
        for(size_t i = 0; i < rows; ++i){
            grid[i] = (char *)malloc(sizeof(char *) * (cols));
        }




        //read in grid
        for(int i = 0; i < rows; i++) {
            for(int j = 0; j <= cols; j++) {
                char ch = fgetc(fptr);
                if(ch != '\n') {
                    grid[i][j] = ch;
                }
            }
        }
    } else {
        printf("ERROR - cannot open file.\n");
    }
    fclose(fptr);
    
    //display the grid
    print_grid(grid, rows, cols);
    printf("\n");


    
    //initialize stack
    struct Stack myStack;
    myStack.p = nullptr;



    int areaSize = 0;
    int areaCounter = 1;

    //pop function required a "return" array of 2 ints, not quite sure what for
    int lastSeen[2] = {0, 0};

    for (int i  = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j] == 'o') {
                push(&myStack, i, j);
                ++areaSize;
                //mark as seen
                grid[i][j] = 'x';

                //Checks neighboring cells after finding initial 'o' char.
                //repeat while there is still items on the stack
                //check neighboring positions for 'o's and place them on the stack
                //note: you should also make sure you're not going out of bounds
                while (myStack.p != NULL) {
                    //Checks if left cell is within bounds then checks if cell contains 'o'
                    if (myStack.p->pLocation[1] - 1 >= 0 && grid[myStack.p->pLocation[0]][myStack.p->pLocation[1] - 1] == 'o') {
                        grid[myStack.p->pLocation[0]][myStack.p->pLocation[1] - 1] = 'x';
                        push(&myStack, myStack.p->pLocation[0], myStack.p->pLocation[1] - 1);
                        ++areaSize;
                    }
                    //Checks if right cell is within bounds then checks if cell contains 'o'
                    else if(myStack.p->pLocation[1] + 1 < cols && grid[myStack.p->pLocation[0]][myStack.p->pLocation[1] + 1] == 'o') {
                        grid[myStack.p->pLocation[0]][myStack.p->pLocation[1] + 1] = 'x';
                        push(&myStack, myStack.p->pLocation[0], myStack.p->pLocation[1] + 1);
                        ++areaSize;
                    }
                    //Checks if upper cell is within bounds then checks if cell contains 'o'
                    else if (myStack.p->pLocation[0] - 1 >= 0 && grid[myStack.p->pLocation[0] - 1][myStack.p->pLocation[1]] == 'o') {
                        grid[myStack.p->pLocation[0] - 1][myStack.p->pLocation[1]] = 'x';
                        push(&myStack, myStack.p->pLocation[0] - 1, myStack.p->pLocation[1]);
                        ++areaSize;
                    }
                    //Checks if lower cell is within bounds then checks if cell contains 'o'
                    else if (myStack.p->pLocation[0] + 1 < rows && grid[myStack.p->pLocation[0] + 1][myStack.p->pLocation[1]] == 'o') {
                        grid[myStack.p->pLocation[0] + 1][myStack.p->pLocation[1]] = 'x';
                        push(&myStack, myStack.p->pLocation[0] + 1, myStack.p->pLocation[1]);
                        ++areaSize;
                    }
                    //If there are no accessible neighboring cells or accessible ones do not contain 'o', then the point being checked is popped from stack
                    //pop an item from the stack
                    else {
                        pop(&myStack, &lastSeen[0]);
                    }
                }
                //display result of each area
                printf("Area %d = %d\n", areaCounter, areaSize);
                areaCounter++;
                areaSize = 0;
            }
        }
    }
    //clean up - free everything that was allocated on the heap
    //at this point everything that was dynamically on the stack should have been freed through the pop function
    for (int i = 0; i < rows; ++i) {
        free(grid[i]);
        grid[i] = nullptr;
    }
    free(grid);
    grid = nullptr;
    return 0;
}