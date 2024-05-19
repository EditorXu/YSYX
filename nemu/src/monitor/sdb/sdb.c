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

#include <isa.h>
#include <cpu/cpu.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "sdb.h"
#include "memory/paddr.h"

static int is_batch_mode = false;

void init_regex();
void init_wp_pool();

/* We use the `readline' library to provide more flexibility to read from stdin. */
static char* rl_gets() {
  static char *line_read = NULL;

  if (line_read) {
    free(line_read);
    line_read = NULL;
  }

  line_read = readline("(nemu) ");

  if (line_read && *line_read) {
    add_history(line_read);
  }

  return line_read;
}

static int cmd_c(char *args) {
  cpu_exec(-1);
  return 0;
}


static int cmd_q(char *args) {
	nemu_state.state = NEMU_QUIT;
  return -1;
}

static int cmd_si(char *args) {
	int n;
	if(args != NULL){
		sscanf(args, "%d", &n);
	}
	else{
		n = 1;
	}
	cpu_exec(n);
	return 0;
}

static int cmd_info(char *args) {
	if( args == NULL) {
		printf("No args.");
	}
	else if(strcmp(args, "r") == 0) {
		isa_reg_display();
	}
	else if(strcmp(args, "w") == 0) {
		watchpoint_display();
	}

	return 0;
}

static int cmd_x(char *args)	{
	char* num = strtok(args, " ");
	char* iaddr = strtok(NULL," ");

	int len;
	paddr_t addr;

	sscanf(num,"%d",&len);
	sscanf(iaddr,"%x",&addr);

	for(int i = 0; i < len; i++) {
		printf("0x%x ---> 0x%08x\n",addr, paddr_read(addr, 4));
		addr += 4;
	}
	
	return 0;
}

static int cmd_p(char* args) {
	if(args == NULL){
		printf("No args\n");
		
		return 0;
	}
	debug("args = %s\n",args);
	bool success = true;
	uint32_t number = expr(args,&success);
	if(success == true){
		printf("%u\n",number);
	}
	
	return 0;
}

static int cmd_t(){
	FILE *fp = fopen("/home/romeo/ysyx-workbench/nemu/tools/gen-expr/input.txt", "r");
	assert(fp != NULL);

	uint32_t result;
	char expression[65536];
	uint32_t count = 0;
	int n;
	int equal = 0;
	int unequal = 0;
	printf("Please input the information's number.\n");
	int read = scanf("%d", &n);
	if(!read){
		printf("Error scanf\n");
		return 1;
	}

	while(count < n && (fscanf(fp, "%u %[^\n]", &result,expression) == 2)){
		uint32_t len = strlen(expression);
		char *ex = malloc((1+len) * sizeof(char));
		strncpy(ex,expression,len);
		ex[len] = '\0';
		debug("result = %u, experssion = %s\n",result,ex);
		debug("test: %c\n",ex[len]); 
		bool success = true;
		uint32_t expr_result = expr(ex,&success);
		debug("expr_result = %u\n",expr_result);
		if(expr_result == result){
			printf("Equal.result = %u, expr = %u\n", result, expr_result);
			equal++;
		}
		else{
			printf("Unequal.result = %u, expr = %u\n", result, expr_result);
			unequal++;
		}
		free(ex);
		count++;
	}
	printf("Equal = %d, Unequal = %d\n",equal,unequal);
	fclose(fp);
	return 0;
}

static int cmd_d(char* args){
	if(args == NULL){
		printf("No args.\n");
	}
	else{
		int number;
		sscanf(args, "%d", &number);
		delete_watchpoint(number);
	}

	return 0;
}

static int cmd_w(char* args){
	create_watchpoint(args);
	
	return 0;
}

static int cmd_help(char *args);

static struct {
  const char *name;
  const char *description;
  int (*handler) (char *);
} cmd_table [] = {
  { "help", "Display information about all supported commands", cmd_help },
  { "c", "Continue the execution of the program", cmd_c },
  { "q", "Exit NEMU", cmd_q },
	{ "si", "Step i the execution of the program", cmd_si},
	{ "info", "Print the SUBCMD information", cmd_info},
	{ "x", "Scan the memory", cmd_x},
	{ "p", "Print expression", cmd_p},
	{ "w", "Create the watchpoint", cmd_w},
	{ "d", "Delete the watchpoint", cmd_d},
	{ "t", "Test the expr", cmd_t},

};

#define NR_CMD ARRLEN(cmd_table)

static int cmd_help(char *args) {
  /* extract the first argument */
  char *arg = strtok(NULL, " ");
  int i;

  if (arg == NULL) {
    /* no argument given */
    for (i = 0; i < NR_CMD; i ++) {
      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
    }
  }
  else {
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(arg, cmd_table[i].name) == 0) {
        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
        return 0;
      }
    }
    printf("Unknown command '%s'\n", arg);
  }
  return 0;
}

void sdb_set_batch_mode() {
  is_batch_mode = true;
}

void sdb_mainloop() {
  if (is_batch_mode) {
    cmd_c(NULL);
    return;
  }

  for (char *str; (str = rl_gets()) != NULL; ) {
    char *str_end = str + strlen(str);

    /* extract the first token as the command */
    char *cmd = strtok(str, " ");
    if (cmd == NULL) { continue; }

    /* treat the remaining string as the arguments,
     * which may need further parsing
     */
    char *args = cmd + strlen(cmd) + 1;
    if (args >= str_end) {
      args = NULL;
    }

#ifdef CONFIG_DEVICE
    extern void sdl_clear_event_queue();
    sdl_clear_event_queue();
#endif

    int i;
    for (i = 0; i < NR_CMD; i ++) {
      if (strcmp(cmd, cmd_table[i].name) == 0) {
        if (cmd_table[i].handler(args) < 0) { return; }
        break;
      }
    }

    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
  }
}

void init_sdb() {
  /* Compile the regular expressions. */
  init_regex();

  /* Initialize the watchpoint pool. */
  init_wp_pool();
}
