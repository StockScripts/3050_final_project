#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../input_error.h"
#define MAX(a, b) (a)>(b)? (a):(b)
struct day{
    int buy[3];
    int sell[3];
    int extream;
};
struct day findMin(int *array,int n);
void createArray(int *array,FILE *fp){
    int price;
    int i=0,j;
    while(!feof(fp)){
        fscanf(fp,"%d",&price);
        array[i]=price;
        //printf("%d\n",array[i]);
        i++;
    }
}

struct day findMax(int *array,int n){
    int diff[n-1];
    int i, a,b;
    struct day day;
    for(i=0;i<n-1;i++){
        diff[i]=array[i+1]-array[i];
    }
    int max=diff[0];
    
    for(i=1;i<n-1;i++){
        if(diff[i-1]>0)
            diff[i]=diff[i]+diff[i-1];
        if(max<diff[i]){
            max=diff[i];
            a=i+1;
            
        }
    }
    for(i=0;i<n-1;i++){
        if(array[a]-array[i]==max)
            b=i+1;
    }
    //printf("%d %d\n",a,b);
    day.buy[0]=b;
    day.sell[0]=a+1;
    day.extream=max;
    return day;

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
    if(size < 2)
        return 0;
   if(k > size/2) //when it's unlimited, it can be easily handled -> corner case;
    {
        int profit = 0;
        for(int i=1; i < size; i++)
            if(prices[i] > prices[i-1])
                profit += prices[i]-prices[i-1];
        return profit;
    }
    int** t = (int**)malloc(sizeof(int*)*(k+1));
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
            printf("%d %d current %d\n",i,j,cur);
        }
        counter++;
    }
    for(i=0;i<k+1;i++){
        for(j=0;j<size;j++){
            
            printf("%d  ",t[i][j]);
        }
        printf("\n");
    }
    for(i=0;i<k+1;i++){
        for(j=0;j<size;j++){
            
            printf("date array %d  ",date[i][j]);
        }
        printf("\n");
    }
    int max=0;
    int min=-99999;
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

    printf("date is %d %d\n",z+1,x+1);
    if(t[k][size-1]==0)
    printf("there is no result");
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
        printf("%d\n",t[1][i]);
    }
    printf("r is %d\n",r);
    for(i=1;i<w-1;i++){
        if(date[1][i]!=date[1][i+1]){
            r=i+1;
        }
        printf("%d\n",date[1][i]);
    }
    printf("r is %d\n",r);
    if(r==1){
        r=0;
    }
    printf("date is %d %d %d %d",q+1,w+1,e+1,r+1);
     
    return t[k][size-1];
}


int main(int argc,char *argv[])
{
    FILE *fp;
    char *file1;
    file1 = argv[1];
    fp = fopen(file1,"r");
    if(argc!=2){
        
        exit(INCORRECT_NUMBER_OF_COMMAND_LINE_ARGUMENTS);
    }
    if(fp==NULL){
        
        exit(PARSING_ERROR_EMPTY_FILE);
    }
    if(!fopen(file1,"r")){
        exit(FILE_FAILED_TO_OPEN);
    }
    int *array;
    int r=100;
    int n=9;
    int max,min;
    struct day day;
    array=malloc(sizeof(int)*(r+1));
 
    createArray(array,fp);
    //day=findMax(array,n);
    //printf("%d\n%d\n",day.buy[0],day.sell[0]);
    //day=findMin(array,n);
    //printf("%d\n%d\n",day.buy[0],day.sell[0]);
    //day=findMax2(array,n);
    //printf("%d\n%d\n%d\n%d\n",day.buy[0],day.sell[0],day.buy[1],day.sell[1]);
    max=maxProfit(2,array,n);
    printf("the max profit is %d",max);
    return 0;
}
