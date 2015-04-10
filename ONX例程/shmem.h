#include <pthread.h>

#define MAX_TEXT_LEN	100

/* 共享内存的机构体，用于保存需要存储的信息 */

typedef struct{
	/* 构建一个互斥信号，用于控制shmem */
	pthread_mutex_t myshemmutex;
	/* 保存的内容 */
	char	text[MAX_TEXT_LEN+1];
	/* 需要添加的内容 。。。。。。*/
} shmem_t;