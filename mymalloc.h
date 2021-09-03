
void *mymalloc(int size);

void myfree(void *ptr);

typedef struct {
  int size;
  int magic;
} header_t;


typedef struct __node_t {
  int size;
  struct __node_t *next;
} node_t;

void findspace(int size, void *ptr, node_t *node);
