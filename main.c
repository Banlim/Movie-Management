#define GLOBAL_DEF

#include "head.h"

int main(){
  printf(">> Welcome to My Movie <<\n");
  printf("File Loading.....\n");

  startReadLog();
  linkLog(movie, director, actor);
  Save_File();
  makeList(movie, director, actor);
  //////////////////////////////////
  printf("You can use add, update, delete, search, sort, save, end commands.\n");
  ////////////////////////////////// start //////////////////////////////////
  while(1){
    Input_Tag(movie, director, actor);
    linkLog(movie,director,actor);
    Save_File();
    makeList(movie, director, actor);
  }
  return 0;
}
