#include<iostream>
#include "encoder.h"
using namespace std;

Encoder::Encoder()
{
	int letters_count = 26;
	char sym;
	for(int i = 0; i < letters_count + 4 + 6; i++) {
		sym = 'a' + (i % 26);
		symbs[i/6][i%6] = sym;
	}
}

char* Encoder::encrypt(const char *str_to_enc)
{
	int i = 0, len = strlen(str_to_enc), col, row;
	cout << len << '\n';
	char *enc_str = new char[len + 1];
	char sym;

	enc_str[len] = 0;
	while(str_to_enc[i] != 0) {
		if(str_to_enc[i] > '9') {
			//'a' = 97
			str_to_enc[i] >= 97 ? sym = 'a' : sym = 'A';
			row = (str_to_enc[i] - sym) / 6;
			col = (str_to_enc[i] - sym) % 6;
			if(sym >=97) {
				enc_str[i] = symbs[(row + 3)%6][col];
			} else {
				enc_str[i] = symbs[(row + 3)%6][col] - 32;
			}
		} else {
			enc_str[i] = '0' + (str_to_enc[i] + 1) % '0';
		}
		i++;
	}

	return enc_str;
}

char* Encoder::decrypt(const char *str_to_dec)
{
	int i = 0, len = sizeof(str_to_dec), col, row;
	char *dec_str = new char[len + 1];
	char sym;

	dec_str[len] = 0;
	while(str_to_dec[i] != 0) {
		if(str_to_dec[i] > '9') {
			str_to_dec[i] >= 97 ? sym = 'a' : sym = 'A';
			col = (str_to_dec[i] - sym) / 6;
			row = (str_to_dec[i] - sym) % 6;
			if(sym >= 97) {
				dec_str[i] = symbs[(row + 6 - 3)%6][col];
			} else {
				dec_str[i] = symbs[(row + 6 - 3)%6][col] - 32;
			}
		} else {
			dec_str[i] = '0' + (str_to_dec[i] + '0' - 1) % '0';
		}
		i++;
	}
	cout << "dec:" << dec_str << endl;

	return dec_str;
}
