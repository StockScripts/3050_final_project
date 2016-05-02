#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "../include/vector.h"
#include "../input_error.h"

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
    printf("%d %d\n",a,b);
    day.buy[0]=b;
    day.sell[0]=a+1;
    day.extream=max;
    return day;

}


struct day findMax2(int *array,int n){
    int diff[n-1];
    int i, a,b;
    int z,x,c;
    int localMax;
    struct day day;
    struct day day1;
    struct day day2;
    struct day day3;
    int *array1;
    int temp[3];
    day1.extream=0;
    day2.extream=0;
    day3.extream=0;
    array1=malloc(sizeof(int)*(n));
    for(i=0;i<n-1;i++){
        diff[i]=array[i+1]-array[i];
    }
    int max=diff[0];
    int max2=diff[0];
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
            b=i;
    } 
    day.buy[0]=b+1;
    day.sell[0]=a+1;
    day.extream=max;
    printf("the b is %d, a is %d\n",b,a);
    if(b-1>1){
        for(i=0;i<b;i++){
        array1[i]=array[i];
    }
        day1=findMax(array1,b);
    }
    if(b-a>1){
    for(i=b;i<a;i++){
        array1[i]=array[i];
    }
        day2=findMin(array1,b-a);
    }
    if(n-a>1){
    for(i=a;i<n-1;i++){
        array1[i]=array[i];
    }
        day3=findMax(array1,n-a);
    }
        //if(day1.extream>day2.extream){
        //    localMax=day1.extream;
       // }
        //else
        //    localMax=day2.extream;
        //if(day3.extream>localMax)
        //    localMax=day3.extream;
        temp[0]=0;
        temp[1]=0;
        temp[2]=0;
        printf("qew %d %d %d\n",temp[0],temp[1],temp[2]);
        printf("qew %d %d %d\n",day1.extream,day2.extream,day3.extream);
        temp[0]=day1.extream;
        temp[1]=day2.extream;
        temp[2]=day3.extream;
        localMax=temp[0];
        printf("qew %d %d %d\n",temp[0],temp[1],temp[2]);
        for(i=0;i<3;i++){
            if(temp[i]>localMax)
                localMax=temp[i];
        }
        
        if(localMax==day1.extream){
            day.buy[1]=day1.buy[0];
            day.sell[1]=day1.sell[0];
        }
        else if(localMax==day2.extream){
            day2.sell[1]=day.sell[0];
            day.sell[0]=day2.buy[0];
            day.buy[1]=day2.sell[0];
            
        }
        else if(localMax==day3.extream){
            day.buy[1]=day3.buy[0];
            day.sell[1]=day3.sell[0];
        }
                
        return day;
    
}
struct day findMin(int *array,int n){
    int diff[n-1];
    int i, a,b;
    struct day day;
    for(i=0;i<n-1;i++){
        diff[i]=array[i+1]-array[i];
    }
    int min=diff[0];
    for(i=1;i<n-1;i++){
        if(diff[i-1]<0)
            diff[i]=diff[i]+diff[i-1];
        if(min>diff[i]){
            min=diff[i];
            a=i+1;
            
        }
    }
    for(i=0;i<n-1;i++){
        if(array[a]-array[i]==min)
            b=i+1;
    }
    //printf("%d\n",min);
    day.buy[0]=b;
    day.sell[0]=a+1;
    day.extream=-min;
    return day;

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
    int n=6;
    int max,min;
    struct day day;
    array=malloc(sizeof(int)*(r+1));
 
    createArray(array,fp);
    day=findMax(array,n);
    printf("%d\n%d\n",day.buy[0],day.sell[0]);
    day=findMin(array,n);
    printf("%d\n%d\n",day.buy[0],day.sell[0]);
    day=findMax2(array,n);
    printf("%d\n%d\n%d\n%d\n",day.buy[0],day.sell[0],day.buy[1],day.sell[1]);

    return 0;
}