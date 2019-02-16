#include "LOCS_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\Quake\quakedef.h"

// V1.00 14.02.19 Bartlomiej Duda

struct lang_line
{
	char  lang_code[10];  // "ENG" by default
	char  lang[50];		  // "English" by default
};

struct loc_line
{
	char identifier[100];
	char loc_text[INT_MAX];
};

struct lang_line line_arr[100]; //max 100 languages
int lang_counter = 0;



/*
static int q_global_handler(void* user, const char* section, const char* name,
	const char* value)
{

#define MATCH(s, n) strcmp(section, s) == 0 && strcmp(name, n) == 0

	if (MATCH("Available langs", name)) 
	{
		*line_arr[lang_counter].lang_code = *name;
		*line_arr[lang_counter].lang = *value;
		lang_counter++;

	}

	else {
		return 0;  /* unknown section/name, error 
	}
	return 1;
}
*/


int starts_with(const char *a, const char *b)
{
	if (strncmp(a, b, strlen(b)) == 0) return 1;
	return 0;
}

char* get_substring(const char* input, int offset, int len)
{
	int input_len = strlen(input);

	if (offset + len > input_len)
	{
		return NULL;
	}

	 char *new = malloc(sizeof(char)*len + 1);
	//*dest = malloc(sizeof(char)*len + 1);

	strncpy(new, input + offset, len);
	new[len] = '\0';
	return new;
}


int get_q_global_config()
{
	Con_Printf("Starting get_q_global_config... \n");
	char *path = ".\\LOCS\\locs_config.txt";
	FILE *glob_config_file = fopen(path, "rt");
	//char * line = NULL;
	int len = 0;
	//ssize_t read;
	char *current_section;
	int line_counter = 0;

	//struct lang_line s_line;


	char line[500]; 
	while (fgets(line, sizeof line, glob_config_file) != NULL) 
	{
		line_counter++;
		Con_Printf("Getting line %d: %s \n", line_counter, line);
		if (strstr(line, "[") != NULL && strstr(line, "]") != NULL)
		{
			//Con_Printf("Getting [[[[[[[ \n");
			len = strlen(line);
			//current_section = "";
			//get_substring(line, current_section, 1, len - 1);
			//printf("Current section: %s", current_section);

			//current_section = strtok(line, "["); // find the first double quote
			//current_section = strtok(NULL, "]");

			current_section = get_substring(line, 1, len-3);



			Con_Printf("####Current section: %s \n", current_section);
			//Con_SafePrintf(
		}
		//printf("%s", line);
	}


	fclose(glob_config_file);
	return 1;
}


void LOCS_Init()
{
	get_q_global_config();
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