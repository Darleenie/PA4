/**
 * Assignment: SWLife
 * Section: (A, B, C)
 * Class: UCSD CSE30-fall2019
 *
 */
#include "cse30life.h"
#include "board.h"


/**
 * create a new board
 *
 * - malloc a boards structure
 * - set the generation to 0
 * - open the file (if it doesn't exist, return a NULL pointer
 * - read the first line which is the number of rows
 * - read the second line which is the number of cols
 * - set the # of rows and # of cols in the boards structure
 * - malloc bufferA and bufferB 
 * - Set currentBuffer and nextBuffer
 * - clear both board buffers
 * - read the file until done.  each row contains a row and a columns separted by
 *   white space
 *     for each line, set the cell in the current buffer
 * - close the file
 * - return the boards pointer
 */
boards_t * createBoard(char *initFileName){
	//allocate memory
	boards_t *boards = malloc(sizeof(boards_t));
	if(boards == NULL){
		free(boards);
		boards = NULL;
		return NULL;
	}

	//set gen to be 0
	boards->gen = 0;

	//read number of cols and rows
	FILE *fp;

	if((fp = fopen(initFileName, "r")) == NULL){
		return NULL;
	}
	uint32_t row = 0;
	uint32_t col = 0;

	fscanf(fp, "%d", &row);
	boards->numRows = row;
	fscanf(fp, "%d", &col);
	boards->numCols = col;

	//initialize bufferA and bufferB
	boards->bufferA = calloc((boards->numRows)*(boards->numCols),sizeof(belem));
	boards->bufferB = calloc((boards->numRows)*(boards->numCols),sizeof(belem));
	if(boards->bufferA == NULL || boards->bufferB == NULL){
		free(boards->bufferA);
		free(boards->bufferB);
		boards->bufferA = NULL;
		boards->bufferB = NULL;
		free(boards);
		boards = NULL;

		return NULL;
	}

	//initialize struct's currentBuffer and nextBuffer and clear
	boards->currentBuffer = boards->bufferA;
	boards->nextBuffer = boards->bufferB;

	clearBoards(boards);

	//initialize the currentBuffer

	while(fscanf(fp, "%d %d", &row, &col) > 0){
		boards->currentBuffer[getIndex(boards, row, col)] = 1;
	}

	fclose(fp);

	return boards;

}



/**
 * delete a board
 */
void deleteBoard(boards_t **bptrPtr){

	free((*bptrPtr)->bufferA);
	free((*bptrPtr)->bufferB);
	(*bptrPtr)->currentBuffer = NULL;
	(*bptrPtr)->nextBuffer = NULL;
	(*bptrPtr)->bufferA = NULL;
	(*bptrPtr)->bufferB = NULL;


	free(*bptrPtr);
	*bptrPtr = NULL;

}

/**
 * set all the belems in both buffers to 0
 */
void clearBoards(boards_t *self){
	for(uint32_t i = 0; i < self->numRows; i++){
		for(uint32_t j = 0; j < self->numCols; j++){
			(self->currentBuffer)[getIndex(self, i, j)] = 0;
			(self->nextBuffer)[getIndex(self, i, j)] = 0;
		}
	}
}

/**
 * swap the current and next buffers
 */
void swapBuffers(boards_t *self){
	belem *temp = NULL;
	temp = self->currentBuffer;
	self->currentBuffer = self->nextBuffer;
	self->nextBuffer = temp;
}


/**
 * get a cell index
 */
int getIndex(boards_t *self, int row, int col){
	return row * (self->numCols) + col;
}

