#include <fstream>
#include <iostream>
#include "image_browser.hpp"
#include <tuple>


int main(int argc, char *argv[]) {
  const std::string stylesheet{"style.css"};
  const std::string title{"Image Browser"};
  
  image_browser::ScoredImage image;
  image_browser::ImageRow image_row;
  std::vector<image_browser::ImageRow> images;
  std::ifstream fin("/home/amarjeet/Project/FastBOW/hw3/src/config.txt");
  std::string path;
  float score;
  size_t i = 0; 
  while (fin >> path >> score) 
  {
    image_row[i++] = make_tuple(path,score);
    if (i == 3) {
      i = 0; 
      images.push_back(image_row);
    }
  } 

  image_browser::CreateImageBrowser(title, stylesheet,images);
  return 0;
}
