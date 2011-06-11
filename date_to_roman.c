#include "includes.h"

/* For addressing pripost-arrays */
#define PR 0
#define POS 1
#define AD 2

/* Handles for switch statements */
#define PRID 2
#define POST 1
#define DIES 0

static const char* abl[4]={"","Kalendis","Nonis","Idibus"};
static const char* ack[4]={"","Kalendas","Nonas","Idus"};
static const char* terse[4]={"","Kal.","Non.","Id."};
static const char* pripost[3]={"pridie","postridie","ante diem"};
static const char* pripost_terse[3]={"pr.","post.","a.d."};
static const char* month_abl[13]={"",
				  "Ianuariis",
				  "Februariis",
				  "Martiis",
				  "Aprilibus",
				  "Maiis",
				  "Iuniis",
				  "Iuliis",
				  "Augustis",
				  "Septembribus",
				  "Octobribus",
				  "Novembribus",
				  "Decembribus"};
static const char* month_ack[13]={"",
				  "Ianuarias",
				  "Februarias",
				  "Martias",
				  "Apriles",
				  "Maias",
				  "Iunias",
				  "Iulias",
				  "Augustas",
				  "Septembres",
				  "Octobres",
				  "Novembres",
				  "Decembres"};
static const char* month_terse[13]={"",
				    "Ian.",
				    "Feb.",
				    "Mar.",
				    "Apr.",
				    "Mai.",
				    "Iun.",
				    "Iul.",
				    "Aug.",
				    "Sep.",
				    "Oct.",
				    "Nov.",
				    "Dec."};

void date_to_roman(struct tm* t, char* s, verb_struct verbosity, int ad, int leap)
{            	
    int kni; /* Which of Kalends, Nones or Ides is the next *day*/
    /* Kalends=1, Nones=2, Ides=3 */
    int n;   /* Number of days to the next */
    char numeral[80], num_year[80];
    int bis; /* Is it the second of the two a.d. V Kal. Mar. of a leap year? */
    int year;/* In special cases (end of december), the year verbose and     */
    int month;/* terse are non-identical.                                    */
    mode m;

    bis=0;
    month=t->tm_mon;

    if(leap!=0 && t->tm_mon==2 && t->tm_mday>23)
    {        
	month++;
/* Special treatment for leap year days!! */
	switch(t->tm_mday)
	{
	case 24:
	    n=6;
	    break;
	case 25:
	    n=6;
	    bis=1;
	    break;
	case 26:
	    n=5;
	    break;
	case 27:
	    n=4;
	    break;
	case 28:
	    n=3;
	    break;
	case 29:
	    n=PRID;  /* pridie */
	    break;
	default:  /* should **NEVER** occur */
	    break;
	}
	kni=1;
    }
    else if(t->tm_mon==3 || t->tm_mon==7 || t->tm_mon==10 || t->tm_mon==5)
    {
	switch(t->tm_mday)
	{
	case 1:
	    kni=1;
	    n=DIES;
	    break;
	case 2:
	    kni=1;
	    n=POST;
	    break;
	case 3:
	case 4:
	case 5:
	    kni=2;
	    n=8-t->tm_mday;
	    break;
	case 6:
	    kni=2;
	    n=PRID;
	    break;
	case 7:
	    kni=2;
	    n=DIES;
	    break;
	case 8:
	    kni=2;
	    n=POST;
	    break;
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	    kni=3;
	    n=16-t->tm_mday;
	    break;
	case 14:
	    kni=3;
	    n=PRID;
	    break;
	case 15:
	    kni=3;
	    n=DIES;
	    break;
	case 16:
	    kni=3;
	    n=POST;
	    break;
	default:
	    kni=1;
	    month++;
	    n=33-t->tm_mday;
	    break;
	}
    }
    else
    {
	switch(t->tm_mday)
	{
	case 1:
	    kni=1;
	    n=DIES;
	    break;
	case 2:
	    kni=1;
	    n=POST;
	    break;
	case 3:
	    kni=2;
	    n=3;
	    break;
	case 4:
	    kni=2;
	    n=PRID;
	    break;	    
	case 5:    
	    kni=2;
	    n=DIES;
	    break;
	case 6:
	    kni=2;
	    n=POST;
	    break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	    kni=3;
	    n=14-t->tm_mday;
	    break;
	case 12:
	    kni=3;
	    n=PRID;
	    break;
	case 13:
	    kni=3;
	    n=DIES;
	    break;
	case 14:
	    kni=3;
	    n=POST;
	    break;
	default:
	    kni=1;
	    month++;
	    if(t->tm_mon==2)
		n=30-t->tm_mday;
	    else if(t->tm_mon==4 || 
		    t->tm_mon==6 || 
		    t->tm_mon==9 || 
		    t->tm_mon==11)
		n=32-t->tm_mday;
	    else
	    {
		n=33-t->tm_mday;
	    }
	}   
    }

    /* What if we have a day in the end of December? */
    if(month==13)
    {
	month=1;
	year=t->tm_year+1;
    }
    else
    {
	year=t->tm_year;
    }
    if(!verbosity.year) /* Year non-verbose */
    {
	m.numeral=1;
	to_roman(year,num_year,m);
    }
    
    if(!verbosity.day && !verbosity.year) /* Nonverbose display */
    {
	if(n==DIES)  /* On a main day */
	{
	    sprintf(s,"%s %s %s",terse[kni],month_terse[month], 
		    num_year);
	    return;
	}
	else
	{
	    if(n==POST) /* postridie */
	    {
		sprintf(s,"%s %s %s %s",pripost_terse[POS],terse[kni],
			month_terse[month],num_year);
		return;
	    }
	    else if(n==PRID) /* pridie */
	    {
		sprintf(s,"%s %s %s %s",pripost_terse[PR],terse[kni],
			month_terse[month], num_year);
		return;
	    }
	    else if(bis==1) /* Second VI Kal. Mar. */
	    {
		m.numeral=1;
		to_roman(n,numeral,m);
		if(ad)
		{
		    sprintf(s,"%s %s %s %s bis %s",pripost_terse[AD], 
			    numeral, terse[kni],
			    month_terse[month],num_year);
		}
		else
		{
		    sprintf(s,"%s %s %s bis %s", numeral, terse[kni],
			    month_terse[month],num_year);
		}
		return;
	    }
	    else
	    {
		m.numeral=1;
		to_roman(n,numeral,m);
		if(ad)
		    sprintf(s,"%s %s %s %s %s",pripost_terse[AD], 
			    numeral, terse[kni],
			    month_terse[month],num_year);
		else
		    sprintf(s,"%s %s %s %s", numeral, terse[kni],
			    month_terse[month],num_year);		    
		return;
	    }
	}
    }
    else /* Verbose or ExVerbose display */
    {
	m.numeral=verbosity.year?0:1;
	if(year!=1)
	    m.numerus=1; /* plural */
	else
	    m.numerus=0; /* singular */
	m.genus=0; /* masculine */
	m.casus=4; /* ablative */
	m.et_bind=0;
	m.type=1;
	to_roman(year,num_year,m);
	if(n==DIES) /* On the main day */
	{
	    sprintf(s,"%s %s %s",abl[kni],month_abl[month],num_year);
	    return;
	}
	else
	{
	    if(n==POST) /* Postridie */
	    {
		sprintf(s,"%s %s %s %s",pripost[POS],ack[kni],
			month_ack[month], num_year);
		return;
	    }
	    else if(n==PRID) /* pridie */
	    {		
		sprintf(s,"%s %s %s %s",pripost[PR],ack[kni],
			month_ack[month], num_year);
		return;
	    }
	    else
	    {
		if(ad==0)  /* Ante diem controls acc. */
		    m.casus=4;
		else
		    m.casus=3;
		m.numerus=0;
		m.genus=0;
		m.numeral=verbosity.day?0:1;
		m.et_bind=0;
		m.type=1;
		to_roman(n,numeral,m);
	    }
	}
	if(bis==1)
	{
	    if(ad)
		sprintf(s,"%s %s %s %s bis %s", pripost[AD], numeral, 
			ack[kni], month_ack[month],num_year);
	    else
		sprintf(s,"%s %s %s bis %s", numeral, 
			ack[kni], month_ack[month],num_year);		    
	    return;
	}
	else
	{
	    if(ad)
		sprintf(s,"%s %s %s %s %s", pripost[AD], numeral, ack[kni],
			month_ack[month],num_year);		
	    else
		sprintf(s,"%s %s %s %s", numeral, ack[kni],
			month_ack[month],num_year);		
	    return;
	}
    }
}





