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
	for(int i = 0; i < len; i ++){
		*(s+i) = rand()%('a'-'z' + 1)+'a';
	}
	*(s+len) = 0;
	return s;
}
inline void srandtime(){
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_sec);	
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
	srandtime();
	const char *newkey = getrandomkey(5);
	db->Put(WriteOptions(), newkey, "newdata");
	delete []newkey;
	string value;
	db->Get(rop, "mykey", &value);
	cout<<"value:"<<value<<endl;
	//根据当前快照获取iterator对象,主要是查看是否有新添加的数据
	Iterator *it = db->NewIterator(rop);
	for(it->SeekToFirst(); it->Valid(); it->Next()){
		cout<<it->key().ToString()<<":"<<it->value().ToString()<<endl;
	}
	delete it;
	db->ReleaseSnapshot(rop.snapshot);
	delete db;
	return 0;
}



