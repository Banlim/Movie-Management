#include "head.h"
//입력 함수
extern int m_srl, d_srl, a_srl; //마지막 시리얼 넘버 저장 전역 변수

int excludeSameRecord(void * ptr, char * compareString, Type type){
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    while(moviePointer->next != NULL){
      if(strcmp(compareString, moviePointer->title) == 0) return 0;
      moviePointer = moviePointer->next;
    }
  }
  else if(type == t_director){
    DIR_ACTOR * directorPointer = ((DIR_ACTOR*)ptr);
    while(directorPointer->next != NULL){
      if(strcmp(compareString, directorPointer->name) == 0) return 0;
      directorPointer= directorPointer->next;
    }
  }
  else if(type == t_actor){
    DIR_ACTOR * actorPointer = (DIR_ACTOR*)ptr;
    while(actorPointer->next != NULL){
      if(strcmp(compareString, actorPointer->name) == 0) return 0;
      actorPointer = actorPointer->next;
    }
  }
  return 1;
}

void add(FILE * fp, void * ptr, Type type){
  if(type == t_movie){
    fp=fopen("movie_log.txt","at");
    char *title,*genre,*director,*actors;
    int year,runtime;
    printf("title > ");
    title=Scan_log();
    printf("genre > ");
    genre=Scan_log();
    printf("director > ");
    director=Scan_log();
    printf("year > ");
    scanf("%d",&year);
    while(getchar()!='\n');
    printf("runtime > ");
    scanf("%d",&runtime);
    while(getchar()!='\n');
    printf("actors > ");
    actors=Scan_log();
    //////////////// 같은 영화 제목 제외 ////////////////
    MOVIE * moviePointer = (MOVIE*)ptr;
    if(excludeSameRecord(moviePointer, title, t_movie) != 0){
      m_srl++;
      fprintf(fp,"add:%d:%s:%s:%s:%d:%d:%s\n",m_srl,title,genre,director,year,runtime,actors);
    }
    else{
      printf("same : %s_%s\n",title, moviePointer->title);  // test 출력
      printf("@@You have the same record in movie list.\n");
      printf("%d:%s:%s:%s:%d:%d:",moviePointer->srl_num,moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
      while(1){
        printf("%s", moviePointer->actors->data_at);
        if(moviePointer->actors->next == NULL)
          break;
        printf(",");
        moviePointer->actors = moviePointer->actors->next;
      }
      printf("\n");
      printf("@@ Do you want to add any way? (Y/N) ");
      char ch;
      scanf(" %c",&ch);
      getchar();
      if(ch=='Y' || ch=='y'){
        m_srl++;
        fprintf(fp,"add:%d:%s:%s:%s:%d:%d:%s\n",m_srl,title,genre,director,year,runtime,actors);
      }
      if(ch=='N' || ch=='n')
        return;
    }
    fclose(fp);
  }
  else if(type == t_director){
    fp=fopen("director_log.txt","at");
    char *name,sex,*best_movies;
    int birth;
    printf("name > ");
    name=Scan_log();
    printf("sex(M/F) > ");
    scanf("%c",&sex);
    while(getchar()!='\n');
    printf("birth(Only 8numbers) > ");
    scanf("%d",&birth);
    while(getchar()!='\n');
    printf("best_movies > ");
    best_movies=Scan_log();
    //////////////// 같은 감독 이름 제외 ////////////////
    DIR_ACTOR * directorPointer = (DIR_ACTOR*)ptr;
    if(excludeSameRecord(directorPointer, name, t_director) != 0){
      d_srl++;
      fprintf(fp,"add:%d:%s:%c:%d:%s\n",d_srl,name,sex,birth,best_movies);
    }
    else{
      printf("same : %s_%s\n",name, directorPointer->name);  // test 출력
      printf("@@You have the same record in director list.\n");
      printf("%d:%s:%s:%d:",directorPointer->srl_num,directorPointer->name,directorPointer->sex,directorPointer->birth);
      while(1){
        printf("%s", directorPointer->best_movies->data_at);
        if(directorPointer->best_movies->next == NULL){
          break;
        }
        printf(",");
        directorPointer->best_movies = directorPointer->best_movies->next;
      }
      printf("\n");
      printf("@@ Do you want to add any way? (Y/N) ");
      char ch;
      scanf(" %c",&ch);
      getchar();
      if(ch=='Y' || ch=='y'){
        d_srl++;
        fprintf(fp,"add:%d:%s:%c:%d:%s\n",d_srl,name,sex,birth,best_movies);
      }
      if(ch=='N' || ch=='n')
        return;
    }
    fclose(fp);
  }
  else if (type == t_actor){
    fp=fopen("actor_log.txt","at");
    char *name,sex,*best_movies;
    int birth;
    printf("name > ");
    name=Scan_log();
    printf("sex(M/F) > ");
    scanf("%c",&sex);
    while(getchar()!='\n');
    printf("birth(Only 8numbers) > ");
    scanf("%d",&birth);
    while(getchar()!='\n');
    printf("best_movies > ");
    best_movies=Scan_log();
    //////////////// 같은 배우 이름 제외 ////////////////
    DIR_ACTOR * actorPointer = (DIR_ACTOR*)ptr;
    if(excludeSameRecord(actorPointer, name, t_director) != 0){
      a_srl++;
      fprintf(fp,"add:%d:%s:%c:%d:%s\n",a_srl,name,sex,birth,best_movies);
    }
    else{
      printf("same : %s_%s\n",name, actorPointer->name);  // test 출력
      printf("@@You have the same record in director list.\n");
      printf("%d:%s:%s:%d:",actorPointer->srl_num,actorPointer->name,actorPointer->sex,actorPointer->birth);
      while(1){
        printf("%s", actorPointer->best_movies->data_at);
        if(actorPointer->best_movies->next == NULL){
          break;
        }
        printf(",");
        actorPointer->best_movies = actorPointer->best_movies->next;
      }
      printf("\n");
      printf("@@ Do you want to add any way? (Y/N) ");
      char ch;
      scanf(" %c",&ch);
      getchar();
      if(ch=='Y' || ch=='y'){
        a_srl++;
        fprintf(fp,"add:%d:%s:%c:%d:%s\n",a_srl,name,sex,birth,best_movies);
      }
      if(ch=='N' || ch=='n')
        return;
    }
    fclose(fp);
  }
}

void update(FILE * fp, int srl, char * option, void * ptr, Type type){
  if(type == t_movie){
    char *title = "=",*genre = "=",*director = "=",*actors = "=";
    char *year = "=", *runtime = "=";
    int i = 0;
    while(1){
      if(*(option+i)=='t'){
        printf("title > ");
        title=Scan_log();
      }
      else if(*(option+i)=='g'){
        printf("genre > ");
        genre=Scan_log();
      }
      else if(*(option+i)=='d'){
        printf("director > ");
        director=Scan_log();
      }
      else if(*(option+i)=='y'){
        printf("year > ");
        year=Scan_log();
      }
      else if(*(option+i)=='r'){
        printf("runtime > ");
        runtime=Scan_log();
      }
      else if(*(option+i)=='a'){
        printf("actors > ");
        actors=Scan_log();
      }
      else if(*(option+i)=='\0'){
        break;
      }
      else{
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  m : [option] : t g d r y a\n");
        return;
      }
      i++;
    }
    //////////////// 같은 영화 제목 제외 ////////////////
    MOVIE * moviePointer = (MOVIE*)ptr;
    if(excludeSameRecord(moviePointer, title, t_movie) != 0){
      fprintf(fp,"update:%d:%s:%s:%s:%s:%s:%s\n",srl,title,genre,director,year,runtime,actors);
    }
    else{
      printf("same : %s_%s\n",title, moviePointer->title);  // test 출력
      printf("@@You have the same record in movie list.\n");
      printf("%d:%s:%s:%s:%d:%d:",moviePointer->srl_num,moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
      while(1){
        printf("%s", moviePointer->actors->data_at);
        if(moviePointer->actors->next == NULL)
          break;
        printf(",");
        moviePointer->actors = moviePointer->actors->next;
      }
      printf("\n");
      printf("@@ Do you want to add any way? (Y/N) ");
      char ch;
      scanf(" %c",&ch);
      getchar();
      if(ch=='Y' || ch=='y'){
        m_srl++;
        fprintf(fp,"update:%d:%s:%s:%s:%s:%s:%s\n",srl,title,genre,director,year,runtime,actors);
      }
      if(ch=='N' || ch=='n')
        return;
    }
  }
  else if(type == t_director){
    char *name="=",sex='=',*best_movies="=",*birth="=";
    int i = 0;
    while(1){
      if(*(option+i)=='n'){
        printf("name > ");
        name=Scan_log();
      }
      else if(*(option+i)=='s'){
        printf("sex(M/F) > ");
        scanf("%c",&sex);
        fflush(stdin);
      }
      else if(*(option+i)=='b'){
        printf("birth(Only 8numbers) > ");
        scanf("%d",&birth);
        while(getchar()!='\n');
      }
      else if(*(option+i)=='m'){
        printf("best_movies > ");
        best_movies=Scan_log();
      }
      else if(*(option+i)=='\0'){
        break;
      }
      else{
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  d|a : [option] : n b s m\n");
        return;
      }
      i++;
    }
    //////////////// 같은 감독 이름 제외 ////////////////
    DIR_ACTOR * directorPointer = (DIR_ACTOR*)ptr;
    if(excludeSameRecord(directorPointer, name, t_director) != 0){
      fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
    }
    else{
      printf("same : %s_%s\n",name, directorPointer->name);  // test 출력
      printf("@@You have the same record in director list.\n");
      printf("%d:%s:%s:%d:",directorPointer->srl_num,directorPointer->name,directorPointer->sex,directorPointer->birth);
      while(1){
        printf("%s", directorPointer->best_movies->data_at);
        if(directorPointer->best_movies->next == NULL){
          break;
        }
        printf(",");
        directorPointer->best_movies = directorPointer->best_movies->next;
      }
      printf("\n");
      printf("@@ Do you want to add any way? (Y/N) ");
      char ch;
      scanf(" %c",&ch);
      getchar();
      if(ch=='Y' || ch=='y'){
        d_srl++;
        fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
      }
      if(ch=='N' || ch=='n')
        return;
    }
  }
  else if(type == t_actor){
    char *name="=",sex='=',*best_movies="=",*birth="=";
    int i = 0;
    while(1){
      if(*(option+i)=='n'){
        printf("name > ");
        name=Scan_log();
      }
      else if(*(option+i)=='s'){
        printf("sex(M/F) > ");
        scanf("%c",&sex);
      }
      else if(*(option+i)=='b'){
        printf("birth(Only 8numbers) > ");
        scanf("%d",&birth);
        while(getchar()!='\n');
      }
      else if(*(option+i)=='m'){
        printf("best_movies > ");
        best_movies=Scan_log();
      }
      else if(*(option+i)=='\0'){
        break;
      }
      else{
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  d|a : [option] : n b s m\n");
        return;
      }
      i++;
    }
    //////////////// 같은 배우 이름 제외 ////////////////
    DIR_ACTOR * actorPointer = (DIR_ACTOR*)ptr;
    if(excludeSameRecord(actorPointer, name, t_director) != 0){
      fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
    }
    else{
      printf("same : %s_%s\n",name, actorPointer->name);  // test 출력
      printf("@@You have the same record in director list.\n");
      printf("%d:%s:%s:%d:",actorPointer->srl_num,actorPointer->name,actorPointer->sex,actorPointer->birth);
      while(1){
        printf("%s", actorPointer->best_movies->data_at);
        if(actorPointer->best_movies->next == NULL){
          break;
        }
        printf(",");
        actorPointer->best_movies = actorPointer->best_movies->next;
      }
      printf("\n");
      printf("@@ Do you want to add any way? (Y/N) ");
      char ch;
      scanf(" %c",&ch);
      getchar();
      if(ch=='Y' || ch=='y'){
        a_srl++;
        fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
      }
      if(ch=='N' || ch=='n')
        return;
    }
  }
}

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
