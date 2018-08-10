#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "darray.h"



struct darray_t_{
	unsigned int capacity;  //容量
	unsigned int curr;      //当前元素个数
	void **data;   //元素指针数组
//多线程支持，加个锁
};

#define AUTO_EXPEND_SIZE 20

//自增长函数
static int autoexpending(darray_t *parr)
{
	void **pbuf;
	if(parr->curr >= parr->capacity){
		unsigned int new_capacity= parr->capacity + AUTO_EXPEND_SIZE;
		pbuf = (void **) malloc(sizeof(void *) * new_capacity);
		if(!pbuf) return DARR_ERROR_FAIL;
		/*拷贝*/
		memcpy((void*)pbuf, parr->data, parr->capacity);
		free(parr->data);
		parr->data = pbuf;
		parr->capacity = new_capacity;
	}
	return DARR_ERROR_OK;
}


darray_t *darray_init(){
	darray_t *parr;
	parr = (darray_t*)malloc(sizeof(darray_t));
	if(parr){ 
		parr->capacity = 0;
		parr->curr = 0;
		parr->data = 0;
	}
	return parr;
}


void darray_free(darray_t *parr){
	int i = 0;
	if(!parr){
		return ;
	}
	darray_free_ex(parr, NULL);
}


void darray_free_ex(darray_t *parr, void(*pfunc)(void*))
{
	int i;
	if(!parr) return;
	if(!pfunc) pfunc = free;
	if(parr->data) {
		for(i = 0; i < parr->curr; i ++)
		{
			pfunc(*(parr->data + i * sizeof(void *)));
		}
		free(parr->data);
	}
	free(parr);
}

int darray_append(darray_t *parr, void *data){
	void **dst;
	assert(parr != NULL);
	if(DARR_ERROR_OK != autoexpending(parr))
	{
		return DARR_ERROR_FAIL;
	}
	dst = (parr->data + parr->curr * sizeof(void *));
	*dst = data;
	++ parr->curr;
	return DARR_ERROR_OK;
}

int darray_insert(darray_t *parr, int index, void *data){
	int i;
	if(!parr || index < 0 || index >= parr->curr)
	{
		return DARR_ERROR_FAIL;
	}
	
	if(DARR_ERROR_OK != autoexpending(parr)){
		return DARR_ERROR_FAIL;
	}

	//从指定index开始，元素往后移动一个
	i = parr->curr - 1;	
	for(; i >= index; --i) {
		*(parr->data + (i + 1)*sizeof(void *)) = *(parr->data + i * sizeof(void *));
	}

	*(parr->data + index * sizeof(void *)) = data;
	parr->curr ++;
	return DARR_ERROR_OK;
}

void *darray_delete(darray_t *parr, int index){
	int i;
	void *data;

	if(!parr || index < 0 || index >= parr->curr){
		return NULL;
	}

	data = *(parr->data + index * sizeof(void*));
	//删除指定位置的元素, 后续元素前移
	for(i = index + 1; i < parr->curr; i ++)
	{
		*(parr->data + (i-1) * sizeof(void *)) = *(parr->data + i * sizeof(void *));
	}
	parr->curr --;
	return data;
}

void *darray_get_element(darray_t *parr, int index){
	if(!parr || index < 0 || index >= parr->curr)
	{
		return NULL;
	}

	return *(parr->data + index * sizeof(void*));
}

int darray_count(darray_t *parr){
	if(!parr) return 0;
	return parr->curr;
}


