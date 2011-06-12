#include "includes.h"

#define YMD 0
#define VERB 1
#define DMY 2
#define MDY 3

int
parse_date(char* datetype, char* dateval, struct tm* p_ts)
{
    int ret;
    char flag,tmp1,tmp2;

    if(strcmp(datetype,"ymd")==0)
    {
	flag=YMD;
    }
    else if(strcmp(datetype,"verbose")==0)
    {	
	flag=VERB;
    }
    else if(strcmp(datetype,"dmy")==0)
    {
	flag=DMY;
    }
    else if(strcmp(datetype,"mdy")==0)
    {	
	flag=MDY;
    }
    else
    {
	print_usage();
	exit(1);
    }
    
    switch(flag)
    {
    case YMD:
	sscanf(dateval,"%d%c%d%c%d",&(p_ts->tm_year),&tmp1,
	       &(p_ts->tm_mon),&tmp2,&(p_ts->tm_mday));
	break;
    case DMY:
	sscanf(dateval,"%d%c%d%c%d",&(p_ts->tm_mday),&tmp1,
	       &(p_ts->tm_mon),&tmp2,&(p_ts->tm_year));
	break;
    case MDY:
	sscanf(dateval,"%d%c%d%c%d",&(p_ts->tm_mon),&tmp1,
	       &(p_ts->tm_mday),&tmp2,&(p_ts->tm_year));
	break;
    }
    p_ts->tm_mon--;
    return ret;
}
