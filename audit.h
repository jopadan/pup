#ifndef __AUDIT__
#define __AUDIT__

enum auditaction_e
{
	AUDIT_ACTION_ADD    = 0,
	AUDIT_ACTION_REMOVE = 1,
	AUDIT_ACTION_CHANGE = 2,
	AUDIT_ACTION_SIZE   = 3,
};
enum auditstring_e
{
	AUDIT_STRING_8   = 8,
	AUDIT_STRING_32  = 32,
	AUDIT_STRING_256 = 256,
};

typedef enum auditaction_e auditaction_t;
typedef enum auditstring_e auditstring_t;

const char auditaction_string[AUDIT_ACTION_SIZE][AUDIT_STRING_8] = { "Add", "Remove", "Change" };

typedef struct auditentry_s {
	char user[AUDIT_STRING_32];
	time_t timestamp;
	auditaction_t action;
	char path[AUDIT_STRING_256];
	uintmax_t old_size;
	time_t old_timestamp;
	uintmax_t new_size;
	time_t new_timestamp;
} auditentry_t;

#endif

