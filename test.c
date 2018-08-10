#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "darray.h"

typedef struct T{
	int a;
	short b;
	char *name;
}T;

T *new_T(){
	T *new_t;
	new_t = (T*)malloc(sizeof(T));
	return new_t;
}

void free_T(T *pt){
	if(pt){
		if(pt->name) free(pt->name);
		free(pt);
	}
}

int main(int argc, char **argv){

	T *s;	
	int i;

	darray_t *array;
	printf("Create empty array.\n");
	array = darray_init();
	if(array == NULL)
	{
		printf("error\n");
		return -1;
	}

	s = new_T();
	if(!s){
		printf("error\n");
		return -1;
	}
	s->a = 10;
	s->b = 11;
	s->name = strdup("hello");

	printf("append element name:%s.\n", s->name);
	darray_append(array, s);

	s = new_T();
	if(!s){
		printf("error\n");
		return -1;
	}
	s->a = 30;
	s->b = 40;
	s->name = strdup("abc");
	printf("append element name:%s.\n", s->name);
	darray_append(array, s);

	
	printf("\n\nNow elements in array are:\n");
	for(i = 0; i < darray_count(array); i ++)
	{
		s = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n",s->a, s->b, s->name);
	}
	printf("\n");

	s = new_T();
	if(!s){
		printf("error\n");
		return -1;
	}
	s->a = 52;
	s->b = 44;
	s->name = strdup("world");
	
	printf("insert element name:%s in index 1.\n", s->name);
	darray_insert(array, 1, s);


	printf("\n\nNow elements in array are:\n");
	for(i = 0; i < darray_count(array); i ++)
	{
		s = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n", s->a, s->b, s->name);
	}
	printf("\n");


	printf("delete element of index 2.\n");
	s = darray_delete(array, 2);


	free_T(s);

	printf("\n\nNow elements in array are:\n");
	for(i = 0; i < darray_count(array); i ++)
	{
		s = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n", s->a, s->b, s->name);
	}

	printf("\n");

	printf("delete element of index 0.\n");
	s = darray_delete(array, 0);
	free_T(s);

	printf("\n\nNow elements in array are:\n");
	for(i = 0; i < darray_count(array); i ++)
	{
		s = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n", s->a, s->b, s->name);
	}


	printf("free array\n");
	darray_free_ex(array, (void(*)(void*))free_T);

	return 0;
}
