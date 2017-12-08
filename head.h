#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef enum type{
  t_movie=1, t_director=2, t_actor=3, //구조체 타입
  t_str=11, t_data_at=12, t_str_all = 13, //반환 문자열 타입
  t_read=21, t_print=22 //모드 설정
} Type;

typedef struct data_at{ // 자기 참조 구조체 : 배우 & 대표작품
  char * data_at;
  void * link;
  struct data_at * next;
} DATA_AT;

typedef struct movie{ // 자기 참조 구조체 : 영화
  char * tag;
  int srl_num;
  char * title;
  char * genre;
  struct data_at * director;
  int year;
  int runtime;
  struct data_at * actors;
  struct movie * next;
} MOVIE;

typedef struct director_actor{ // 자기 참조 구조체 : 감독 &배우
  char * tag;
  int srl_num;
  char * name;
  char * sex;
  int birth;
  struct data_at * best_movies;
  struct director_actor * next;
} DIR_ACTOR;

////////////////////////////
void * readLog(FILE * fp, void * ptr, fpos_t * pos, Type type);
void linkLog(MOVIE * mPtr, DIR_ACTOR * dPtr, DIR_ACTOR * aPtr);
char* preArrange(char* cmpstr, char* stdstr);
////////////////////////////
void Input_Tag(MOVIE *, DIR_ACTOR *, DIR_ACTOR *);
char* Scan_log();
void add(FILE * fp, void * ptr, Type type);
void update(FILE * fp, int srl, char * option, void * ptr, Type type);
int excludeSameRecord(void * ptr, char * compareString, Type type);
char* changeColon(char* ptr, Type mode);
void makeList(MOVIE * mPtr, DIR_ACTOR * dPtr, DIR_ACTOR * aPtr);
////////////////////////////
void Save_File();
void PrintOption(void * ptr, int srl, Type type);
void SearchOption(void * ptr, char * str, Type type, int num);
void saveOption(Type type, void * ptr, char * option, char * filename);
void sortOption(Type type, void * ptr, char * option, char * filename);
////////////////////////////
int compareOptionT(const void * ptr1, const void * ptr2);
int compareOptionG(const void * ptr1, const void * ptr2);
int compareOptionD(const void * ptr1, const void * ptr2);
int compareOptionY(const void * ptr1, const void * ptr2);
int compareOptionR(const void * ptr1, const void * ptr2);
int compareOptionA(const void * ptr1, const void * ptr2);
int compareOptionN(const void * ptr1, const void * ptr2);
int compareOptionS(const void * ptr1, const void * ptr2);
int compareOptionB(const void * ptr1, const void * ptr2);
int compareOptionM(const void * ptr1, const void * ptr2

////////////////////////////
#ifdef GLOBAL_DEF
MOVIE * movie = NULL;
DIR_ACTOR * director = NULL;
DIR_ACTOR * actor = NULL;

int m_srl=0, d_srl=0, a_srl=0; //마지막 시리얼 넘버 저장 전역 변수
fpos_t moviePos=0, directorPos=0, actorPos=0; // 파일 위치 저장 전역 변수
fpos_t *moviePosPtr=&moviePos, *directorPosPtr=&directorPos, *actorPosPtr=&actorPos;
#else
extern MOVIE * movie;
extern DIR_ACTOR * director, * actor;

extern int m_srl, d_srl, a_srl; //마지막 시리얼 넘버 저장 전역 변수
extern fpos_t moviePos, directorPos, actorPos; // 파일 위치 저장 전역 변수
extern fpos_t *moviePosPtr, *directorPosPtr, *actorPosPtr;
#endif
