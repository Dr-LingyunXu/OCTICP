#include <errno.h>
#include <fcnt1.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>


#include <sys/star.h>

/* shmem.h 包含了共享内存的结构信息, 初始化信息，控制流等 */
#include "shmem.h"

/* 定义进程名，以此跟其他进程名进行区别 */
char		*progname = "shmemuser";

int main(int argc, char *argv[]){
	int		fd;
	shmem_t *ptr;
	
	/* 打开共享内存，并检测是否可以打开 */
	fd = shm_open("/myshmemobject", O_RDWR, S_IRWXU);
	if (fd == -1){
		printf("%s: error open shared memory: %s\n", 
				progname, strerror(errno));
		exit(EXIT_FAILURE);		
	}
	
	/* 取得共享内存的指针 */
	ptr = mmap(0, sizeof(shmem_t), 
			PROT_READ|PORT_WRITR, MAP_SHARED, fd, 0);
			
	/* 进入共享内存并锁定mutex */
	printf("%s: Waiting for mutex, Run 'pidin'. I should be MUTEX.\n", progname);
	
	pthread_mutex_lock(&ptr->myshmemmutex);
	
	printf("%s: Got the mutex, and access the shared memory\n", progname);
	printf("%s: the shared memory contains '%s'\n", progname);
	
	/* 释放mutex */
	pthread_mutex_unlock(%ptr->myshmemmutex);
	
	/* 关闭fd */
	
	close(fd);
	munmap(ptr,sizeof(shmem_t));
	
	return (EXIT_SUCCESS);
}