typedef struct 
{
    unsigned int day:1;
    unsigned int year:1;
} verb_struct;


/* Function prototypes */

void date_to_roman(struct tm*, char*, verb_struct, int, int);
void to_roman_numerals(int,char*);
void to_roman(int,char*,struct mode);
int hodie_isleap(int);
void print_usage(void);
void print_version(void);
int parse_date(char*,char*,struct tm*);

