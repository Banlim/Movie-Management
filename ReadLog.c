#include "head.h"

extern int m_srl, d_srl, a_srl; //마지막 시리얼 넘버 저장 전역 변수

char * read(FILE * fp, Type type){
  char * str = (char*)malloc(100);
  if(type == t_str){
    fscanf(fp, "%[ a-zA-Z=?;]:", str);
  }
  else if(type == t_data_at){
    fscanf(fp, "%[ a-zA-Z0-9.?;]", str);
  }
  else if(type == t_str_all){
    fscanf(fp, "%[ a-zA-Z0-9=?;]:", str);
  }
  str = changeColon(str, t_read);
  str = (char*)realloc(str, sizeof(char)*(strlen(str)+1));
  return str;
}

MOVIE * read_movie_log(MOVIE * mptr){
  FILE * fp = fopen("movie_log.txt", "rt");
  int tmp_num, up_cnt;
  char * tmp_tag, * tmp_str;
  MOVIE * p_mptr = NULL, * u_mptr;
  MOVIE * c_mptr = mptr;
  DATA_AT * c_atptr = mptr->actors;
  while(1){
    tmp_tag=read(fp, t_str);
    fscanf(fp,"%d:",&tmp_num);
    if(strcmp(tmp_tag, "update") == 0){
      u_mptr = mptr;
      while(u_mptr->srl_num < tmp_num){
        u_mptr = u_mptr->next;
      }
      up_cnt = 3;
      while(up_cnt <= 8){
        tmp_str = read(fp, t_str_all);
        switch(up_cnt){
          case 3:
            if(strcmp(tmp_str, "=") != 0)
              u_mptr->title = tmp_str;
            break;
          case 4:
            if(strcmp(tmp_str, "=") != 0)
              u_mptr->genre = tmp_str;
            break;
          case 5:
            if(strcmp(tmp_str, "=") != 0){
              u_mptr->director->data_at = tmp_str;
              u_mptr->director->next = NULL;
            }
            break;
          case 6:
            if(strcmp(tmp_str, "=") != 0)
              u_mptr->year = atoi(tmp_str);
            break;
          case 7:
            if(strcmp(tmp_str, "=") != 0)
              u_mptr->runtime = atoi(tmp_str);
            break;
          case 8:
            if(strcmp(tmp_str, "=") != 0){
              c_atptr = u_mptr->actors;
              fseek(fp,-strlen(tmp_str), SEEK_CUR);
              while(1){
                c_atptr->data_at = read(fp, t_data_at);
                if(fgetc(fp) == '\n'){
                  c_atptr->next = NULL;
                  break;
                }
                c_atptr->next = (DATA_AT*)malloc(sizeof(DATA_AT));
                c_atptr = c_atptr->next;
              }
            }
            else
              fgetc(fp);
            break;
        }
        up_cnt++;
      }
    }
    else if(strcmp(tmp_tag, "delete") == 0){
      if(tmp_num == p_mptr->srl_num){
        u_mptr = mptr;
        while(u_mptr->next->srl_num < tmp_num){
          u_mptr = u_mptr->next;
        }
        p_mptr = u_mptr;
      }
      mptr = delete_m(fp, mptr, tmp_num);
    }
    else{ //add일때
      if(p_mptr!=NULL){
        c_mptr = (MOVIE*)malloc(sizeof(MOVIE)); //할당
        p_mptr->next = c_mptr; // 연결
      }
      c_mptr->actors = (DATA_AT*)malloc(sizeof(DATA_AT)); //할당
      c_mptr->tag=tmp_tag;
      c_mptr->srl_num=tmp_num;
      c_mptr->title=read(fp, t_str);
      c_mptr->genre=read(fp, t_str);
      c_mptr->director=(DATA_AT*)malloc(sizeof(DATA_AT));
      c_mptr->director->data_at=read(fp, t_str);
      c_mptr->director->next=NULL;
      fscanf(fp,"%d:",&tmp_num);
      c_mptr->year=tmp_num;
      fscanf(fp,"%d:",&tmp_num);
      c_mptr->runtime=tmp_num;
      c_atptr = c_mptr->actors;
      while(1){
        c_atptr->data_at = read(fp, t_data_at);
        if(fgetc(fp) == '\n'){
          c_atptr->next = NULL;
          break;
        }
        c_atptr->next = (DATA_AT*)malloc(sizeof(DATA_AT));
        c_atptr = c_atptr->next;
      }
      m_srl = c_mptr->srl_num;
      p_mptr = c_mptr;
    }

    if(fgetc(fp) == EOF){
      c_mptr->next = NULL;
      break;
    }
    else
      fseek(fp, -1, SEEK_CUR);
  }
  return mptr;
  fclose(fp);
}

MOVIE * delete_m(FILE * fp, MOVIE * mptr, int tmp_num){
  MOVIE * u_mptr;
  if(tmp_num == mptr->srl_num){
    mptr = mptr->next;
    u_mptr = mptr;
  }
  else{
    u_mptr = mptr;
    while(u_mptr->next->srl_num < tmp_num)
      u_mptr = u_mptr->next;
    u_mptr->next = u_mptr->next->next;
  }
  fseek(fp, 7, SEEK_CUR);
  return mptr;
}

DIR_ACTOR * read_da_log(DIR_ACTOR * daptr, Type type){
  FILE * fp;
  if (type == t_director)
    fp = fopen("director_log.txt", "rt");
  else if (type == t_actor)
    fp = fopen("actor_log.txt", "rt");
  int tmp_num, up_cnt;
  char * tmp_tag, * tmp_str;
  DIR_ACTOR * p_daptr = NULL, * u_daptr;
  DIR_ACTOR * c_daptr = daptr;
  DATA_AT * c_datptr = daptr->best_movies;
  while(1){
    tmp_tag=read(fp, t_str);
    fscanf(fp,"%d:",&tmp_num);
    if(strcmp(tmp_tag, "update") == 0){
      u_daptr = daptr;
      while(u_daptr->srl_num < tmp_num){
        u_daptr = u_daptr->next;
      }
      up_cnt = 3;
      while(up_cnt <= 6){
        tmp_str = read(fp, t_str_all);
        switch(up_cnt){
          case 3:
            if(strcmp(tmp_str, "=") != 0)
              u_daptr->name = tmp_str;
            break;
          case 4:
            if(strcmp(tmp_str, "=") != 0)
              u_daptr->sex = tmp_str;
            break;
          case 5:
            if(strcmp(tmp_str, "=") != 0){
              u_daptr->birth = atoi(tmp_str);
            }
            break;
          case 6:
            if(strcmp(tmp_str, "=") != 0){
              c_datptr = u_daptr->best_movies;
              fseek(fp,-strlen(tmp_str), SEEK_CUR);
              while(1){
                c_datptr->data_at = read(fp, t_data_at);
                if(fgetc(fp) == '\n'){
                  c_datptr->next = NULL;
                  break;
                }
                c_datptr->next = (DATA_AT*)malloc(sizeof(DATA_AT));
                c_datptr = c_datptr->next;
              }
            }
            else
              fgetc(fp);
            break;
        }
        up_cnt++;
      }
    }
    else if(strcmp(tmp_tag, "delete") == 0){
      if(tmp_num == p_daptr->srl_num){
        u_daptr = daptr;
        while(u_daptr->next->srl_num < tmp_num){
          u_daptr = u_daptr->next;
        }
        p_daptr = u_daptr;
      }
      daptr = delete_da(fp, daptr, tmp_num);
    }
    else{ //add일때
      if(p_daptr!=NULL){
        c_daptr = (DIR_ACTOR*)malloc(sizeof(DIR_ACTOR)); //할당
        p_daptr->next = c_daptr; // 연결
      }
      c_daptr->best_movies = (DATA_AT*)malloc(sizeof(DATA_AT)); //할당
      c_daptr->tag=tmp_tag;
      c_daptr->srl_num=tmp_num;
      c_daptr->name=read(fp, t_str);
      c_daptr->sex=read(fp, t_str);
      fscanf(fp,"%d:",&tmp_num);
      c_daptr->birth=tmp_num;
      c_datptr = c_daptr->best_movies;
      while(1){
        c_datptr->data_at = read(fp, t_data_at);
        if(fgetc(fp) == '\n'){
          c_datptr->next = NULL;
          break;
        }
        c_datptr->next = (DATA_AT*)malloc(sizeof(DATA_AT));
        c_datptr = c_datptr->next;
      }
      if (type == t_director)
        d_srl = c_daptr->srl_num;
      else if (type == t_actor)
        a_srl = c_daptr->srl_num;
      p_daptr = c_daptr;
    }

    if(fgetc(fp) == EOF){
      c_daptr->next = NULL;
      break;
    }
    else
      fseek(fp, -1, SEEK_CUR);
  }
  return daptr;
  fclose(fp);
}

DIR_ACTOR * delete_da(FILE * fp, DIR_ACTOR * daptr, int tmp_num){
  DIR_ACTOR * u_daptr;
  if(tmp_num == daptr->srl_num){
    daptr = daptr->next;
    u_daptr = daptr;
  }
  else{
    u_daptr = daptr;
    while(u_daptr->next->srl_num < tmp_num)
      u_daptr = u_daptr->next;
    u_daptr->next = u_daptr->next->next;
  }
  fseek(fp, 5, SEEK_CUR); /////////////// 확인 바람
  return daptr;
}
