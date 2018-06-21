#include <iostream>
#include <leveldb/db.h>
#include <string.h>

using namespace std;
using namespace leveldb;

//get next number based on current number
void getnextnumber(char *buffer){
	int i = 0;
	while(buffer[i] != '\0'){
		if(buffer[i] >= '0' && buffer[i] < '9')
		{
			buffer[i] += 1;
			return;
		}
		else
		{
			buffer[i] = '0';
		}
		i ++;
	}
	buffer[i] = '1';
}

int main(void){
	DB* db;
	Options options;
	options.create_if_missing = true;
	string dbpath = "testdb";
	Status status = DB::Open(options, dbpath, &db);
	if(status.ok()){
		char key[10];
		bzero(key, sizeof(key));
		key[0] = '0';
		while(key[4] != '9'){		//<100000
			string nv = string(key);
			db->Put(WriteOptions(), nv, nv);
			getnextnumber(key);
			cout<<key<<" ";
		}	
		
	}
	delete db;
	return 0;
}



