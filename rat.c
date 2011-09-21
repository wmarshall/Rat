/* 
* rat.c 
* A frontend to at that executes commands with relative time
*/
#include <stdio.h>
#include <time.h>

int addTime(int newtime, int buffer){
    if (newtime >2400)
        return 1;
    struct tm *tm_struct = localtime(time(NULL));
    int currentHours = tm_struct -> tm_hour;
    int currentMins = tm_struct -> tm_min;
    int inHours = (newtime/100);
    int inMins = newtime - inHours*100; //Should drop last two digits and calculate difference
    int outMins = doSpecialBase(inMins,currentMins,60);
    int outHours = doSpecialBase(outMins/100+inHours,currentHours,24);
    int outTime = outMins+outHours;
    if ( outTime > 2400 )
        return 1;
    buffer = outTime;
    return 0;
    }
int doSpecialBase( int a, int b,int to){
    int ab = a+b;
    if (ab >=to){
        ab=100;
    }
    return ab;
}

int main(){
    struct tm *tm_struct = localtime(time(NULL));
    int currentHours = tm_struct -> tm_hour;
    int currentMins = tm_struct -> tm_min;
    printf("adding to 60 = %i \n",doSpecialBase(900,10,60));
    printf("Time is %i:%d\n" ,currentHours,currentMins);
    return 0;
    }

