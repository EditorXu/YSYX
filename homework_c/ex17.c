#include<stdio.h>
#include<assert.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

struct Address
{
	char *id;
	char *set;
	char *name;
	char *email;
	char *phone;
};

struct Database
{
	struct Address *rows;
	int MAX_DATA;
	int MAX_ROWS;
};

struct Connection
{
	FILE *file;
	struct Database *db;
};

struct Connection *global_conn = NULL;

void Database_close()
{
	if(global_conn)
	{
		if(global_conn->file) fclose(global_conn->file);
		if(global_conn->db) 
		{

			if(global_conn->db->rows) 
			{
				for(int i = 0; i < global_conn->db->MAX_ROWS; i++)
				{
					if(global_conn->db->rows[i].id)
					{
						free(global_conn->db->rows[i].id);
						global_conn->db->rows[i].id = NULL;
					}
					
					
					if(global_conn->db->rows[i].set)
					{
						free(global_conn->db->rows[i].set);
						global_conn->db->rows[i].set = NULL;
					}
					
					if(global_conn->db->rows[i].name)
					{
						free(global_conn->db->rows[i].name);
						global_conn->db->rows[i].name = NULL;
					}

					if(global_conn->db->rows[i].email)
					{
						free(global_conn->db->rows[i].email);
						global_conn->db->rows[i].email = NULL;
					}

					if(global_conn->db->rows[i].phone)
					{
						free(global_conn->db->rows[i].phone);
						global_conn->db->rows[i].phone = NULL;
					}
				}
				free(global_conn->db->rows);
				global_conn->db->rows = NULL;
			}

			free(global_conn->db);
			global_conn->db = NULL;
		}
		free(global_conn);
		global_conn = NULL;
	}
}

void die(const char *message)
{
	if(errno)
	{
		perror(message);
	}
	else
	{
		printf("ERROR: %s\n",message);
	}

	Database_close();

	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%s %s %s %s\n",addr->id,addr->name,addr->email,addr->phone);
}

struct Connection *Database_open(const char *filename,char mode,int MAX_DATA,int MAX_ROWS)
{
	global_conn = malloc(sizeof(struct Connection));
	if(!global_conn) die("Memory error");

	global_conn->db = malloc(sizeof(struct Database));
	if(!global_conn->db) die("Memory error");

	global_conn->db->rows = malloc(MAX_ROWS * sizeof(struct Address));
	if(!global_conn->db->rows) die("Memory error");

	global_conn->db->MAX_DATA = MAX_DATA;
	global_conn->db->MAX_ROWS = MAX_ROWS;

	return global_conn;
}

void Database_load()
{
	
	for(int i = 0;i < global_conn->db->MAX_ROWS ;i++)
	{
		
		global_conn->db->rows[i].id = malloc(sizeof(char) * 2);
		if(global_conn->db->rows[i].id != NULL)
		{
			int rh = fread(global_conn->db->rows[i].id,sizeof(char) * 2,1,global_conn->file);
			if(rh != 1) die("Failed to load database.");
		}
	}


  for(int i = 0; i < global_conn->db->MAX_ROWS; i++)
	{
		global_conn->db->rows[i].set = malloc(sizeof(char));
		if(global_conn->db->rows[i].set != NULL)
		{
			int ri = fread(global_conn->db->rows[i].set,sizeof(char),1,global_conn->file);
			if(ri != 1) die("Failed to load database.");
		}
		
		global_conn->db->rows[i].name = malloc(global_conn->db->MAX_DATA);
		if(global_conn->db->rows[i].name != NULL)
		{
			int rb = fread(global_conn->db->rows[i].name,9,1,global_conn->file);
			if(rb != 1) die("Failed to load database.");
		}
	
		global_conn->db->rows[i].email = malloc(global_conn->db->MAX_DATA);
		if(global_conn->db->rows[i].email != NULL)
		{
		 int rd = fread(global_conn->db->rows[i].email,30,1,global_conn->file);
			if(rd != 1) die("Failed to load database.");
		}
	
		global_conn->db->rows[i].phone = malloc(global_conn->db->MAX_DATA);
		if(global_conn->db->rows[i].phone != NULL)
		{
		 int re = fread(global_conn->db->rows[i].phone,11,1,global_conn->file);
			if(re != 1) die("Failed to load database.");
		}
	}

}

void Database_write()
{
	rewind(global_conn->file);

	for(int i = 0;i < global_conn->db->MAX_ROWS ;i++)
	{
		
		if(global_conn->db->rows[i].id != NULL)
		{
			int rh = fwrite(global_conn->db->rows[i].id,sizeof(char) * 2,1,global_conn->file);
			if(rh != 1) die("Failed to write database.");
			rh = fflush(global_conn->file);
			if(rh == -1) die("Cannot flush database.");
		}
	}


	for(int i = 0; i < global_conn->db->MAX_ROWS; i++)
	{
		if(global_conn->db->rows[i].set != NULL)
		{
			int ri = fwrite(global_conn->db->rows[i].set,sizeof(char),1,global_conn->file);
			if(ri != 1) die("Failed to write database.");
			ri = fflush(global_conn->file);
			if(ri == -1) die("Cannot flush database.");
		}

		if(global_conn->db->rows[i].name != NULL)
		{
		int rb = fwrite(global_conn->db->rows[i].name,9,1,global_conn->file);
			if(rb != 1) die("Failed to write database.");
			rb = fflush(global_conn->file);
			if(rb == -1) die("Cannot flush database.");
		}
	
		if(global_conn->db->rows[i].email != NULL)
		{
		int rd = fwrite(global_conn->db->rows[i].email,30,1,global_conn->file);
			if(rd != 1) die("Failed to write database.");
			rd = fflush(global_conn->file);
			if(rd == -1) die("Cannot flush database.");
		}
	
		if(global_conn->db->rows[i].phone != NULL)
		{
		int re = fwrite(global_conn->db->rows[i].phone,11,1,global_conn->file);
			if(re != 1) die("Failed to write database.");
			re = fflush(global_conn->file);
			if(re == -1) die("Cannot flush database.");
		}
		
	}
}


void Database_create()
{
	for(int i = 0; i < global_conn->db->MAX_ROWS;i++)
	{
		global_conn->db->rows[i].id = malloc(sizeof(char) * 2);
		if(global_conn->db->rows[i].id == NULL) die("Memory allocation error");
	
		struct Address *addr = &global_conn->db->rows[i];
		char n[12];
		sprintf(n,"%d",i + 1);
		strncpy(addr->id,n,strlen(n));
		addr->id[strlen(n)] = '\0';
		
	}

}

void Database_set(int id,const char *name,const char *email,const char *phone,int MAX_DATA)
{
	if(id > global_conn->db->MAX_ROWS) die("ID is out of range");

	struct Address *addr = &global_conn->db->rows[id];
	char* set = "1";
	//if(addr->set == 1) die("Already set,delete it first");
	addr->set = malloc(2);
	if(!addr->set) die("Memory allocation error");
	strncpy(addr->set, set,strlen(set));
	addr->set[strlen(set)] = '\0';

	addr->name = malloc(global_conn->db->MAX_DATA);
	if(!addr->name)
	{
		die("Memory allocation error");
	}
	strncpy(addr->name, name, strlen(name));
	addr->name[strlen(name)] = '\0';

	addr->email = malloc(global_conn->db->MAX_DATA);
	if(!addr->email)
	{
		die("Memory allocation error");
	}
	strncpy(addr->email, email, strlen(email));
	addr->email[strlen(email)] = '\0';

	addr->phone = malloc(global_conn->db->MAX_DATA);
	if(!addr->phone)
	{
		die("Memory allocation error");
	}
	strncpy(addr->phone, phone, strlen(phone));
	addr->phone[strlen(phone)] = '\0';
}

void Database_get(int id)
{
	Database_load();

	struct Address *addr = &global_conn->db->rows[id];

	if(*addr->set = '1')
	{
		Address_print(addr);
	}
	else
	{
		die("ID is not set");
	}

}

void Database_delete(int id)
{
	Database_load();

	struct Address *addr = &global_conn->db->rows[id];
	char *set = "0";
	strncpy(addr->set,set,strlen(set));

}

void Database_list(int MAX_ROWS)
{
		Database_load();

	for(int i = 0;i < MAX_ROWS;i++)
	{
			struct Address *cur = &global_conn->db->rows[i];
			if(*cur->set == '1')
				{
					Address_print(cur);
				}
	}
}

void Database_find(const char *search_term,int MAX_ROWS)
{
	
	Database_load();
	
	for(int i = 0; i < MAX_ROWS;i++)
	{
		struct Address *cur = &global_conn->db->rows[i];
		if(!cur) die("There is not memory");

		if((*cur->set = '1') && (strstr(cur->name,search_term) || strstr(cur->email, search_term) || strstr(cur->phone, search_term)))
		{
			Address_print(cur);
		}

	}

}

int main(int argc,char *argv[])
{
	if(argc < 3) die("USAGE: ex17 <dbfile> <action> [MAX_DATA] [MAX_ROWS] [action params]");

	char *filename = argv[1];
	char action = argv[2][0];

	int MAX_DATA = atoi(argv[3]);
	int MAX_ROWS = atoi(argv[4]);

	global_conn = Database_open(filename,action,MAX_DATA,MAX_ROWS);

//	printf("%c\n",action);

	int id = -1;

	if(argc > 5) id = atoi(argv[5]);
	id = id - 1;
	if(id > MAX_ROWS) die("There's not that many records.");

	switch(action)
	{
		case'c':
			global_conn->file = fopen(filename,"w");
			Database_create();
			Database_write();
			break;

		case'g':

			if(argc != 6) die("Need an id to get");
			global_conn->file = fopen(filename,"r+b");
			Database_get(id);
			Database_write;
			break;

		case's':
			if(argc != 9) die("Need id, name, email, phone to set");

			global_conn->file = fopen(filename,"a+b");
		//	Database_load_half();
			Database_set(id, argv[6], argv[7], argv[8],MAX_DATA);
			Database_write();
			break;

		case'd':
			if(argc != 6) die("Need id to delete");

			global_conn->file = fopen(filename,"r+b");
			Database_delete(id);
			Database_write();
			break;

		case'l':
			global_conn->file = fopen(filename,"r+b");
			Database_list(MAX_ROWS);
			break;

		case'f':
			global_conn->file = fopen(filename,"r+b");
			Database_find(argv[6],MAX_ROWS);
			break;

		default:
			die("Invaild action,only: c=create, g=get, s=set, d=delete, l=list, f=find");
	}

	Database_close();

	return 0;
}



