#include "head.h"

void makeList(MOVIE * mPtr, DIR_ACTOR * dPtr, DIR_ACTOR * aPtr){
  MOVIE * crntMoviePtr = mPtr;
  DIR_ACTOR * crntDirectorPtr = dPtr;
  DIR_ACTOR * crntActorPtr = aPtr;
  DATA_AT * crntMovieActorsPtr = mPtr->actors;
  DATA_AT * crntDirectorBestTitlesPtr = dPtr->best_movies;
  DATA_AT * crntActorBestTitlesPtr = aPtr->best_movies;
  FILE * fp;

  crntMoviePtr = mPtr;
  crntMovieActorsPtr = mPtr->actors;
  fp = fopen("movie_list.txt", "wt");
  while(1){
    fprintf(fp,"%s:", crntMoviePtr->title);
    fprintf(fp,"%s:", crntMoviePtr->genre);
    fprintf(fp,"%s:", crntMoviePtr->director->data_at);
    fprintf(fp,"%d:", crntMoviePtr->year);
    fprintf(fp,"%d:", crntMoviePtr->runtime);
    crntMovieActorsPtr = crntMoviePtr->actors;
    while(1){
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
  fp = fopen("director_list.txt", "wt");
  while(1){
    fprintf(fp,"%s:", crntDirectorPtr->name);
    fprintf(fp,"%s:", crntDirectorPtr->sex);
    fprintf(fp,"%d:", crntDirectorPtr->birth);
    crntDirectorBestTitlesPtr = crntDirectorPtr->best_movies;
    while(1){
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
  fp = fopen("actor_list.txt", "wt");
  while(1){
    fprintf(fp,"%s:", crntActorPtr->name);
    fprintf(fp,"%s:", crntActorPtr->sex);
    fprintf(fp,"%d:", crntActorPtr->birth);
    crntActorBestTitlesPtr = crntActorPtr->best_movies;
    while(1){
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
  FILE *fp = fopen("movie_list.txt","rt");
  if(fp != NULL){
    strftime(backupFile,28,"movie_list.%Y%m%d%H%M.txt",localtime(&now));
    sprintf(save,"cp movie_list.txt %s",backupFile);
    rc=system(save);
    if( rc != 0 )
      printf( "정상적으로 수행되지 않았습니다.\n" );
    fclose(fp);
  }
  fp = fopen("director_list.txt","rt");
  if(fp != NULL){
    strftime(backupFile,31,"director_list.%Y%m%d%H%M.txt",localtime(&now));
    sprintf(save,"cp director_list.txt %s",backupFile);
    rc=system(save);
    if( rc != 0 )
       printf( "정상적으로 수행되지 않았습니다.\n" );
    fclose(fp);
  }
  fp = fopen("actor_list.txt","rt");
  if(fp != NULL){
    strftime(backupFile,31,"actor_list.%Y%m%d%H%M.txt",localtime(&now));
    sprintf(save,"cp actor_list.txt %s",backupFile);
    rc=system(save);
    if( rc != 0 )
       printf( "정상적으로 수행되지 않았습니다.\n" );
    fclose(fp);
  }
}
