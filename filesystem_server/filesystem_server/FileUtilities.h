#ifndef __FILEUTILITIES_H__
#define __FILEUTILITIES_H__
#define _CRT_SECURE_NO_WARNINGS 1
//#include "Server.h"

#include <iostream>
#include <fstream>
#include <string>
#include <direct.h>
#include <filesystem>
#define MAIN_REPO_PATH "C:\\backupsvr"
#define RAND_NAME_TO_LIST "list.info"
class FileUtilities {
public:
	std::ofstream file_w;
	std::ifstream file_r;

	bool file_write(std::string file_name, int user_id_path, std::string content);
	std::string file_read(std::string file_name, int user_id_path);
	int create_directory(std::string path);
	bool is_file_exists();

	std::string get_list_info_content(int user_id_path);
	void set_list_info_content(int user_id_path, std::string content);









	/* helpers - utilities */
	bool is_file_exists(std::string filename);
	char* __string_to_char(std::string s);
	std::string __char_to_string(char* c);
};




#endif