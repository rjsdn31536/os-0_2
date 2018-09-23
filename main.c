#include "main.h"

int main(){
	char command[100], original_command[100];
	char *token;
	char seps[4] = "\t _"; 
	int del_index;
	int ll_index, ll_index2, value, index, index1, index2, max_num, min_num;
	int bm_index, h_index;

	while(1){
		fgets(command, sizeof(command), stdin); // get command

		command[strlen(command)-1] = '\0';
		strcpy(original_command, command); // token 시 자기 자신도 잘려나가기 때문에 원본 유지

		token = strtok(command, seps); // token(\t, 띄어쓰기, _로 앞부분 받아오기)

		if(token == NULL)
			continue;

		// CASE 0_1. quit
		else if(!strcmp(token, "quit"))
			break;

		// CASE 0_2. create
		else if(!strcmp(token, "create")){
			token = strtok(NULL, seps);

			// CASE 0_2_1. create list <list_name> - list 생성
			if(!strcmp(token, "list")){
				token = strtok(NULL, seps);
				llList[llList_num].link = newlist();
				strcpy(llList[llList_num].name, token);
				list_init(llList[llList_num].link);
				
				llList_num++;
			}
			
			// CASE 0_2_2. create hashtable <hashtable_name> - hashtable 생성
			else if(!strcmp(token, "hashtable")){
				// token : hashtable_name
				token = strtok(NULL, seps);
				strcpy(hList[hList_num].name, token);

				hList[hList_num].hash = (struct hash*)malloc(sizeof(struct hash));
				hash_init(hList[hList_num].hash, hash_hash_function, hash_less_function,NULL);
				
				hList_num++;
			}

			// CASE 0_2_3. create bitmap <bitmap_name> <bit_count> - bitmap 생성
			else if(!strcmp(token, "bitmap")){
				// token : bitmap_name
				token = strtok(NULL, seps);
				strcpy(bmList[bmList_num].name, token);
				
				// token : bit_count
				token = strtok(NULL, seps);
				sscanf(token, "%u", &bit_cnt_tmp);

				bmList[bmList_num].bm = bitmap_create(bit_cnt_tmp);

				bmList_num++;
			}
		}

		// CASE 0_3. delete <list_name|hashtable_name|bitmap_name> - 주어진 이름의 자료구조 삭제
		else if(!strcmp(token, "delete")){
			token = strtok(NULL, seps);
			flag = 0;
			
			// delete 하는 자료구조가 list인지 확인, list가 맞으면 flag = 1
			for(i = 0; i < llList_num; i++){
				if(!strcmp(token, llList[i].name)){
					flag = 1;
					del_index = i;
					break;
				}
			}
			// delete 하는 자료구조가 hash인지 확인, hash가 맞으면 flag = 2
			for(i = 0; i < hList_num; i++){
				if(!strcmp(token, hList[i].name)){
					flag = 2;
					del_index = i;
					break;
				}
			}
			// delete 하는 자료구조가 bitmap인지 확인, bitmap이 맞으면 flag = 3
			for(i = 0; i < bmList_num; i++){
				if(!strcmp(token, bmList[i].name)){
					flag = 3;
					del_index = i;
					break;
				}
			}


			// 자료구조가 list(flag == 1) 인 경우
			if(flag == 1){
				for(i=del_index; i<9; i++){
					llList[i] = llList[i+1];
				}
				llList_num--;
			}

			// 자료구조가 hash(flag == 2) 인 경우
			else if(flag == 2){
				//hash_destroy(hList[del_index].hash, NULL);

				for(i=del_index; i<9; i++){
					hList[i] = hList[i+1];
				}
				hList_num--;
			}

			// 자료구조가 bitmap(flag == 3) 인 경우
			else if(flag == 3){
				bitmap_destroy(bmList[del_index].bm);
				for(i=del_index; i<9; i++){
					bmList[i] = bmList[i+1];
				}
				bmList_num--;
			}

		}

		// CASE 0_4. dumpdata <list_name|hashtable_name|bitmap_name> - 주어진 이름의 자료구조 내용을 stdout에 출력
		else if(!strcmp(token, "dumpdata")){
			token = strtok(NULL, seps);
			flag = 0;
			
			// dumpdata 하는 자료구조가 list인지 확인, list가 맞으면 flag = 1
			for(i = 0; i < llList_num; i++){
				if(!strcmp(token, llList[i].name)){
					flag = 1;
					ll_index = i;
					break;
				}
			}

			// dumpdata 하는 자료구조가 bitmap인지 확인, dumpdata가 맞으면 flag = 3
			for(i = 0; i < bmList_num; i++){
				if(!strcmp(token, bmList[i].name)){
					flag = 3;
					bm_index = i;
					break;
				}
			}
			// dumpdata 하는 자료구조가 hash인지 확인, bitmap이 맞으면 flag = 2
			// 채워넣어야함
			for(i = 0; i < hList_num; i++){
				if(!strcmp(token, hList[i].name)){
					flag = 2;
					h_index = i;
					break;
				}
			}


			// 자료구조가 list(flag == 1) 인 경우
			if(flag == 1){
				struct list_elem *e;

				for(e = list_begin((llList[ll_index].link)) ;
					e!=list_end((llList[ll_index].link)) ;
					e=list_next(e)){
					struct list_item *f = list_entry(e, struct list_item, elem);
					printf("%d ",f->data);

					flag = 0;
				}
				if(flag == 0)
					printf("\n");
			}

			// 자료구조가 hash(flag == 2) 인 경우
			else if(flag == 2){
				struct hash_iterator i;

				hash_first(&i,hList[h_index].hash);    
				while(hash_next(&i)){
					struct hash_item *f= hash_entry(hash_cur(&i),struct hash_item,elem);
					printf("%d ",f->data);

					flag = 0;
				}
				if(flag == 0)
					printf("\n");
			}


			// 자료구조가 bitmap(flag == 3) 인 경우
			else if(flag == 3){
				for(i=0; i< bitmap_size(bmList[bm_index].bm);i++){
					if(bitmap_test(bmList[bm_index].bm,i) == true) printf("1");
					else printf("0");
				}
				printf("\n");
			}

		}


		// CASE 1. list
		else if(!strcmp(token, "list")){
			token = strtok(NULL, seps);

			// CASE 1_1. list_insert
			if(!strcmp(token, "insert")){
				token = strtok(NULL, seps);

				// CASE 1_1_1. list_insert_ordered <list_name> <value>
				if(!strcmp(token,"ordered")){
					// token : list name
					token = strtok(NULL, seps);
					ll_index = ll_index_num(token);

					// token : value
					token = strtok(NULL, seps);
					sscanf(token, "%d", &value);


					struct list_item *new_tmp;
					new_tmp = newitem();
					new_tmp->data = value;

					struct list_elem *e;
					for(e = list_begin((llList[ll_index].link)) ;
							e!=list_end((llList[ll_index].link)) ;
							e=list_next(e)){
						struct list_item *f = list_entry(e, struct list_item, elem);

						// value와 item의 data를 비교
						if(f->data > value){
							list_insert(e, &new_tmp->elem);
							break;
						}
						// 들어가야 하는 value가 가장 클 경우
						else if(list_next(e) == list_end(llList[ll_index].link)){
							list_insert(list_next(e), &new_tmp->elem);
							break;
						}
					}
				}

				// CASE 1_1_2. list_insert <list_name> <index> <value>
				else if(1){
					// token : list name
					ll_index = ll_index_num(token);

					// token : index
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index);

					// token : value
					token = strtok(NULL, seps);
					sscanf(token, "%d", &value);

					struct list_item *new_tmp;
					new_tmp = newitem();
					new_tmp->data = value;

					struct list_elem *e;
					e = list_begin((llList[ll_index].link));

					for(i=0; i<index; i++){
						e=list_next(e);
					}
					list_insert(e, &new_tmp->elem);
				}
			}

			// CASE 1_2. list_splice <list_name1> <index> <list_name2> <index1> <index2>
			else if(!strcmp(token, "splice")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);
				// token : index
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index);
				// token : list name2
				token = strtok(NULL, seps);
				ll_index2 = ll_index_num(token);
				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index1);
				// token : index2
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index2);

				struct list_elem *e1, *e2, *e3;
				e1 = list_begin((llList[ll_index].link));
				e2 = list_begin((llList[ll_index2].link));
				e3 = list_begin((llList[ll_index2].link));

				for(i=0; i<index; i++)
					e1=list_next(e1);
				for(i=0; i<index1; i++)
					e2=list_next(e2);
				for(i=0; i<index2; i++)
					e3=list_next(e3);

				list_splice(e1, e2, e3);
			}

			// CASE 1_3. list_push
			else if(!strcmp(token, "push")){
				token = strtok(NULL, seps);

				// CASE 1_3_1. list_push_front
				if(!strcmp(token, "front")){
					// token : list name
					token = strtok(NULL, seps);
					ll_index = ll_index_num(token);

					// token : value
					token = strtok(NULL, seps);
					sscanf(token, "%d", &value);

					struct list_item *new_tmp;
					new_tmp = newitem();
					new_tmp->data = value;
					
					list_push_front(llList[ll_index].link, &new_tmp->elem);
				}

				// CASE 1_3_2. list_push_back
				else if(!strcmp(token, "back")){
					// token : list name
					token = strtok(NULL, seps);
					ll_index = ll_index_num(token);

					// token : value
					token = strtok(NULL, seps);
					sscanf(token, "%d", &value);

					struct list_item *new_tmp;
					new_tmp = newitem();
					new_tmp->data = value;
					
					list_push_back(llList[ll_index].link, &new_tmp->elem);
				}
			}

			// CASE 1_4. list_remove <list_name> <index>
			else if(!strcmp(token, "remove")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				// token : index
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index);

				// end link를 e로 assign
				struct list_elem *e;
				e = list_begin((llList[ll_index].link));

				for(i=0 ; i<index ; i++)
					e=list_next(e);

				list_remove(e);

			}

			// CASE 1_5. list_pop
			else if(!strcmp(token, "pop")){
				token = strtok(NULL, seps);

				// CASE 1_5_1. list_pop_front <list_name>
				if(!strcmp(token, "front")){
					// token : list name
					token = strtok(NULL, seps);
					ll_index = ll_index_num(token);
					
					list_pop_front(llList[ll_index].link);
				}

				// CASE 1_5_2. list_pop_back <list_name>
				else if(!strcmp(token, "back")){
					// token : list name
					token = strtok(NULL, seps);
					ll_index = ll_index_num(token);
					
					list_pop_back(llList[ll_index].link);
				}
			}

			// CASE 1_6. list_front <list_name>
			else if(!strcmp(token, "front")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				// 처음의 link를 e로 assign
				struct list_elem *e;
				e = list_begin((llList[ll_index].link));
			
				// f는 e의 data
				struct list_item *f = list_entry(e, struct list_item, elem);
				printf("%d\n",f->data);
			}

			// CASE 1_7. list_back
			else if(!strcmp(token, "back")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				// end link를 e로 assign
				struct list_elem *e;
				e = list_end(llList[ll_index].link);

				e = list_prev(e);
				struct list_item *f = list_entry(e, struct list_item, elem);
				printf("%d\n",f->data);	
			}

			// CASE 1_8. list_size <list_name>
			else if(!strcmp(token, "size")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				// i is list_size
				i = list_size(llList[ll_index].link);
				printf("%d\n", i);
			}

			// CASE 1_9. list_empty <list_name>
			else if(!strcmp(token, "empty")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);
				
				bool empty;
				empty = list_empty(llList[ll_index].link);
				if(empty)
					printf("true\n");
				else
					printf("false\n");
			}

			// CASE 1_10. list_reverse <list_name>
			else if(!strcmp(token, "reverse")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				list_reverse(llList[ll_index].link);
			}

			// CASE 1_11. list_sort <list_name>
			else if(!strcmp(token, "sort")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				list_sort(llList[ll_index].link, less, NULL);
			}

			// CASE 1_12. list_unique <list_name1> <list_name2>
			else if(!strcmp(token, "unique")){
				// token : list name1
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				// token : list name2
				token = strtok(NULL, seps);

				if(token){
					ll_index2 = ll_index_num(token);
					list_unique(llList[ll_index].link, llList[ll_index2].link,less,NULL);

				}
				else
					list_unique(llList[ll_index].link, NULL ,less,NULL);
			}

			// CASE 1_13. list_max <list_name>
			else if(!strcmp(token, "max")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				struct list_elem *e;

				e = list_max(llList[ll_index].link, less, NULL);
				struct list_item *f = list_entry(e, struct list_item, elem);
				printf("%d\n",f->data);
			}

			// CASE 1_14. list_min <list_name>
			else if(!strcmp(token, "min")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				struct list_elem *e;

				e = list_min(llList[ll_index].link, less, NULL);
				struct list_item *f = list_entry(e, struct list_item, elem);
				printf("%d\n",f->data);
			}

			// CASE 1_15. list_swap <list_name> <index1> <index2>
			else if(!strcmp(token, "swap")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);

				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index1);

				// token : index2
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index2); 

				list_swap(ll_index, index1, index2);
			}
			// CASE 1_16. list_shuffle <list_name>
			else if(!strcmp(token, "shuffle")){
				// token : list name
				token = strtok(NULL, seps);
				ll_index = ll_index_num(token);
				list_shuffle(llList[ll_index].link);
			}
		}

		// CASE 2. hash
		else if(!strcmp(token, "hash")){
			token = strtok(NULL, seps);

			// CASE 2_1. hash_insert <hashtable_name> <value>
			if(!strcmp(token, "insert")){
				// token : hashtable name
				token = strtok(NULL, seps);
				h_index = h_index_num(token);

				// token : value
				token = strtok(NULL, seps);
				sscanf(token, "%d", &value);

				struct hash_elem *e;
				e = newhash_elem();

				struct hash_item *f;
				f = hash_entry(e, struct hash_item, elem);
				f->data = value;

				hash_insert(hList[h_index].hash, e);
			}

			// CASE 2_2. hash_replace <hashtable_name> <value>
			if(!strcmp(token, "replace")){
				// token : hashtable name
				token = strtok(NULL, seps);
				h_index = h_index_num(token);

				// token : value
				token = strtok(NULL, seps);
				sscanf(token, "%d", &value);

				struct hash_elem *e;
				e = newhash_elem();

				struct hash_item *f;
				f = hash_entry(e, struct hash_item, elem);
				f->data = value;

				hash_replace(hList[h_index].hash, e);
			}

			// CASE 2_3. hash_find <hashtable_name> <value>
			if(!strcmp(token, "find")){
				// token : hashtable name
				token = strtok(NULL, seps);
				h_index = h_index_num(token);

				// token : value
				token = strtok(NULL, seps);
				sscanf(token, "%d", &value);

				struct hash_elem *e, *return_e;
				e = newhash_elem();

				struct hash_item *f;
				f = hash_entry(e, struct hash_item, elem);
				f->data = value;

				return_e = hash_find(hList[h_index].hash, e);

				if(return_e)
					printf("%d\n",value);
			}

			// CASE 2_4. hash_delete <hashtable_name> <value>
			if(!strcmp(token, "delete")){
				// token : hashtable name
				token = strtok(NULL, seps);
				h_index = h_index_num(token);

				// token : value
				token = strtok(NULL, seps);
				sscanf(token, "%d", &value);

				struct hash_elem *e;
				e = newhash_elem();

				struct hash_item *f;
				f = hash_entry(e, struct hash_item, elem);
				f->data = value;

				hash_delete(hList[h_index].hash, e);
			}

			// CASE 2_5. hash_clear <hashtable_name>
			if(!strcmp(token, "clear")){
				// token : hashtable name
				token = strtok(NULL, seps);
				h_index = h_index_num(token);

				hash_clear(hList[h_index].hash, NULL);
			}

			// CASE 2_6. hash_size <hashtable_name>
			if(!strcmp(token, "size")){
				token = strtok(NULL, seps);
				h_index = h_index_num(token);

				size_t size;

				size = hash_size(hList[h_index].hash);

				printf("%d\n", size);
			}

			// CASE 2_7. hash_empty <hashtable_name>
			if(!strcmp(token, "empty")){
				token = strtok(NULL, seps);
				h_index = h_index_num(token);
				
				bool tf;

				tf = hash_empty(hList[h_index].hash);

				if(tf)
					printf("true\n");
				else
					printf("false\n");
			}

			// CASE 2_8. hash_apply <hashtable_name> <func>
			if(!strcmp(token, "apply")){
				token = strtok(NULL, seps);
				h_index = h_index_num(token);

				// token : func
				token = strtok(NULL, seps);

				if(!strcmp(token, "square")){
					hash_apply(hList[h_index].hash, &hash_square);
				}
				else if(!strcmp(token, "triple")){
					hash_apply(hList[h_index].hash, &hash_triple);
				}
			}
		}

		// CASE 3. bitmap
		else if(!strcmp(token, "bitmap")){
			token = strtok(NULL, seps);

			// CASE 3_1. bitmap_size <bitmap_name>
			if(!strcmp(token, "size")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);
				
				bit_cnt_tmp = bitmap_size(bmList[bm_index].bm);
				printf("%u\n", bitmap_size(bmList[bm_index].bm));
			}

			// CASE 3_2. bitmap_set
			else if(!strcmp(token, "set")){
				token = strtok(NULL, seps);

				// CASE 3_7_1. bitmap_size_all <bitmap_name> <value(boolean)>
				if(!strcmp(token, "all")){
					// token : bitmap name
					token = strtok(NULL, seps);
					bm_index = bm_index_num(token);

					// token : value
					token = strtok(NULL, seps);
					if(!strcmp(token, "true"))
						value = 1;
					else
						value = 0;

					bitmap_set_all(bmList[bm_index].bm, value);
				}

				// CASE 3_7_2. bitmap_size_multiple <bitmap_name> <index1> <index2> <value(boolean)>
				else if(!strcmp(token, "multiple")){
					// token : bitmap name
					token = strtok(NULL, seps);
					bm_index = bm_index_num(token);

					// token : index1
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index); 

					// token : index2
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index1); 

					// token : value
					token = strtok(NULL, seps);
					if(!strcmp(token, "true"))
						value = 1;
					else
						value = 0;
					bitmap_set_multiple(bmList[bm_index].bm, index, index1, value);
				}

				// CASE 3_7_3. bitmap_set <bitmap_name> <index> <value(boolean)>
				else{
					// token : bitmap name
					bm_index = bm_index_num(token);

					// token : index
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index); 

					// token : value
					token = strtok(NULL, seps);
					if(!strcmp(token, "true"))
						value = 1;
					else
						value = 0;

					bit_cnt_tmp = bitmap_size(bmList[bm_index].bm);

					bitmap_set(bmList[bm_index].bm, index, value);
				}
			}

			// CASE 3_3. bitmap_mark <bitmap_name> <index>
			else if(!strcmp(token, "mark")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index
				token = strtok(NULL, seps);
				sscanf(token, "%d", &bit_cnt_tmp); 

				bitmap_mark(bmList[bm_index].bm, bit_cnt_tmp);
			}

			// CASE 3_4. bitmap_reset <bitmap_name> <index>
			else if(!strcmp(token, "reset")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index
				token = strtok(NULL, seps);
				sscanf(token, "%d", &bit_cnt_tmp); 

				bitmap_reset(bmList[bm_index].bm, bit_cnt_tmp);
			}

			// CASE 3_5. bitmap_flip <bitmap_name> <index>
			else if(!strcmp(token, "flip")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index
				token = strtok(NULL, seps);
				sscanf(token, "%d", &bit_cnt_tmp); 

				bitmap_flip(bmList[bm_index].bm, bit_cnt_tmp);
			}

			// CASE 3_6. bitmap_test <bitmap_name> <index>
			else if(!strcmp(token, "test")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index
				token = strtok(NULL, seps);
				sscanf(token, "%d", &bit_cnt_tmp); 

				if(bitmap_test(bmList[bm_index].bm, bit_cnt_tmp))
					printf("true\n");
				else
					printf("false\n");
			}

			// CASE 3_7. bitmap_count <bitmap_name> <index1> <index2> <value(booolean)>
			else if(!strcmp(token, "count")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index); 

				// token : index2
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index1); 

				// token : value
				token = strtok(NULL, seps);
				if(!strcmp(token, "true"))
					value = 1;
				else
					value = 0;

				bit_cnt_tmp = bitmap_count(bmList[bm_index].bm, index, index1, value);
				printf("%u\n", bit_cnt_tmp);
			}

			// CASE 3_8. bitmap_contains  <bitmap_name> <index1> <index2> <value(booolean)>
			else if(!strcmp(token, "contains")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index); 

				// token : index2
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index1); 

				// token : value
				token = strtok(NULL, seps);
				if(!strcmp(token, "true"))
					value = 1;
				else
					value = 0;

				if(bitmap_contains(bmList[bm_index].bm, index, index1, value))
					printf("true\n");
				else
					printf("false\n");
			}

			// CASE 3_9. bitmap_any <bitmap_name> <index1> <index2>
			else if(!strcmp(token, "any")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index); 

				// token : index2
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index1); 

				if(bitmap_any(bmList[bm_index].bm, index, index1))
					printf("true\n");
				else
					printf("false\n");
			}

			// CASE 3_10. bitmap_none <bitmap_name> <index1> <index2>
			else if(!strcmp(token, "none")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index); 

				// token : index2
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index1); 

				if(bitmap_none(bmList[bm_index].bm, index, index1))
					printf("true\n");
				else
					printf("false\n");
			}

			// CASE 3_11. bitmap_all <bitmap_name> <index1> <index2>
			else if(!strcmp(token, "all")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index); 

				// token : index2
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index1); 

				if(bitmap_all(bmList[bm_index].bm, index, index1))
					printf("true\n");
				else
					printf("false\n");
			}

			// CASE 3_12. bitmap_scan
			else if(!strcmp(token, "scan")){
				token = strtok(NULL, " ");

				// CASE 3_12_1. bitmap_scan_and_flip <bitmap_name> <index1> <index2> <value(boolean)>
				if(!strcmp(token, "and_flip")){
					// token : bitmap name
					token = strtok(NULL, seps);
					bm_index = bm_index_num(token);

					// token : index1
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index); 

					// token : index2
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index1); 

					// token : value
					token = strtok(NULL, seps);
					if(!strcmp(token, "true"))
						value = 1;
					else
						value = 0;
					bit_cnt_tmp = bitmap_scan_and_flip(bmList[bm_index].bm, index, index1, value);
					printf("%u\n", bit_cnt_tmp);
				}

				// CASE 3_12_2. bitmap_scan <bitmap_name> <index1> <index2> <value(boolean)>
				else{
					// token : bitmap name
					bm_index = bm_index_num(token);

					// token : index1
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index); 

					// token : index2
					token = strtok(NULL, seps);
					sscanf(token, "%d", &index1); 

					// token : value
					token = strtok(NULL, seps);
					if(!strcmp(token, "true"))
						value = 1;
					else
						value = 0;
					bit_cnt_tmp = bitmap_scan(bmList[bm_index].bm, index, index1, value);
					printf("%u\n", bit_cnt_tmp);
				}
			}

			// CASE 3_13. bitmap_dump <bitmap_name>
			else if(!strcmp(token, "dump")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				bitmap_dump(bmList[bm_index].bm);
			}

			// CASE 3_14. bitmap_expand <bitmap_name> <index>
			else if(!strcmp(token, "expand")){
				// token : bitmap name
				token = strtok(NULL, seps);
				bm_index = bm_index_num(token);

				// token : index1
				token = strtok(NULL, seps);
				sscanf(token, "%d", &index); 

				bmList[bm_index].bm = bitmap_expand(bmList[bm_index].bm, index);
			}
		}
	}

	return 0;
}
