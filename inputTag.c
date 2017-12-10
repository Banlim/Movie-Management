#include "head.h"
//입력 함수
void Input_Tag(MOVIE * mPtr, DIR_ACTOR * dPtr, DIR_ACTOR * aPtr){
  char *tag=NULL, *op1=NULL, *op2=NULL, *op3=NULL, *op4=NULL;
  char ** str = NULL;
  char * tmp = NULL, * tmp_str = NULL, * searchTmp = NULL;
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
    // search 옵션 구현 시 사용자의 입력 사항을 모두 전달하기 위해
    // searchTmp 변수에 따로 저장해둔다.
    searchTmp=(char*)malloc(sizeof(strlen(tmp))+1);
    strcpy(searchTmp, tmp);
    while( getchar() != '\n' );
    //예외 처리
    if(scanfNum == 0){
      // 올바르게 입력된 값이 없다면 break 처리.
      break;
    }
    else{
      // 사용자의 입력 값을 strtok() 함수를 이용하여 자른다.
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
    // 태그 입력 후 옵션 및 문자열의 입력이 없을 경우
    // return 처리하여 input_Tag() 함수를 종료한다.
    return;
  }
  tag = (char*)malloc(sizeof(char)*(strlen(*str)+1));
  strcpy(tag, *(str));
  //tag 판단을 시작한다.
  // 각각의 tag를 처리하는 방법으로는 num 변수를 사용하여 각각의 옵션을 나누어 처리한다.
  // num 변수는 tag 입력 후 옵션 및 문자열의 입력 갯수이다.
  // 각각의 옵션을 처리하기 위하여 해당 옵션의 함수를 호출하여
  // 세부 요구 사항을 처리한다.
  if(strcmp(tag, "add") == 0){ // add 옵션
    if(num == 2){
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      if(strcmp(op1, "m") == 0){
        fp=fopen("movie_log.txt","at");
        add(fp, movie, t_movie);
        fclose(fp);
        fp = fopen("movie_log.txt", "rt");
        readLog(fp, movie, moviePosPtr, t_movie);
        fclose(fp);
      }
      else if(strcmp(op1, "d") == 0){
        fp=fopen("director_log.txt","at");
        add(fp, director, t_director);
        fclose(fp);
        fp = fopen("director_log.txt", "rt");
        readLog(fp, director, directorPosPtr, t_director);
        fclose(fp);
      }
      else if (strcmp(op1, "a") == 0){
        fp=fopen("actor_log.txt","at");
        add(fp, actor, t_actor);
        fclose(fp);
        fp = fopen("actor_log.txt", "rt");
        readLog(fp, actor, actorPosPtr, t_actor);
        fclose(fp);
      }
      else
        printf("'%s' is not correct option\noption : m d a\n", op1);
    }
    else
      printf("\tInput format is not correct\n\tadd m|d|a\n");
  }
  else if(strcmp(tag, "update") == 0){ // update 옵션
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
          if(preArrange(op2, "tgdyra") == NULL){
            printf("%s is not correct option\n", op2);
            return;
          }
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
        fp = fopen("movie_log.txt", "rt");
        readLog(fp, movie, moviePosPtr, t_movie);
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
          if(preArrange(op2, "nsbm") == NULL){
            printf("%s is not correct option\n", op2);
            return;
          }
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
        fp = fopen("director_log.txt", "rt");
        readLog(fp, director, directorPosPtr, t_director);
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
          if(preArrange(op2, "nsbm") == NULL){
            printf("%s is not correct option\n", op2);
            return;
          }
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
        fp = fopen("actor_log.txt", "rt");
        readLog(fp, actor, actorPosPtr, t_actor);
        fclose(fp);
      }
      else
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  m : [option] : t g d r y a\n\td|a : [option] : n s b m\n");
    }
    else
      printf("Input format is not correct\nupdate m|d|a [option] num\n\t  m : [option] : t g d r y a\n\td|a : [option] : n s b m\n");
  }
  else if(strcmp(tag, "delete") == 0){ // delete 옵션
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
          if(mPtr->srl_num == srl){
            break;
          }
          if(mPtr->next == NULL){
            break;
          }
          mPtr = mPtr->next;
        }
        if(mPtr->srl_num != srl){
          printf("@@ No sush record.\n");
          return ;
        }
        fp = fopen("movie_log.txt", "at");
        fprintf(fp, "delete:%d::::::\n", srl);
        fclose(fp);
        fp = fopen("movie_log.txt", "rt");
        readLog(fp, movie, moviePosPtr, t_movie);
        fclose(fp);
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "d") == 0){
        while(1){
          if(dPtr->srl_num == srl){
            break;
          }
          if(dPtr->next == NULL){
            break;
          }
          dPtr = dPtr->next;
        }
        if(dPtr->srl_num != srl){
          printf("@@ No sush record.\n");
          return ;
        }
        fp = fopen("director_log.txt", "at");
        fprintf(fp, "delete:%d::::\n", srl);
        fclose(fp);
        fp = fopen("director_log.txt", "rt");
        readLog(fp, director, directorPosPtr, t_director);
        fclose(fp);
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "a") == 0){
        while(1){
          if(aPtr->srl_num == srl){
            break;
          }
          if(aPtr->next == NULL){
            break;
          }
          aPtr = aPtr->next;
        }
        if(aPtr->srl_num != srl){
          printf("@@ No sush record.\n");
          return ;
        }
        fp = fopen("actor_log.txt", "at");
        fprintf(fp, "delete:%d::::\n", srl);
        fclose(fp);
        fp = fopen("actor_log.txt", "rt");
        readLog(fp, actor, actorPosPtr, t_actor);
        fclose(fp);
        printf("@@ Done.\n");
      }
      else
        printf("'%s' is not correct option\noption : m d a\n", op1);
    }
    else
      printf("Input format is not correct\ndelete m|d|a num\n");
  }
  else if(strcmp(tag, "print") == 0){ // print 옵션
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
  else if(strcmp(tag, "search") == 0){ // search 옵션
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
      if(preArrange(op1, "-mda") == NULL){
        printf("%s is not correct option\n", op1);
        return;
      }
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
        else if(*(op1+i) == ' ');
        else{
          printf("'%s' is not correct option\n[option] : -m|d|a\n", op1);
          break;
        }
        i++;
      }
      printf("@@ Done.\n");
    }
  }
  else if(strcmp(tag, "sort") == 0){ // sort 옵션
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
        printf("'%s' is not correct option\n[option] : m|d|a\n", op1);
    }
    else if(num == 3){ //option
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      if(strlen(op2) != 1){
        printf("Input option must be one\n");
        return;
      }
      if(strcmp(op1, "m") == 0){
        sortOption(t_movie, movie, op2, NULL);
      }
      else if(strcmp(op1, "d") == 0){
        sortOption(t_director, director, op2, NULL);
      }
      else if(strcmp(op1, "a") == 0){
        sortOption(t_actor, actor, op2, NULL);
      }
      else
        printf("'%s' is not correct option\n[option] : m|d|a\n", op1);
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
        else
          printf("'%s' is not correct option\n[option] : m|d|a\n", op1);
      }
      else
        printf("Input format is not correct\nsort m|d|a [option] [-f file_name]\n");
    }
    else if(num == 5){ //option -f filename
      op1 = (char*)malloc(sizeof(char)*(strlen(*str+1)+1));
      strcpy(op1, *(str+1));
      op2 = (char*)malloc(sizeof(char)*(strlen(*str+2)+1));
      strcpy(op2, *(str+2));
      if(strlen(op2) != 1){
        printf("Input option must be one\n");
        return;
      }
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
        else
          printf("'%s' is not correct option\n[option] : m|d|a\n", op1);
      }
      else
        printf("Input format is not correct\nsort m|d|a [option] [-f file_name]\n");
    }
    else
      printf("Input format is not correct\nsort m|d|a [option] [-f file_name]\n");
  }
  else if(strcmp(tag, "save") == 0){ // save 옵션
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
        if(preArrange(op2, "tgdyra") == NULL){
          printf("%s is not correct option\n", op2);
          return;
        }
        saveOption(t_movie, movie, op2, "movie_list.txt");
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "d") == 0){
        if(preArrange(op2, "nsbm") == NULL){
          printf("%s is not correct option\n", op2);
          return;
        }
        saveOption(t_director, director, op2, "director_list.txt");
        printf("@@ Done.\n");
      }
      else if(strcmp(op1, "a") == 0){
        if(preArrange(op2, "nsbm") == NULL){
          printf("%s is not correct option\n", op2);
          return;
        }
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
        else
          printf("'%s' is not correct option\n[option] : m|d|a\n", op1);
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
        printf("The options are written like '-%s'.\n",*(str+2));
        return;
      }
      op3 = (char*)malloc(sizeof(char)*(strlen(*str+3)+1));
      strcpy(op3, *(str+3));
      op4 = (char*)malloc(sizeof(char)*(strlen(*str+4)+5));
      strcpy(op4, *(str+4));
      strcat(op4, ".txt");
      if(strcmp(op3, "-f") == 0){
        if(strcmp(op1, "m") == 0){
          if(preArrange(op2, "tgdrya") == NULL){
            printf("%s is not correct option\n", op2);
            return;
          }
          saveOption(t_movie, movie, op2, op4);
          printf("@@ Done.\n");
        }
        else if(strcmp(op1, "d") == 0){
          if(preArrange(op2, "nsbm") == NULL){
            printf("%s is not correct option\n", op2);
            return;
          }
          saveOption(t_director, director, op2, op4);
          printf("@@ Done.\n");
        }
        else if(strcmp(op1, "a") == 0){
          if(preArrange(op2, "nsbm") == NULL){
            printf("%s is not correct option\n", op2);
            return;
          }
          saveOption(t_actor, actor, op2, op4);
          printf("@@ Done.\n");
        }
        else
          printf("'%s' is not correct option\n[option] : m|d|a\n", op1);
      }
      else
      printf("Input format is not correct\nsave m|d|a [option] [-f file_name]\n");
    }
    else
      printf("Input format is not correct\nsave m|d|a [option] [-f file_name]\n");
  }
  else if(strcmp(tag, "end") == 0){ // end 옵션
    exit(0);
  }
  else  // 올바른 tag 및 옵션 사용이 아닐 경우
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

char* preArrange(char* cmpstr, char* stdstr){
  // cmpstr에는 미리 변환할 문자열을, stdstr에는 변환될 기준이 될 문자열을 받아서
  // cmpstr에 있는 문자열의 문자들을 stdstr에 있는 문자면 stdstr의 문자의 위치를 기준으로 문자를 넣고,
  // 만약 stdstr에 있는 문자지만 cmpstr에 없을경우에는 그문자의 위치는 공백으로 남기고 cmpstr를 수정한다.
  // 단 cmpstr에는 있지만stdstr에 없는 문자나 중복된 문자가 있을경우에는 NULL을 반환한다.
  int cmpLoc = 0, stdLoc = 0, i = 0;
  char * returnStr = (char*)malloc((strlen(stdstr)+1)*sizeof(char));
  for(i = 0; i < strlen(stdstr); i++){
    *(returnStr+i) = ' ';
  }
  *(returnStr+strlen(stdstr)) = '\0';
  while(1){
    if(*(cmpstr+cmpLoc) == '\0')
      break;
    stdLoc = 0;
    while(1){
      if(*(cmpstr+cmpLoc) == *(stdstr+stdLoc)){
        if(*(returnStr+stdLoc) != *(stdstr+stdLoc))
          *(returnStr+stdLoc) = *(stdstr+stdLoc);
        else
          return NULL;
        cmpLoc++;
        break;
      }
      else if(*(stdstr+stdLoc) == '\0')
        return NULL;
      else
        stdLoc++;
    }
  }
  cmpstr = (char*)realloc(cmpstr, (strlen(stdstr)+1)*sizeof(char));
  strcpy(cmpstr, returnStr);
}

char* Scan_log(){
  // 사용자의 입력값을 처리하기 위한 함수
  char *op;
  char *tmp=(char *)malloc(100);
  scanf("%[ a-zA-Z,.0-9:]",tmp);
  while(getchar()!='\n');
  op=(char *)malloc(strlen(tmp)+1);
  strcpy(op,tmp);
  op = changeColon(op, t_print);
  op = (char*)realloc(op, sizeof(char)*(strlen(op)+1));
  return op;
}

char* changeColon(char* ptr, Type mode){
  // 파일에서 읽은 문자열을 출력하는 경우는 t_print,
  //사용자에게 입력 받은 경우는 t_read로 mode를 받아서
  // t_read일경우에는 문자열에서 ??;를 strstr함수로 찾아서 모두 :으로 바꿔준 문자열을 반환하고,
  // t_print인경우에는 문자열에서 :을 strstr함수로 찾아서 모두 ??;로 바꿔준 문자열을 반환한다.
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
