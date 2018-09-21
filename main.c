#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bitmap.h"
#include "list.h"
#include "hash.h"

void main(){
	char command[100], original_command[100];
	char *token;
	char seps[4] = "\t _"; 

	while(1){
		gets(command, sizeof(command), stdin);
		command[strlen(command)-1] = '\0';
		strcpy(origianl_command, command); // token 시 자기 자신도 잘려나가기 때문에 원본 유지

		token = strtok(command, seps); // token(\t, 띄어쓰기, _로 앞부분 받아오기)

		if(token == NULL)
			continue;
		else if(strcmp(token == "quit"))
			break;
		// CASE 1. list
		else if(strcmp(token == "list")){
			token = strtok(NULL, seps);

			// CASE 1_1. list_insert
			if(strcmp(token == "insert")){
				token = strtok(NULL, seps);

				// CASE 1_1_1. list_insert
				if(token == NULL){
				}

				// CASE 1_1_2. list_insert_ordered
				else if(token == "ordered"){
				}
			}

			// CASE 1_2. list_splice
			else if(strcmp(token == "splice")){
			}

			// CASE 1_3. list_push
			else if(strcmp(token == "push")){
				token = strtok(NULL, seps);

				// CASE 1_3_1. list_push_front
				if(strcmp(token == "front")){
				}

				// CASE 1_3_2. list_push_back
				else if(strcmp(token == "back")){
				}
			}

			// CASE 1_4. list_remove
			else if(strcmp(token == "remove")){
			}

			// CASE 1_5. list_pop
			else if(strcmp(token == "pop")){
				token = strtok(NULL, seps);
				
				// CASE 1_5_1. list_pop_front
				if(strcmp(token == "front")){
				}

				// CASE 1_5_2. list_pop_ordered
				else if(strcmp(token == "back")){
				}
			}

			// CASE 1_6. list_front
			else if(strcmp(token == "front")){
			}

			// CASE 1_7. list_back
			else if(strcmp(token == "back")){
			}

			// CASE 1_8. list_size
			else if(strcmp(token == "size")){
			}

			// CASE 1_9. list_empty
			else if(strcmp(token == "empty")){
			}

			// CASE 1_10. list_reverse
			else if(strcmp(token == "reverse")){
			}

			// CASE 1_11. list_sort
			else if(strcmp(token == "sort")){
			}
			// CASE 1_12. list_unique
			else if(strcmp(token == "unique")){
			}

			// CASE 1_13. list_max
			else if(strcmp(token == "max")){
			}

			// CASE 1_14. list_min
			else if(strcmp(token == "min")){
			}
		}
	}
}
