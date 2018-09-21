#include <stdio.h>
#include "main.h"

int main(){
	char command[100], original_command[100];
	char *token;
	char seps[4] = "\t _"; 
	int del_index;
	int ll_index, value, index, max_num, min_num;

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
			}

			// CASE 0_2_3. create bitmap <bitmap_name> <bit_count> - bitmap 생성
			else if(!strcmp(token, "bitmap")){
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
			// delete 하는 자료구조가 bitmap인지 확인, bitmap이 맞으면 flag = 2
			// 채워넣어야함

			// 자료구조가 list(flag == 1) 인 경우
			if(flag == 1){
				for(i=del_index; i<9; i++){
					llList[i] = llList[i+1];
				}
				llList_num--;
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
			// dumpdata 하는 자료구조가 bitmap인지 확인, bitmap이 맞으면 flag = 2
			// 채워넣어야함


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
		}

		// CASE 0_5. command <list_name|hashtable_name|bitmap_name> [arguments] - 주어진 이름의 자료구조에 argument 이용하여 command 실행
		else if(!strcmp(token, "command")){
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

			// CASE 1_2. list_splice
			else if(!strcmp(token, "splice")){
				printf("list_splice\n");
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

//				for(e = list_begin((llList[ll_index].link)) ;
//						list_next(e) != list_end((llList[ll_index].link)) ;
//						e=list_next(e)){}
//				// f는 e의 data
//				struct list_item *f = list_entry(e, struct list_item, elem);
//				printf("%d\n",f->data);
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
			// CASE 1_12. list_unique
			else if(!strcmp(token, "unique")){
				printf("list_unique\n");
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
		}
	}


	return 0;
}
