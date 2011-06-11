#include "includes.h"

const char* AUC[3]={"ab urbe condita","AUC","ab urbe condita"};

int
main(int argc, char** argv)
{
    char sec[16],min[16],hrs[16],day[16],mon[16],year[16],verbose[80];
    struct tm* p_ts;
    time_t t;
    int i, auc_base;
    short numerals, auc, leap, custom, ad;
    mode m;
    verb_struct verbosity;

    verbosity.year=0;
    verbosity.day=0;
    numerals=1;
    auc=0;
    leap=0;
    custom=0;
    auc_base=0;
    ad=0;

    t=time(NULL);
    p_ts=localtime(&t);

    if(argc!=1)
    {
	for(i=1; i<argc; i++)
	{
	    if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0)
	    {
		print_usage();
		return 0;
	    }
	    else if(strcmp(argv[i],"--version")==0)
	    {
		print_version();
		exit(0);
	    }
	    else if(strcmp(argv[i],"-ad")==0 || strcmp(argv[i],"--ante-diem")==0)
		ad=1;
	    else if(strcmp(argv[i],"-n")==0 || strcmp(argv[i],"--numerals")==0)
		numerals=0;
	    else if((strcmp(argv[i],"-v")==0
		     || strcmp(argv[i],"--verbose")==0))
	    {
		if(verbosity.day==1)
		    verbosity.year=1;
		else
		    verbosity.day=1;
	    }
	    else if(strcmp(argv[i],"-vv")==0 || 
		    strcmp(argv[i],"--extremely-verbose")==0)
	    {
		verbosity.day=1;
		verbosity.year=1;
	    }
	    else if(strcmp(argv[i],"-c")==0 || 
		    strcmp(argv[i],"--classic")==0 ||
		    strcmp(argv[i],"--auc")==0)
	    {
		    auc=1;
		    auc_base=753;
	    }
	    else if(strcmp(argv[i],"-r")==0 ||
		     strcmp(argv[i],"--republican")==0)
	    {
		if(
		    (i+1<argc) &&
		    (
			isdigit(*(argv[i])) || 
			(
			    (*(argv[i])=='-') && 
			    isdigit(*(argv[i+1]))
			    )
			)
		    )
		{
		    i++;
		    auc_base=-atoi(argv[i]);
		    auc=1;
		}
		else
		{
		    fprintf(stderr,"%s\n",ERR_NO_REP);
		    exit(-1);
		}
	    }
	    else if(strcmp(argv[i],"-d")==0 || strcmp(argv[i],"--date")==0)
	    {
		i=parse_date(argc,argv,i,p_ts);
		custom=1;
	    }
	    else if(strcmp(argv[i],"-x")==0 || 
		    strcmp(argv[i],"--force-numerals")==0)
		numerals=-1;
	    else
	    {
		print_usage();
		return 0;
	    }
	}
    }    

    if(hodie_isleap(p_ts->tm_year)==1)
       leap=1;

    if(custom==0)
    {
	p_ts->tm_year=p_ts->tm_year+auc_base+1900;
    }
    
    p_ts->tm_mon++;


/* Setup the mode struct */
    m.numeral=1;
    
    to_roman(p_ts->tm_sec,sec,m);
    to_roman(p_ts->tm_min,min,m);
    to_roman(p_ts->tm_hour,hrs,m);
    to_roman(p_ts->tm_mday,day,m);
    to_roman(p_ts->tm_mon,mon,m);
    to_roman(p_ts->tm_year,year,m);

    date_to_roman(p_ts, verbose, verbosity, ad, leap);

    if(numerals!=0 && auc!=0)
    {
	printf("Hodie %s %s est\n",verbose,AUC[verbosity.day+1]);
    }
    else if(numerals!=0)
    {
	printf("Hodie %s est\n",verbose);
    }

    if(numerals==-1) /* The only case where both numerals and text exist */
	printf("\n");

    if(numerals < 1)
    {
	if(auc!=0)
	    printf("%s/%s-%s %s\n%s:%s:%s\n", 
		   day,mon,year,AUC[verbosity.day+1],hrs,min,sec);
	else
	    printf("%s/%s-%s\n%s:%s:%s\n", 
		   day,mon,year,hrs,min,sec);
    }	
    return 0;
}




