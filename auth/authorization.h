#ifndef AUTHORIZATION_H_SENTRY
#define AUTHORIZATION_H_SENTRY

#include<fstream>
#include<iostream>
#include<string>

class Authorization {
public:
	static void start();
	static void login(std::fstream *fs);
	//static void login_error(std::string log_in);
	static void reg(std::fstream *fs);
};

class Check {
public:
	//static void login_log(std::string log);
	static void pass_error_log(std::string *pass);
	static void login_reg(std::string *log);
	static void pass_reg(std::string *pass);
	static int login_exists(const std::string *log, std::fstream *fs);
	//static void pass_error_reg(std::string pass);
	static int checksym(std::string *str);
};


#endif
