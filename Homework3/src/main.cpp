#include "image_browser.hpp"
#include <vector>
#include <string>
#include <array>
#include <tuple>


using image_browser::ScoredImage;
using image_browser::ImageRow;

int main() {
 
    std::string title = "Yifei's Image Browser";
    std::string stylesheet = "tests/web_app/style.css";

   
    ImageRow row1 = {
        ScoredImage{"tests/web_app/data/000000.png", 0.98f},
        ScoredImage{"tests/web_app/data/000100.png", 0.96f},
        ScoredImage{"tests/web_app/data/000200.png", 0.92f}
    };


    ImageRow row2 = {
        ScoredImage{"tests/web_app/data/000300.png", 0.88f},
        ScoredImage{"tests/web_app/data/000400.png", 0.85f},
        ScoredImage{"tests/web_app/data/000500.png", 0.79f}
    };


    ImageRow row3 = {
        ScoredImage{"tests/web_app/data/000600.png", 0.75f},
        ScoredImage{"tests/web_app/data/000700.png", 0.64f},
        ScoredImage{"tests/web_app/data/000800.png", 0.50f}
    };


    std::vector<ImageRow> all_rows = {row1, row2, row3};

    
    image_browser::CreateImageBrowser(title, stylesheet, all_rows);

    return 0;
}