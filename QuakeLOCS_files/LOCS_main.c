#include "LOCS_main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "..\Quake\quakedef.h"

// V1.00 14.02.19 Bartlomiej Duda
// V1.01 19.03.19 Bartlomiej Duda
// V1.02 26.04.19 Bartlomiej Duda

struct lang_line
{
	char  lang_code[10];  // "ENG" by default
	char  lang[50];		  // "English" by default
};

struct parameter_config_line
{
	char var_name[100];   // "LOCS_Enabled" 
	int value;			  // '1'
};


struct loc_line
{
	char identifier[100];
	char loc_text[INT_MAX];
};

struct lang_line line_arr[100]; //max 100 languages
int lang_counter = 0;
char q_glob_current_lang[100];
int q_glob_locs_enabled;




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
	strncpy(new, input + offset, len);
	new[len] = '\0';
	return new;
}


char* str_to_upper(char *input)
{
	int input_len = strlen(input);
	char *new = malloc(sizeof(char)*input_len);
	int i = 0;

	while (*input) 
	{
		*(new+i) = toupper((unsigned char)*input);
		input++;
		i++;

	}
	new[input_len] = '\0';

	return new;
}



char* str_split_and_get_element(char* a_str, char* a_delimeter, int a_position)
{
	char* result_ptr = NULL;
	int counter = 0;


	if (a_position <= 0)
		return (char *)"error_split_010";

	int a_str_len = strlen(a_str);
	char* temp_str = (char*)malloc(a_str_len * sizeof(*temp_str));
	strcpy(temp_str, a_str);


	char *ptr = strtok(temp_str, a_delimeter); //get first element from string

	while (ptr != NULL) //iterating through splitted elements
	{
		if (a_position == 1)
		{
			result_ptr = ptr; //get first element from splitted string
			break;
		}


		counter++;
		ptr = strtok(NULL, a_delimeter);
		result_ptr = ptr;

		if (counter >= a_position - 1)
		{
			break;
		}


	}

	if (ptr == NULL && result_ptr == NULL)
		return (char *)"error_split_020"; //a_position is larger than number of splitted elements
								  //this error also happens if string cannot be splitted (wrong delimeter for example)

	int res_str_len = strlen(result_ptr);
	char* result = (char*)malloc(res_str_len * sizeof(*result));
	strcpy(result, result_ptr);

	//temp_str = NULL;
	//free(temp_str);

	return result;
}





int get_q_global_config()
{
	Con_Printf("Starting get_q_global_config... \n");
	char *path = ".\\LOCS\\locs_config.txt";
	FILE *glob_config_file = fopen(path, "rt");
	int len = 0;
	char *current_section = "";
	int line_counter = 0;
	char line[32000];
	int lang_counter = 0;

	int count_tok1 = 0;
	int count_tok2 = 0;
	char p_delim[] = "=";
	char* ptr_p_delim = p_delim;
	char p_newlineim[] = "\n";
	char* ptr_p_newline = p_newlineim;


	while (fgets(line, sizeof line, glob_config_file) != NULL) 
	{
		line_counter++;
		Con_Printf("Getting line %d: %s \n", line_counter, line);
		if (strstr(line, "[") != NULL && strstr(line, "]") != NULL)
		{
			len = strlen(line);

			line[strcspn(line, "\r\n")] = 0;
			current_section = get_substring(line, 1, len-3);
			Con_Printf("####Current section: %s \n", current_section);

			/*char *cmp1 = str_to_upper(current_section);
			char *cmp2 = str_to_upper("Available langs");

			Con_Printf("####Cmp1: %s\n", cmp1);
			Con_Printf("####Cmp2: %s\n", cmp2);*/


		}

		if (current_section != NULL && current_section != "")
		{
			if (strcmp(str_to_upper(current_section), str_to_upper("Global config")) == 0)
			{
				if (strstr(line, current_section) != NULL) // continue if line contains current section
				{
					continue;
				}
				
				if (strstr(str_to_upper(line), str_to_upper("LOCS_Enabled")) != NULL) // if line contains word "LOCS_Enabled"
				{
					q_glob_locs_enabled = atoi(str_split_and_get_element(str_split_and_get_element(line, ptr_p_delim, 2), ptr_p_newline, 1));

					if (q_glob_locs_enabled == 0)
					{
						Con_Printf("LOCS Disabled. \n");
						return -1;  // LOCS disabled, nothing to do, exiting
					}
					else
					{
						Con_Printf("LOCS Enabled. \n");
					}
						
				}

				if (strstr(str_to_upper(line), str_to_upper("Default_current_lang")) != NULL) // if line contains word "Default_current_lang"
				{
					strcpy(q_glob_current_lang, str_split_and_get_element(str_split_and_get_element(line, ptr_p_delim, 2), ptr_p_newline, 1)); // setting current lang 
				}



			}



			if ( strcmp(str_to_upper(current_section) , str_to_upper("Available langs") ) == 0)
			{
				if (strstr(line, current_section) != NULL) // continue if line contains current section
				{
					continue;
				}


				struct lang_line a, *pa = &a;
				strcpy(a.lang_code, str_split_and_get_element(str_split_and_get_element(line, ptr_p_delim, 1), ptr_p_newline, 1)); //getting lang code from line
				strcpy(a.lang, str_split_and_get_element(str_split_and_get_element(line, ptr_p_delim, 2), ptr_p_newline, 1)); // getting lang from line
				Con_Printf("####lang: %s, lang_code: %s ####\n", a.lang, a.lang_code);
				Con_Printf("###");
				
			}
		}

		

	}


	fclose(glob_config_file);
	return 1;
}


void LOCS_Init()
{
	get_q_global_config();
}

char* get_q__glob_current_lang()
{
	return q_glob_current_lang;
}

void set_q_glob_current_lang(char* input_val)
{
	strcpy(q_glob_current_lang, input_val);
}

int get_q_glob_locs_enabled()
{
	return q_glob_locs_enabled;
}

void set_q_glob_locs_enabled(int input_val)
{
	q_glob_locs_enabled = input_val;
}

char* get_q_text(char *q_identifier, char* input_string)
{
	if (get_q_glob_locs_enabled() == 0)  
		return input_string; //LOCS disabled, return default string

	char* result = "res";


	char *q_lang = "";
	q_lang = get_q__glob_current_lang();

	if (q_lang == "")
	{
		q_lang = "ENG";
	}


	char line[32000];
	char *path = ".\\LOCS\\ENG\\ENG_engine_text.txt";
	FILE *text_file = fopen(path, "rt");


	


	while (fgets(line, sizeof line, text_file) != NULL)
	{
		if (strstr(str_to_upper(line), str_to_upper(q_identifier)) != NULL) // if line contains q_identifier
		{
			char p_delim[] = "=";
			char* ptr_p_delim = p_delim;
			char p_newlineim[] = "\n";
			char* ptr_p_newline = p_newlineim;

			int len = strlen(line);
			result = malloc(sizeof(char) * len);

			strcpy(result, str_split_and_get_element(str_split_and_get_element(line, ptr_p_delim, 2), ptr_p_newline, 1)); //getting text

			fclose(text_file);
			return result;
		}
	}

	fclose(text_file);
	return result;
}