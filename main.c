#define GLOBAL_DEF

#include "head.h"

int main(){
  signal(SIGINT, contrl_C);  // 인터럽트 신호 처리기
  printf(">> Welcome to My Movie <<\n");
  printf("File Loading.....\n");

  startReadLog(); // 구조체를 선언하고 메모리를 할당하기 위한 함수
  linkLog(movie, director, actor);  // 같은 데이터를 찾아 연결해주기 위한 함수
  Save_File(); // list.txt 파일이 존재한다면 백업해주는 함수
  makeList(movie, director, actor); // list.txt 파일에 현재 레코드값을 적는 함수
  //////////////////////////////////
  printf("You can use add, update, delete, search, sort, save, end commands.\n");
  ////////////////////////////////// start //////////////////////////////////
  while(1){
    Input_Tag(movie, director, actor); // 사용자에게 옵션을 입력받는 함수
    linkLog(movie,director,actor);
    Save_File();
    makeList(movie, director, actor);
  }
  return 0;
}
