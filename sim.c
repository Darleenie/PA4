/**
 * Assignment: SWLife
 * Section: (A, B, C)
 * Class: UCSD CSE30-fall2019
 *
 */
#include "sim.h"

#define CIMP
extern void asm_doRow(belem *, belem *, belem *, uint32_t);

/**
 * process one row of the board
 */
static void doRow(belem *dest, belem *srcStart, belem * srcEnd, uint32_t cols){
	uint32_t numAliveN;
	uint32_t isAlive;
	//going thru all cells
	//and count alive neighbors in currentBuffer
	while(srcStart != srcEnd){
		numAliveN = 0;
		isAlive = *srcStart;
		numAliveN += *(srcStart-cols);//up dir check
		numAliveN += *(srcStart+cols);//dw dir check
		numAliveN += *(srcStart-1);//le dir check
		numAliveN += *(srcStart-cols-1);//le+up dir check
		numAliveN += *(srcStart+cols-1);//le+dw dir check
		numAliveN += *(srcStart+1);//ri dir check
		numAliveN += *(srcStart-cols+1);//ri+up dir check
		numAliveN += *(srcStart+cols+1);//ri+dw dir check
		if(isAlive == 1){
			//if 2 or 3 neighbers ---> alive
			//if 0 or 1 neighbors ---> dead
			//if 4+ ---> dead
			if(!(numAliveN == 2 || numAliveN == 3)){
				*dest = 0;
			}else{
				*dest = 1;
			}

		}else{
			//For dead cells
			//if exactly 3 neighbors ---> alive
			if(numAliveN == 3){
				*dest = 1;
			}else{
				*dest = 0;
			}
		}

		srcStart++;//update srcStart
		dest++;//update dest with srcStart

	}
}


/**
 * perform a simulation for "steps" generations
 *
 * for steps
 *   calculate the next board
 *   swap current and next
 */
void simLoop(boards_t *self, uint32_t steps){
	uint32_t cols = self->numCols;
	belem *dest;//pointer on nextBuffer
	belem *srcStart;//pointer start on currentBuffer
	belem *srcEnd;//pointer end on currentBuffer

	//run the process "steps" times
	while(steps > 0){
		//update the valid part of the board
		for(uint32_t i = 1; i < (self->numRows)-1; i++){
			//find the line and go to the proper position
			dest = (self->nextBuffer)+getIndex(self,i, 1);
			srcStart  = (self->currentBuffer)+getIndex(self,i, 1);
			srcEnd = (self->currentBuffer)+getIndex(self,i, cols-1);

			doRow(dest, srcStart, srcEnd, cols);
		}

		//swap Buffers
		swapBuffers(self);
		//update gen
		(self->gen)++;
		//update steps
		steps--;
	}
}




