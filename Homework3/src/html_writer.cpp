#include "html_writer.hpp"
#include <iostream>
#include <iomanip>
#include <experimental/filesystem>
namespace fs = std::experimental::filesystem;

using std::cout;
using std::endl;
using std::string;
using std::cerr;

namespace html_writer {
    void OpenDocument(){
        cout << "<!DOCTYPE html>" << endl;
        cout << "<html>" << endl;
    }

    void CloseDocument(){
        cout << "</html>" << endl;
    }

    void AddCSSStyle(const std::string& stylesheet){
        cout << "<head>" << endl;
        cout << "<link rel=\"stylesheet\" type=\"text/css\" href=\"" << stylesheet << "\">" << endl;
        cout << "</head>" << endl;
    }

    void AddTitle(const std::string& title){
        cout << "<title>" << title << "</title>" << endl;
    }

    void OpenBody(){
        cout << "<body>" << endl;
    }

    void CloseBody(){
        cout << "</body>" << endl;
    }

    void OpenRow(){
        cout << "<div class=\"row\">" << endl;
    }

    void CloseRow(){
        cout << "</div>" << endl;
    }

    void AddImage(const std::string& img_path, float score, bool highlight){
        fs::path path(img_path);
        string filename = path.filename().string();
        string extension = path.extension().string();
        if (extension != ".jpg" && extension != ".png"){
            cerr << "Error: Unsupported file format for image: " << img_path << endl;
            return;
        }


        std::ostringstream score_stream;
        score_stream << std::fixed << std::setprecision(2) << score;
        string formatted_score = score_stream.str(); 

        if (highlight){
            cout << "<div class=\"column\" style=\"border: 5px solid green;\">" << endl;
        } else {
            cout << "<div class=\"column\">" << endl;
        }

        cout << "<h2>" << filename << "</h2>" << endl;
        cout << "<img src= \"" << img_path << "\" />" << endl;
        cout << "<p>score = " << formatted_score << "</p>" << endl;
        cout << "</div>" << endl;

    }


}