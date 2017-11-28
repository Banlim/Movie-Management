MOVIE * movie = (MOVIE*)malloc(sizeof(MOVIE));
movie->actors = (DATA_AT*)malloc(sizeof(DATA_AT));
DATA_AT * m_atptr = movie->actors;

DIR_ACTOR * director = (DIR_ACTOR*)malloc(sizeof(DIR_ACTOR));
director->best_movies = (DATA_AT*)malloc(sizeof(DATA_AT));
DATA_AT * d_datptr = director->best_movies;

DIR_ACTOR * actor = (DIR_ACTOR*)malloc(sizeof(DIR_ACTOR));
actor->best_movies = (DATA_AT*)malloc(sizeof(DATA_AT));
DATA_AT * a_datptr = actor->best_movies;
