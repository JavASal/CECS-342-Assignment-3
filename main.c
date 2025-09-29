/* Name: Javier Salamanca
   Date: 09/27/25
   Assignment #3 - Grid Area Counter using Depth First Search implemented with a linked stack.
*/

#include <stdio.h>
#include <stdlib.h>

/* Structure: Point
Represents a location in the grid that will be placed on the stack.
[document your struct's variables here]
*/
struct Point{
    int pLocation[2];
    struct Point *next;
};

/* Structure: Stack
Represents a Stack data structure to store Point objects in LIFO order.
[document your struct's variables here]
*/
struct Stack{
    struct Point *top;
};

/* Function: push
Adds a new Point object to the top of the stack.
struct Stack *stack - [fill in your documentation here]
int r - [fill in your documentation here]
int c - [fill in your documentation here]
*/
void push(struct Stack *stack, int r, int c) {
    struct Point *temp = (struct Point*)malloc(sizeof(struct Point));
    temp->pLocation[0] = c;
    temp->pLocation[1] = r;
    temp->next = stack->top;

    stack->top = temp;
}

/* Function: pop
Removes and deallocates the Point object from the top of the stack.
struct Stack *stack - [fill in your documentation here]
int *retloc - return parameter - [fill in your documentation here]
*/
void pop(struct Stack *stack, int *retloc) {
    retloc[0] = stack->top->pLocation[0];
    retloc[1] = stack->top->pLocation[1];

    struct Point *temp = stack->top;

    stack->top = stack->top->next;
    free(temp);
}


/* Function: print_grid
Displays the contents of the grid in a matrix format.
char **grid - [fill in your documentation here]
int rows - [fill in your documentation here]
int cols - [fill in your documentation here]
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
            grid[i] = (char *)malloc(sizeof(char *) * (cols + 1));
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


    
    //initialize stack
    struct Stack myStack;
    myStack.top = NULL;

    for(size_t i = 0; i < rows && myStack.top == NULL; ++i){
        for(size_t j = 0; j < cols && myStack.top == NULL; ++j){
            if (grid[i][j] =='o'){
                push(&myStack, i, j);
            }
        }
    }
    if(myStack.top == NULL){
        printf("No \'o\' found in grid.");
        exit(0);
    }






    //traverse the grid to find initial 'o' for each area




                //repeat while there is still items on the stack


                    //pop an item from the stack

                    //check neighboring positions for 'o's and place them on the stack
                    //note: you should also make sure you're not going out of bounds







                //display result of each area


    //clean up - free everything that was allocated on the heap





    
    return 0;
}