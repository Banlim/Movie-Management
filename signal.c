#include "head.h"

void contrl_C(int sig){
  char ch;
  printf("\nControl+C\n");
  printf("Get Interrupt Signal.\n");
  printf("Do you want to exit myMOVIE program? (Y/N) ");
  scanf(" %c",&ch);
  if(ch=='Y' || ch=='y'){
    exit(1);
  }
}
