#include <stdio.h>
#include <stdlib.h>


int main(){
  FILE *file;

  file = fopen("test.txt", "r");
  
  if(!file){
    printf("No such file");
    exit(0);
  }

  /* char c;
  c=fgetc(file);

  while(c != EOF){
    printf("%c", c);
    c = fgetc(file);
  }
  */
  char str[60];

  if(fgets(str, 60, file) != NULL){
    puts(str);
  }

  fclose(file);

  printf("Welcome to ACME Solutions.\nEnter the option number:\n");
  printf("1)Add New Employee \n2)Remove Employee \n3)Show All Employee Names\n");

  
  return 0;


}
