struct info {
	long _type;
	char _txt[256];
};

#define KEY ((key_t)(1234))
#define SEGSIZE sizeof(struct info)