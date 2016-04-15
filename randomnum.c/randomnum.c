//randomnum by George Dimitrakopoulos 2004 Public Domain
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

//define some colors
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define RESET "\033[0m"

//define max numbers 
#define MAXNUMS 13


bool isValueInArray(int val, int *arr, int size);
int prand(int nums,int max);
int prandOne(int max, int *arr, int size);

int main()
{
    int numnums,max;
    int x=0;

    printf(KYEL "***************************\n" RESET);
    printf(KYEL "*" RESET "RANDOM NUMBER GENERATOR" KYEL "*" RESET  "\n");
    printf(KYEL "***************************\n" RESET);

    printf("Please enter how many random numbers to produce (" KGRN "max %d" RESET  "):",MAXNUMS);
    scanf("%d", &numnums);

    printf("Please enter maximum number value (" KGRN "default 45" RESET  "):");
    scanf("%d", &max);

    if ( numnums < 0 || numnums == 0 ) {
       printf("\nProducing 6 numbers...");
       numnums = 6;
    } else if (numnums > MAXNUMS) {
       printf("\nProducing  13 numbers...");
       numnums = MAXNUMS;
    } else {
       printf("\nProducing %d numbers...", numnums);
    }

    if (max < 0 || max == 0) {
        max = 45;
    }

   if (max < numnums) {
	printf(KRED "\n You cannot choose less numbers to be produced than the max possible value of them!\n" RESET);
	return 1;
   }

    printf("\n--------------");

    prand(numnums,max);

    printf("\n--------------\n thats all folks!\n");

    return 0;
}

int prand(int nums,int max) {
 int r,x=0;
 int numarr[MAXNUMS];

 srand(time(NULL)); // seed
 for(x=0;x<nums;x++) {
    r = prandOne(max,numarr,nums);   // ignore results over max

    numarr[x] = r; //store in array

    printf(KWHT "\n %d" RESET, r);
 }

 return 0;
}


int prandOne(int max, int *arr, int size) {
 bool isthere;
 int newnum = rand() % max;

//  printf("\n---->test num:%d",newnum);


 if (newnum == 0) {
    newnum = prandOne(max,arr,size);
 }

 isthere = isValueInArray(newnum,arr,size);

 if (isthere) {
   newnum = prandOne(max,arr,size);
 }

 return newnum;
}

bool isValueInArray(int val, int *arr, int size){
 int i;

 for (i=0; i < size; i++) {
    if (arr[i] == val)
       return true;
 }
 return false;
}

