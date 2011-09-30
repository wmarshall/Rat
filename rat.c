/* 
* rat.c 
* A frontend to at that executes commands with relative time
*/
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

const char atPath[]="/usr/bin/at";

int addTime( int newtime, int *buffer ){
    if (newtime >2400)
        return 1;
    time_t curTime = time(NULL);
    struct tm *tm_struct = localtime (&curTime);
    int currentHours = tm_struct -> tm_hour;
    int currentMins = tm_struct -> tm_min;
    int inHours = (newtime/100);
    int inMins = newtime - inHours*100; 
    int outMins = doSpecialBase(inMins+currentMins,60);
    int outHours = doSpecialBase(outMins/100+inHours+currentHours,24);
    int outTime = outMins+outHours*100;
    if ( outTime > 2400 )
        return 1;
    *buffer = outTime;
    return 0;
    }

int doSpecialBase( int ab, int to ){
    if (ab >=to){
        ab=100;
    }
    return ab;
}

int main( int argc, char *argv[] ){
    if ( argc != 2 ){
        printf("usage: rat HHMM\nNothing else supported/implemented yet\n");
        return 2;
    }
    int argTime = atoi( argv[1] );
    int result=1;
    int *buffer = &result; 
    if( addTime( argTime, buffer ) ){
        printf("ERR\n");
        return 1;
    }
    char stringyResult[5]="";
    sprintf( (&stringyResult[0]),"%04i",result);
    printf("currentTime +%02i:%02i = %04d\n",argTime/100,argTime-argTime/100,result);
    const char callString[16] = "";
    sprintf( (&callString[0]), "%s %04i", atPath, result);
    return system( (&callString[0]) );
    }

