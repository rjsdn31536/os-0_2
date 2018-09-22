#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>

#include "list.h"
#include "hash.h"
#include "bitmap.h"

//#include "list.c"
//#include "bitmap.c"

struct list_item{
	struct list_elem elem;
	int data;
};

typedef struct _list_ll{
	char name[100];
	struct list *link;
}list_ll;
typedef struct _list_bm{
	char name[100];
	struct bitmap *bm;
}list_bm;

list_ll llList[10];
list_bm bmList[10];
int llList_num = 0, bmList_num = 0;


// Create new linked_list 
struct list *newlist(){
	struct list *tmp;
	tmp = (struct list*)malloc(sizeof(struct list));
	return tmp;
}

// Create new linked_list's item
struct list_item *newitem(){
	struct list_item *tmp;
	tmp = (struct list_item*)malloc(sizeof(struct list_item));
	return tmp;
}

int ll_index_num(char *list_name){
	int i;

	for(i=0; i<llList_num ; i++){
		if(!strcmp(llList[i].name, list_name))
			return i;
	}
}

bool less(const struct list_elem *a, const struct list_elem *b, void *aux)
{
	struct list_item *a_data, *b_data;

	a_data=list_entry(a, struct list_item, elem);
	b_data=list_entry(b, struct list_item, elem);
	if(a_data->data < b_data->data)
		return true;
	else
		return false;
}

void list_swap(int ll_index, int a, int b){
	int i, tmp;
	struct list_elem *e1, *e2;
	struct list_item *f1, *f2;

	e1 = list_begin(llList[ll_index].link);
	e2 = list_begin(llList[ll_index].link);

	for(i=0; i<a; i++)
		e1=list_next(e1);
	for(i=0; i<b; i++)
		e2=list_next(e2);
	f1 = list_entry(e1, struct list_item, elem);
	f2 = list_entry(e2, struct list_item, elem);
	tmp = f1->data;
	f1->data = f2->data;
	f2->data = tmp;
}

int bm_index_num(char *list_name){
	int i;

	for(i=0; i<bmList_num ; i++){
		if(!strcmp(bmList[i].name, list_name))
			return i;
	}
}

struct bitmap *bitmap_expand(struct bitmap *bitmap, int size){
	size_t bit_cnt;
	struct bitmap *tmp;
	int i;

	bit_cnt = bitmap_size(bitmap);
	tmp = bitmap_create(bit_cnt + size);

	for(i=0 ; i<bit_cnt ; i++)
		if(bitmap_test(bitmap, i))
			bitmap_mark(tmp, i);

	return tmp;
}

int i, j, flag;
size_t bit_cnt_tmp;
