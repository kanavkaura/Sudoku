#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


int board[9][9]; //9x9 sudoku board
int corrects[11]; //returns a 1 to a valid, and 0 if it doesnt
int threegrid = 2; //goes thru threexthree subgrid
int fake[9][9];


/* struct is created to send info thru each thread */
typedef struct{

    int row;
    int column;

}parameters;

pthread_t cct, rrt, onet, twot, threet, fourt, fivet, sixt, sevent, eightt, ninet;

/* 3x3, for rows and columns */
void *colm(void *pm);
void *rowr(void *pm);
void *sq1w(void *pm);


int main(int argc, char *argv[])
{
   	int a = 0; //for loop to elements in board array
	int b = 0; 
    int x = 0; //check array to see if its correct
    int y=0;


        
	FILE *sudoku;
	sudoku = fopen(argv[1], "r"); //reading the file and opening it from arg
	printf("Sudoku Puzzle input is: \n "); //print statement
	for(b = 0; b < 10; b++){
		for(a = 0; a < 10; a++){
			fscanf(sudoku, "%d ", &fake[b][a]);
			if(b!=0 && a!=0)
			{
				x=b-1;
				y=a-1;
				board[x][y] = fake[b][a];
			printf("%d ", board[x][y]);
			}
		}
		printf("\n");
	}

    /*checking the rows, columns, and smaller 3x3 matrixs*/
    parameters *cRow = (parameters *) malloc(sizeof(parameters)); //the rows
    cRow->row = 0;
    cRow->column = 0;

    parameters *cCol = (parameters *) malloc(sizeof(parameters)); //the columns
    cCol->row = 0;
    cCol->column = 0;

    parameters *first3sub = (parameters *) malloc(sizeof(parameters)); //first 3x3
    first3sub->row = 0;
    first3sub->column = 0;

    parameters *second3sub = (parameters *) malloc(sizeof(parameters)); //2nd 3x3
    second3sub->row = 0;
    second3sub->column = 3;

    parameters *third3sub = (parameters *) malloc(sizeof(parameters)); //3rd 3x3
    third3sub->row = 0;
    third3sub->column = 6;

    parameters *four3sub = (parameters *) malloc(sizeof(parameters)); //4th 3x3
    four3sub->row = 3;
    four3sub->column = 0;

    parameters *five3sub = (parameters *) malloc(sizeof(parameters)); //5th 3x3
    five3sub->row = 3;
    five3sub->column = 3;

    parameters *six3sub = (parameters *) malloc(sizeof(parameters)); //6th 3x3
    six3sub->row = 3;
    six3sub->column = 6;

    parameters *seven3sub = (parameters *) malloc(sizeof(parameters)); //7th 3x3
    seven3sub->row = 6;
    seven3sub->column = 0;

    parameters *eight3sub = (parameters *) malloc(sizeof(parameters)); //8th 3x3
    eight3sub->row = 6;
    eight3sub->column = 3;

    parameters *nine3sub = (parameters *) malloc(sizeof(parameters)); //9th 3x3
    nine3sub->row = 6;
    nine3sub->column = 6;


        //when pthread joined
    void * roww;
    void * coll;
    void * onesq;
    void * twosq;
    void * threesq;
    void * foursq;
    void * fivesq;
    void * sixsq;
    void * sevensq;
    void * eightsq;
    void * ninesq;


        //creating the pthreads 
    pthread_create(&cct, NULL, colm, (void *) cRow);
    pthread_create(&rrt, NULL, rowr, (void *) cCol);
    pthread_create(&onet, NULL, sq1w, (void *) first3sub);
    pthread_create(&twot, NULL, sq1w, (void *) second3sub);
    pthread_create(&threet, NULL, sq1w, (void *) third3sub);
    pthread_create(&fourt, NULL, sq1w, (void *) four3sub);
    pthread_create(&fivet, NULL, sq1w, (void *) five3sub);
    pthread_create(&sixt, NULL, sq1w, (void *) six3sub);
    pthread_create(&sevent, NULL, sq1w, (void *) seven3sub);
    pthread_create(&eightt, NULL, sq1w, (void *) eight3sub);
    pthread_create(&ninet, NULL, sq1w, (void *) nine3sub);



	/*need to use join for each specifc child so the parent will wait */
	pthread_join(cct, &coll);
    pthread_join(rrt, &roww);
    pthread_join(onet, &onesq);
    pthread_join(twot, &twosq);
    pthread_join(threet, &threesq);
    pthread_join(fourt, &foursq);
    pthread_join(fivet, &fivesq);
    pthread_join(sixt, &sixsq);
    pthread_join(sevent, &sevensq);
    pthread_join(eightt, &eightsq);
    pthread_join(ninet, &ninesq);


        /* checking to see if they all correct, they should ==1, then k will increase*/
	while(x < 11){


		if(corrects[x] == 1){
			x++;
        }
        else{
        	printf("The Sudoku Puzzle is invalid. \n"); //print statement if its incorrect
        	exit(0);
        }
	}
    printf("Sudoku Puzzle is valid. \n"); //print statement if its correct
	return 0;
}



void *colm(void *prams) //checking the column 
{
    int a, b;
    parameters * colW= (parameters *) prams;
    int firstC = colW->column; //beginning of col
    int FirstR = colW->row; //beginning of row

    //there cannot be no numbers that are seen more then once in each column and row

    for(a = firstC; a < 9; a++){

	int cc[9]= {0}; //array created for the column

        for(b = FirstR; b < 9; b++){

            int numb = board[a][b]; //checking to find the number in the col



            if(cc[numb-1] == 0 && numb > 0){
            	cc[numb-1] = numb;
            }
		//if the numb != 0 then its either a duplicate or invalid so its not solved and sudoku not right
            else{
            	corrects[0] = 0;
                pthread_exit(0);
            }
        }
    }
    corrects[0] = 1;
    pthread_exit(0);
}



void *rowr(void *prams){ //checking for rows

    int a, b;

    parameters * r_worker = (parameters *) prams;
    int firstC = r_worker->column;
    int firstR = r_worker->row;

    //if row has dupes its not correct and returns 0

    for(a = firstC; a < 9; a++){

        int rr[9]= {0};//array crearted for rr

        for(b = firstR; b < 9; b++){

            int numb = board[a][b];

            
        //if value is 0 then its not correct
            if(rr[numb-1] == 0 && numb > 0){
                rr[numb-1] = numb;
            }

            else{
                corrects[1] = 0;
                pthread_exit(0);
            }
        }
    }
    corrects[1] = 1;
    pthread_exit(0);
}



void *sq1w(void *prams){ //checking the 3x3s

    int a, b;
    parameters * check = (parameters *) prams;
    int firstR = check->row;
    int firstC = check->column;


    int sqqr[9] = {0}; //an array thats one dimension to chekc the 3x3

    for (a = firstR; a < firstR + 3; ++a) {
        for (b = firstC; b < firstC + 3; ++b) {
            int numb = board[a][b];
            
            if (sqqr[numb-1] == 0 && numb > 0) {
                sqqr[numb-1] = numb;
            }
            //if value is 0 then its not correct
            else{
                corrects[threegrid] = 0;
                threegrid++;
                pthread_exit(0);
            }
        }
    }
    corrects[threegrid] = 1;
    threegrid++;
    pthread_exit(0);
}
