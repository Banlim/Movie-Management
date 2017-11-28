#include "head.h"

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

void Save_File(){
  time_t now=time(NULL);
  char backupFile[28];
  char save[56];
  int rc;
  strftime(backupFile,28,"movie_list.%Y%m%d%H%M.txt",localtime(&now));
  printf("%s\n",backupFile);
  sprintf(save,"mv movie_list.txt %s",backupFile);
  rc=system(save);
  if( rc != 0 )
     printf( "정상적으로 수행되지 않았습니다.\n" );
  FILE *fp = fopen("movie_list.txt","a");
  fclose(fp);
  strftime(backupFile,31,"director_list.%Y%m%d%H%M.txt",localtime(&now));
  printf("%s\n",backupFile);
  sprintf(save,"mv director_list.txt %s",backupFile);
  rc=system(save);
  if( rc != 0 )
     printf( "정상적으로 수행되지 않았습니다.\n" );
  fp = fopen("director_list.txt","a");
  fclose(fp);
  strftime(backupFile,31,"actor_list.%Y%m%d%H%M.txt",localtime(&now));
  printf("%s\n",backupFile);
  sprintf(save,"mv actor_list.txt %s",backupFile);
  rc=system(save);
  if( rc != 0 )
     printf( "정상적으로 수행되지 않았습니다.\n" );
  fp = fopen("actor_list.txt","a");
  fclose(fp);
}
