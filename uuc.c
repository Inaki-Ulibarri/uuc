/* uuc, a shitty wc copy by Iñaki Ulibarri Utrilla
 * Unlicensed, because you'd have to be crazy to steal this thing :D
 * 
 */

//TODO: fix the options and the totals
#include "uuc.h"

/* Print the usage of the program to stdout*/
void print_help(){
	puts("uuc: <options> <files>\n"
		"	-h Display this help text\n"
		"	-l Show line numbers of the file\n"
		"	-w Show number of words in the file\n"
		"	-b Show size of the file in bytes\n" 
		"uuc, a shitty wc copy by Iñaki Ulibarri Utrilla\n"
		"Unlicensed, because you'd have to be crazy to steal this thing :D"
		);
	}

/* Count the amount of '\n' in
 * foofile.*/
int count_nl(FILE *foofile){
	int count = 0, ch;
	
	while((ch=getc(foofile)) != EOF){
		if(ch=='\n') count++;
	}

	return (count);
}

/* Count the amount of words in foofile
 * reading two characters at a time, if one is a 
 * space and the other a alphanumeric or a punctutation
 * character, the counter is upped by one.*/	
int count_w(FILE *foofile){
	int count = 0;
	char ch1, ch2;
	ch1 = getc(foofile);
	while(ch1 != EOF || ch2 != EOF){
		ch2 = ch1;
		ch1 = getc(foofile);
		if(isspace(ch1) && isalnum(ch2))
			count++;

		else if(isspace(ch1) && ispunct(ch2))
			count++;
		}
	return (count);
	}
	
int main(int argc, char *argv[]){
	//check correct usage
	if(argc<2){
		print_help();
		exit(0);
	}

	flgs.nl = false;
	flgs.w = false;
	flgs.b = false;
	
	//Ik this is clunky and Yanderedevy, but it's the best method I could
	//come up with :v
	int opt;
	int i = 1;
	//things break when taking more than one argument 
	//per argv[]
	do{
		opt = getopt(argc, argv, "hlwb");
		if(opt == 'h'){
			print_help();
			exit(0);
		}
		else if(opt == 'l'){
			flgs.nl = true;
			i++;
		}
		else if(opt == 'w'){
			flgs.w = true;
			i++;
		}
		else if(opt == 'b'){
			flgs.b = true;
			i++;
		}else if(opt == -1 && i == 1){
			flgs.nl = true;
			flgs.w = true;
			flgs.b = true;
		}
	}while(opt != -1);
	
	FILE *file;
	//getopt shenanigans
	int f_count = optind;
	int o_files = 0;
	
	do{
		file = fopen(argv[f_count], "r");
		if(!file){
			fprintf(stderr, "Error opening file: %s\n", argv[f_count]);
			exit (1);
		}
		o_files++;
		
		struct stat stt;
		lstat(argv[f_count], &stt);

		//places to put stuff
		int nl, w;
		
		if(flgs.nl){
			nl = count_nl(file);
			printf("%4d ", nl);
			//gotta go back
			fseek(file, 0, SEEK_SET); 
		}
		if(flgs.w){
			w = count_w(file);
			printf("%4d ", w);
		}
		if(flgs.b){
			printf("%4ld ", stt.st_size);
		}
		printf("%s\n", argv[f_count]);

		//totals are always calculated
		totals.nl += nl;
		totals.w += w;
		totals.b += stt.st_size;

		f_count++;
	}while(f_count < argc);

	if(o_files > 1){
		if(flgs.nl){
			printf("%4d ", totals.nl);
		}
		if(flgs.w){
			printf("%4d ", totals.w);
		}
		if(flgs.b){
			printf("%4ld ", totals.b);
		}

		printf("total\n");
	}

	return EXIT_SUCCESS;
}
