#include <iostream>
#include <assert.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;
using namespace leveldb;
//获取一个随机的key值
const char * getrandomkey(int len){
	char *s = new char[len+1];
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_sec);
	for(int i = 0; i < len; i ++){
		*(s+i) = rand()%('a'-'z' + 1)+'a';
	}
	*(s+len) = 0;
	return s;
}
int main(void){
	DB *db;
	Options option;
	option.create_if_missing = true;
	DB::Open(option, "testdb", &db);	
	ReadOptions rop;
	//添加数据
	db->Put(WriteOptions(), "mykey", "shannon");
	//获取快照对象
	rop.snapshot = db->GetSnapshot();
	//修改数据
	db->Put(WriteOptions(), "mykey", "fujinghui");
	//添加数据,每次启动该进程都会添加一个数据进来
	//添加大量的数据进来
	for(int i = 0; i < 1000; i ++)
	{
		const char *newkey = getrandomkey(5);
		db->Put(WriteOptions(), newkey, "newdata");
		delete []newkey;
	}
	string value;
	db->Get(rop, "mykey", &value);
	cout<<"value:"<<value<<endl;
	//根据当前快照获取iterator对象
	Iterator *it = db->NewIterator(ReadOptions());
	WriteBatch batch;
	//在获取完Iterator之后，在插入一条数据
	batch.Put("fujinghui", "fujinghui");
	db->Write(WriteOptions(), &batch);

	for(it->SeekToFirst(); it->Valid(); it->Next()){
		cout<<it->key().ToString()<<":"<<it->value().ToString()<<endl;
		//根据快照里的信息将该数据给删除掉
		//batch.Delete(it->key());
		db->Delete(WriteOptions(), it->key());
	}
	//db->Write(WriteOptions(), &batch);
	db->ReleaseSnapshot(rop.snapshot);
	delete db;
	return 0;
}



