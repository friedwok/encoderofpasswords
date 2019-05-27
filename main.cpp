#include<iostream>
#include "auth/authorization.h"
#include<fstream>
//#include "encr/encoder.h"
//#include "datapass.h"
using namespace std;

//Encoder enc;

int main()
{
	const char *login;
	fstream fs_user_data;

	login = Authorization::start();
	cout << login << endl;
	if(!fs_user_data.is_open()) {
		fs_user_data.open(login, fstream::in | fstream::out | fstream::app);
	} else {
		fs_user_data.close();
		fs_user_data.open(login, fstream::in | fstream::out | fstream::app);
	}
	fs_user_data.close();

	return 0;
}
