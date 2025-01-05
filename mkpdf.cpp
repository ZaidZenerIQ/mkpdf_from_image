#include <iostream>
#include <filesystem>
#include <opencv2/opencv.hpp>
#include <hpdf.h>
#include <vector>

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

std::vector<std::string>iterate_through(std::string path){	
	cv::Mat temp;
	std::vector <std::string> path_imgs;
	for (const auto& dirEntry : recursive_directory_iterator(path)){
	     std::filesystem::path path{dirEntry};
	     std::string path_string{path.string()};
	     temp = cv::imread(path_string);
	     if(temp.cols > 0){
			path_imgs.push_back(path_string);
			/*std::cout << path_string << '\n';*/
		}
	}
	return path_imgs;
}

bool mk_pdf(std::vector<std::string> paths,const char * fname,bool type_b){
	if(paths.size() <= 0) return false;
 	HPDF_Doc pdf = HPDF_New(nullptr, nullptr);
	if (!pdf) {
        std::cerr << "Error: Unable to create PDF document." << std::endl;
 	       return false;;
    	}
	HPDF_Image image;
	for(std::string path : paths){
		std::cout << "add page for " << path << '\n';
		HPDF_Page page = HPDF_AddPage(pdf);
		HPDF_Page_SetSize(page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);
		if(type_b)image = HPDF_LoadJpegImageFromFile(pdf,path.c_str());
		else image = HPDF_LoadPngImageFromFile(pdf,path.c_str());
		float image_width = HPDF_Image_GetWidth(image);
	        float image_height = HPDF_Image_GetHeight(image);
		float page_width = HPDF_Page_GetWidth(page);
		float page_height = HPDF_Page_GetHeight(page);
		float scale = std::min(page_width / image_width, page_height / image_height);
		float x = (page_width - image_width * scale) / 2;
		float y = (page_height - image_height * scale) / 2;
		HPDF_Page_DrawImage(page, image, x, y, image_width * scale, image_height * scale);
	}
	HPDF_SaveToFile(pdf, fname);
	HPDF_Free(pdf);
	return true;
}
