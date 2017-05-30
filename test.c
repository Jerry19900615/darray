#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "darray.h"

struct aaaa{
	int a;
	short b;
	char *name;
};

void free_aaaa(void *ps){
	struct aaaa *p = (struct aaaa*)ps;
	if(p->name) free(p->name);
	free(ps);
}

int main(int argc, char **argv){

	struct aaaa *s;	
	struct aaaa *pout;
	int i;

	darray_t *array;

	array = darray_init();
	if(array == NULL)
	{
		printf("error\n");
		return 1;
	}

	s = (struct aaaa*)malloc(sizeof(struct aaaa));
	s->a = 10;
	s->b = 11;
	s->name = strdup("hello");

	darray_append(array, s);

	s = (struct aaaa*)malloc(sizeof(struct aaaa));
	s->a = 30;
	s->b = 40;
	s->name = strdup("abc");
	darray_append(array, s);


	for(i = 0; i < darray_count(array); i ++)
	{
		pout = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n", pout->a, pout->b, pout->name);
	}
	printf("\n");

	s = (struct aaaa*) malloc(sizeof(struct aaaa));
	s->a = 52;
	s->b = 44;
	s->name = strdup("world");
	darray_insert(array, 1, s);

	for(i = 0; i < darray_count(array); i ++)
	{
		pout = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n", pout->a, pout->b, pout->name);
	}
	printf("\n");
	
	pout = darray_delete(array, 2);

	printf("a = %d, b = %d, name= %s\n\n", pout->a, pout->b, pout->name);

	free_aaaa(pout);

	for(i = 0; i < darray_count(array); i ++)
	{
		pout = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n", pout->a, pout->b, pout->name);
	}

	printf("\n");
	pout = darray_delete(array, 0);
	printf("a = %d, b = %d, name= %s\n\n", pout->a, pout->b, pout->name);
	free_aaaa(pout);
	for(i = 0; i < darray_count(array); i ++)
	{
		pout = darray_get_element(array, i);
		printf("a = %d, b = %d, name= %s\n", pout->a, pout->b, pout->name);
	}
	
	darray_free_ex(array, free_aaaa);

	return 0;
}
