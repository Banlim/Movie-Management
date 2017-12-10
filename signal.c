#include "head.h"

void contrl_C(int sig){
  char ch; // 사용자에게 Y 또는 y 문자를 입력받기 위해 char형을 선언한다.
  printf("\nControl+C\n");
  printf("Get Interrupt Signal.\n");
  printf("Do you want to exit myMOVIE program? (Y/N) ");
  scanf(" %c",&ch);
  if(ch=='Y' || ch=='y'){
    exit(1);
  }
}
