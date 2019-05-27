#ifndef ENCODER_H_SENTRY
#define ENCODER_H_SENTRY

class Encoder {
	char symbs[6][6];
public:
	Encoder();
	char* encrypt(const char *str_to_enc);
	char* decrypt(const char *str_to_dec);
};


#endif
