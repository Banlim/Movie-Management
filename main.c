#define GLOBAL_DEF

#include "head.h"

int main(){
  printf(">> Welcome to My Movie <<\n");
  printf("File Loading.....\n");

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
    movie=(MOVIE*)readLog(fp, movie, moviePosPtr, t_movie);
    if(fgetc(fp) == EOF)
      break;
  }
  fclose(fp);
  fp = fopen("director_log.txt", "rt");
  while(1){
    director=(DIR_ACTOR*)readLog(fp, director, directorPosPtr, t_director);
    if(fgetc(fp) == EOF)
      break;
  }
  fclose(fp);
  fp = fopen("actor_log.txt", "rt");
  while(1){
    actor=(DIR_ACTOR*)readLog(fp, actor, actorPosPtr, t_actor);
    if(fgetc(fp) == EOF)
      break;
  }
  fclose(fp);

  Save_File();
  makeList(movie, director, actor);

  linkLog(movie,director,actor);
  //////////////////////////////////
  printf("You can use add, update, delete, search, sort, save, end commands.\n");
  ////////////////////////////////// start //////////////////////////////////
  while(1){
    Input_Tag(movie, director, actor);
    makeList(movie, director, actor);
    linkLog(movie,director,actor);
    Save_File();
  }
  return 0;
}
