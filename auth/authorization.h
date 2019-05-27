#ifndef AUTHORIZATION_H_SENTRY
#define AUTHORIZATION_H_SENTRY

#include<fstream>
#include<iostream>
#include<string>
#include "encoder.h"

extern Encoder enc;
char* string_to_char(std::string *str);

class Authorization {
public:
	static char* start();
	static void login(std::fstream *fs, char **login);
	static void reg(std::fstream *fs, char **login);
};

class Check {
public:
	static void login_log(std::string *log, std::fstream *fs);
	static void pass_error_log(std::string *pass);
	static void login_reg(std::string *log);
	static void pass_reg(std::string *pass);
	static void pass_log(std::string *pass, std::fstream *fs);
	static int login_exists(const std::string *log, std::fstream *fs);
	//static void pass_error_reg(std::string pass);
	static int checksym(std::string *str);
};


#endif
