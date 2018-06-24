#include <leveldb/c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
	const char *dbpath = "testdb";
	leveldb_t *db;
	leveldb_options_t *options = leveldb_options_create();
	char *errptr = NULL;
	leveldb_options_set_create_if_missing(options, 1);
	db = leveldb_open(options, dbpath, &errptr);
	if(errptr != NULL){
		printf("open error:%s\n", errptr);
		return 0;
	}
	char *value = NULL;
	size_t vlen = 0;
	{
		value = leveldb_get(db, leveldb_readoptions_create(), "mykey", 5, &vlen, &errptr);
	}
	value[vlen] = '\0';
	printf("value:%s\n", value);
	return 0;
}
