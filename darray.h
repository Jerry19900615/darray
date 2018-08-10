/********************************************************************
author: wujilei
date: 2017/05/29
 ********************************************************************/
#ifndef D_ARRAY
#define D_ARRAY


typedef enum darray_err_{
	DARR_ERROR_OK,
	DARR_ERROR_FAIL,
	DARR_ERROR_END
}darray_err_t;


struct darray_t_;

typedef struct darray_t_ darray_t;

/*
 *name: darray_init
 *description: 初始化空的动态数组
 *param:
 *return:
 *	成功返回空的动态数组指针，失败返回NULL	
 */
darray_t *darray_init();

/*
 *name: darray_destroy
 *description: 销毁动态数组
 *param:
 *	darray_t *parr    //the array to free
 *reuturn:
 *	
 */
void darray_free(darray_t *parr);

/*
 *name: darray_free_ex
 *description: 销毁动态数组
 *param:
 *	darray_t *parr        //动态数组
 *	void(*pfunc)(void*)  //元素销毁函数
 *return:
 */
void darray_free_ex(darray_t *parr, void(*pfunc)(void*));

/*
 *name: darray_append
 *description: 增加元素到数组尾部
 *param:
 *	darray_t *parr,     // the array to append data to
 *	void *data          // the data to be appended 元素内存需要调用者申请，由darray_free_ex负责释放
 *return:
 *  成功返回 DARR_ERROR_OK， 失败返回DARR_ERROR_FAIL
 */
int darray_append(darray_t *parr, void *data);  


/*
 *name: darray_insert
 *description: 插入元素
 *param:
 *	darray_t *parr,     // the array to append data to
 *	int index,          // the index to insert
 *	void *data          // the data to be appended 元素内存需要调用者申请，由darray_free_ex负责释放
 *return:
 *  成功返回 DARR_ERROR_OK， 失败返回DARR_ERROR_FAIL
 */
int darray_insert(darray_t *parr, int index, void *data);

/*
 *name: darray_delete
 *description: 删除动态数组指定项
 *param:
 *	darray_t *parr  //要操作的数组
 *	int index       //索引
 *return:
 *  删除成功，返回指向元素的指针，需要调用者释放元素内存
 */
void *darray_delete(darray_t *parr, int index);

/*
 *name: darray_get_element
 *description: 获取指定索引的元素
 *param:
 *	darray_t *parr  //要操作的数组
 *	int index       //索引
 *return:
 *  返回指向该元素的指针, 失败返回NULL
 */
void *darray_get_element(darray_t *parr, int index);

/*
 *name: darray_count
 *description: 获取动态数组的元素个数
 *param:
 *	darray_t *parr  //要操作的数组
 *return:
 *  返回动态数组中元素的个数
 */
int darray_count(darray_t *parr);


#endif

