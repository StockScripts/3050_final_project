#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "input_error.h"
#define MAX(a, b) (a)>(b)? (a):(b)

void free_arr( int** arr , int s );
void createArray(int *array,FILE *fp){
    int price;
    int i=0,j;
    while(!feof(fp)){
        if(!fscanf(fp,"%d",&price))
            exit(PARSING_ERROR_INVALID_FORMAT);
        array[i]=price;
        //printf("%d\n",array[i]);
        i++;
    }
}



int maxProfit(int k, int* prices, int size)
{
    int i,j;
    int **date;
    int counter=0;
    int q=0,w=1,e=0,r=1;
    int a=0,s=1,d=0,f=1,g=0,h=1;
    date = (int**)malloc(sizeof(int*)*(k));
    for(int i = 0; i <= k; i++)
    {
        date[i] = (int*)malloc(sizeof(int)*size);
        memset(date[i], 0, sizeof(int)*size);
    }
    if(size < 2){
            printf("We need more input numbers");
    
        return 0;
    }
    if(size==2||size==3){
        k=1;
    }
    if(size==4||size==5)
    {
        k=2;
    }
    if(k > size/2) //when it's unlimited, it can be easily handled -> corner case;
    {
        k=3;
    }
    int room=k;
    //printf("%d",k);
    if(k==size/2){
        k--;
    }

    int** t = (int**)malloc(sizeof(int*)*(room+1));
    for(int i = 0; i <= k; i++)
    {
        t[i] = (int*)malloc(sizeof(int)*size);
        memset(t[i], 0, sizeof(int)*size);
    }
    int cur = 0;
    for(i=1; i <= k; i++)
    {
        cur = -prices[0];
        for(j = 1; j < size; j++)
        {   
            t[i][j] = MAX(t[i][j-1], prices[j]+cur); //max profit sell at j;
            cur = MAX(cur, t[i-1][j-1]-prices[j]); //max profit buy at j;
            date[i][j]=cur;
            //printf("%d %d current %d\n",i,j,cur);
        }
        counter++;
    }
    int max=0;
    if(k==1){
    for(i=0;i<k+1;i++){
        for(j=0;j<size;j++){
            
            //printf("%d  ",t[i][j]);
        }
        //printf("\n");
    }
    for(i=0;i<k+1;i++){
        for(j=0;j<size;j++){
            
            //printf("date array %d  ",date[i][j]);
        }
        //printf("\n");
    }
    int z=1,x=size;
    for(i=0;i<size;i++){
        if(max<t[1][i]){
            max=t[1][i];
            x=i;
        }
        
    }
    for(i=0;i<x;i++){
        if(date[1][i]!=date[1][i+1]){
            z=i+1;
        }
    }
    if(z==1){
        z=0;
    }

    printf("%d\n%d\n",z+1,x+1);
    
    if(t[k][size-1]==0)
    printf("there is no result");
    }
    else if(k==2){
    for(i=0;i<size;i++){
        if(max<t[2][i]){
            max=t[2][i];
            q=i;
        }
    }
    for(i=0;i<q;i++){
        if(date[2][i]!=date[2][i+1]){
            w=i+1;
        }
    }
    max=0;
    for(i=0;i<w;i++){
        if(max<t[1][i]){
            max=t[1][i];
            e=i;
        }
       // printf("%d\n",t[1][i]);
    }
    //printf("r is %d\n",r);
    for(i=1;i<w-1;i++){
        if(date[1][i]!=date[1][i+1]){
            r=i+1;
        }
        //printf("%d\n",date[1][i]);
    }
    //printf("r is %d\n",r);
    if(r==1){
        r=0;
    }
    printf("%d\n%d\n%d\n%d\n",r+1,e+1,w+1,q+1);
    }
    else if(k==3){
    for(i=0;i<size;i++){
        if(max<t[3][i]){
            max=t[3][i];
            a=i;
        }
    }
    for(i=0;i<a;i++){
        if(date[3][i]!=date[3][i+1]){
            s=i+1;
        }
    }
        //printf("s is %d",s);
    for(i=0;i<size;i++){
        if(max<t[3][i]){
            max=t[3][i];
            a=i;
        }
    }
    for(i=0;i<a;i++){
        if(date[3][i]!=date[3][i+1]){
            s=i+1;
        }
    }
    max=0;
    for(i=0;i<s;i++){
        if(max<t[2][i]){
            max=t[2][i];
            d=i;
        }
        //printf("%d\n",t[2][i]);
    }
    //printf("r is %d\n",r);
    for(i=1;i<d;i++){
        if(date[2][i]!=date[2][i+1]){
            f=i+1;
        }
        //printf("%d\n",date[1][i]);
    }
    max=0;
    for(i=0;i<f;i++){
        if(max<t[1][i]){
            max=t[1][i];
            g=i;
            
        }
        //printf("%d qwe %d\n",t[1][i],i);
    }
    //printf("%d",g);
    for(i=0;i<g;i++){
        if(date[1][i]!=date[1][i+1]){
            h=i+1;
        }
    }
    //printf("r is %d\n",r);
    if(h==1){
        h=0;
    }
    printf("%d\n%d\n%d\n%d\n%d\n%d\n",h+1,g+1,f+1,d+1,s+1,a+1);
    }
    //free(*date,size);
    //free(*t,size);
    

    return t[k][size-1];
}
void free_arr( int** arr , int s ) {
	
	int i = 0;
	
	for( i = 0; i < s; i++) {
		free(arr[i]);
	}
	
	free(arr);

}

int main(int argc,char *argv[])
{
    FILE *fp;
    char *file1;
    file1 = argv[3];
    fp = fopen(file1,"r");
        if(fp==NULL)
        exit(PARSING_ERROR_EMPTY_FILE);
    if(argc!=4){
        
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    if(fp==NULL){
        
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    if(!fopen(file1,"r")){
        exit(FILE_FAILED_TO_OPEN);
    }
    int *price_arr;
    int r;
    r=atoi(argv[2]);
    int n;
    n=atoi(argv[1]);
    //printf("%d %d",r,n);
    int max,min;
    price_arr=malloc(sizeof(int)*(n+1));
 
    createArray(price_arr,fp);
    max=maxProfit(r,price_arr,n);
    //printf("the max profit is %d\n",max);
    free(price_arr);
    fclose(fp);
        if(!fclose(fp)){
        exit(FILE_FAILED_TO_CLOSE);
    }
    return 0;
}
