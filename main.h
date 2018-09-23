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
//#include "hash.c"

struct list_item{
	struct list_elem elem;
	int data;
};

struct hash_item{
	struct hash_elem elem;
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
typedef struct _list_h{
	char name[100];
	struct hash *hash;
}list_h;


list_ll llList[10];
list_bm bmList[10];
list_h hList[10];
int llList_num = 0, bmList_num = 0, hList_num = 0;


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

struct hash_item *new_hashitem(){
	struct hash_item *tmp;
	tmp = (struct hash_item*)malloc(sizeof(struct hash_item));
	return tmp;
}


struct hash_elem *newhash_elem(){
	struct hash_elem *tmp;
	tmp = (struct hash_elem*)malloc(sizeof(struct hash_elem));
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

void list_shuffle(struct list *list){
	int i, tmp;
	int randnum;
	struct list_elem *e1, *e2;
	struct list_item *f1, *f2;

	srand(time(NULL));

	for(i=0; i<100 ; i++){
		for(e1 = list_begin(list);
				list_next(e1) != list_end(list);
				e1=list_next(e1)){
			randnum = rand()%2;
			e2 = list_next(e1);

			f1 = list_entry(e1, struct list_item, elem);
			f2 = list_entry(e2, struct list_item, elem);

			if(randnum){
				tmp = f1->data;
				f1->data = f2->data;
				f2->data = tmp;
			}
		}
	}
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

unsigned hash_int_2(int i){
	int hash_num;
	hash_num = i%4;

	return hash_num;
}

int h_index_num(char *list_name){
	int i;

	for(i=0; i<hList_num ; i++){
		if(!strcmp(hList[i].name, list_name))
			return i;
	}
}
unsigned hash_hash_function(const struct hash_elem *e, void *aux){
	struct hash_item *f = hash_entry(e,struct hash_item,elem);

	return hash_int(f->data);
}

bool hash_less_function(const struct hash_elem *a, const struct hash_elem *b, void *aux){
    struct hash_item *c = hash_entry(a,struct hash_item,elem);
    struct hash_item *d = hash_entry(b,struct hash_item,elem);

	if(c->data < d->data)
		return true;
	else
		return false;
}

void hash_square(struct hash_elem *e, void *aux) {
	struct hash_item *f;
	int tmp;
		
	f = hash_entry(e,struct hash_item,elem);
	tmp = f->data;

	f->data *= tmp;
}

void hash_triple(struct hash_elem *e, void *aux) {
	struct hash_item *f;
	int tmp;
		
	f = hash_entry(e,struct hash_item,elem);
	tmp = f->data;

	f->data = tmp*tmp*tmp;
}


int i, j, flag;
size_t bit_cnt_tmp;
