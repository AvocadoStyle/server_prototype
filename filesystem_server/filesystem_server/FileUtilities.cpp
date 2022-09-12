#include "FileUtilities.h"


std::string FileUtilities::file_read(std::string file_name) {
	this->file_r.open(file_name);
	std::string line;
	std::string file_content;
	if (this->file_r.is_open()) {
		while (std::getline(this->file_r, line)) {
			file_content += line;
		}
		this->file_r.close();
	}
	return file_content;
}


bool FileUtilities::file_write(std::string file_name) {
	this->file_w.open(file_name);
	this->file_w << "kaki gadol" << "kaki katan";
	this->file_w.close();
	return 0;
}

int main() {

}