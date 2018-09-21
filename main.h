#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>
#include<time.h>

#include "list.c"
#include "list.h"
#include "hash.h"
#include "bitmap.h"


struct list_item{
	struct list_elem elem;
	int data;
};

typedef struct _list_ll{
	char name[100];
	struct list *link;
}list_ll;

list_ll llList[10];
int llList_num = 0;


struct list *newlist(){
	struct list *tmp;
	tmp = (struct list*)malloc(sizeof(struct list));
	return tmp;
}

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


int i, j, flag;
