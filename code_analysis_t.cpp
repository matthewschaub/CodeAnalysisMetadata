/*
  @file code_analysis_t.cpp

  Test program for analysis requests
*/

#include "code_analysis.hpp"

#include <string>
#include <cassert>

int main() {

    // all parts of the request are empty
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }
    //filename is explicitly defined
    //case overlap added language test
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "main.cpp";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "main.cpp");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "C++");
        assert(code_analysis(request) == false);
    }
    //given_filename is name on the disk
    {
        analysis_request request;
        request.given_filename  = "main.cpp";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "main.cpp");
        assert(request.given_filename == "main.cpp");
        assert(request.entry_filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "C++");
        assert(code_analysis(request) == false);
    }
    //given_filename is source code archive
    {
        analysis_request request;
        request.given_filename  = "project.tar.gz";
        request.entry_filename  = "different.tar.gz";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "different.tar.gz");
        assert(request.given_filename == "project.tar.gz");
        assert(request.entry_filename == "different.tar.gz");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }
    //entry_filename is data
    {
        analysis_request request;
        request.given_filename  = "main.cpp";
        request.entry_filename  = "data";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "main.cpp");
        assert(request.given_filename == "main.cpp");
        assert(request.entry_filename == "data");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "C++");
        assert(code_analysis(request) == false);
    }
    // option url precedence
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "www.google.com";
        request.option_filename = "";
        request.option_url      = "www.facebook.com";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "www.facebook.com");
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }
    // given url test
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "www.google.com";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "www.google.com");
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }
    //language option precedence test
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "C++";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "C++");
        assert(code_analysis(request) == false);
    }
    //filename from std in 
    {
        analysis_request request;
        request.given_filename  = "-";
        request.entry_filename  = "data";
        request.given_url       = "";
        request.option_filename = "main.cpp";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "main.cpp");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "C++");
        assert(code_analysis(request) == false);
    }
    //filename from std in 
    {
        analysis_request request;
        request.given_filename  = "-";
        request.entry_filename  = "data";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        assert(filename == "");
        assert(analysis_url(request) == "");
        assert(analysis_language(request, filename) == "");
        assert(code_analysis(request) == false);
    }
    //test for extension not supported error
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "";

        auto filename = analysis_filename(request);
        auto language = analysis_language(request, filename);
        assert(filename == "");
        assert(analysis_language(request, filename) == "");
        assert(extSupport(language) == false);
        assert(code_analysis(request) == false);
    }
    //test when extension defined 
    {
        analysis_request request;
        request.given_filename  = "";
        request.entry_filename  = "";
        request.given_url       = "";
        request.option_filename = "";
        request.option_url      = "";
        request.option_language = "C++";

        auto filename = analysis_filename(request);
        auto language = analysis_language(request, filename);
        assert(filename == "");
        assert(analysis_language(request, filename) == "C++");
        assert(extSupport(language) == true);
        assert(code_analysis(request) == false);
    }



    return 0;
}
