#include <assert.h>
#include <iostream>
#include <sstream>
#include "leveldb/db.h"

using namespace std;
int main(int argc, char *argv[]){
	leveldb::DB *db;
	leveldb::Options options;
	options.create_if_missing = true;
	std::string dbpath = "testdb";
	leveldb::Status status = leveldb::DB::Open(options, dbpath, &db);
	assert(status.ok());
	char cStr[10] = "key:";
	leveldb::Status s;
	for(int i = 0; i < 100000; i ++){
		cStr[4] = (char)i;
		string key(cStr);
		string value;
		s = db->Get(leveldb::ReadOptions(), key, &value);
		cout<<"key:"<<key<<" value:"<<value<<endl;
	}
	delete db;
	return 0;
}
