#include <leveldb/c.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

int main(int argc, char **argv){
	struct leveldb_t *db;
	struct leveldb_options_t *options = leveldb_options_create();
	char *errptr = NULL;
	//设置options.create_if_missing = true
	leveldb_options_set_create_if_missing(options, 1);
	db = leveldb_open(options, "testdb", &errptr);
	if(errptr != NULL)
	{
		printf("open db error:%s\n", errptr);
		exit(0);
	}
	if(argc >= 2)
	{
		//添加数据
		if(strcmp(argv[1], "add") == 0)
		{
			//通过writebatch批量添加数据
			leveldb_writebatch_t *batch = leveldb_writebatch_create();
			for(int i = 2; i + 1 < argc; i += 2){
				char *key = argv[i];
				char *value = argv[i+1];
				leveldb_writebatch_put(batch, key, strlen(key),
						value, strlen(value));
			}
			leveldb_write(db, leveldb_writeoptions_create(),
					batch, &errptr);
			leveldb_writebatch_destroy(batch);
		}
		//删除数据
		else if(strcmp(argv[1], "del") == 0){
			//通过writebatch批量删除数据
			leveldb_writebatch_t *batch = leveldb_writebatch_create();
			for(int i = 2; i < argc; i += 1){
				char *key = argv[i];
				leveldb_writebatch_delete(batch, key, strlen(key));
			}
			leveldb_write(db, leveldb_writeoptions_create(),
					batch, &errptr);
			leveldb_writebatch_destroy(batch);
		}
		//清理数据库中所有的数据
		else if(strcmp(argv[1], "clean") == 0){
			//通过writebatch删除数据
			leveldb_writebatch_t *batch = leveldb_writebatch_create();
			leveldb_iterator_t *it = leveldb_create_iterator(db, leveldb_readoptions_create());
			leveldb_iter_seek_to_first(it);
			while(leveldb_iter_valid(it)){
				const char *key;
				size_t klen;
				key = leveldb_iter_key(it, &klen);
				if(klen > 0 && key != NULL){
					((char*)key)[klen] = 0;
					leveldb_writebatch_delete(batch, key, strlen(key));
				}
				leveldb_iter_next(it);
			}
			leveldb_write(db, leveldb_writeoptions_create(),
				batch, &errptr);
			leveldb_writebatch_destroy(batch);
			printf("数据清理完毕!\n");
		}
		//通过迭代器显示所有数据
		else if(strcmp(argv[1], "iterator") == 0){
			leveldb_iterator_t *it = leveldb_create_iterator(db, leveldb_readoptions_create());
			leveldb_iter_seek_to_first(it);
			while(leveldb_iter_valid(it)){
				const char *key,*value;
				size_t klen,vlen;
				key = leveldb_iter_key(it, &klen);
				value = leveldb_iter_value(it, &vlen);
				((char *)key)[klen] = '\0';
				printf("%s:%s\n", key, value);
				leveldb_iter_next(it);
			}
			leveldb_iter_destroy(it);
		}
		//获取数据
		else if(strcmp(argv[1], "get") == 0){
			for(int i = 2; i < argc; i ++){
				char *key = argv[i];
				size_t len = 0;
				char *value = leveldb_get(
					db, leveldb_readoptions_create(),
					key, strlen(key), &len, &errptr);
					value[len] = '\0';
				if(len > 0 && value != NULL && errptr == NULL){
					printf("%s:%s\n", key, value);
				}
				else
				{
					printf("%s:null\n", key);
				}
			}
		}
		//默认修改mykey的值为当前的时间
		else if(strcmp(argv[1], "snapshot") == 0){
			char ctime[128];
			time_t timep;
			time(&timep);
			sprintf(ctime, "%s", asctime(gmtime(&timep)));
			//获取系统快照
			const leveldb_snapshot_t *snapshot = leveldb_create_snapshot(db);
			leveldb_readoptions_t *readoptions = leveldb_readoptions_create();
			//设置为当前快照
			leveldb_readoptions_set_snapshot(readoptions, snapshot);
			//修改数据
			leveldb_put(db, leveldb_writeoptions_create(),
					"mykey", 5, ctime, strlen(ctime), &errptr);
			size_t len;
			printf("数据已修改，使用快照读取的值:\n");
			char *value = leveldb_get(db, readoptions, "mykey", 5, &len, &errptr);
			if(len > 0 && value != NULL && errptr == NULL){
				printf("%s:%s\n", "mykey", value);
			}
			else{
				printf("%s:null\n", "mykey");
			}
			printf("不使用快照读取的值:\n");
			value = leveldb_get(db, leveldb_readoptions_create(), 
					"mykey", 5, &len, &errptr);
			if(len > 0 && value != NULL && errptr == NULL){
				printf("%s:%s\n", "mykey", value);
			}
			else{
				printf("%s:null\n", "mykey");
			}
			leveldb_release_snapshot(db, snapshot);
		}
	}
	//add data
	leveldb_close(db);
	return 0;
}

