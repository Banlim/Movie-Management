#include "head.h"
//입력 함수
extern int m_srl, d_srl, a_srl; //마지막 시리얼 넘버 저장 전역 변수

void Input_Tag(MOVIE * movie, DIR_ACTOR * director, DIR_ACTOR * actor){
  char *tag=NULL, *op1=NULL, *op2=NULL, *op3=NULL;
  char ** str = NULL;
  char * tmp = NULL, * tmp_str = NULL;
  int i = 0, scanfNum = 0, num = 0, free_num = 0;
  int srl = 0;
  FILE * fp = NULL;
  //////////////////////////입력
  while(1){
    free(tmp);
    free(str);
    tmp = NULL;
    str = NULL;
    tmp=(char *)malloc(sizeof(char)*200);
    tmp_str=(char*)malloc(sizeof(char)*200);
    str=(char**)malloc(sizeof(char*)*(1));
    num=0;
    printf("(movie) ");
    scanfNum = scanf("%[ a-zA-Z0-9*?-:]", tmp);
    while( getchar() != '\n' );
    //예외 처리
    if(scanfNum == 0){
      break;
    }
    else{
      tmp_str = strtok(tmp, " ");
      *(str+num) = (char*)malloc(sizeof(char)*(strlen(tmp_str)+1));
      strcpy(*(str+num), tmp_str);
    }
    //예외 처리
    if(*(str+num) == NULL){
      break;
    }
    num++;
    while(1){
      str = (char**)realloc(str, sizeof(char*)*(num+1));
      tmp_str = strtok(NULL, " ");
      if(tmp_str == NULL){
        break;
      }
      *(str+num) = (char*)malloc(sizeof(char)*(strlen(tmp_str)+1));
      strcpy(*(str+num), tmp_str);
      num++;
    }
    break;
  }
  //////////////////////////판단
  i = 0;
  if(num == 0){
    return;
  }
  tag = (char*)malloc(sizeof(char)*(strlen(*str)+1));
  strcpy(tag, *(str));
  //tag 판단
  if(strcmp(tag, "add") == 0){
    if(num == 2){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      if(strcmp(op1, "m") == 0)
        add(fp, movie, t_movie);
      else if(strcmp(op1, "d") == 0)
        add(fp, director, t_director);
      else if (strcmp(op1, "a") == 0)
        add(fp, actor, t_actor);
      else
        printf("'%s' is not correct option\noption : m d a\n", op1);
    }
    else
      printf("\tInput format is not correct\n\tadd m|d|a\n");
  }
  else if(strcmp(tag, "print") == 0){ ////////////////////////////////////////////////////////////////
    if(num == 3){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      srl = atoi(op2);
      if(srl == 0)
        return;
      if(strcmp(op1, "m") == 0)
        PrintOption(movie, srl, t_movie);
      else if(strcmp(op1, "d") == 0)
        PrintOption(director, srl, t_director);
      else if(strcmp(op1, "a") == 0)
        PrintOption(actor, srl, t_actor);
      else
        printf("'%s' is not correct option\noption : m d a\n", op1);
    }
    else
      printf("Input format is not correct\nprint m|d|a num\n");
  }
  else
    printf("'%s' is not correct tag\ntag : search, print, add, update, delete, sort, save, end\n", tag);
  //free
  free_num = 0;
  while(free_num < num){
    if(num == 0)
      break;
    free(*(str+free_num));
    *(str+num) = NULL;
    free_num++;
  }
}
