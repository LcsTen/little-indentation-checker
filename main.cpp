#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <cstring>

enum class Mode {
	TAB,
	TAB_STRICT,
	SPACES
};

enum class ErrCode {
	OK = 0,
	NOT_OK = 1,
	ERROR = 2
};

Mode mode = Mode::TAB;

bool check(std::ifstream& stream, std::vector<int>& errors_list){
	bool ok = true;
	int line_nb = 1;
	std::string line;
	while(getline(stream, line)){
		bool has_tabs = false;
		int total_spaces = 0;
		int final_spaces = 0;
		for(size_t i = 0;i < line.size();i++){
			if(line[i] == '\t'){
				has_tabs = true;
				final_spaces = 0;
			}else if(line[i] == ' '){
				total_spaces++;
				final_spaces++;
			}else{
				break;
			}
		}
		bool line_ok;
		if(mode == Mode::TAB){
			line_ok = (total_spaces == final_spaces
				   && final_spaces < 8);
		}else if(mode == Mode::TAB_STRICT){
			line_ok = (total_spaces == 0);
		}else if(mode == Mode::SPACES){
			line_ok = !has_tabs;
		}
		if(!line_ok){
			errors_list.push_back(line_nb);
		}
		ok &= line_ok;
		line_nb++;
	}
	return ok;
}

int main(int argc,char** argv){
	int i = 1;
	for(;i < argc;i++){
		if(!strcmp(argv[i], "--tab")){
			mode = Mode::TAB;
		}else if(!strcmp(argv[i], "--tab-strict")){
			mode = Mode::TAB_STRICT;
		}else if(!strcmp(argv[i], "--spaces")){
			mode = Mode::SPACES;
		}else if(!strcmp(argv[i], "--")){
			i++;
			break;
		}else{
			break;
		}
	}
	std::map<std::string, std::vector<int>> files;
	int errcode = 0;
	for(;i < argc;i++){
		std::ifstream stream(argv[i], std::ios::in);
		if(stream.is_open()){
			std::vector<int> errors;
			bool ok = check(stream, errors);
			if(!ok){
				errcode = std::max(errcode,
						   (int)ErrCode::NOT_OK);
			}
			files[argv[i]] = errors;
		}else{
			std::cerr << "Error: Can't open file " << argv[i] << "."
				  << std::endl;
			errcode = std::max(errcode, (int)ErrCode::ERROR);
		}
	}
	if(files.empty()){
		std::cout << "No input files." << std::endl;
	}else{
		std::cout << "Summary:" << std::endl;
	}
	for(std::pair<std::string, std::vector<int>> file : files){
		if(file.second.empty()){
			std::cout << file.first << ": OK" << std::endl;
		}else{
			std::cout << file.first << ": " << file.second.size()
				  << " errors" << std::endl;
			for(int line_nb : file.second){
				std::cout << " - " << line_nb << std::endl;
			}
		}
	}
	return errcode;
}
