#include <iostream>
#include "html_writer.hpp"
#include <fmt/core.h>
#include <experimental/filesystem>
#include <algorithm>
#include <string>

using std::cout;
using std::endl;
namespace fs = std::experimental;

namespace index_extension
{
  int findFileName(const std::string& s) 
  {
    std::string temp = s;
    reverse(temp.begin(), temp.end());
    return - temp.size();
  }
} // namespace index_extension

void html_writer::OpenDocument() {
  cout << "<!DOCTYPE html>\n<html>" << endl;  
}

void html_writer::CloseDocument() {
  cout << "</html>" << endl;  
}

void html_writer::AddTitle(const std::string& title) {
  cout << " <title>" << title << "</title>" << endl;
}

void html_writer::AddCSSStyle(const std::string& stylesheet) {
  cout << " <head>" << endl;
  cout << "   <link rel=\"stylesheet\"" <<  " type=\"text/css\"" <<  " href=\"" << stylesheet << "\" />" << endl;
  cout << "</head>" << endl;
}

void html_writer::OpenBody() {
  cout << " <body>" << endl;
}

void html_writer::CloseBody() {
  cout << " <body>" << endl;
}

void html_writer::OpenRow() {
  cout << "     <div class=\"row\">" << endl;
}

void html_writer::CloseRow() {
  cout <<"      </div>" << endl;
}

void html_writer::AddImage(const std::string& img_path, float score, bool highlight) {
  fs::filesystem::path fs_image_path{img_path};
  if (!(fs::filesystem::exists(fs_image_path))) {
    std::cerr << "File not found" << endl;
    exit(EXIT_FAILURE);
  }

  const std::string file_name = fs_image_path.filename();

  if ((file_name.find("jpg") == std::string::npos) && 
        (file_name.find("png") == std::string::npos)) {
    std::cerr << "Invalid Format of Image (not jpg/png)" << endl;
    exit(EXIT_FAILURE);
  }

  if (highlight) {
    cout << "<div class=\"column\" style=\"border: 5px solid green;\">" << endl;
  } 
  else {
    cout << "<div class=\"column\">" << endl;
  } 

  cout << "<h2>" << img_path.substr(img_path.rfind("/") + 1) << "</h2>" << endl; 
  cout << " <img src=\"" << img_path << "\"/>" << endl;
  fmt::print("<p>score = {:.2f}</p>\n", score);
  cout << "</div>" << endl;
}
