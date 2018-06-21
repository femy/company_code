#include <assert.h>
#include <iostream>
#include <sstream>
#include "leveldb/db.h"

using namespace std;

int main(int argc, char * argv[]){
	leveldb::DB* db;
	leveldb::Options options;
	options.create_if_missing = true;
	std::string dbpath = "testdb";
	leveldb::Status status = leveldb::DB::Open(options, dbpath, &db);
	assert(status.ok());
	string key1 = "fa";
	string key2 = "fa2";
	stringstream strKeys;

	string value;
	char cStr[10]="key:";
	leveldb::Status s;
	for(int i = 0; i < 1000000; i ++)
	{
		cStr[4] = (char)i;
		string key1(cStr);
		
		s = db->Put(leveldb::WriteOptions(), string(key1), key2);
	}
	//s = db->Get(leveldb::ReadOptions(), key1, &value);
	cout<<value<<endl;
	delete db;
	return 0;
}



