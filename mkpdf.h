#ifndef __MKPDF_H__
#define __MKPDF_H__

std::vector<std::string>iterate_through(std::string path);
bool mk_pdf(std::vector<std::string> paths,const char * fname,bool type_b);
#endif
