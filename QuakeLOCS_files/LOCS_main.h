


// V1.00 14.02.19 Bartlomiej Duda
// V1.01 27.04.19 Bartlomiej Duda


int starts_with(const char *a, const char *b);
char* get_substring(const char* input, int offset, int len);
int get_q_global_config();
void LOCS_Init();
char* get_q_text(char *q_identifier, char* input_string);
char* get_q__glob_current_lang();
void set_q_glob_current_lang(char* input_val);

// global LOCS variables below
extern char q_glob_current_lang[100];
extern int  q_glob_locs_enabled;