/*	
 * shm.h
 *  Created on: 2015/4/10
 * 	    Author: maxtom0
 * Description: 共享内存头文件
 *
 */
 #include "shm.h"
 
/**@共享内存初始化
*@mem_name[输入]：共享内存的名称；
*@shared_mem_fd[输出]：共享内存对应的文件指针；
*@shared_mem_ptr[输出]：共享内存块指针；
*@返回 int；
*/
 void ErrReport(char* message)
 {
	 fprintf(stderr, "Error: %s error, at file: %s, function: %s, line: %d\n, system error info: %s;\n", 
					message,
					__FILE__, 
					__FUNCTION__, 
					__LINE__, 
					strerror(errno));
	return (-1);
 }
 
 
/**@共享内存初始化
*@mem_name[输入]：共享内存的名称；
*@shared_mem_fd[输出]：共享内存对应的文件指针；
*@shared_mem_ptr[输出]：共享内存块指针；
*@返回 int；
*/
 int InitShmRWLock(char* mem_name, 
					int* shared_mem_fd, 
					shared_memory** shared_mem_ptr)
{
	// 检测内存是否可用
	if(access(mem_name, F_OK)==0){
		
		// 是否存在
		*shared_mem_fd = shm_open(mem_name, O_RDWR, S_IRWXU);
		/* shm_open参数说明
		* O_RDWR: 可读写操作；
		* O_CREAT：如何共享内存存在，此无用；否侧根据当前的权限创建；
		* O_TRUNC：如果共享内存存在且O_RDWR，则可以进行
		*/
		if(*shared_mem_fd == -1) ErrReport("open shared memory");
		
		// 分配共享内存
		*shared_mem_ptr = mmap(0, sizeof(shared_memory),
								PROT_READ|PROT_WRITE, 
								MAP_SHARED,
								*shared_mem_fd,
								0);
								
		if(MAP_FAILED == *shared_mem_ptr) ErrReport();
	}
	else { // 共享内存不存在，打开文件，初始化读写锁
		
		// 打开共享文件
		*shared_mem_fd = shm_open(mem_name, O_RDWR|O_CREAT|O_TRUNC,
								  S_IRWXU);
		
		if(*shared_mem_fd == -1) ErrReport("map shared memory");
		
		// 分配共享内存
		*shared_mem_ptr = mmap(0, sizeof(shared_memory),
								PROT_READ|PROT_WRITE,
								MAP_SHARED,
								*shared_mem_fd,
								0);
		
		// 初始化读写锁
		pthread_rwlockattr_t attr;
		if(EOK != pthread_rwlockattr_init(&attr)) 
			ErrReport("initialze relock attribute");
		if(EOK != pthread_rwlockattr_setpshared(&attr, PTHREAD_PROCESS_SHARED))
			ErrReport("set rwlock shared property");
		if(EOK != pthread_rwlock_init(&((*shared_mem_ptr)->rw_lock),&attr))
			ErrReport("initialize rwlock");
	}
}