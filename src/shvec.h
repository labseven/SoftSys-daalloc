#define MAX_SHVECTS 100
#define GROWTH_FACTOR 2

int shvec_create();
int shvec_set(int id, int index);
int shvec_get(int id, int index);
int shvec_free(int id);