#include <iostream>
#include <assert.h>
#include <leveldb/db.h>
#include <leveldb/write_batch.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
using namespace std;

const char *getrandomkey(int len){
	char *s = new char[len+1];
	if(s == NULL)
		return NULL;
	struct timeval tv;
	gettimeofday(&tv, NULL);
	srand(tv.tv_sec);
	for(int i = 0; i < len; i ++){
		cout<<rand()<<" ";
		*(s + i) = rand() % ('a' - 'z' + 1) + 'a';
	}
	*(s+len) = 0;
	return s;
}
int main(void){
	for(int i = 0; i < 1000; i ++){
		const char *key = getrandomkey(5);
		cout<<key<<endl;
		delete []key;
	}
	return 0;
}



