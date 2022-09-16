
#ifndef __FILEUTILITIES_H__
#define __FILEUTILITIES_H__
//#include "Server.h"

#include <iostream>
#include <fstream>



class FileUtilities {
protected:
	std::ofstream file_w;
	std::ifstream file_r;
public:

	//bool file_open();
	//bool file_close();
	bool file_write(std::string file_name);
	std::string file_read(std::string file_name);
	std::ofstream output_file;

	std::string get_files_names_list();
	bool is_file_exists();

	//bool file_close();

};




#endif