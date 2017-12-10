#include "head.h"

void makeList(MOVIE * mPtr, DIR_ACTOR * dPtr, DIR_ACTOR * aPtr){
  // 기존에 존재하는 레코드의 값을 모두 적기 위한 함수
  MOVIE * crntMoviePtr = mPtr;
  DIR_ACTOR * crntDirectorPtr = dPtr;
  DIR_ACTOR * crntActorPtr = aPtr;
  DATA_AT * crntMovieActorsPtr = mPtr->actors;
  DATA_AT * crntDirectorBestTitlesPtr = dPtr->best_movies;
  DATA_AT * crntActorBestTitlesPtr = aPtr->best_movies;
  FILE * fp;

  crntMoviePtr = mPtr;
  crntMovieActorsPtr = mPtr->actors;
  // 적고자 하는 텍스트 파일을 연다.
  fp = fopen("movie_list.txt", "wt");
  while(1){
    // 반복문을 통해 해당 레코드의 값을
    // 모두 텍스트 파일에 적는다.
    fprintf(fp,"%s:", crntMoviePtr->title);
    fprintf(fp,"%s:", crntMoviePtr->genre);
    fprintf(fp,"%s:", crntMoviePtr->director->data_at);
    fprintf(fp,"%d:", crntMoviePtr->year);
    fprintf(fp,"%d:", crntMoviePtr->runtime);
    crntMovieActorsPtr = crntMoviePtr->actors;
    while(1){
      // 영화 레코드의 배우의 경우도 마찬가지로 반복문을 통해
      // 모든 데이터를 적는다.
      fprintf(fp,"%s", crntMovieActorsPtr->data_at);
      if(crntMovieActorsPtr->next == NULL){
        break;
      }
      fprintf(fp,",");
      crntMovieActorsPtr = crntMovieActorsPtr->next;
    }
    fprintf(fp,"\n");
    if(crntMoviePtr->next == NULL){
      break;
    }
    crntMoviePtr = crntMoviePtr->next;
  }
  fclose(fp);

  crntDirectorPtr = dPtr;
  crntDirectorBestTitlesPtr = dPtr->best_movies;
  // 적고자 하는 텍스트 파일을 연다.
  fp = fopen("director_list.txt", "wt");
  while(1){
    // 반복문을 통해 해당 레코드의 값을
    // 모두 텍스트 파일에 적는다.
    fprintf(fp,"%s:", crntDirectorPtr->name);
    fprintf(fp,"%s:", crntDirectorPtr->sex);
    fprintf(fp,"%d:", crntDirectorPtr->birth);
    crntDirectorBestTitlesPtr = crntDirectorPtr->best_movies;
    while(1){
      // 대표작의 경우도 마찬가지로 반복문을 통해
      // 모든 데이터를 적는다.
      fprintf(fp,"%s", crntDirectorBestTitlesPtr->data_at);
      if(crntDirectorBestTitlesPtr->next == NULL){
        break;
      }
      fprintf(fp,",");
      crntDirectorBestTitlesPtr = crntDirectorBestTitlesPtr->next;
    }
    fprintf(fp,"\n");
    if(crntDirectorPtr->next == NULL){
      break;
    }
    crntDirectorPtr = crntDirectorPtr->next;
  }
  fclose(fp);

  crntActorPtr = aPtr;
  crntActorBestTitlesPtr = aPtr->best_movies;
  // 적고자 하는 텍스트 파일을 연다.
  fp = fopen("actor_list.txt", "wt");
  while(1){
    // 반복문을 통해 해당 레코드의 값을
    // 모두 텍스트 파일에 적는다.
    fprintf(fp,"%s:", crntActorPtr->name);
    fprintf(fp,"%s:", crntActorPtr->sex);
    fprintf(fp,"%d:", crntActorPtr->birth);
    crntActorBestTitlesPtr = crntActorPtr->best_movies;
    while(1){
      // 대표작의 경우도 마찬가지로 반복문을 통해
      // 모든 데이터를 적는다.
      fprintf(fp,"%s", crntActorBestTitlesPtr->data_at);
      if(crntActorBestTitlesPtr->next == NULL){
        break;
      }
      fprintf(fp,",");
      crntActorBestTitlesPtr = crntActorBestTitlesPtr->next;
    }
    fprintf(fp,"\n");
    if(crntActorPtr->next == NULL){
      break;
    }
    crntActorPtr = crntActorPtr->next;
  }
  fclose(fp);
}

void Save_File(){
  time_t now=time(NULL);
  char backupFile[31];
  char save[56];
  int rc;
  // 기존 파일의 존재 여부를 파악하기 위한 절차
  FILE *fp = fopen("movie_list.txt","rt");
  if(fp != NULL){
    // 현재 시간과 날짜를 형식화 하는 strftime() 함수를 이용하여
    // 백업 파일 명을 변수에 저장한다.
    strftime(backupFile,28,"movie_list.%Y%m%d%H%M.txt",localtime(&now));
    sprintf(save,"cp movie_list.txt %s",backupFile);
    rc=system(save);
    // 해당 명령이 정상적으로 수행되었는지 파악하기 위함.
    // 리턴값이 0일 경우 정상적인 처리가 이루어지지 않음.
    if( rc != 0 )
      printf( "정상적으로 수행되지 않았습니다.\n" );
    fclose(fp);
  }
  // 기존 파일의 존재 여부를 파악하기 위한 절차
  fp = fopen("director_list.txt","rt");
  if(fp != NULL){
    // 현재 시간과 날짜를 형식화 하는 strftime() 함수를 이용하여
    // 백업 파일 명을 변수에 저장한다.
    strftime(backupFile,31,"director_list.%Y%m%d%H%M.txt",localtime(&now));
    sprintf(save,"cp director_list.txt %s",backupFile);
    rc=system(save);
    // 해당 명령이 정상적으로 수행되었는지 파악하기 위함.
    // 리턴값이 0일 경우 정상적인 처리가 이루어지지 않음.
    if( rc != 0 )
       printf( "정상적으로 수행되지 않았습니다.\n" );
    fclose(fp);
  }
  // 기존 파일의 존재 여부를 파악하기 위한 절차
  fp = fopen("actor_list.txt","rt");
  if(fp != NULL){
    // 현재 시간과 날짜를 형식화 하는 strftime() 함수를 이용하여
    // 백업 파일 명을 변수에 저장한다.
    strftime(backupFile,31,"actor_list.%Y%m%d%H%M.txt",localtime(&now));
    sprintf(save,"cp actor_list.txt %s",backupFile);
    rc=system(save);
    // 해당 명령이 정상적으로 수행되었는지 파악하기 위함.
    // 리턴값이 0일 경우 정상적인 처리가 이루어지지 않음.
    if( rc != 0 )
       printf( "정상적으로 수행되지 않았습니다.\n" );
    fclose(fp);
  }
}
