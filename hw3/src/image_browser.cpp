#include "image_browser.hpp"


void image_browser::AddFullRow(const ImageRow& row, bool first_row){
    for(int i = 0; i < 3; i++){
        if (i != 0 && first_row) first_row = false;
        html_writer::AddImage(std::get<0>(row[i]), std::get<1>(row[i]), first_row);
    }
}
void image_browser::CreateImageBrowser(const std::string& title, const std::string& stylesheet,
    const std::vector<ImageRow>& rows) {
    html_writer::OpenDocument();
    html_writer::AddTitle(title);
    html_writer::AddCSSStyle(stylesheet);
    html_writer::OpenBody();
    html_writer::OpenRow();
    size_t num_rows = rows.size();
    for(size_t i = 0; i < num_rows; i++)
        AddFullRow(rows[i], i == 0);
    html_writer::CloseRow();
    html_writer::CloseBody();
    html_writer::CloseDocument();
}
