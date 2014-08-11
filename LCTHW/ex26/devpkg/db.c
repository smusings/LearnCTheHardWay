#include <unistd.h>
#include <apr_errno.h>
#include <apr_file_io.h>

#include "db.h"
#include "bstrlib.h"
#include "dbg.h"

//opens a database
static FILE *DB_open(const char *path, const char *mode){
	return fopen(path, mode);
}

//closes a database when done
static void DB_close(FILE *db){
	fclose(db);
}


//loads data into the Databae, if there is an error it will close the database
//destroy the data and return NULL
static bstring DB_load(){

	//the file and the bstring are both empty
	FILE *db=NULL;
	bstring data=NULL;
	
	//opens the database
	//checks the database for the file
	db=DB_open(DB_FILE, "r");
	check(db, "Failed to open database: %s", DB_FILE);
	
	//checks the data
	data=bread((bNread)fread, db);
	check(data, "Failed to read from db file: %s", DB_FILE);
	
	//closes the database
	DB_close(db);
	return data;
error:
	if(db) DB_close(db);
	if(data) bdestroy(data);
	return NULL;
}

//updates the database
int DB_update(const char *url){
	//if file is present, then it says so
	if(DB_find(url)){
		log_info("Already recorded as installed: %s", url);
	}
	
	//checks for file
	FILE *db=DB_open(DB_FILE, "a+");
	check(db, "Failed to open DB file: %s", DB_FILE);
	
	//writes the line into the db, if failed gives error back
	bstring line=bfromcstr(url);
	bconchar(line, '\n');
	int rc=fwrite(line->data, blength(line), 1, db);
	check(rc==1, "Failed to append to the db.");
	
	return 0;
error:
	if(db) DB_close(db);
	return -1;
}

//searched the database for the url
//gives error if the database did not have the file
int DB_find(const char *url){
	bstring data=NULL;
	bstring line=bfromcstr(url);
	int res = -1;
	
	data=DB_load();
	check(data, "Failed to load: %s", DB_FILE);
	
	if(binstr(data, 0, line)==BSTR_ERR){
		res=0;
	} else {
		res=1;
	}

error: //fallthrough
	if(data) bdestroy(data);
	if(line) bdestroy(line);
	
	return res;
}

//initilized the database
int DB_init(){
	apr_pool_t *p=NULL;
	apr_pool_initialize();
	apr_pool_create(&p, NULL);
	
	//access the database and makes a new directory
	if(access(DB_DIR, W_OK | X_OK)==-1){
		apr_status_t rc=apr_dir_make_recursive(DB_DIR,
			APR_UREAD | APR_UWRITE | APR_UEXECUTE |
			APR_GREAD | APR_GWRITE | APR_GEXECUTE, p);
		check(rc==APR_SUCCESS, "Failed to make database dir: %s", DB_DIR);
	}
	
	if(access(DB_FILE, W_OK)==-1){
		FILE *db=DB_open(DB-FILE, "w");
		check(db, "Cannot open database: %s", DB_FILE);
		DB_close(db);
	}
	
	apr_pool_destroy(p);
	return 0;
	
error:
	apr_pool_destroy(p);
	return -1;
}

int DB_list(){
	bstring data=DB_load();
	check(data, "Faied to read load: %s", DB_FILE);
	
	printf("%s", bdata(data));
	bdestroy(data);
	return 0;
	
error:
	return -1;
}
