/*	
 * shm.h
 *  Created on: 2015/4/10
 * 	    Author: maxtom0
 * Description: 共享内存头文件
 *
 */
 
 #ifndef SHM_H_
 #define SHM_H_
 
 #include "global.h"
 
 /* 共享内存数据块 */
 typedef struct{
	 pthread_rwlock_t rw_lock;
	 /* 共享数据 */
	 double a;
	 float  b;
	 int    c;
	 
	 char str[100];
 }shared_memory;
 
/**@错误返回
*@mem_name[输入]：共享内存的名称；
*@shared_mem_fd[输出]：共享内存对应的文件指针；
*@shared_mem_ptr[输出]：共享内存块指针；
*@返回 int；
*/
 void ErrReport(void);
 
/**@共享内存初始化
*@mem_name[输入]：共享内存的名称；
*@shared_mem_fd[输出]：共享内存对应的文件指针；
*@shared_mem_ptr[输出]：共享内存块指针；
*@返回 int；
*/
 int InitShmRWLock(char* mem_name, 
					int* shared_mem_fd, 
					shared_memory** shared_mem_ptr);
 
 #endif