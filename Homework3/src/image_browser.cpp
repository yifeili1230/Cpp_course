#include "html_writer.hpp"
#include "image_browser.hpp"


namespace image_browser {
    using ScoredImage = std::tuple<std::string, float>;
    using ImageRow = std::array<ScoredImage, 3>;

    void AddFullRow(const ImageRow& row, bool first_row){
        html_writer::OpenRow();
        for (size_t i = 0; i < row.size(); ++i){
            const auto& [img_path, score] = row[i];
            bool highlight = first_row && (i == 0);
            html_writer::AddImage(img_path, score, highlight);
        }
        html_writer::CloseRow();
    }

    void CreateImageBrowser(const std::string& title, const std::string& stylesheet,
                            const std::vector<ImageRow>& rows){
        html_writer::OpenDocument();
        html_writer::AddTitle(title);
        if (!stylesheet.empty()){
            html_writer::AddCSSStyle(stylesheet);
        }
        html_writer::OpenBody();
        for (size_t i = 0; i < rows.size(); ++i){
            AddFullRow(rows[i], i == 0);
        }
        html_writer::CloseBody();
        html_writer::CloseDocument();
        
    }
}