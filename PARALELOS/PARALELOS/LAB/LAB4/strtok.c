#include <stdio.h>
#include <omp.h>

#include <string.h>
#include <stdlib.h>

#define MAX 255
FILE * pFile;

void Get_text(char* lines[], int* line_count_p);
void Tokenize(char* lines[], int line_count, int thread_count);

int main(int argc, char ** argv){
	if(argc != 2){
		printf("Faltan Argumentos <numThread>\n");
		return 0;
	}
	
	char * lines[100];
	int line_count,i;
	int numThread = atoi(argv[1]);
	pFile = fopen("strTest","r");
	Get_text(lines,&line_count);

	Tokenize(lines,line_count,numThread);
	for (i = 0; i < line_count; i++)
      if (lines[i] != NULL) free(lines[i]);
  	return 0;

}
void Get_text(char* lines[], int* line_count_p) {
   char* line = malloc(MAX*sizeof(char));
   int i = 0;
   char* fg_rv;

   fg_rv = fgets(line, MAX, pFile);
   while (fg_rv != NULL) {
      lines[i++] = line;
      line = malloc(MAX*sizeof(char));
      fg_rv = fgets(line, MAX, pFile);
   }
   *line_count_p = i;
} 


void Tokenize(
      char*  lines[]       /* in/out */, 
      int    line_count    /* in     */, 
      int    thread_count  /* in     */) {
   int my_rank, i, j;
   char *my_token, *saveptr;

#  pragma omp parallel num_threads(thread_count) \
      default(none) private(my_rank, i, j, my_token, saveptr) \
      shared(lines, line_count)
   {
      my_rank = omp_get_thread_num();
#     pragma omp for schedule(static, 1)
      for (i = 0; i < line_count; i++) {
         printf("Thread %d > line %d = %s\n", my_rank, i, lines[i]);
         j = 0; 
         my_token = strtok_r(lines[i], " \t\n", &saveptr);
         while ( my_token != NULL ) {
            printf("Thread %d > token %d = %s\n", my_rank, j, my_token);
            my_token = strtok_r(NULL, " \t\n", &saveptr);
            j++;
         } 
      } /* for i */
   }  /* omp parallel */

}  /* Tokenize */
