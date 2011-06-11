typedef struct mode {
    unsigned char numeral : 1; /* 0 if verbose, 1 if of the form CXCVII */
    unsigned char numerus : 1; /* 0 if singular, 1 if plural */
    unsigned char casus   : 3; /* 0 Nom, 1 Gen, 2 Dat, 3 Ack, 4 Abl */
    unsigned char genus   : 2; /* 0 M, 1 F, 2 N */
    unsigned char et_bind : 1; /* 1 string high numbers together with 'et' */
    unsigned char type    : 2; /* 0: one two three, 
				* 1: first second third
				* 2: one each, two each ...
				* 3: once, twice, ... */
} mode;
