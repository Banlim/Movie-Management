#include "head.h"
//입력 함수
extern int m_srl, d_srl, a_srl; //마지막 시리얼 넘버 저장 전역 변수

char* changeColon(char* ptr, Type mode){
  char* returnPointer = (char*)malloc(1);
  *returnPointer = '\0';
  char* prevPointer = ptr;
  char* crntPointer = ptr;
  if(mode == t_read){
    while(1){
      if(strstr(ptr, "??;") == NULL){
        return ptr;
      }
      else{
        if(strstr(crntPointer, "??;") != NULL){
          crntPointer = strstr(crntPointer, "??;");
          returnPointer = (char*)realloc(returnPointer, sizeof(char)*(crntPointer-prevPointer+1));
          strncat(returnPointer, prevPointer, crntPointer-prevPointer);
          strncat(returnPointer, ":", 1);
          crntPointer+=3;
          prevPointer = crntPointer;
        }
        else{
          strcat(returnPointer, crntPointer);
          return returnPointer;
        }
      }
    }
  }
  else if(mode == t_print){
    while(1){
      if(strstr(ptr, ":") == NULL){
        return ptr;
      }
      else{
        if(strstr(crntPointer, ":") != NULL){
          crntPointer = strstr(crntPointer, ":");
          returnPointer = (char*)realloc(returnPointer, sizeof(char)*(crntPointer-prevPointer+3));
          strncat(returnPointer, prevPointer, crntPointer-prevPointer);
          strncat(returnPointer, "??;", 3);
          crntPointer+=1;
          prevPointer = crntPointer;
        }
        else{
          strcat(returnPointer, crntPointer);
          return returnPointer;
        }
      }
    }
  }
  free(returnPointer);
}

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
    scanfNum = scanf("%[ a-zA-Z0-9*?-]", tmp);
    printf("Tmp > %s\n",tmp);
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
      printf("NULL");
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
      printf("Input format is not correct\nadd m|d|a\n");
  }
  else if(strcmp(tag, "update") == 0){
    if(num != 1 && num != 2){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      printf("%s\n",*(str+1));
      strcpy(op1, *(str+1));
      if(strcmp(op1, "m") == 0){
        fp=fopen("movie_log.txt","at");
        if(num == 3){
          op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
          strcpy(op2, *(str+2));
          srl = atoi(op2);
          if(srl == 0){
            printf("%s is not number\n", op2);
            return;
          }
          op3 = "tgdyra";
          update(fp, srl, op3, movie, t_movie);
        }
        else if(num == 4){
          op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
          strcpy(op2, *(str+2));
          op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+1));
          strcpy(op3, *(str+3));
          srl = atoi(op3);
          if(srl == 0){
            printf("%s is not number\n", op3);
            return;
          }
          update(fp, srl, op2, movie, t_movie);
        }
        else
          printf("Input format is not correct\nupdate m|d|a [option] num\n\t[option] : t g d r y a\n");
      }
      else if(strcmp(op1, "d") == 0){
        fp=fopen("director_log.txt","at");
        if(num == 3){
          op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
          strcpy(op2, *(str+2));
          srl = atoi(op2);
          if(srl == 0){
            printf("%s is not number\n", op2);
            return;
          }
          op3 = "nsbm";
          update(fp, srl, op3, director, t_director);
        }
        else if(num == 4){
          op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
          strcpy(op2, *(str+2));
          op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+1));
          strcpy(op3, *(str+3));
          srl = atoi(op3);
          if(srl == 0){
            printf("%s is not number\n", op3);
            return;
          }
          update(fp, srl, op2, director, t_director);
        }
        else
          printf("Input format is not correct\nupdate m|d|a [option] num\n\t[option] : n s b m\n");
        fclose(fp);
      }
      else if(strcmp(op1, "a") == 0){
        fp=fopen("actor_log.txt","at");
        if(num == 3){
          op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
          strcpy(op2, *(str+2));
          srl = atoi(op2);
          if(srl == 0){
            printf("%s is not number\n", op2);
            return;
          }
          op3 = "nsbm";
          update(fp, srl, op3, actor, t_actor);
        }
        else if(num == 4){
          op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
          strcpy(op2, *(str+2));
          op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+1));
          strcpy(op3, *(str+3));
          i = 0;
          srl = atoi(op3);
          if(srl == 0){
            printf("%s is not number\n", op3);
            return;
          }
          update(fp, srl, op2, actor, t_actor);
        }
        else
          printf("Input format is not correct\nupdate m|d|a [option] num\n\t[option] : n s b m\n");
        fclose(fp);
      }
      else
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  m : [option] : t g d r y a\n\td|a : [option] : n s b m\n");
    }
    else
      printf("Input format is not correct\nupdate m|d|a [option] num\n\t  m : [option] : t g d r y a\n\td|a : [option] : n s b m\n");
  }
  else if(strcmp(tag, "delete") == 0){
    if(num == 3){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      srl = atoi(op2);
      if(srl == 0){
        printf("%s is not number\n", op2);
        return;
      }
      if(strcmp(op1, "m") == 0){
        fp = fopen("movie_log.txt", "at");
        fprintf(fp, "delete:%d::::::\n", srl);
        fclose(fp);
      }
      else if(strcmp(op1, "d") == 0){
        fp = fopen("director_log.txt", "at");
        fprintf(fp, "delete:%d::::\n", srl);
        fclose(fp);
      }
      else if(strcmp(op1, "a") == 0){
        fp = fopen("actor_log.txt", "at");
        fprintf(fp, "delete:%d::::\n", srl);
        fclose(fp);
      }
      else
        printf("'%s' is not correct option\noption : m d a\n", op1);
    }
    else
      printf("Input format is not correct\ndelete m|d|a num\n");
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

char* Scan_log(){
  char *op;
  char *tmp=(char *)malloc(100);
  scanf("%[ a-zA-Z,0-9:]",tmp);
  while(getchar()!='\n');
  op=(char *)malloc(strlen(tmp)+1);
  strcpy(op,tmp);
  op = changeColon(op, t_print);
  return op;
}
