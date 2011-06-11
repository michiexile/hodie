#include "includes.h"

#define YMD 0
#define VERB 1
#define DMY 2
#define MDY 3

int
parse_date(int argc, char** argv, int pos, struct tm* p_ts)
{
    int i,ret;
    char flag,tmp1,tmp2;

    i=pos; i++;
    if(i>=argc)
    {
	print_usage();
	exit(1);
    }
    if(strcmp(argv[i],"ymd")==0)
    {
	flag=YMD;
	ret=pos+2;
    }
    else if(strcmp(argv[i],"verbose")==0)
    {	
	flag=VERB;
	ret=pos+7;
    }
    else if(strcmp(argv[i],"dmy")==0)
    {
	flag=DMY;
	ret=pos+2;
    }
    else if(strcmp(argv[i],"mdy")==0)
    {	
	flag=MDY;
	ret=pos+2;
    }
    else
    {
	print_usage();
	exit(1);
    }

    i++;
    
    switch(flag)
    {
    case YMD:
	sscanf(argv[i],"%d%c%d%c%d",&(p_ts->tm_year),&tmp1,
	       &(p_ts->tm_mon),&tmp2,&(p_ts->tm_mday));
	break;
    case VERB:
	for(;i<argc;i++)
	{
	    if(strcmp(argv[i],"--year")==0 || strcmp(argv[i],"-y")==0)
	    {
		p_ts->tm_year=atoi(argv[i+1]);
	    }
	    else if(strcmp(argv[i],"--month")==0 || strcmp(argv[i],"-m")==0)
	    {
		p_ts->tm_mon=atoi(argv[i+1]);
	    }
	    else if(strcmp(argv[i],"--day")==0 || strcmp(argv[i],"-d")==0)
	    {
		p_ts->tm_mday=atoi(argv[i+1]);
	    }
	}
	break;
    case DMY:
	sscanf(argv[i],"%d%c%d%c%d",&(p_ts->tm_mday),&tmp1,
	       &(p_ts->tm_mon),&tmp2,&(p_ts->tm_year));
	break;
    case MDY:
	sscanf(argv[i],"%d%c%d%c%d",&(p_ts->tm_mon),&tmp1,
	       &(p_ts->tm_mday),&tmp2,&(p_ts->tm_year));
	break;
    }
    p_ts->tm_mon--;
    return ret;
}
