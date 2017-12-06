#include "head.h"
//입력 함수
extern int m_srl, d_srl, a_srl; //마지막 시리얼 넘버 저장 전역 변수

void Input_Tag(MOVIE * movie, DIR_ACTOR * director, DIR_ACTOR * actor){
  char *tag=NULL, *op1=NULL, *op2=NULL, *op3=NULL, *op4=NULL;
  char ** str = NULL;
  char * tmp = NULL, * tmp_str = NULL;
  int i = 0, scanfNum = 0, num = 0, free_num = 0;
  int srl = 0;
  FILE * fp = NULL;
  //////////////////////////입력
  while(1){
    free(tmp);
    free(str);
    free(searchTmp);
    tmp = NULL;
    str = NULL;
    tmp=(char *)malloc(sizeof(char)*200);
    tmp_str=(char*)malloc(sizeof(char)*200);
    str=(char**)malloc(sizeof(char*)*(1));
    num=0;
    printf("(movie) ");
    scanfNum = scanf("%[ a-zA-Z0-9*?-:_]", tmp);
    searchTmp=(char*)malloc(sizeof(strlen(tmp))+1);
    strcpy(searchTmp, tmp);
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
  else if(strcmp(tag, "update") == 0){
    if(num != 1 && num != 2){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
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
          printf("@@ Done.\n");
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
          printf("@@ Done.\n");
        }
        else
          printf("Input format is not correct\nupdate m|d|a [option] num\n\t[option] : t g d r y a\n");
        fclose(fp);
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
          printf("@@ Done.\n");
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
          printf("@@ Done.\n");
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
          printf("@@ Done.\n");
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
          printf("@@ Done.\n");
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
        while(1){
          if(movie->srl_num == srl){
            break;
          }
          if(movie->next == NULL){
            break;
          }
          movie = movie->next;
        }
        if(movie->srl_num != srl){
          printf("@@ No sush record.\n");
          return ;
        }
        fp = fopen("movie_log.txt", "at");
        fprintf(fp, "delete:%d::::::\n", srl);
        printf("@@ Done.\n");
        fclose(fp);
      }
      else if(strcmp(op1, "d") == 0){
        while(1){
          if(director->srl_num == srl){
            break;
          }
          if(director->next == NULL){
            break;
          }
          director = director->next;
        }
        if(director->srl_num != srl){
          printf("@@ No sush record.\n");
          return ;
        }
        fp = fopen("director_log.txt", "at");
        fprintf(fp, "delete:%d::::\n", srl);
        printf("@@ Done.\n");
        fclose(fp);
      }
      else if(strcmp(op1, "a") == 0){
        while(1){
          if(actor->srl_num == srl){
            break;
          }
          if(actor->next == NULL){
            break;
          }
          actor = actor->next;
        }
        if(actor->srl_num != srl){
          printf("@@ No sush record.\n");
          return ;
        }
        fp = fopen("actor_log.txt", "at");
        fprintf(fp, "delete:%d::::\n", srl);
        printf("@@ Done.\n");
        fclose(fp);
      }
      else
        printf("'%s' is not correct option\noption : m d a\n", op1);
    }
    else
      printf("Input format is not correct\ndelete m|d|a num\n");
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
  else if(strcmp(tag, "search") == 0){ ////////////////////////////////////////////////////////////////
    if(num == 1){
      printf("Input format is not correct\nsearch [option] string\n[option] : -m -d -a\n");
      return;
    }
    if(*(*(str+1)) != '-')
      num = 2;
    else
      num = 3;
    if(num == 2){  //search string
      char * jdgtmp;
      int strnum=0;
      jdgtmp = strstr(searchTmp, " ");
      jdgtmp+=1;
      while(1){
        if(*(jdgtmp+i) == '*')
          strnum++;
        if(strnum == 2){
          printf("' * ' can only be used once.\n");
          return;
        }
        if(*(jdgtmp+i) == '\0')
            break;
        i++;
      }
      SearchOption(movie, searchTmp, t_movie, 0);
      SearchOption(director, searchTmp, t_director, 0);
      SearchOption(actor, searchTmp, t_actor, 0);
      printf("@@ Done.\n");
    }
    else if(num == 3){  // search [option] string
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      i=1;
      while(i<4){
        if(*(op1+i) == 'm'){
          SearchOption(movie, searchTmp, t_movie, 1);
        }
        else if(*(op1+i) == 'd'){
          SearchOption(director, searchTmp, t_director, 1);
        }
        else if(*(op1+i) == 'a'){
          SearchOption(actor, searchTmp, t_actor, 1);
        }
        else if(*(op1+i) == '\0'){
          break;
        }
        else{
          printf("'%s' is not correct option\n[option] : -m|d|a\n", op1);
          break;
        }
        i++;
      }
      printf("@@ Done.\n");
    }
  }
  else if(strcmp(tag, "sort") == 0){
    if(num == 2){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      if(strcmp(op1, "m") == 0){
        sortOption(t_movie, movie, "t", NULL);
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "d") == 0){
        sortOption(t_director, director, "n", NULL);
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "a") == 0){
        sortOption(t_actor, actor, "n", NULL);
        printf("@@ Done.\n");
      }
      else
      ;
    }
    else if(num == 3){ //option
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      if(strcmp(op1, "m") == 0){
        sortOption(t_movie, movie, op2, NULL);
      }
      else if(strcmp(op1, "d") == 0){
        sortOption(t_director, director, op2, NULL);
      }
      else if(strcmp(op1, "a") == 0){
        sortOption(t_actor, actor, op2, NULL);
      }
    }
    else if(num == 4){ //-f filename
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+5));
      strcpy(op3, *(str+3));
      strcat(op3, ".txt");
      if(strcmp(op2, "-f") == 0){
        if(strcmp(op1, "m") == 0){
          sortOption(t_movie, movie, "t", op3);
        }
        else if(strcmp(op1, "d") == 0){
          sortOption(t_director, director, "n", op3);
        }
        else if(strcmp(op1, "a") == 0){
          sortOption(t_actor, actor, "n", op3);
        }
      }
      else
      ;
    }
    else if(num == 5){ //option -f filename
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+1));
      strcpy(op3, *(str+3));
      op4 = (char*)malloc(sizeof(char)*(strlen(*str+4)+5));
      strcpy(op4, *(str+4));
      strcat(op4, ".txt");
      if(strcmp(op3, "-f") == 0){
        if(strcmp(op1, "m") == 0){
          sortOption(t_movie, movie, op2, op4);
        }
        else if(strcmp(op1, "d") == 0){
          sortOption(t_director, director, op2, op4);
        }
        else if(strcmp(op1, "a") == 0){
          sortOption(t_actor, actor, op2, op4);
        }
      }
      else
      ;
    }
    else
    ;
  }
  else if(strcmp(tag, "save") == 0){
    if(num == 2){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      if(strcmp(op1, "m") == 0){
        saveOption(t_movie, movie, "tgdyra", "movie_list.txt");
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "d") == 0){
        saveOption(t_director, director, "nsbm", "director_list.txt");
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "a") == 0){
        saveOption(t_actor, actor, "nsbm", "actor_list.txt");
        printf("@@ Done.\n");
      }
      else
      printf("Input format is not correct\nsave m|d|a [option] [-f file_name]\n");
    }
    else if(num == 3){ //option
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      if(*(*(str+2)) == '-'){
        op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)));
        strcpy(op2, *(str+2)+1);
      }
      else{
        printf("The options are written like '-%s'.\n",*(str+2));
        return;
      }
      if(strcmp(op1, "m") == 0){
        saveOption(t_movie, movie, op2, "movie_list.txt");
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "d") == 0){
        saveOption(t_director, director, op2, "director_list.txt");
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "a") == 0){
        saveOption(t_actor, actor, op2, "actor_list.txt");
        printf("@@ Done.\n");
      }
      else
        printf("Input format is not correct\nsave m|d|a [option] [-f file_name]\n");
    }
    else if(num == 4){ //-f filename
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+5));
      strcpy(op3, *(str+3));
      strcat(op3, ".txt");
      if(strcmp(op2, "-f") == 0){
        if(strcmp(op1, "m") == 0){
          saveOption(t_movie, movie, "tgdrya", op3);
          printf("@@ Done.\n");
        }
        else if(strcmp(op1, "d") == 0){
          saveOption(t_director, director, "nsbm", op3);
          printf("@@ Done.\n");
        }
        else if(strcmp(op1, "a") == 0){
          saveOption(t_actor, actor, "nsbm", op3);
          printf("@@ Done.\n");
        }
      }
      else
        printf("Input format is not correct\nsave m|d|a [option] [-f file_name]\n");
    }
    else if(num == 5){ //option -f filename
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      if(*(*(str+2)) == '-'){
        op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)));
        strcpy(op2, *(str+2)+1);
      }
      else{
        return;
      }
      op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+1));
      strcpy(op3, *(str+3));
      op4 = (char*)malloc(sizeof(char)*(strlen(*str+4)+5));
      strcpy(op4, *(str+4));
      strcat(op4, ".txt");
      if(strcmp(op3, "-f") == 0){
        if(strcmp(op1, "m") == 0){
          saveOption(t_movie, movie, op2, op4);
          printf("@@ Done.\n");
        }
        else if(strcmp(op1, "d") == 0){
          saveOption(t_director, director, op2, op4);
          printf("@@ Done.\n");
        }
        else if(strcmp(op1, "a") == 0){
          saveOption(t_actor, actor, op2, op4);
          printf("@@ Done.\n");
        }
      }
      else
      printf("Input format is not correct\nsave m|d|a [option] [-f file_name]\n");
    }
    else
      printf("Input format is not correct\nsave m|d|a [option] [-f file_name]\n");
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
