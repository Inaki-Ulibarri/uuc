#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>

//total of various files
struct total{
	int nl;
	int w;
	long int b;
} totals;

//flags
struct flags{
	bool nl;
	bool w;
	bool b;
} flgs;
