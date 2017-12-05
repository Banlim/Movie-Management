#include "head.h"

extern int m_srl, d_srl, a_srl; //마지막 시리얼 넘버 저장 전역 변수
// add 옵션 함수
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
      printf("@@ Done.\n");
    }
    else{
      printf("@@You have the same record in movie list.\n");
      printf("\t%d:%s:%s:%s:%d:%d:",moviePointer->srl_num,moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
      while(1){
        printf("%s", moviePointer->actors->data_at);
        if(moviePointer->actors->next == NULL)
        break;
        printf(",");
        moviePointer->actors = moviePointer->actors->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      while(1){
        printf("@@ Do you want to add any way? (Yes/No) ");
        ch = (char*)malloc(20);
        scanf("%s",ch);
        tmp = (char*)malloc((strlen(ch)+1));
        strcpy(tmp,ch);
        getchar();
        if(strcmp(tmp,"Yes") == 0){
          m_srl++;
          fprintf(fp,"add:%d:%s:%s:%s:%d:%d:%s\n",m_srl,title,genre,director,year,runtime,actors);
          printf("@@ Done.\n");
          free(tmp);
          break;
        }
        else if(strcmp(tmp,"No") == 0){
          free(tmp);
          return;
        }
      }
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
      printf("@@ Done.\n");
    }
    else{
      printf("@@You have the same record in director list.\n");
      printf("\t%d:%s:%s:%d:",directorPointer->srl_num,directorPointer->name,directorPointer->sex,directorPointer->birth);
      while(1){
        printf("%s", directorPointer->best_movies->data_at);
        if(directorPointer->best_movies->next == NULL){
          break;
        }
        printf(",");
        directorPointer->best_movies = directorPointer->best_movies->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      while(1){
        printf("@@ Do you want to add any way? (Yes/No) ");
        ch = (char*)malloc(20);
        scanf(" %s",ch);
        tmp = (char*)malloc((strlen(ch)+1));
        strcpy(tmp,ch);
        getchar();
        if(strcmp(tmp,"Yes") == 0){
          d_srl++;
          fprintf(fp,"add:%d:%s:%c:%d:%s\n",d_srl,name,sex,birth,best_movies);
          printf("@@ Done.\n");
          free(tmp);
          break;
        }
        else if(strcmp(tmp,"No") == 0){
          free(tmp);
          return;
        }
      }
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
      printf("@@ Done.\n");
    }
    else{
      printf("@@You have the same record in director list.\n");
      printf("\t%d:%s:%s:%d:",actorPointer->srl_num,actorPointer->name,actorPointer->sex,actorPointer->birth);
      while(1){
        printf("%s", actorPointer->best_movies->data_at);
        if(actorPointer->best_movies->next == NULL){
          break;
        }
        printf(",");
        actorPointer->best_movies = actorPointer->best_movies->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      while(1){
        printf("@@ Do you want to add any way? (Yes/No) ");
        ch = (char*)malloc(20);
        scanf(" %s",ch);
        tmp = (char*)malloc((strlen(ch)+1));
        strcpy(tmp,ch);
        getchar();
        if(strcmp(tmp,"Yes") == 0){
          d_srl++;
          fprintf(fp,"add:%d:%s:%c:%d:%s\n",d_srl,name,sex,birth,best_movies);
          printf("@@ Done.\n");
          free(tmp);
          break;
        }
        else if(strcmp(tmp,"No") == 0){
          free(tmp);
          return;
        }
      }
    }
    fclose(fp);
  }
}
// update 옵션 함수
void update(FILE * fp, int srl, char * option, void * ptr, Type type){
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    char *title = "=",*genre = "=",*director = "=",*actors = "=";
    char *year = "=", *runtime = "=";
    int i = 0;
    while(1){
      if(moviePointer->srl_num == srl){
        break;
      }
      if(moviePointer->next == NULL){
        break;
      }
      moviePointer = moviePointer->next;
    }
    if(moviePointer->srl_num != srl){
      printf("@@ No sush record.\n");
      return ;
    }
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
    moviePointer = (MOVIE*)ptr;
    //////////////// 같은 영화 제목 제외 ////////////////
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
        printf("@@ Done.\n");
      }
      if(ch=='N' || ch=='n')
      return;
    }
  }
  else if(type == t_director){
    DIR_ACTOR * directorPointer = (DIR_ACTOR*)ptr;
    char *name="=",sex='=',*best_movies="=",*birth="=";
    int i = 0;
    while(1){
      if(directorPointer->srl_num == srl){
        break;
      }
      if(directorPointer->next == NULL){
        break;
      }
      directorPointer = directorPointer->next;
    }
    if(directorPointer->srl_num != srl){
      printf("@@ No sush record.\n");
      return ;
    }
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
    directorPointer = (DIR_ACTOR*)ptr;
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
    DIR_ACTOR * actorPointer = (DIR_ACTOR*)ptr;
    char *name="=",sex='=',*best_movies="=",*birth="=";
    int i = 0;
    while(1){
      if(actorPointer->srl_num == srl){
        break;
      }
      if(actorPointer->next == NULL){
        break;
      }
      actorPointer = actorPointer->next;
    }
    if(actorPointer->srl_num != srl){
      printf("@@ No sush record.\n");
      return ;
    }
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
    actorPointer = (DIR_ACTOR*)ptr;
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
// PrintOption
void PrintOption(void * ptr, int srl, Type type){
  int i=1;
  DATA_AT * Pointer;
  MOVIE * linkPointer;
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    DIR_ACTOR * DlinkPointer;
    while(moviePointer->next != NULL){
      if(srl == moviePointer->srl_num)
        break;
      moviePointer = moviePointer->next;
    }
    if(srl != moviePointer->srl_num){
      printf("@@ No such record.\n");
      return;
    }
    printf("%d, %s, %s\n",moviePointer->srl_num, moviePointer->title,moviePointer->genre);
    printf("\tD : %s",moviePointer->director->data_at);
    DlinkPointer = moviePointer->director->link;
    //////////// director birth 파악 ////////////
    if(moviePointer->director->link == NULL)
      printf("\n");
    else
      printf(" (%d)\n",DlinkPointer->birth);
    //////////// actor 출력 & actor birth 파악 ////////////
    Pointer = moviePointer->actors;
    while(1){
      printf("\tA%d : %s ",i,Pointer->data_at);
      if(Pointer->link == NULL)
        printf(" (-)\n");
      else
        printf(" (%d)\n", ((DIR_ACTOR*)Pointer->link)->birth);
      if(Pointer->next == NULL){
        printf("@@ Done.\n");
        break;
      }
      i++;
      Pointer = Pointer->next;
    }
  }
  if(type == t_director){
    DIR_ACTOR * directorPointer = (DIR_ACTOR*)ptr;
    while(directorPointer->next != NULL){
      if(srl == directorPointer->srl_num)
        break;
      directorPointer = directorPointer->next;
    }
    if(srl != directorPointer->srl_num){
      printf("@@ No such record.\n");
      return;
    }
    printf("%d, %s, %s, %d\n",directorPointer->srl_num, directorPointer->name,directorPointer->sex,directorPointer->birth);
    //////////// director best_movies 파악 ////////////
    Pointer = directorPointer->best_movies;
    linkPointer = directorPointer->best_movies->link;
    while(1){
      printf("\tBest_Movie%d : %s",i,Pointer->data_at);
      if(Pointer->link == NULL)
        printf("\n");
      else
        printf(", %d, %d\n", linkPointer->year, linkPointer->runtime);
      if(Pointer->next == NULL){
        printf("@@ Done.\n");
        break;
      }
      i++;
      Pointer = Pointer->next;
    }
  }
  if(type == t_actor){
    DIR_ACTOR * actorPointer = (DIR_ACTOR*)ptr;
    while(actorPointer->next != NULL){
      if(srl == actorPointer->srl_num)
        break;
      actorPointer = actorPointer->next;
    }
    if(srl != actorPointer->srl_num){
      printf("@@ No such record.\n");
      return;
    }
    printf("%d, %s, %s, %d\n",actorPointer->srl_num,actorPointer->name,actorPointer->sex,actorPointer->birth);
    //////////// actor best_movies 파악 ////////////
    Pointer = actorPointer->best_movies;
    linkPointer = actorPointer->best_movies->link;
    while(1){
      printf("\tBest_Movie%d : %s",i,Pointer->data_at);
      if(Pointer->link == NULL)
        printf("\n");
      else
        printf(", %d, %d\n", linkPointer->year, linkPointer->runtime);
      if(Pointer->next == NULL){
        printf("@@ Done.\n");
        break;
      }
      i++;
      Pointer = Pointer->next;
    }
  }
}
// save 옵션 함수
void saveOption(Type type, void * ptr, char * option, char * filename){
  FILE * fp = fopen(filename, "wt");
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    while(1){
      int i = 0;
      while(1){
        if(*(option+i) == 't'){
          fprintf(fp, "%s", moviePointer->title);
        }
        else if(*(option+i) == 'g'){
          fprintf(fp, "%s", moviePointer->genre);
        }
        else if(*(option+i) == 'd'){
          fprintf(fp, "%s", moviePointer->director->data_at);
        }
        else if(*(option+i) == 'y'){
          fprintf(fp, "%d", moviePointer->year);
        }
        else if(*(option+i) == 'r'){
          fprintf(fp, "%d", moviePointer->runtime);
        }
        else if(*(option+i) == 'a'){
          DATA_AT * movieActorsPointer = moviePointer->actors;
          while(1){
            fprintf(fp, "%s", movieActorsPointer->data_at);
            if(movieActorsPointer->next == NULL){
              break;
            }
            fprintf(fp, ",");
            movieActorsPointer = movieActorsPointer->next;
          }
        }
        if(*(option+i+1) == '\0'){
          fprintf(fp, "\n");
          break;
        }
        fprintf(fp, ":");
        i++;
      }
      if(moviePointer->next == NULL){
        break;
      }
      moviePointer = moviePointer->next;
    }
  }
  else if(type == t_director || type == t_actor){
    DIR_ACTOR * diractorPointer = (DIR_ACTOR*)ptr;
    while(1){
      int i = 0;
      while(1){
        if(*(option+i) == 'n'){
          fprintf(fp, "%s", diractorPointer->name);
        }
        else if(*(option+i) == 's'){
          fprintf(fp, "%s", diractorPointer->sex);
        }
        else if(*(option+i) == 'b'){
          fprintf(fp, "%d", diractorPointer->birth);
        }
        else if(*(option+i) == 'm'){
          DATA_AT * diractorBestMoviesPointer = diractorPointer->best_movies;
          while(1){
            fprintf(fp, "%s", diractorBestMoviesPointer->data_at);
            if(diractorBestMoviesPointer->next == NULL){
              break;
            }
            fprintf(fp, ",");
            diractorBestMoviesPointer = diractorBestMoviesPointer->next;
          }
        }
        if(*(option+i+1) == '\0'){
          fprintf(fp, "\n");
          break;
        }
        fprintf(fp, ":");
        i++;
      }
      if(diractorPointer->next == NULL){
        break;
      }
      diractorPointer = diractorPointer->next;
    }
  }
  else  ;
  fclose(fp);
}
