#include <iostream>
#include <vector>
#include "mkpdf.h"

int main(int argc,char **argv){
	std::string source_file;
	std::string output_file;
	std::string type;
	bool type_b;
	std::cout<<"source file: ";
	std::cin >> source_file;
	std::cout<<"0-Png/1-Jpeg: ";
	std::cin >> type;
	std::cout<<"output file: ";
	std::cin >> output_file;
	std::cout<<"wait...\n";
	type_b = atoi(type.c_str());
	std::vector paths = iterate_through(source_file);
	bool state = mk_pdf(paths,output_file.c_str(),type_b);
	if(!state)return 1;
	std::cout<<"press <ctrl>+<c> to close\n";
	short x;
	std::cin >> x;
	return 0;
}
