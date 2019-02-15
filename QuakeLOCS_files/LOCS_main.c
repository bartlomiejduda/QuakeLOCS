#include "LOCS_main.h"
#include "quakedef.h"
#include <stdio.h>


// V1.00 14.02.19 Bartlomiej Duda

struct config_global 
{
	char  lang[50];
	char  lang_code[10];
};


void get_q_global_config(FILE *fp)
{
	fp = fopen(".\\LOCS\\locs_config.txt", "rt");

	fclose(fp);
}

void get_q_text(char *q_identifier)
{
	char *q_lang = "";
	// q_lang = get_q_lang();   <--TODO

	if (q_lang == "")
	{
		q_lang = "ENG";
	}

}