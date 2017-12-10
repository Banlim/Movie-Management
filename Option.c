#include "head.h"

// add 옵션 함수
void add(FILE * fp, void * ptr, Type type){
  if(type == t_movie){
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
    DATA_AT * movieActorsPointer = moviePointer->actors;
    if(excludeSameRecord(moviePointer, title, t_movie) != 0){
      // 같은 레코드가 존재하지 않는다면 현재 시리얼넘버에 1을 더하고
      // 그 값을 log.txt 파일에 입력한다.
      m_srl++;
      fprintf(fp,"add:%d:%s:%s:%s:%d:%d:%s\n",m_srl,title,genre,director,year,runtime,actors);
      printf("@@ Done.\n");
    }
    else{
      // 같은 레코드가 존재한다면 해당 레코드의 값을 출력해준다.
      printf("@@You have the same record in movie list.\n");
      while(1){
        if(strcmp(title, moviePointer->title) == 0)
          break;
        moviePointer = moviePointer->next;
      }
      printf("\t%d:%s:%s:%s:%d:%d:",moviePointer->srl_num,moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
      movieActorsPointer = moviePointer->actors;
      while(1){
        printf("%s", movieActorsPointer->data_at);
        if(movieActorsPointer->next == NULL)
        break;
        printf(",");
        movieActorsPointer = movieActorsPointer->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      // Yes 또는 No를 정확하게 입력받기 위해 반복문을 사용하여
      // 사용자가 정확하게 입력할 때까지 반복한다.
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
  }
  else if(type == t_director){
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
    DATA_AT * directorBestTitlesPointer = directorPointer->best_movies;
    if(excludeSameRecord(directorPointer, name, t_director) != 0){
      // 같은 레코드가 존재하지 않는다면 현재 시리얼넘버에 1을 더하고
      // 그 값을 log.txt 파일에 입력한다.
      d_srl++;
      fprintf(fp,"add:%d:%s:%c:%d:%s\n",d_srl,name,sex,birth,best_movies);
      printf("@@ Done.\n");
    }
    else{
      // Yes 또는 No를 정확하게 입력받기 위해 반복문을 사용하여
      // 사용자가 정확하게 입력할 때까지 반복한다.
      printf("@@You have the same record in director list.\n");
      while(1){
        if(strcmp(name, directorPointer->name) == 0)
          break;
        directorPointer = directorPointer->next;
      }
      printf("\t%d:%s:%s:%d:",directorPointer->srl_num,directorPointer->name,directorPointer->sex,directorPointer->birth);
      directorPointer->best_movies;
      while(1){
        printf("%s", directorBestTitlesPointer->data_at);
        if(directorBestTitlesPointer->next == NULL){
          break;
        }
        printf(",");
        directorBestTitlesPointer = directorBestTitlesPointer->next;
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
  }
  else if (type == t_actor){
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
    DATA_AT * actorBestTitlesPointer = actorPointer->best_movies;
    if(excludeSameRecord(actorPointer, name, t_director) != 0){
      // 같은 레코드가 존재하지 않는다면 현재 시리얼넘버에 1을 더하고
      // 그 값을 log.txt 파일에 입력한다.
      a_srl++;
      fprintf(fp,"add:%d:%s:%c:%d:%s\n",a_srl,name,sex,birth,best_movies);
      printf("@@ Done.\n");
    }
    else{
      printf("@@You have the same record in director list.\n");
      while(1){
        if(strcmp(name, actorPointer->name) == 0)
          break;
        actorPointer = actorPointer->next;
      }
      printf("\t%d:%s:%s:%d:",actorPointer->srl_num,actorPointer->name,actorPointer->sex,actorPointer->birth);
      actorBestTitlesPointer = actorPointer->best_movies;
      while(1){
        printf("%s", actorBestTitlesPointer->data_at);
        if(actorBestTitlesPointer->next == NULL){
          break;
        }
        printf(",");
        actorBestTitlesPointer = actorBestTitlesPointer->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      while(1){
        // Yes 또는 No를 정확하게 입력받기 위해 반복문을 사용하여
        // 사용자가 정확하게 입력할 때까지 반복한다.
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
  }
}
// update 옵션 함수
void update(FILE * fp, int srl, char * option, void * ptr, Type type){
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    // 기본 값인 '='로 초기화 하여 값의 변동이 없을 시
    // 기본 값으로 자동 입력되게 하였다.
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
      // update 옵션 시 해당 레코드의 존재 여부를 먼저 검사한다.
      printf("@@ No sush record.\n");
      return ;
    }
    while(1){
      // 해당 옵션 문자열을 하나씩 문자로 비교하여 옵션을 처리한다.
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
      else if(*(option+i)==' ');
      else{
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  m : [option] : t g d r y a\n");
        return;
      }
      i++;
    }
    //////////////// 같은 영화 제목 제외 ////////////////
    moviePointer = (MOVIE*)ptr;
    DATA_AT * movieActorsPointer = moviePointer->actors;
    if(excludeSameRecord(moviePointer, title, t_movie) != 0){
      // 같은 레코드가 존재하지 않는다면
      // 그 값을 log.txt 파일에 입력한다.
      fprintf(fp,"update:%d:%s:%s:%s:%s:%s:%s\n",srl,title,genre,director,year,runtime,actors);
    }
    else{
      printf("@@You have the same record in movie list.\n");
      while(1){
        if(strcmp(title, moviePointer->title) == 0)
          break;
        moviePointer = moviePointer->next;
      }
      printf("%d:%s:%s:%s:%d:%d:",moviePointer->srl_num,moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
      movieActorsPointer = moviePointer->actors;
      while(1){
        printf("%s", movieActorsPointer->data_at);
        if(movieActorsPointer->next == NULL)
        break;
        printf(",");
        movieActorsPointer = movieActorsPointer->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      while(1){
        // Yes 또는 No를 정확하게 입력받기 위해 반복문을 사용하여
        // 사용자가 정확하게 입력할 때까지 반복한다.
        printf("@@ Do you want to add any way? (Yes/No) ");
        ch = (char*)malloc(20);
        scanf("%s",ch);
        tmp = (char*)malloc((strlen(ch)+1));
        strcpy(tmp,ch);
        getchar();
        if(strcmp(tmp,"Yes") == 0){
          m_srl++;
          fprintf(fp,"update:%d:%s:%s:%s:%d:%d:%s\n",srl,title,genre,director,year,runtime,actors);
          free(tmp);
          break;
        }
        else if(strcmp(tmp,"No") == 0){
          free(tmp);
          return;
        }
      }
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
      else if(*(option+i)==' ');
      else{
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  d|a : [option] : n b s m\n");
        return;
      }
      i++;
    }
    //////////////// 같은 감독 이름 제외 ////////////////
    directorPointer = (DIR_ACTOR*)ptr;
    DATA_AT * directorBestTitlesPointer = directorPointer->best_movies;
    if(excludeSameRecord(directorPointer, name, t_director) != 0){
      // 같은 레코드가 존재하지 않는다면
      // 그 값을 log.txt 파일에 입력한다.
      fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
    }
    else{
      printf("@@You have the same record in director list.\n");
      while(1){
        if(strcmp(name, directorPointer->name) == 0)
          break;
        directorPointer = directorPointer->next;
      }
      printf("%d:%s:%s:%d:",directorPointer->srl_num,directorPointer->name,directorPointer->sex,directorPointer->birth);
      directorPointer->best_movies;
      while(1){
        printf("%s", directorBestTitlesPointer->data_at);
        if(directorBestTitlesPointer->next == NULL){
          break;
        }
        printf(",");
      directorBestTitlesPointer = directorBestTitlesPointer->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      while(1){
        // Yes 또는 No를 정확하게 입력받기 위해 반복문을 사용하여
        // 사용자가 정확하게 입력할 때까지 반복한다.
        printf("@@ Do you want to add any way? (Yes/No) ");
        ch = (char*)malloc(20);
        scanf("%s",ch);
        tmp = (char*)malloc((strlen(ch)+1));
        strcpy(tmp,ch);
        getchar();
        if(strcmp(tmp,"Yes") == 0){
          d_srl++;
          fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
          free(tmp);
          break;
        }
        else if(strcmp(tmp,"No") == 0){
          free(tmp);
          return;
        }
      }
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
      else if(*(option+i)==' ');
      else{
        printf("Input format is not correct\nupdate m|d|a [option] num\n\t  d|a : [option] : n b s m\n");
        return;
      }
      i++;
    }
    //////////////// 같은 배우 이름 제외 ////////////////
    actorPointer = (DIR_ACTOR*)ptr;
    DATA_AT * actorBestTitlesPointer = actorPointer->best_movies;
    if(excludeSameRecord(actorPointer, name, t_director) != 0){
      // 같은 레코드가 존재하지 않는다면
      // 그 값을 log.txt 파일에 입력한다.
      fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
    }
    else{
      printf("@@You have the same record in director list.\n");
      while(1){
        if(strcmp(name, actorPointer->name) == 0)
          break;
        actorPointer = actorPointer->next;
      }
      printf("%d:%s:%s:%d:",actorPointer->srl_num,actorPointer->name,actorPointer->sex,actorPointer->birth);
      actorBestTitlesPointer = actorPointer->best_movies;
      while(1){
        printf("%s", actorBestTitlesPointer->data_at);
        if(actorBestTitlesPointer->next == NULL){
          break;
        }
        printf(",");
        actorBestTitlesPointer = actorBestTitlesPointer->next;
      }
      printf("\n");
      char * ch = NULL, * tmp = NULL;
      while(1){
        // Yes 또는 No를 정확하게 입력받기 위해 반복문을 사용하여
        // 사용자가 정확하게 입력할 때까지 반복한다.
        printf("@@ Do you want to add any way? (Yes/No) ");
        ch = (char*)malloc(20);
        scanf("%s",ch);
        tmp = (char*)malloc((strlen(ch)+1));
        strcpy(tmp,ch);
        getchar();
        if(strcmp(tmp,"Yes") == 0){
          d_srl++;
          fprintf(fp,"update:%d:%s:%c:%d:%s\n",srl,name,sex,birth,best_movies);
          free(tmp);
          break;
        }
        else if(strcmp(tmp,"No") == 0){
          free(tmp);
          return;
        }
      }
    }
  }
}
// 중복 레코드 예외 처리 함수
int excludeSameRecord(void * ptr, char * compareString, Type type){
  // 각각의 레코드의 타이틀 명이나 감독의 이름, 배우의 이름이 존재여부를 파악하기 위하여
  // 반복문과 문자열 비교함수인 strcmp() 함수를 사용하여 문자열을 비교한다.
  // 문자열이 같다면 리턴 값으로 0을 전달한다.
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    while(1){
      if(strcmp(compareString, moviePointer->title) == 0)
        return 0;
      if(moviePointer->next == NULL)
        break;
      moviePointer = moviePointer->next;
    }
  }
  else if(type == t_director){
    DIR_ACTOR * directorPointer = (DIR_ACTOR*)ptr;
    while(1){
      if(strcmp(compareString, directorPointer->name) == 0)
        return 0;
      if(directorPointer->next == NULL)
        break;
      directorPointer= directorPointer->next;
    }
  }
  else if(type == t_actor){
    DIR_ACTOR * actorPointer = (DIR_ACTOR*)ptr;
    while(1){
      if(strcmp(compareString, actorPointer->name) == 0)
        return 0;
      if(actorPointer->next == NULL)
        break;
      actorPointer = actorPointer->next;
    }
  }
  return 1;
}
// PrintOption
void PrintOption(void * ptr, int srl, Type type){
  int i=1;
  DATA_AT * Pointer;
  if(type == t_movie){
    MOVIE * linkPointer;
    MOVIE * moviePointer = (MOVIE*)ptr;
    DIR_ACTOR * DlinkPointer;
    while(1){
      // 해당 시리얼 넘버의 존재여부 파악을 위해
      // 반복문을 사용하여 해당 레코드를 조사한다.
      if(srl == moviePointer->srl_num)
        break;
      if(moviePointer->next == NULL){
        printf("@@ No such record.\n");
        return;
      }
      moviePointer = moviePointer->next;
    }
    printf("%d, %s, %s\n",moviePointer->srl_num, moviePointer->title,moviePointer->genre);
    printf("\tD : %s",moviePointer->director->data_at);
    DlinkPointer =(DIR_ACTOR*)moviePointer->director->link;
    //////////// director birth 파악 ////////////
    if(DlinkPointer == NULL)
      printf("\n");
    else
      printf(" (%d)\n",DlinkPointer->birth);
    //////////// actor 출력 & actor birth 파악 ////////////
    Pointer = moviePointer->actors;
    while(1){
      // 해당 배우의 link에 값이 NULL이라면 (-)를 출력하고
      // 값이 존재한다면 생년월일을 촐력한다.
      printf("\tA%d : %s ",i,Pointer->data_at);
      if(Pointer->link == NULL)
        printf(" (-)\n");
      else
        printf(" (%d)\n", ((DIR_ACTOR*)Pointer->link)->birth);
      if(Pointer->next == NULL){
        // 배우가 여러명 존재할 때를 위해 다음 next에 값의 존재 여부를 파악한다.
        printf("@@ Done.\n");
        break;
      }
      i++;
      Pointer = Pointer->next;
    }
  }
  else if(type == t_director){
    MOVIE * linkPointer;
    DIR_ACTOR * directorPointer = (DIR_ACTOR*)ptr;
    while(1){
      // 해당 시리얼 넘버의 존재여부 파악을 위해
      // 반복문을 사용하여 해당 레코드를 조사한다.
      if(srl == directorPointer->srl_num)
        break;
      if(directorPointer->next == NULL){
        printf("@@ No such record.\n");
        return;
      }
      directorPointer = directorPointer->next;
    }
    printf("%d, %s, %s, %d\n",directorPointer->srl_num, directorPointer->name,directorPointer->sex,directorPointer->birth);
    //////////// director best_movies 파악 ////////////
    Pointer = directorPointer->best_movies;
    linkPointer = (MOVIE*)directorPointer->best_movies->link;
    while(1){
      // 해당 영화의 link에 값이 NULL이라면 아무 것도 출력하지 않고,
      // 값이 존재한다면 개봉년도와 runtime을 촐력한다.
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
  else if(type == t_actor){
    MOVIE * linkPointer;
    DIR_ACTOR * actorPointer = (DIR_ACTOR*)ptr;
    while(1){
      // 해당 시리얼 넘버의 존재여부 파악을 위해
      // 반복문을 사용하여 해당 레코드를 조사한다.
      if(srl == actorPointer->srl_num)
        break;
      if(actorPointer->next == NULL){
        printf("@@ No such record.\n");
        return;
      }
      actorPointer = actorPointer->next;
    }
    if(srl != actorPointer->srl_num){
      printf("@@ No such record.\n");
      return;
    }
    printf("%d, %s, %s, %d\n",actorPointer->srl_num,actorPointer->name,actorPointer->sex,actorPointer->birth);
    //////////// actor best_movies 파악 ////////////
    Pointer = actorPointer->best_movies;
    linkPointer = (MOVIE*)actorPointer->best_movies->link;
    while(1){
      // 해당 영화의 link에 값이 NULL이라면 아무 것도 출력하지 않고,
      // 값이 존재한다면 개봉년도와 runtime을 촐력한다.
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
  // 옵션을 문자열 option으로 받은 후, 문자열을 차례로 읽으며 해당 정보를 출력한다.
  // filename이 NULL일 경우에는 디폴트 출력 파일인 list.txt 파일에 출력하고,
  // 아닌 경우에는 파일에 출력한다.
  FILE * fp = fopen(filename, "wt");
  int end = 0;
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    while(1){
      int i = 0;
      end = 0;
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
        int j = 1;
        while(1){
          if(*(option+i) == ' ')
            break;
          if(*(option+i+j) == '\0'){
            fprintf(fp, "\n");
            end = 1;
            break;
          }
          else if(*(option+i+j) == ' '){
            j++;
          }
          else{
            fprintf(fp, ":");
            break;
          }
        }
        if(end == 1)
          break;
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
      end = 0;
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
        int j = 1;
        while(1){
          if(*(option+i) == ' ')
            break;
          if(*(option+i+j) == '\0'){
            fprintf(fp, "\n");
            end = 1;
            break;
          }
          else if(*(option+i+j) == ' '){
            j++;
          }
          else{
            fprintf(fp, ":");
            break;
          }
        }
        if(end == 1)
          break;
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
// search 옵션 함수
void SearchOption(void * ptr, char * str, Type type, int num){
  char * tmp, * cmptmp;
  int i=0,last=0, cmplast=0, cnt=0, strnum=0;
  // 각각 옵션의 입력여부에 따라 문자열을 나누는 방법이 다르다
  if(num == 0){  //search string
    // search 를 잘라내고 뒷부분의 string을 tmp에 저장하기 위한 과정이다.
    tmp = strstr(str, " ");
    tmp+=1;
  }
  if(num == 1){ //search [option] string
    // search 를 잘라내고 뒷부분의 string을 tmp에 저장하기 위한 과정이다.
    tmp = strstr(str, " ");
    tmp+=1;
    // 뒷부분의 string 에서  옵션을 잘라내어 온전한 string을 tmp에 저장하기 위한 과정이다.
    // 다음 띄어쓰기가 나올때까지 string 문자열에 더하기 1을 해준다.
    while(*(tmp) != ' '){
      tmp+=1;
    }
    tmp+=1;
  }
  if(strcmp(tmp, "*")==0){
    // string의 값이 메타문자 *일 경우에 모든 레코드 값을 출력해주기 위해
    // 따로 구분하여 구현하였다.
    if(type == t_movie){
      MOVIE * moviePointer = (MOVIE*)ptr;
      DATA_AT * movieActorsPointer = moviePointer->actors;
      printf("> Movie_list\n");
      while(1){
        printf("\t%d:%s:%s:%s:%d:%d:",moviePointer->srl_num, moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
        movieActorsPointer = moviePointer->actors;
        while(1){
          printf("%s", movieActorsPointer->data_at);
          if(movieActorsPointer->next == NULL){
            printf("\n");
            break;
          }
          printf(", ");
          movieActorsPointer = movieActorsPointer->next;
        }
        if(moviePointer->next == NULL){
          break;
        }
        moviePointer = moviePointer->next;
      }
    }
    if(type == t_director || type == t_actor){
      DIR_ACTOR * daPointer = (DIR_ACTOR*)ptr;
      DATA_AT * daBestTitlesPointer = daPointer->best_movies;
      if(type == t_director){
        printf("> Director_list\n");
      }
      if(type == t_actor){
        printf("> Actor_list\n");
      }
      while(1){
        printf("\t%d:%s:%s:%d:",daPointer->srl_num, daPointer->name,daPointer->sex,daPointer->birth);
        daBestTitlesPointer = daPointer->best_movies;
        while(1){
          printf("%s", daBestTitlesPointer->data_at);
          if(daBestTitlesPointer->next == NULL){
            printf("\n");
            break;
          }
          printf(", ");
          daBestTitlesPointer = daBestTitlesPointer->next;
        }
        if(daPointer->next == NULL){
          break;
        }
        daPointer = daPointer->next;
      }
    }
    return;
  }
  while(1){
    // 사용자가 메타문자 *의 다중 사용을 막기 위한
    // 전처리 과정으로 다중 사용 시 return 한다.
    if(*(tmp+i) == '*')
      strnum++;
    if(strnum == 2){
      printf("' * ' can only be used once.\n");
      return;
    }
    if(*(tmp+i) == '\0')
        break;
    i++;
  }
  if(type == t_movie){
    MOVIE * moviePointer = (MOVIE*)ptr;
    DATA_AT * movieActorsPointer = moviePointer->actors;
    cnt=0;
    printf("> Movie_list\n");
    while(1){  // movie의 title
      cmptmp=NULL;
      cmptmp = (char*)malloc(sizeof(char)*(strlen(moviePointer->title)+1));
      strcpy(cmptmp, moviePointer->title);
      i=0;
      while(1){ // movie의 title 비교 시작
        if(*(cmptmp+i) == *(tmp+i) || *(tmp+i) == '?'){ // 값을 하나씩 비교를 하고 메타문자 ?의 경우 한번 지나가기 위해 continue를 사용한다.
          if(*(tmp+i) == '\0' && *(cmptmp+i) == '\0'){ // 문자열을 끝까지 다 비교하였을 때, 해당 문자열을 출력한다.
            printf("\t%d:%s:%s:%s:%d:%d:",moviePointer->srl_num, moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
            movieActorsPointer = moviePointer->actors;
            while(1){
              printf("%s", movieActorsPointer->data_at);
              if(movieActorsPointer->next == NULL){
                printf("\n");
                break;
              }
              printf(", ");
              movieActorsPointer = movieActorsPointer->next;
            }
            cnt++;
            break;
          }
          i++;
          continue;
        }
        else if(*(tmp+i) == '*'){ // 해당 값이 매타문자 *일 때
          last = strlen(tmp)-1;
          cmplast = strlen(cmptmp)-1;
          if(i==0){ // 문자열의 처음이 *로 시작할 때
            while(last != 0){
              // 문자열의 총 길이를 변수에 저장하여
              // 문자열의 끝부터 비교하기 시작한다.
              if(*(cmptmp+cmplast) == *(tmp+last) || *(tmp+last) == '?'){
                last--;
                cmplast--;
                continue;
              }
              else{
                // 값이 다를 경우 break하여 반복문을 빠져나간다.
                break;
              }
            }
            if(last == 0){ // 문자열이 메타문자 * 하나일 경우
              printf("\t%d:%s:%s:%s:%d:%d:",moviePointer->srl_num, moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
              movieActorsPointer = moviePointer->actors;
              while(1){
                printf("%s", movieActorsPointer->data_at);
                if(movieActorsPointer->next == NULL){
                  printf("\n");
                  break;
                }
                printf(", ");
                movieActorsPointer = movieActorsPointer->next;
              }
              cnt++;
            }
            break;
          }
          else if(i == last){ // 문자열의 끝이 *일 때
            // 해당 레코드를 다 출력한다.
            printf("\t%d:%s:%s:%s:%d:%d:",moviePointer->srl_num, moviePointer->title,moviePointer->genre,moviePointer->director->data_at,moviePointer->year,moviePointer->runtime);
            movieActorsPointer = moviePointer->actors;
            while(1){
              printf("%s", movieActorsPointer->data_at);
              if(movieActorsPointer->next == NULL){
                printf("\n");
                break;
              }
              printf(", ");
              movieActorsPointer = movieActorsPointer->next;
            }
            cnt++;
            break;
          }
          else{
            printf("Input format is not correct\nsearch [option] string\n[option] : -m -d -a\n");
            return;
          }
        }
        else{
          break;
        }
      }
      if(moviePointer->next == NULL)
        break;
      moviePointer = moviePointer->next;
    }
    if(cnt == 0) // 한번도 레코드를 출력하지 않았다면, 해당 문자열과 같은 레코드를 찾지 못한 것
      printf("@@ No sush record.\n");
  }
  if(type == t_director || type == t_actor){
    // 감독과 배우의 경우
    // 영화의 같은 원리를 사용하여 search 옵션을 구현하였다.
    DIR_ACTOR * daPointer = (DIR_ACTOR*)ptr;
    DATA_AT * daBestTitlesPointer = daPointer->best_movies;
    cnt=0;
    if(type == t_director){
      printf("> Director_list\n");
    }
    if(type == t_actor){
      printf("> Actor_list\n");
    }
    while(1){  // movie의 title
      cmptmp=NULL;
      cmptmp = (char*)malloc(sizeof(char)*(strlen(daPointer->name)+1));
      strcpy(cmptmp, daPointer->name);
      i=0;
      while(1){ // movie의 title 비교 시작
        if(*(cmptmp+i) == *(tmp+i) || *(tmp+i) == '?'){
          if(*(tmp+i) == '\0' && *(cmptmp+i) == '\0'){
            printf("\t%d:%s:%s:%d:",daPointer->srl_num, daPointer->name,daPointer->sex,daPointer->birth);
            daBestTitlesPointer = daPointer->best_movies;
            while(1){
              printf("%s", daBestTitlesPointer->data_at);
              if(daBestTitlesPointer->next == NULL){
                printf("\n");
                break;
              }
              printf(", ");
              daBestTitlesPointer = daBestTitlesPointer->next;
            }
            cnt++;
            break;
          }
          i++;
          continue;
        }
        else if(*(tmp+i) == '*'){
          last = strlen(tmp)-1;
          cmplast = strlen(cmptmp)-1;
          if(i==0){
            while(last != 0){
              if(*(cmptmp+cmplast) == *(tmp+last) || *(tmp+last) == '?'){
                last--;
                cmplast--;
                continue;
              }
              else{
                break;
              }
            }
            if(last == 0){
              printf("\t%d:%s:%s:%d:",daPointer->srl_num, daPointer->name,daPointer->sex,daPointer->birth);
              daBestTitlesPointer = daPointer->best_movies;
              while(1){
                printf("%s", daBestTitlesPointer->data_at);
                if(daBestTitlesPointer->next == NULL){
                  printf("\n");
                  break;
                }
                printf(", ");
                daBestTitlesPointer = daBestTitlesPointer->next;
              }
              cnt++;
            }
            break;
          }
          else if(i == last){
            printf("\t%d:%s:%s:%d:",daPointer->srl_num, daPointer->name,daPointer->sex,daPointer->birth);
            daBestTitlesPointer = daPointer->best_movies;
            while(1){
              printf("%s", daBestTitlesPointer->data_at);
              if(daBestTitlesPointer->next == NULL){
                printf("\n");
                break;
              }
              printf(", ");
              daBestTitlesPointer = daBestTitlesPointer->next;
            }
            cnt++;
            break;
          }
          else{
            printf("Input format is not correct\nsearch [option] string\n[option] : -m -d -a\n");
            return;
          }
        }
        else{
          break;
        }
      }
      if(daPointer->next == NULL)
        break;
      daPointer = daPointer->next;
    }
    if(cnt == 0)
      printf("@@ No sush record.\n");
  }
  return;
}
// sort 옵션 함수
void sortOption(Type type, void * ptr, char * option, char * filename){
  // 옵션을 문자열 option으로 받아서 구조체 포인터 배열을 만든 뒤,
  // qsort함수를 이용하여 옵션을 기준으로 정렬한다.
  // filename이 NULL일 경우에는 화면에 출력하고, 아닌 경우에는 파일에 출력한다.
  int i = 0;
  if(type == t_movie){
    MOVIE ** pointerArray = (MOVIE**)malloc(sizeof(MOVIE*)*1);
    MOVIE * crntMoviePtr = (MOVIE*)ptr;
    while(1){
      pointerArray = (MOVIE**)realloc(pointerArray, sizeof(MOVIE*)*(i+1));
      *(pointerArray+i) = crntMoviePtr;
      if(crntMoviePtr->next == NULL){
        break;
      }
      crntMoviePtr = crntMoviePtr->next;
      i++;
    }
    if(i+1 == 1){
      return;
    }
    if(*(option) == 't'){
      qsort(pointerArray, i+1, sizeof(MOVIE*), compareOptionT);
    }
    else if(*(option) == 'g'){
      qsort(pointerArray, i+1, sizeof(MOVIE*), compareOptionG);
    }
    else if(*(option) == 'd'){
      qsort(pointerArray, i+1, sizeof(MOVIE*), compareOptionD);
    }
    else if(*(option) == 'y'){
      qsort(pointerArray, i+1, sizeof(MOVIE*), compareOptionY);
    }
    else if(*(option) == 'r'){
      qsort(pointerArray, i+1, sizeof(MOVIE*), compareOptionR);
    }
    else if(*(option) == 'a'){
      qsort(pointerArray, i+1, sizeof(MOVIE*), compareOptionA);
    }
    else{
      printf("%s is not correct option\n", option);
      return;
    }
    int j = 0;
    if(filename == NULL){
      while(1){
        printf("%d:", (*(pointerArray+j))->srl_num);
        printf("%s:", (*(pointerArray+j))->title);
        printf("%s:", (*(pointerArray+j))->genre);
        printf("%s:", (*(pointerArray+j))->director->data_at);
        printf("%d:", (*(pointerArray+j))->year);
        printf("%d:", (*(pointerArray+j))->runtime);
        DATA_AT * pointerArrayActors = (*(pointerArray+j))->actors;
        while(1){
          printf("%s", pointerArrayActors->data_at);
          if(pointerArrayActors->next == NULL){
            printf("\n");
            break;
          }
          printf(",");
          pointerArrayActors = pointerArrayActors->next;
        }
        if(j == i){
          break;
        }
        j++;
      }
    }
    else{
      FILE * fp = fopen(filename, "wt");
      while(1){
        fprintf(fp, "%d:", (*(pointerArray+j))->srl_num);
        fprintf(fp, "%s:", (*(pointerArray+j))->title);
        fprintf(fp, "%s:", (*(pointerArray+j))->genre);
        fprintf(fp, "%s:", (*(pointerArray+j))->director->data_at);
        fprintf(fp, "%d:", (*(pointerArray+j))->year);
        fprintf(fp, "%d:", (*(pointerArray+j))->runtime);
        DATA_AT * pointerArrayActors = (*(pointerArray+j))->actors;
        while(1){
          fprintf(fp, "%s", pointerArrayActors->data_at);
          if(pointerArrayActors->next == NULL){
            fprintf(fp, "\n");
            break;
          }
          fprintf(fp, ",");
          pointerArrayActors = pointerArrayActors->next;
        }
        if(j == i){
          break;
        }
        j++;
      }
      fclose(fp);
    }
  }
  else if(type == t_director || type == t_actor){
    DIR_ACTOR ** pointerArray = (DIR_ACTOR**)malloc(sizeof(DIR_ACTOR*)*1);
    DIR_ACTOR * crntDirActorPtr = (DIR_ACTOR*)ptr;
    while(1){
      pointerArray = (DIR_ACTOR**)realloc(pointerArray, sizeof(DIR_ACTOR*)*(i+1));
      *(pointerArray+i) = crntDirActorPtr;
      if(crntDirActorPtr->next == NULL){
        break;
      }
      crntDirActorPtr = crntDirActorPtr->next;
      i++;
    }
    if(i+1 == 1){
      return;
    }
    if(*(option) == 'n'){
      qsort(pointerArray, i+1, sizeof(DIR_ACTOR*), compareOptionN);
    }
    else if(*(option) == 's'){
      qsort(pointerArray, i+1, sizeof(DIR_ACTOR*), compareOptionS);
    }
    else if(*(option) == 'b'){
      qsort(pointerArray, i+1, sizeof(DIR_ACTOR*), compareOptionB);
    }
    else if(*(option) == 'm'){
      qsort(pointerArray, i+1, sizeof(DIR_ACTOR*), compareOptionM);
    }
    else{
      printf("%s is not correct option\n", option);
      return;
    }
    int j = 0;
    if(filename == NULL){
      while(1){
        printf("%d:", (*(pointerArray+j))->srl_num);
        printf("%s:", (*(pointerArray+j))->name);
        printf("%s:", (*(pointerArray+j))->sex);
        printf("%d:", (*(pointerArray+j))->birth);
        DATA_AT * pointerArrayBestMovies = (*(pointerArray+j))->best_movies;
        while(1){
          printf("%s", pointerArrayBestMovies->data_at);
          if(pointerArrayBestMovies->next == NULL){
            printf("\n");
            break;
          }
          printf(",");
          pointerArrayBestMovies = pointerArrayBestMovies->next;
        }
        if(j == i){
          break;
        }
        j++;
      }
    }
    else{
      FILE * fp = fopen(filename, "wt");
      while(1){
        fprintf(fp, "%d:", (*(pointerArray+j))->srl_num);
        fprintf(fp, "%s:", (*(pointerArray+j))->name);
        fprintf(fp, "%s:", (*(pointerArray+j))->sex);
        fprintf(fp, "%d:", (*(pointerArray+j))->birth);
        DATA_AT * pointerArrayBestMovies = (*(pointerArray+j))->best_movies;
        while(1){
          fprintf(fp, "%s", pointerArrayBestMovies->data_at);
          if(pointerArrayBestMovies->next == NULL){
            fprintf(fp, "\n");
            break;
          }
          fprintf(fp, ",");
          pointerArrayBestMovies = pointerArrayBestMovies->next;
        }
        if(j == i){
          break;
        }
        j++;
      }
      fclose(fp);
    }
  }
  else
    ;
}
// compare함수
int compareOptionT(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 제목을 비교해 오름 차순으로 반환한다.
  return strcmp((char*)(*(MOVIE**)ptr1)->title, (char*)(*(MOVIE**)ptr2)->title);
}

int compareOptionG(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 장르를 비교해 오름 차순으로 반환한다.
  return strcmp((char*)(*(MOVIE**)ptr1)->genre, (char*)(*(MOVIE**)ptr2)->genre);
}

int compareOptionD(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 감독 이름을 비교해 오름 차순으로 반환한다.
  return strcmp((char*)((DATA_AT*)(*(MOVIE**)ptr1)->director)->data_at, (char*)((DATA_AT*)(*(MOVIE**)ptr2)->director)->data_at);
}

int compareOptionY(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 년도를 비교해 오름 차순으로 반환한다.
  if((int)(*(MOVIE**)ptr1)->year > (int)(*(MOVIE**)ptr2)->year){
    return 1;
  }
  else if((int)(*(MOVIE**)ptr1)->year == (int)(*(MOVIE**)ptr2)->year){
    return 0;
  }
  else{
    return -1;
  }
}

int compareOptionR(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 상영시간을 비교해 오름 차순으로 반환한다.
  if((int)(*(MOVIE**)ptr1)->runtime > (int)(*(MOVIE**)ptr2)->runtime){
    return 1;
  }
  else if((int)(*(MOVIE**)ptr1)->runtime == (int)(*(MOVIE**)ptr2)->runtime){
    return 0;
  }
  else{
    return -1;
  }
}

int compareOptionA(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 배우를 순서대로 비교해서
  // 배우끼리 이름이 같은 경우에는 다음 배우 비교로 판단하고
  // 한쪽이 다음으로 비교될 배우가 없는 경우에는 더 배우 수가 적은 쪽이 우선한다.
  //배우 이름이 다른 경우에는 오름차순으로 반환한다.
  DATA_AT * cmpPointer1 = (DATA_AT*)(*(MOVIE**)ptr1)->actors;
  DATA_AT * cmpPointer2 = (DATA_AT*)(*(MOVIE**)ptr2)->actors;
  while(1){
    if(strcmp((char*)cmpPointer1->data_at, (char*)cmpPointer2->data_at) == 0){
      if(cmpPointer1->next == NULL && cmpPointer2->next != NULL){
        return -1;
      }
      else if(cmpPointer1->next != NULL && cmpPointer2->next == NULL){
        return 1;
      }
      else if(cmpPointer1->next == NULL && cmpPointer2->next == NULL){
        return 0;
      }
      else{
        cmpPointer1 = cmpPointer1->next;
        cmpPointer2 = cmpPointer2->next;
      }
    }
    else{
      return strcmp((char*)cmpPointer1->data_at, (char*)cmpPointer2->data_at);
    }
  }
}

int compareOptionN(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 이름을 비교해 오름 차순으로 반환한다.
  return strcmp((char*)(*(DIR_ACTOR**)ptr1)->name, (char*)(*(DIR_ACTOR**)ptr2)->name);
}

int compareOptionS(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 성별을 비교해 오름 차순으로 반환한다.
  return strcmp((char*)(*(DIR_ACTOR**)ptr1)->sex, (char*)(*(DIR_ACTOR**)ptr2)->sex);
}

int compareOptionB(const void * ptr1, const void * ptr2){
  //qsort함수에 쓰이는 compare함수로 생년월일을 비교해 오름 차순으로 반환한다
  if((int)(*(DIR_ACTOR**)ptr1)->birth > (int)(*(DIR_ACTOR**)ptr2)->birth){
    return 1;
  }
  else if((int)(*(DIR_ACTOR**)ptr1)->birth == (int)(*(DIR_ACTOR**)ptr2)->birth){
    return 0;
  }
  else{
    return -1;
  }
}

int compareOptionM(const void * ptr1, const void * ptr2){
  // qsort함수에 쓰이는 compare함수로 제목을 순서대로 비교해서
  // 제목끼리 이름이 같은 경우에는 다음 영화 제목 비교로 판단하고
  // 한 쪽이 다음으로 비교될 제목이 없는 경우에는 더 대표작 수가 적은 쪽이 우선한다.
  // 제목이 다른 경우에는 오름차순으로 반환한다.
  DATA_AT * cmpPointer1 = (DATA_AT*)(*(DIR_ACTOR**)ptr1)->best_movies;
  DATA_AT * cmpPointer2 = (DATA_AT*)(*(DIR_ACTOR**)ptr2)->best_movies;
  while(1){
    if(strcmp((char*)cmpPointer1->data_at, (char*)cmpPointer2->data_at) == 0){
      if(cmpPointer1->next == NULL && cmpPointer2->next != NULL){
        return 1;
      }
      else if(cmpPointer1->next != NULL && cmpPointer2->next == NULL){
        return -1;
      }
      else if(cmpPointer1->next == NULL && cmpPointer2->next == NULL){
        return 0;
      }
      else{
        cmpPointer1 = cmpPointer1->next;
        cmpPointer2 = cmpPointer2->next;
      }
    }
    else{
      return strcmp((char*)cmpPointer1->data_at, (char*)cmpPointer2->data_at);
    }
  }
}
