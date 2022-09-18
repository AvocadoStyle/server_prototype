#include "FileUtilities.h"


std::string FileUtilities::file_read(std::string file_name, int user_id_path) {
	std::string user_id_path_st = "\\" + std::to_string(user_id_path) + "\\";
	std::string path_to_file = MAIN_REPO_PATH + user_id_path_st;
	std::string path_with_filename = path_to_file + file_name;
	this->file_r.open(path_with_filename);
	std::string line;
	std::string file_content;
	while (std::getline(this->file_r, line)) {
		file_content += line;
		file_content += '\n';
	}
		this->file_r.close();
	return file_content;
}

bool FileUtilities::file_write(std::string file_name, int user_id_path, std::string content) {
	std::string user_id_path_st = "\\" + std::to_string(user_id_path) + "\\";
	std::string path_to_file = MAIN_REPO_PATH + user_id_path_st;
	this->create_directory(path_to_file);
	std::string path_with_filename = path_to_file + file_name;
	std::cout << path_with_filename << std::endl;
	this->file_w.open(path_with_filename);
	this->file_w << content;
	this->file_w.close();
	return true;
}

int FileUtilities::create_directory(std::string path) {
	char* ch_path = this->__string_to_char(path);
	return _mkdir(ch_path); // -1 already exists        // 0 new
}

std::string FileUtilities::get_list_info_content(int user_id_path) {
	return this->file_read(RAND_NAME_TO_LIST, user_id_path);
}

void FileUtilities::set_list_info_content(int user_id_path, std::string content_file) {
	std::string content = this->get_list_info_content(user_id_path);
	content_file += '\n';
	content += content_file;
	this->file_write(RAND_NAME_TO_LIST, user_id_path, content);
}

bool FileUtilities::is_file_exists(std::string filename) {
	std::ifstream f(filename.c_str());
	if (FILE* fp = fopen(this->__string_to_char(filename), "r")) {
		fclose(fp);
		return true;
	}
	return false;
}











char* FileUtilities::__string_to_char(std::string s) {
	int n = s.length() + 1;
	// declaring character array
	char* char_array = (char*)malloc(n);
	// copying the contents of the
	// string to char array
	strcpy(char_array, s.c_str());
	return char_array;
}


std::string FileUtilities::__char_to_string(char* c) {
	return std::string(c);
}
