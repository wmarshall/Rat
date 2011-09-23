/* 
* rat.c 
* A frontend to at that executes commands with relative time
*/
#include <stdio.h>
#include <time.h>

int addTime(int newtime, int *buffer){
    if (newtime >2400)
        return 1;
    time_t curTime = time(NULL);
    struct tm *tm_struct = localtime (&curTime);
    int currentHours = tm_struct -> tm_hour;
    printf("Hour = %i\n",currentHours);
    int currentMins = tm_struct -> tm_min;
    printf("Min = %i\n",currentMins);
    int inHours = (newtime/100);
    printf("inHours = %i\n",inHours);
    int inMins = newtime - inHours*100; //Should drop last two digits and calculate difference
    printf("inMins = %i\n",inMins);
    int outMins = doSpecialBase(inMins,currentMins,60);
    
    int outHours = doSpecialBase(outMins/100+inHours,currentHours,24);
    int outTime = outMins+outHours*100;
    if ( outTime > 2400 )
        return 1;
    *buffer = outTime;
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
    time_t curTime;
    struct tm *tm_struct;
    curTime = time (NULL);
    tm_struct = localtime (&curTime);
    int currentHours = tm_struct -> tm_hour;
    int currentMins = tm_struct -> tm_min;
    printf("Time is %i:%d\n" ,currentHours,currentMins);
    int result=1;
    int *buffer = &result; 
    if(addTime(1022, (buffer))){
        printf("ERR");
        return 1;
    }
    printf("currentTime +%i:%i = %d\n", 10,22,result);
    return 0;
    }

