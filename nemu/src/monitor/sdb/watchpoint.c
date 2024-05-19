/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"

WP wp_pool[NR_WP] = {};

static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i+1;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
		debug("wp_pool[%d].NO = %d\n",i,wp_pool[i].NO);
  }

  head = NULL;
  free_ = wp_pool;
}

WP* new_wp(){
	for(WP* p = free_; p->next != NULL; p = p->next){
		if(p->flag == false){
			p->flag = true;
			if(head == NULL){
				head = p;
			}
			return p;
		}
	}
	printf("No unuse point.\n");
	assert(0);

return NULL;
}

void free_wp(WP* wp){
	if(head->NO == wp->NO){
		head->flag = false;
		head = NULL;
		printf("Delete watchpoint success.\n");
		}
	for(WP* p = head;p->next != NULL; p = p->next){
		if(p->next->NO == wp->NO){
			WP* tmp = p->next;
			p->next = p->next->next;
			tmp->flag = false;
			printf("free success");
		}
	}
}

void watchpoint_display(){
	for(int i = 0; i < NR_WP; i++){
		if(wp_pool[i].flag){
			printf("Watchpoint.No: %d, expr = %s, old_value = %d, new_value = %d\n.",wp_pool[i].NO,wp_pool[i].expr,wp_pool[i].old_value,wp_pool[i].new_value);
		}
	}
}

void delete_watchpoint(int NO){
	for(int i = 0; i < NR_WP; i++){
		free_wp(&wp_pool[i]);
		}
}

void create_watchpoint(char *args){
	WP* p = new_wp();
	strcpy(p->expr,args);
	bool success = true;
	debug("success = %d\n",success);
	uint32_t tmp = expr(p->expr,&success);
	debug("success = %d, tmp = %u\n",success,tmp);
	if(success){
		p->old_value = tmp;
	}
	else {
		printf("watchpoint expr wrong\n.");
	}
		printf("Create watchpoint No.%d success.\n",p->NO);
}













/* TODO: Implement the functionality of watchpoint */

