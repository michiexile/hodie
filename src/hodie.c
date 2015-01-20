#include "includes.h"
#include <getopt.h>

const char* AUC[3]={"ab urbe condita","AUC","ab urbe condita"};

int
main(int argc, char** argv)
{
    char sec[16],min[16],hrs[16],day[16],mon[16],year[16],verbose[80],datetype[16],dateval[16];
    struct tm* p_ts;
    time_t t;
    int auc_base;
    short numerals, auc, leap, custom, ad;
    mode m;
    verb_struct verbosity;
    int verbosity_level = 0;

    int c;
    int xverbosity = 0;

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

    /* Parsing command line arguments with getopt */

    while (1) 
    {
        int option_index = 0;
        static struct option long_options[] = {
            {"help", 0, 0, 'h'},
            {"verbose", 0, 0, 'v'},
            {"extremely-verbose", 0, 0, 'X'},
            {"version", 0, 0, 'V'},
            {"numerals", 0, 0, 'n'},
            {"force-numerals", 0, 0, 'x'},
            {"classic", 0, 0, 'c'},
            {"auc", 0, 0, 'c'},
            {"ante-diem", 0, 0, 'a'},
            {"date", 1, 0, 'd'},
            {"republican", 0, 0, 'r'},
            {"year", 0, 0, 'Y'},
            {"month", 0, 0, 'M'},
            {"day", 0, 0, 'D'},
            {0,0,0,0},
        };
        
        c = getopt_long(argc, argv, 
                        "a:cd:hr:nvxD:M:VXY:",
                        long_options, &option_index);

        if(c == -1)
            break;

        switch(c)
        {
        case 'h':
            print_usage();
            exit(0);
            break;
        case 'V':
            print_version();
            exit(0);
            break;
        case 'v':
            verbosity_level++;
            break;
        case 'X':
            xverbosity++;
            break;
        case 'n':
            numerals = 0;
            break;
        case 'x':
            numerals = -1;
            break;
        case 'c':
            auc = 1;
            auc_base = 753;
            break;
        case 'a':
            ad = 1;
            break;
        case 'd':
            if(optarg)
            {
                strncpy(datetype,optarg,16);
            }
            custom=1;
            break;
        case 'r':
            auc = 1;
            if(optarg)
                auc_base = atoi(optarg);
            break;
        case 'Y':
            if(optarg)
                p_ts->tm_year = atoi(optarg);
            break;
        case 'M':
            if(optarg)
                p_ts->tm_mon = atoi(optarg)-1; // 0-indexed months
            break;
        case 'D':
            if(optarg)
                p_ts->tm_mday = atoi(optarg);
            break;
        default:
            break;
        }
    }

    if(verbosity_level > 2)
        verbosity_level = 2;

    switch(verbosity_level) 
    {
    case 2:
        verbosity.year = 1;
    case 1:
        verbosity.day = 1;
        break;
    }

    if(optind < argc && custom == 1) {
        strncpy(dateval,argv[optind++],16);
    }

    if(custom) {
      parse_date(datetype, dateval, p_ts);
      if (auc) {
        p_ts->tm_year=p_ts->tm_year+auc_base;
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
