#include "includes.h"

const char *unus[32]={
		      "unus", "una", "unum",
		      "unius", "unius", "unius",
		      "uni","uni","uni",
		      "unum","unam","unum",
		      "uno","una","uno",
		      
		      "uni","unae","una",
		      "unorum","unarum","unorum",
		      "unis","unis","unis",
		      "unos","unas","una",
		      "unis","unis","unis"};

const char *duo[16]={
		     "duo","duae","duo",
		     "duorum","duarum","duorum",
		     "duobus","duabus","duobus",
		     "duos","duas","duo",
		     "duobus","duabus","duobus"};

const char *tres[16]={
                      "tres","tres","tria",
		      "trium","trium","trium",
		      "tribus","tribus","tribus",
		      "tres","tres","tria",
		      "tribus","tribus","tribus"};

const char *duode[2]={"unde","duode"};

const char *one[20]={"",
		      "",
		      "",
		      "",
		      "quattuor",
		      "quinque",
		      "sex",
		      "septem",
		      "octo",
		      "novem",
		      "decem",
		      "undecim",
		      "duodecim",
		      "tredecim",
		      "quattuordecim",
		      "quindecim",
		      "sedecim",
		      "septendecim"};

const char *ten[15]={"",
		     "decem",
		     "viginti",
		     "triginta",
		     "quadraginta",
		     "quinquaginta",
		     "sexaginta",
		     "septuaginta",
		     "octoginta",
		     "nonaginta",};

const char *cent[15]={"",
		      "centum",
		      "ducent",
		      "trecent",
		      "quadringent",
		      "quingent",
		      "sescent",
		      "septingent",
		      "octingent",
		      "nongent"};

const char *regular[32]={"us","a","um",
			 "i","ae","i",
			 "o","ae","o",
			 "um","am","um",
			 "o","a","o",
			 
			 "i","ae","a",
			 "orum","arum","orum",
			 "is","is","is",
			 "os","as","a",
			 "is","is","is"};

const char *milia[16]={"milia",
		       "milium",
		       "milibus",
		       "milia",
		       "milibus"};

const char *primus[13]={"",
			"prim",
			"secund",
			"terti",
			"quart",
			"quint",
			"sext",
			"septim",
			"octav",
			"non",
			"decim",
			"undecim",
			"duodecim"};

const char* decimus[13]={"",
			 "decim",
			 "vicesim",
			 "tricesim",
			 "quadragesim",
			 "quinquagesim",
			 "sexagesim",
			 "septuagesim",
			 "octogesim",
			 "nonagesim",
			 "centesim"};

const char* centesimus[13]={"",
			    "centesim",
			    "ducentesim",
			    "trecentesim",
			    "quadringentesim",
			    "quingentesim",
			    "sescentesim",
			    "septingentesim",
			    "octingentesim",
			    "nongentesim"};

const char* millesimus="millesim";

const char* semel[13]={"",
		       "semel",
		       "bis",
		       "ter",
		       "quater",
		       "quinquies",
		       "sexies",
		       "septies",
		       "octies",
		       "novies",
		       "decies",
		       "undecies",
		       "duodecies"};

const char* decies[12]={"",
			"decies",
			"vicies",
			"tricies",
			"quadragies",
			"quinquagies",
			"sexagies",
			"septuagies",
			"octogies",
			"nonagies",
			"centies"};

const char* centies[12]={"",
			 "centies",
			 "ducenties",
			 "trecenties",
			 "quadringenties",
			 "quingenties",
			 "sescenties",
			 "septingenties",
			 "octingenties",
			 "nongenties",
			 "milies"};

const char* milies="milies";


void build_one(int n, char* str, mode m);
void build_first(int n, char* str, mode m);
void build_singuli(int n, char* str, mode m);
void build_semel(int n, char* str, mode m);
    




void to_roman(int n, char* str, mode m)
{

    if(m.numeral)
    {
	to_roman_numerals(n, str);
	return;
    }
    
    switch(m.type)
    {
    case 0: 
	build_one(n, str, m);
	break;
    case 1:
	build_first(n, str, m);
	break;
    case 2:
	build_singuli(n, str, m);
	break;
    case 3:
	build_semel(n, str, m);
	break;
    }
    
    return;
}

void build_one(int n, char* str, mode m)
{
    char tmp[80], tmp1[80];
    mode M;
    
    M=m;
    
    if(n==0)
    {
	sprintf(str, " ");
	return;
    }
    if(n>=2000)
    {
	if(n%1000 < 100)
	    M.et_bind=0;
	build_one(n%1000, tmp, M);
	build_one(n/1000, tmp1, m);
	if(m.et_bind)
	    sprintf(str, "%s %s et %s", tmp1, milia[m.casus], tmp);
	else
	    sprintf(str, "%s %s %s", tmp1, milia[m.casus], tmp);
    }
    else if(n>=1000)
    {
	if(n%1000 < 100)
	    M.et_bind=0;
	build_one(n%1000, tmp, M);
	if(m.et_bind)
	    sprintf(str, "mille et %s", tmp);
	else
	    sprintf(str, "mille %s", tmp);
    }
    else if(n>=200)
    {
	M.et_bind=0;
	build_one(n%100, tmp, M);
	if(m.et_bind)
	    sprintf(str, "%s%s et %s", cent[(n-(n%100))/100], 
		    regular[15+m.casus*3+m.genus], tmp);
	else
	    sprintf(str, "%s%s %s", cent[(n-(n%100))/100], 
		    regular[15+m.casus*3+m.genus], tmp);
    }
    
    else if(n>=100)
    {
	M.et_bind=0;
	build_one(n%100, tmp, M);
	if(m.et_bind)
	    sprintf(str, "%s et %s", cent[1], tmp);
	else
	    sprintf(str, "%s %s", cent[1], tmp);	    
    }
    else
    {
	if((n==98)||(n==99))
	{
	    if(m.et_bind)
		sprintf(str, "%s et %s", one[n%10], ten[9]);
	    else
		sprintf(str, "%s %s", one[n%10], ten[9]);
	}
	else
	if(n>=20)
	{
	    switch(n%10)
	    {
	    case 0:
		sprintf(str,"%s", ten[n/10]);
		break;
	    case 1:
		if(m.et_bind)
		    sprintf(str,"%s et %s", 
			    unus[15*m.numerus+3*m.casus+m.genus],ten[(n-1)/10]);
		else
		    sprintf(str,"%s %s", ten[(n-1)/10], 
			    unus[15*m.numerus+3*m.casus+m.genus]);
		break;
	    case 2:
		if(m.et_bind)
		    sprintf(str,"%s et %s", 
			    duo[3*m.casus+m.genus],ten[(n-1)/10]);
		else
		    sprintf(str,"%s %s", ten[(n-1)/10], 
			    duo[3*m.casus+m.genus]);
		break;
	    case 3:
		if(m.et_bind)
		    sprintf(str,"%s et %s", 
			    tres[3*m.casus+m.genus],ten[(n-1)/10]);
		else
		    sprintf(str,"%s %s", ten[(n-1)/10], 
			    tres[3*m.casus+m.genus]);
		break;		
	    case 8:
		sprintf(str,"%s%s", duode[1], ten[(n+2)/10]);
		break;
	    case 9:
		sprintf(str,"%s%s", duode[0], ten[(n+1)/10]);
		break;
	    default:
		if(m.et_bind)
		    sprintf(str,"%s et %s", one[n%10],ten[(n-(n%10))/10]);
		else
		    sprintf(str,"%s %s", ten[(n-(n%10))/10], one[n%10]);
		break;	
	    }
	    
	}
	else
	{
	    switch(n)
	    {
	    case 1:
		sprintf(str, "%s", unus[15*m.numerus+3*m.casus+m.genus]);
		break;
	    case 2:
		sprintf(str, "%s", duo[3*m.casus+m.genus]);
		break;
	    case 3:
		sprintf(str, "%s", tres[3*m.casus+m.genus]);
		break;
	    case 18:
		sprintf(str,"%s%s", duode[1], ten[2]);
		break;
	    case 19:
		sprintf(str,"%s%s", duode[0], ten[2]);
		break;
	    default:
		sprintf(str, "%s", one[n]);
		
		
	    }
	}
    }
    
}

void build_first(int n,char* str,mode m)
{
    char tmp[80], tmp1[80];

    if(n<13)
    {
	sprintf(str,"%s%s",primus[n],regular[m.numerus*15+m.casus*3+m.genus]);
	return;
    }
    else if(n<18)
    {
	sprintf(str,"%s%s %s%s",decimus[1],
		regular[m.numerus*15+m.casus*3+m.genus],primus[n-10],
		regular[m.numerus*15+m.casus*3+m.genus]);
	return;
    }
    if(n>1000)
    {
	if(n%1000==0)
	{
	    if(n/1000>1)
	    {
		build_semel(n/1000, tmp, m);
		sprintf(str, "%s %s%s", tmp, millesimus, 
			regular[m.numerus*15+m.casus*3+m.genus]);
	    }
	    else
	    {
		sprintf(str, "%s%s", millesimus, 
			regular[m.numerus*15+m.casus*3+m.genus]);		
	    }
	}
	else
	{
	    build_first(n%1000,tmp,m);
	    if((n-(n%1000))/1000>1)
	    {
		build_semel((n-(n%1000))/1000, tmp1, m);
		sprintf(str,"%s %s%s %s", tmp1, millesimus,
			regular[m.numerus*15+m.casus*3+m.genus],tmp);
	    }
	    else
	    {
		sprintf(str,"%s%s %s", millesimus,
			regular[m.numerus*15+m.casus*3+m.genus],tmp);		
	    }
	}
	return;
    }
    if(n>100)
    {
	if(n%100!=0)
	    build_first(n%100,tmp,m);
	sprintf(tmp1,"%s%s",centesimus[(n-(n%100))/100],
		regular[m.numerus*15+m.casus*3+m.genus]);
	if(n%100!=0)
	    sprintf(str,"%s %s",tmp1, tmp);
	else
	    sprintf(str,"%s",tmp1);
	return;
    }
    if(n<100)
    {
	if((n%10==8)||(n%10==9)) 
	{
	    sprintf(str,"%s%s%s",duode[9-n%10],decimus[(n+(10-n%10))/10],
		    regular[m.numerus*15+m.casus*3+m.genus]);
	    return;
	}
	if(n%10==0)
	{
	    sprintf(str,"%s%s",decimus[n/10],
		    regular[m.numerus*15+m.casus*3+m.genus]);
	    return;
	}
	sprintf(str,"%s%s %s%s",decimus[(n-(n%10))/10],
		regular[m.numerus*15+m.casus*3+m.genus], primus[n%10],
		regular[m.numerus*15+m.casus*3+m.genus]);
	return;
    }
}

void build_singuli(int n,char* str, mode m)
{
    sprintf(str,"Distributives coming soon");
}


void build_semel(int n, char* str, mode m)
{
    char tmp[80], tmp1[80];
    int n_hi, n_lo;
    
    if(n==0)
    {
        str[0]=0;
	return;
    }
    if(n==1000)
	sprintf(str,"%s",milies);    
    if(n>1000)
    {
	n_lo=n%1000;
	n_hi=(n-n_lo)/1000;
	
	build_semel(n_lo,tmp,m);
	build_semel(n_hi,tmp1,m);
	if(n_lo)
	    sprintf(str,"%s %s %s",tmp1, milies, tmp);
	else
	    sprintf(str,"%s %s",tmp1, milies);
	
	return;
    }
    if(n>100)
    {
	n_lo=n%100;
	n_hi=(n-n_lo)/1000;
	
	build_semel(n_lo,tmp,m);
	sprintf(str, "%s %s", centies[n_hi], tmp);
	return;
    }
    if(n>12)
    {
	switch(n%10)
	{
	case 0:
	    sprintf(str,"%s",decies[n/10]);
	    break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	    sprintf(str, "%s et %s", semel[n%10], decies[(n-(n%10))/10]);
	    break;
	case 8:
	case 9:
	    sprintf(str, "%s%s", duode[9-(n%10)], decies[(n+10-(n%10))/10]);
	    break;
	}
	return;
    }
    sprintf(str,"%s", semel[n]);
    return;
}


