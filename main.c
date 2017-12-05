#include "head.h"

int m_srl=0, d_srl=0, a_srl=0; //마지막 시리얼 넘버 저장 전역 변수

int main(){
  #include "declare.h"
  printf(">> Welcome to My Movie <<\n");
  printf("File Loading.....\n");

  movie=read_movie_log(movie);
  director=read_da_log(director,t_director);
  actor=read_da_log(actor,t_actor);
  makeList(movie, director, actor);

  //////////////////////////////////
  printf("You can use add, update, delete, search, sort, save, end commands.\n");
  ////////////////////////////////// start //////////////////////////////////
  while(1){
    Input_Tag(movie, director, actor);
    movie=read_movie_log(movie);
    director=read_da_log(director,t_director);
    actor=read_da_log(actor,t_actor);
    makeList(movie, director, actor);
  }
  return 0;
}
