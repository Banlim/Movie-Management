#include "head.h"

char * read(FILE * fp, Type type){
  char * str = (char*)malloc(100);
  if(type == t_str){
    fscanf(fp, "%[ a-zA-Z.=?;]:", str);
  }
  else if(type == t_data_at){
    fscanf(fp, "%[ a-zA-Z0-9.?;]", str);
  }
  else if(type == t_str_all){
    fscanf(fp, "%[ a-zA-Z0-9.=?;]:", str);
  }
  str = changeColon(str, t_read);
  str = (char*)realloc(str, sizeof(char)*(strlen(str)+1));
  return str;
}

void startReadLog(void){
  movie = (MOVIE*)malloc(sizeof(MOVIE));
  movie->actors = (DATA_AT*)malloc(sizeof(DATA_AT));
  movie->next = NULL;
  movie->title = NULL;
  director = (DIR_ACTOR*)malloc(sizeof(DIR_ACTOR));
  director->best_movies = (DATA_AT*)malloc(sizeof(DATA_AT));
  director->next = NULL;
  director->name = NULL;
  actor = (DIR_ACTOR*)malloc(sizeof(DIR_ACTOR));
  actor->best_movies = (DATA_AT*)malloc(sizeof(DATA_AT));
  actor->next = NULL;
  actor->name = NULL;

  FILE * fp;
  fp = fopen("movie_log.txt", "rt");
  while(1){
    readLog(fp, movie, moviePosPtr, t_movie);
    fgetc(fp);
    if(fgetc(fp) == EOF)
      break;
  }
  fclose(fp);
  fp = fopen("director_log.txt", "rt");
  while(1){
    readLog(fp, director, directorPosPtr, t_director);
    fgetc(fp);
    if(fgetc(fp) == EOF)
      break;
  }
  fclose(fp);
  fp = fopen("actor_log.txt", "rt");
  while(1){
    readLog(fp, actor, actorPosPtr, t_actor);
    fgetc(fp);
    if(fgetc(fp) == EOF)
      break;
  }
  fclose(fp);
  return;
}

void readLog(FILE * fp, void * ptr, fpos_t * pos, Type type){
  char * tag, * tmp_str;
  int srlNum, tmp_num, up_cnt;
  if(type == t_movie){
    MOVIE *previousPointer=NULL, *moviePointer = (MOVIE*)ptr;
    MOVIE *currentPointer=NULL, *updatePointer=NULL;
    void *tmpPointer = NULL;
    DATA_AT *currentActorsPointer = moviePointer->actors;
    previousPointer = moviePointer;
    while(1){
      if(previousPointer->next == NULL)
        break;
      previousPointer = previousPointer->next;
    }
    if(previousPointer->title == NULL){
      previousPointer = NULL;
      currentPointer = moviePointer;
    }
    if(*pos == 0)
      fgetpos(fp, pos);
    fsetpos(fp, pos);
    tag=read(fp, t_str);
    fscanf(fp, "%d:", &srlNum);
    if(strcmp(tag, "update") == 0){
      updatePointer = movie;
      while(1){
        if(updatePointer->srl_num == srlNum)
          break;
        if(updatePointer->next == NULL)
          break;
        updatePointer = updatePointer->next;
      }
      up_cnt = 3;
      while(up_cnt <= 8){
        tmp_str = read(fp, t_str_all);
        switch(up_cnt){
          case 3:
            if(strcmp(tmp_str, "=") != 0)
              updatePointer->title = tmp_str;
            break;
          case 4:
            if(strcmp(tmp_str, "=") != 0)
              updatePointer->genre = tmp_str;
            break;
          case 5:
            if(strcmp(tmp_str, "=") != 0){
              updatePointer->director->data_at = tmp_str;
              updatePointer->director->next = NULL;
            }
            break;
          case 6:
            if(strcmp(tmp_str, "=") != 0)
              updatePointer->year = atoi(tmp_str);
            break;
          case 7:
            if(strcmp(tmp_str, "=") != 0)
              updatePointer->runtime = atoi(tmp_str);
            break;
          case 8:
            if(strcmp(tmp_str, "=") != 0){
              currentActorsPointer = updatePointer->actors;
              fseek(fp,-strlen(tmp_str), SEEK_CUR);
              while(1){
                currentActorsPointer->data_at = read(fp, t_data_at);
                if(fgetc(fp) == '\n'){
                  currentActorsPointer->next = NULL;
                  break;
                }
                currentActorsPointer->next = (DATA_AT*)malloc(sizeof(DATA_AT));
                currentActorsPointer = currentActorsPointer->next;
              }
            }
            else
              fgetc(fp);
            break;
        }
        up_cnt++;
      }
    }
    else if(strcmp(tag, "delete") == 0){
      if(srlNum == moviePointer->srl_num){
        tmpPointer = moviePointer;
        movie = movie->next;
      }
      else{
        updatePointer = moviePointer;
        while(1){
          if(updatePointer->next == NULL)
            break;
          if(updatePointer->next->srl_num == srlNum)
            break;
          updatePointer = updatePointer->next;
        }
        tmpPointer = updatePointer->next;
        updatePointer->next = updatePointer->next->next;
      }
      updatePointer = (MOVIE*)tmpPointer;
      free(updatePointer->tag);
      free(updatePointer->title);
      free(updatePointer->genre);
      free(updatePointer->director->data_at);
      free(updatePointer->director);
      currentActorsPointer = updatePointer->actors;
      while(1){
        tmpPointer = currentActorsPointer;
        if(currentActorsPointer->next == NULL){
          free(((DATA_AT*)tmpPointer)->data_at);
          free((DATA_AT*)tmpPointer);
          break;
        }
        currentActorsPointer = currentActorsPointer->next;
        free(((DATA_AT*)tmpPointer)->data_at);
        free((DATA_AT*)tmpPointer);
      }
      free(updatePointer);
      fseek(fp, 7, SEEK_CUR);
    }
    else if(strcmp(tag, "add") == 0){
      if(previousPointer!=NULL){
        currentPointer = (MOVIE*)malloc(sizeof(MOVIE)); //할당
        currentPointer->actors = (DATA_AT*)malloc(sizeof(DATA_AT)); //할당
        previousPointer->next = currentPointer; // 연결
      }
      currentPointer->tag = tag;
      currentPointer->srl_num=srlNum;
      currentPointer->title=read(fp, t_str);
      currentPointer->genre=read(fp, t_str);
      currentPointer->director=(DATA_AT*)malloc(sizeof(DATA_AT));
      currentPointer->director->data_at=read(fp, t_str);
      currentPointer->director->next=NULL;
      fscanf(fp,"%d:",&tmp_num);
      currentPointer->year=tmp_num;
      fscanf(fp,"%d:",&tmp_num);
      currentPointer->runtime=tmp_num;
      currentActorsPointer = currentPointer->actors;
      while(1){
        currentActorsPointer->data_at = read(fp, t_data_at);
        if(fgetc(fp) == '\n'){
          currentActorsPointer->next = NULL;
          break;
        }
        currentActorsPointer->next = (DATA_AT*)malloc(sizeof(DATA_AT));
        currentActorsPointer = currentActorsPointer->next;
      }
      currentPointer->next = NULL;
      m_srl = currentPointer->srl_num;
    }
    fgetpos(fp, pos);
    return;
  }
  else if(type == t_director || type == t_actor){
    DIR_ACTOR *previousPointer=NULL, *dir_actorPointer = (DIR_ACTOR*)ptr;
    DIR_ACTOR *currentPointer=NULL, *updatePointer=NULL;
    void  *tmpPointer = NULL;
    DATA_AT *currentBestmoviesPointer = dir_actorPointer->best_movies;
    previousPointer = dir_actorPointer;
    while(1){
      if(previousPointer->next == NULL)
        break;
      previousPointer = previousPointer->next;
    }
    if(previousPointer->name == NULL){
      previousPointer = NULL;
      currentPointer = dir_actorPointer;
    }
    if(*pos == 0)
      fgetpos(fp, pos);
    else
      fsetpos(fp, pos);
    tag=read(fp, t_str);
    fscanf(fp, "%d:", &srlNum);
    if(strcmp(tag, "update") == 0){
      updatePointer = dir_actorPointer;
      while(1){
        if(updatePointer->srl_num == srlNum)
          break;
        if(updatePointer->next == NULL)
          break;
        updatePointer = updatePointer->next;
      }
      up_cnt = 3;
      while(up_cnt <= 6){
        tmp_str = read(fp, t_str_all);
        switch(up_cnt){
          case 3:
            if(strcmp(tmp_str, "=") != 0)
              updatePointer->name = tmp_str;
            break;
          case 4:
            if(strcmp(tmp_str, "=") != 0)
              updatePointer->sex = tmp_str;
            break;
          case 5:
            if(strcmp(tmp_str, "=") != 0)
              updatePointer->birth = atoi(tmp_str);
            break;
          case 6:
            if(strcmp(tmp_str, "=") != 0){
              currentBestmoviesPointer = updatePointer->best_movies;
              fseek(fp,-strlen(tmp_str), SEEK_CUR);
              while(1){
                currentBestmoviesPointer->data_at = read(fp, t_data_at);
                if(fgetc(fp) == '\n'){
                  currentBestmoviesPointer->next = NULL;
                  break;
                }
                currentBestmoviesPointer->next = (DATA_AT*)malloc(sizeof(DATA_AT));
                currentBestmoviesPointer = currentBestmoviesPointer->next;
              }
            }
            else
              fgetc(fp);
            break;
        }
        up_cnt++;
      }
    }
    else if(strcmp(tag, "delete") == 0){
      if(srlNum == dir_actorPointer->srl_num){
        tmpPointer = dir_actorPointer;
        if(type == t_director)
          director = director->next;
        else if(type == t_actor)
          actor = actor->next;
      }
      else{
        updatePointer = dir_actorPointer;
        while(1){
          if(updatePointer->next == NULL)
            break;
          if(srlNum == updatePointer->next->srl_num)
            break;
          updatePointer = updatePointer->next;
        }
        tmpPointer = updatePointer->next;
        updatePointer->next = updatePointer->next->next;
      }
      updatePointer = (DIR_ACTOR*)tmpPointer;
      free(updatePointer->tag);
      free(updatePointer->name);
      free(updatePointer->sex);
      currentBestmoviesPointer = updatePointer->best_movies;
      while(1){
        tmpPointer = currentBestmoviesPointer;
        if(currentBestmoviesPointer->next == NULL){
          free(((DATA_AT*)tmpPointer)->data_at);
          free((DATA_AT*)tmpPointer);
          break;
        }
        currentBestmoviesPointer = currentBestmoviesPointer->next;
        free(((DATA_AT*)tmpPointer)->data_at);
        free((DATA_AT*)tmpPointer);
      }
      free(updatePointer);
      fseek(fp, 5, SEEK_CUR);
    }
    else if(strcmp(tag, "add") == 0){
      if(previousPointer!=NULL){
        currentPointer = (DIR_ACTOR*)malloc(sizeof(DIR_ACTOR)); //할당
        currentPointer->best_movies = (DATA_AT*)malloc(sizeof(DATA_AT)); //할당
        previousPointer->next = currentPointer; // 연결
      }
      currentPointer->tag=tag;
      currentPointer->srl_num=srlNum;
      currentPointer->name=read(fp, t_str);
      currentPointer->sex=read(fp, t_str);
      fscanf(fp,"%d:",&tmp_num);
      currentPointer->birth=tmp_num;
      currentBestmoviesPointer = currentPointer->best_movies;
      while(1){
        currentBestmoviesPointer->data_at = read(fp, t_data_at);
        if(fgetc(fp) == '\n'){
          currentBestmoviesPointer->next = NULL;
          break;
        }
        currentBestmoviesPointer->next = (DATA_AT*)malloc(sizeof(DATA_AT));
        currentBestmoviesPointer = currentBestmoviesPointer->next;
      }
      currentPointer->next = NULL;
      if(type == t_director){
        d_srl = currentPointer->srl_num;
      }
      else if(type == t_actor){
        a_srl = currentPointer->srl_num;
      }
    }
    fgetpos(fp, pos);
    return;
  }
  else{
    printf("error\n");
  }
}

void linkLog(MOVIE * mPtr, DIR_ACTOR * dPtr, DIR_ACTOR * aPtr){ //함수 사용시 형변환 주의
  MOVIE * crntMoviePtr = mPtr;
  DIR_ACTOR * crntDirectorPtr = dPtr;
  DIR_ACTOR * crntActorPtr = aPtr;
  DATA_AT * crntMovieActorsPtr = mPtr->actors;
  DATA_AT * crntDirectorBestTitlesPtr = dPtr->best_movies;
  DATA_AT * crntActorBestTitlesPtr = aPtr->best_movies;
  /////////// movie의 director 연결 ///////////
  crntMoviePtr = mPtr;
  crntDirectorPtr = dPtr;
  while(1){ //movie의 director
    crntDirectorPtr = dPtr;
    while(1){ //director의 name
      if(strcmp(crntMoviePtr->director->data_at, crntDirectorPtr->name) == 0){
        crntMoviePtr->director->link = crntDirectorPtr;
        break;
      }
      else{
        crntMoviePtr->director->link = NULL;
      }
      if(crntDirectorPtr->next == NULL){
        break;
      }
      crntDirectorPtr = crntDirectorPtr->next;
    }
    if(crntMoviePtr->next == NULL){
      break;
    }
    crntMoviePtr = crntMoviePtr->next;
  }
  /////////// movie의 actor 연결 ///////////
  crntMoviePtr = mPtr;
  crntActorPtr = aPtr;
  while(1){ //movie의 actors
    crntMovieActorsPtr = crntMoviePtr->actors;
    while(1){  //movie의 actors의 title
      crntActorPtr = aPtr;
      while(1){ //actor의 name
        if(strcmp(crntMovieActorsPtr->data_at, crntActorPtr->name) == 0){
          crntMovieActorsPtr->link = crntActorPtr;
          break;
        }
        else{
          crntMovieActorsPtr->link = NULL;
        }
        if(crntActorPtr->next == NULL){
          break;
        }
        crntActorPtr = crntActorPtr->next;
      }
      if(crntMovieActorsPtr->next == NULL){
        break;
      }
      crntMovieActorsPtr = crntMovieActorsPtr->next;
    }
    if(crntMoviePtr->next == NULL){
      break;
    }
    crntMoviePtr = crntMoviePtr->next;
  }
  /////////// actor의 movie 연결 ///////////
  crntActorPtr = aPtr;
  crntMoviePtr = mPtr;
  while(1){ //actor의 best_movies
    crntActorBestTitlesPtr = crntActorPtr->best_movies;
    while(1){ //actor의 best_movies의 title
      crntMoviePtr = mPtr;
      while(1){ //movie의 title
        if(strcmp(crntActorBestTitlesPtr->data_at, crntMoviePtr->title) == 0){
          crntActorBestTitlesPtr->link = crntMoviePtr;
          break;
        }
        else{
          crntActorBestTitlesPtr->link = NULL;
        }
        if(crntMoviePtr->next == NULL){
          break;
        }
        crntMoviePtr = crntMoviePtr->next;
      }
      if(crntActorBestTitlesPtr->next == NULL){
        break;
      }
      crntActorBestTitlesPtr = crntActorBestTitlesPtr->next;
    }
    if(crntActorPtr->next == NULL){
      break;
    }
    crntActorPtr = crntActorPtr->next;
  }
  /////////// director의 movie 연결 ///////////
  crntDirectorPtr = dPtr;
  crntMoviePtr = mPtr;
  while(1){ //director의 best_movies
    crntDirectorBestTitlesPtr = crntDirectorPtr->best_movies;
    while(1){ //director의 best_movies의 title
      crntMoviePtr = mPtr;
      while(1){ //movie의 title
        if(strcmp(crntDirectorBestTitlesPtr->data_at, crntMoviePtr->title) == 0){
          crntDirectorBestTitlesPtr->link = crntMoviePtr;
          break;
        }
        else{
          crntDirectorBestTitlesPtr->link = NULL;
        }
        if(crntMoviePtr->next == NULL){
          break;
        }
        crntMoviePtr = crntMoviePtr->next;
      }
      if(crntDirectorBestTitlesPtr->next == NULL){
        break;
      }
      crntDirectorBestTitlesPtr = crntDirectorBestTitlesPtr->next;
    }
    if(crntDirectorPtr->next == NULL){
      break;
    }
    crntDirectorPtr = crntDirectorPtr->next;
  }
}
