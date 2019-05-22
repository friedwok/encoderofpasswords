#include<iostream>
#include<string>
#include<fstream>
#include "authorization.h"

void Authorization::start()
{
	const char *ans_yes = "Y";
	const char *ans_no = "N";
	//std::string log;
	//std::string pass;
	std::string ans1;
	int state = 0;
	std::fstream fs;

	std::cout << "Do you have an account(Y/N)?" << std::endl;
	std::cin >> ans1;
	while(!state) {
		if(!ans1.compare(ans_yes)) {
			Authorization::login(&fs);
			state = 1;
		} else if(!ans1.compare(ans_no)) {
			Authorization::reg(&fs);
			state = 1;
		} else {
			std::cout << "Input \"Y\" or \"N\": ";
			std::cin >> ans1;
		}
	}
}

/*void Authorization::login_error(std::string log_in)
{
	
	std::cout << "test_err" << std::endl;
}
*/
void Authorization::login(std::fstream *fs)
{
	std::string log;
	std::string pass;

	if(!fs->is_open()) {
		fs->open("logpass.txt", std::fstream::in | std::fstream::out);
	}
	std::cout << "Login:" << std::endl;
	std::cin >> log;
	Check::login_log(&log, fs);
	std::cout << "Password:" << std::endl;
	std::cin >> pass;
	Check::pass_log(&pass, fs);
}

void Authorization::reg(std::fstream *fs)
{
	std::string log;
	std::string pass, pass_r;
	int pass_fl = 0;
	char tmp_buf_log[32];
	char tmp_buf_pass[32];
	char s = '\n';

	if(!fs->is_open()) {
		std::cout << "File opened\n";
		fs->open("logpass.txt", std::fstream::in | std::fstream::out);
	}
	std::cout << "Login and password contains only latin letters and numbers" << std::endl;
	std::cout << "Login:" << std::endl;
	std::cin >> log;
	Check::login_reg(&log);
	while(Check::login_exists(&log, fs)) {
		std::cout << "This name is already in use\n";
		std::cout << "Login:\n";
		std::cin >> log;
	}
	while(!pass_fl) {
		std::cout << "Password:" << std::endl;
		std::cin >> pass;
		Check::pass_reg(&pass);
		std::cout << "Confirm the password:" << std::endl;
		std::cin >> pass_r;
		if(pass.compare(pass_r) == 0) {
			pass_fl = 1;
		} else {
			std::cout << "Passwords don't match" << std::endl;
		}
	}
	fs->close();
	if(!fs->is_open()) {
		fs->open("logpass.txt", std::fstream::in | std::fstream::out | std::fstream::app);
	}
	strcpy(tmp_buf_log, log.c_str());
	strcpy(tmp_buf_pass, pass.c_str());
	fs->write(tmp_buf_log, log.size());
	fs->write(&s, sizeof(s));
	fs->write(tmp_buf_pass, pass.size());
	fs->write(&s, sizeof(s));
	fs->close();
	//create file "login"
}

void Check::login_reg(std::string *log)
{
	if(log->size() > 10) {
		std::cout << "Too many symbols, number of symbols should be less or equal then 10" << std::endl;
		std::cout << "Login:" << std::endl;
		std::cin >> *log;
		Check::login_reg(log);
	} else if(Check::checksym(log)) {
		std::cout << "Login contains only latin letters and numbers" << std::endl;
		std::cout << "Login:" << std::endl;
		std::cin >> *log;
		Check::login_reg(log);
	}
}

void Check::pass_reg(std::string *pass)
{
	if(pass->size() > 10) {
		std::cout << "Too many symbols in password, grater than 10" << std::endl;
		std::cout << "Password:" << std::endl;
		std::cin >> *pass;
		Check::pass_reg(pass);
	} else if(Check::checksym(pass)) {
		std::cout << "Password contains only latin letters and numbers" << std::endl;
		std::cout << "Password:" << std::endl;
		std::cin >> *pass;
		Check::pass_reg(pass);
	}
}

int Check::login_exists(const std::string *log, std::fstream *fs)
{
	int read_log = 1, i = 0;
	char sym[1], login_comp[32];

	fs->read(sym, 1);
	while(!fs->eof()) {
		if((sym[0] != '\n')&&(read_log)) {
			login_comp[i] = sym[0];
			i++;
			login_comp[i] = 0;
		} else if((sym[0] == '\n')&&(read_log)) {
			std::string str_tmp(login_comp, i);
			if(!log->compare(0, i, str_tmp)) {
				//std::cout << "compare" << '\n';
				return 1;
			}
			//std::cout << "comp1 i = " << i << '\n';
			read_log = 0;
			i = 0;
		} else if((sym[0] == '\n')&&(!read_log)) {
			read_log = 1;
		}
		fs->read(sym, 1);
	}
	return 0;
}

void Check::login_log(std::string *log, std::fstream *fs)
{
	char buffer[255];
	char sym;
	//std::string login;
	int i = 0, log_read = 1;

	//fs->seekg(0, fs->beg);
	while(fs->read(&sym, sizeof(char))) {
		//std::cout << sym << std::endl;
		if((sym != '\n')&&(log_read)) {
			buffer[i] = sym;
			i++;
		} else if((sym == '\n')&&(!log_read)) {
			log_read = 1;
		} else if((sym == '\n')&&(log_read)) {
			buffer[i] = 0;
			//std::cout << buffer;
			if(!log->compare(0, i, buffer)) {
				std::cout << "equal" << std::endl; 
				return;
			}
			i = 0;
			log_read = 0;
		}
	}

	std::cout << "Incorrect login:" << std::endl;
	std::cout << "Login:" << std::endl;
	std::cin >> *log;
	fs->close();
	fs->open("logpass.txt", std::fstream::in | std::fstream::out);
	Check::login_log(log, fs);
}

void Check::pass_log(std::string *pass, std::fstream *fs)
{
	char buffer[255];
	char sym;
	int i = 0, pass_read = 0;

	while(fs->read(&sym, sizeof(char))) {
		//std::cout << sym << std::endl;
		if((sym != '\n')&&(pass_read)) {
			buffer[i] = sym;
			i++;
		} else if((sym == '\n')&&(!pass_read)) {
			pass_read = 1;
		} else if((sym == '\n')&&(pass_read)) {
			buffer[i] = 0;
			if(!pass->compare(0, i, buffer)) {
				std::cout << "equal" << std::endl;
				return;
			}
			i = 0;
			pass_read = 0;
		}
	}

	std::cout << "Incorrect password:" << std::endl;
	std::cout << "Password:" << std::endl;
	std::cin >> *pass;
	fs->close();
	fs->open("logpass.txt", std::fstream::in | std::fstream::out);
	Check::pass_log(pass, fs);
}

void Check::pass_error_log(std::string *pass)
{
//	char buffer[255];
//	char sym;
//	std::string pass;
//	int i = 0, pass_read = 0, pass_found = 0;
}

int Check::checksym(std::string *str)
{
	int i = 0;
	char s;

	while((*str)[i] != 0) {
		s = (*str)[i];
		if(((s <= '9')&&(s >= '0'))||((s >= 'a')&&(s <= 'z'))||((s >= 'A')&&(s <= 'Z'))) {
			i++;
		} else {
			return 1;
		}
	}

	return 0;
}
