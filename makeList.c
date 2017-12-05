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
    while(1){
      fprintf(fp,"%s,", crntMovieActorsPtr->data_at);
      if(crntMovieActorsPtr->next == NULL){
        break;
      }
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
    while(1){
      fprintf(fp,"%s,", crntDirectorBestTitlesPtr->data_at);
      if(crntDirectorBestTitlesPtr->next == NULL){
        break;
      }
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
    while(1){
      fprintf(fp,"%s,", crntActorBestTitlesPtr->data_at);
      if(crntActorBestTitlesPtr->next == NULL){
        break;
      }
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
