/* uuc, a shitty wc copy by Iñaki Ulibarri Utrilla
 * Unlicensed, because you'd have to be crazy to steal this thing :D
 */

// TODO: add options to get individual information of files
#include "uuc.h"

/* Print the usage of the program to stdout*/
void print_help(){
	puts("uuc: <options> <files>\n"
		"options:\n"
		"	-h	Display this help text\n"
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

	int opt;
	while((opt = getopt(argc, argv, "h")) != -1){
		switch(opt){
			case 'h':
				print_help();
				exit(0);
				//no need to break here
			default:
				break;
			}
		}

		FILE *file;
		int o_files = 1;
		do{
			assert(file);
			file = fopen(argv[o_files], "r");

			int nl = count_nl(file);
			fseek(file, 0, SEEK_SET);
			//we need to back to the beginnig to count

			int w = count_w(file);

			struct stat stt;
			lstat(argv[o_files], &stt);
			//get bytes of the file

			printf("%4d %4d %4ld  %s\n",
				nl, w, stt.st_size, argv[o_files]);

			if(o_files < argc){
				totals.nl += nl;
				totals.w += w;
				totals.b += stt.st_size;
			}

			o_files++;
		}while(o_files < argc);

		if(o_files > 1){
			printf("%4d %4d %4ld  %s\n",
				totals.nl, totals.w, totals.b , "totals");
		}

		return EXIT_SUCCESS;
	}
