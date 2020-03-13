#include<stdio.h>
#include<stdlib.h>

// Include my helper functions and structs.
/* ----------------------- Data Structures -------------------------------- */

/* Node */
typedef struct node {
	int x;
	int y;
	struct node *next;
} Node;
/* End Node*/

/* Stack */
typedef struct stack {
	Node *top;
} Stack;

// Inserts a node into the stack.
void push(Stack *s, int x, int y) {
	Node *n = (Node *) calloc(1, sizeof(Node));
	if (n == NULL) return;
	n->x = x;
	n->y = y;
	n->next = s->top;
	s->top = n;
}

// Removes a node from the stack.
// Returns NULL if stack is empty.
Node *pop(Stack *s) {
	// Is stack empty?
	if (s->top == NULL) return NULL;

	// Remove node at top of stack.
	Node *n = s->top;
	s->top = s->top->next;

    // Make sure the removed node does not reference stack.
    n->next = NULL;

	return n;
}

// Determine if stack is empty. 
// Return 1 if stack is empty.
// Return 0 if stack is not empty
int isEmpty(Stack *s) {
	return s->top == NULL;
}

/* End Stack */

/* Linked List */

// Insert at head.
Node *insert(Node *head, int x, int y) {
    Node *n = (Node *) calloc(1, sizeof(Node));
	if (n == NULL) return NULL;
	n->x = x;
	n->y = y;
    
    if (head == NULL) return n;
    n->next = head;
    return n;
}

// Recursive search.
Node *search(Node *head, int x, int y) {
    if (head == NULL) return NULL;
    if (head->x == x && head->y == y) return head;
    return search(head->next, x, y);
}


/* End Linked List */

/* ------------------------------------------------------------------------ */

void printImgArray(char array[10][10])
{
 // Print out the contents of the array, it can be
 // used with the original array, or with the labeled
 // output after calling cell_count().
  
 printf("------ Image Contents -------\n");
 for (int i=0; i<10; i++)
 {
   for (int j=0; j<10; j++)
     printf("%c, ",array[i][j]);
   printf("\n");
 }
 printf("-----------------------------\n");
}

// Helper function to determine if a given co-orindate is on the map
// Return 1 if on map, and 0 otherwise.
int onmap(int x, int y) {
	return (x >= 0 && x < 10 && y >= 0 && y < 10);
}

void floodFill(char image[10][10], int x, int y, char value, char bound)
{
 // This function takes as input a 2D image array
 // which contains pixel values. 
 //
 // It floodFills (if you haven't tried floodfill,
 // open up a picture editor and use the paint tool!)
 // starting at location (x,y), filling the image
 // with the specified 'value', up to (but not
 // including) the boundary of the shape in the
 // picture, whose colour is given by 'bound'
 //
 // This function should do its work NON-recursively!
  
 // TO DO: Complete this function!

	// We've reached the boundary before even starting, exit the function.
	if ((int) image[x][y] == (int) bound) return;

	// I need a stack to keep track of which co-ordinates I will visit next.
	Stack *stack = (Stack *) calloc(1, sizeof(Stack));
	if (stack == NULL) return;

	// I need a list to keep track of visited co-ordinates.
	Node *visited = (Node *) calloc(1, sizeof(Node));

	// A node variable to keep track of co-ordinate I am analyzing.
	Node *node;

	// An offset array that will be used to visit the neighbouring (x, y) co-ordinates.
	int offset[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

	// Visit start co-ordinate.
	image[x][y] = value;
	push(stack, x, y);
	visited = insert(visited, x, y);

	// Variables to keep track of current co-ordinates we are visiting.
	int curr_x;
	int curr_y;

	// Keep visiting co-ordinates until you can't visit anymore!
	while (!isEmpty(stack)) {
		// Remove co-ordinate from queue to being analysis.
		node = pop(stack);

		// Visit all of the neighbours! (up, down, left, right)
		for (int i = 0; i < 4; i++) {
			curr_x = (node->x) + offset[i][0];
			curr_y = (node->y) + offset[i][1];
		
			// If the co-ordinate above exists on the map, has not been visited, and is not a boundary.
			if (onmap(curr_x, curr_y) && !search(visited, curr_x, curr_y) && 
					(int) image[curr_x][curr_y] != (int) bound) {
				// visit the co-ordinate.
				image[curr_x][curr_y] = value;
				push(stack, curr_x, curr_y);
				visited = insert(visited, curr_x, curr_y);
			}
		}
	}
}

void floodFill_R(char image[10][10], int x, int y, char value, char bound)
{
 // This function takes as input a 2D image array
 // which contains pixel values. 
 //
 // It floodFills (if you haven't tried floodfill,
 // open up a picture editor and use the paint tool!)
 // starting at location (x,y), filling the image
 // with the specified 'value', up to (but not
 // including) the boundary of the shape in the
 // picture, whose colour is given by 'bound'
 //
 // This function should do its work recursively!
  
 // TO DO: Complete this function!

	// Co-ordinate does not exist, exit the function.
	if (!onmap(x, y)) return;

 	// We've reached the boundary before even starting, exit the function.
	if ((int) image[x][y] == (int) bound) return;

	// We've already sen this node, exit the function.
	if ((int) image[x][y] == (int) value) return;

	// Visit current co-ordinate.
	image[x][y] = value;

	// Recursively fill up/down/left/right.
	floodFill_R(image, x + 1, y, value, bound);
	floodFill_R(image, x - 1, y, value, bound);
	floodFill_R(image, x, y + 1, value, bound);
	floodFill_R(image, x, y - 1, value, bound);
}

int main()
{
  char polyImg[10][10]={{'_','_','_','_','_','_','_','_','_','_'},
		               {'_','_','X','_','_','_','_','X','_','_'},
		               {'_','X','_','X','_','_','X','_','X','_'},
		               {'_','X','_','_','X','_','X','_','X','_'},
		               {'_','_','X','_','X','X','_','_','X','_'},
		               {'_','_','X','_','_','_','_','X','X','_'},
		               {'_','X','_','_','_','X','_','X','_','_'},
		               {'_','_','X','_','X','X','_','_','X','_'},
		               {'_','_','X','X','_','_','X','X','X','_'},
		               {'_','_','_','_','_','_','_','_','_','_'}};
		       
  printImgArray(polyImg);
  floodFill(polyImg,5,4,'a','X');
  printImgArray(polyImg);
  
  return 0;
}

