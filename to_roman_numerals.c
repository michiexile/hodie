#include "includes.h"

static const char* ones[10]={"","I","II","III","IV","V","VI","VII","VIII","IX"};
static const char* tens[10]={"","X","XX","XXX","XL","L","LX","LXX","LXXX","XC"};
static const char* cents[10]={"","C","CC","CCC","CD","D","DC","DCC","DCCC","CM"};
static const char* mils[10]={"","M","MM","MMM","MMMM","MMMMM","MMMMMM","MMMMMMMM","MMMMMMMMM"};
static const char* naught="-";
		     
void to_roman_numerals(int n, char* str)
{
    int o,t,c,m;
    
    if(n==0)
    {
	sprintf(str,"%s",naught);
	return;
    }
    
    o=n%10;
    n=n/10;

    t=n%10;
    n=n/10;

    c=n%10;
    n=n/10;

    m=n%10;

    if(m>9)
	m=0;
    
    sprintf(str, "%s%s%s%s",mils[m],cents[c],tens[t],ones[o]);
}
