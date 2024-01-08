#include "html_writer.hpp"
#include <iostream>

int main(int argc, char *argv[]) 
{
	html_writer::OpenDocument();
	html_writer::AddTitle("Image Browser");
	html_writer::AddCSSStyle("/home/amarjeet/Project/FastBOW/hw3/src/style.css");
	html_writer::OpenBody();
	html_writer::OpenRow();
	html_writer::AddImage("/home/amarjeet/Project/FastBOW/hw3/src/data/000000.png", 0.96, true);
	html_writer::AddImage("/home/amarjeet/Project/FastBOW/hw3/src/data/000100.png", 0.9);
	html_writer::AddImage("/home/amarjeet/Project/FastBOW/hw3/src/data/000200.png", 0.011);
	html_writer::CloseRow();
	html_writer::OpenRow();
	html_writer::AddImage("/home/amarjeet/Project/FastBOW/hw3/src/data/000300.png", 0.96, true);
	html_writer::AddImage("/home/amarjeet/Project/FastBOW/hw3/src/data/000400.png", 0.9);
	html_writer::AddImage("/home/amarjeet/Project/FastBOW/hw3/src/data/000500.png", 0.011);
	html_writer::CloseRow();
	html_writer::CloseBody();
	html_writer::CloseDocument();	
 	return 0;
}