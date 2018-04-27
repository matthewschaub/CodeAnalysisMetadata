
# matthewschaub

## Files
% ls

    Makefile
    README.md
    analysis_request.hpp
    code_analysis.cpp
    code_analysis.hpp
    code_analysis_t.cpp
    get_language_from_filename.cpp
    get_language_from_filename.hpp
    get_language_from_filename_t.cpp

## Changed files
% git diff baa2b2fa58cb52ada94597a9b2e5d687f6a3261f --name-only

    code_analysis.cpp
    code_analysis.hpp
    code_analysis_t.cpp

## Build
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

## Test
% make test

    ./code_analysis_t
    Extension not supported
    Extension not supported
    Extension not supported
    Extension not supported
    Extension not supported
    Using stdin requires a declared language
    Extension not supported
    Extension not supported
    Using stdin requires a declared language

## Test Oracle: code\_analysis\_t.cpp
% cp ~collard/CodeAnalysisMetadataEvaluation/code_analysis_t.cpp .  
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

% make test

    ./code_analysis_t
    Extension not supported
    ./code_analysis_t: code_analysis_t.cpp:62: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:78: main Check `analysis_language(request, filename) == "C++"' failed.
    Extension not supported
    ./code_analysis_t: code_analysis_t.cpp:79: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:96: main Check `code_analysis(request) == true' failed.
    Extension not supported
    Using stdin requires a declared language
    ./code_analysis_t: code_analysis_t.cpp:130: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:144: main Check `filename == "foo.cpp"' failed.
    ./code_analysis_t: code_analysis_t.cpp:146: main Check `analysis_language(request, filename) == "C++"' failed.
    Extension not supported
    Using stdin requires a declared language
    ./code_analysis_t: code_analysis_t.cpp:147: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:161: main Check `filename == "foo.cpp"' failed.
    ./code_analysis_t: code_analysis_t.cpp:163: main Check `analysis_language(request, filename) == "C++"' failed.
    Extension not supported
    Using stdin requires a declared language
    ./code_analysis_t: code_analysis_t.cpp:164: main Check `code_analysis(request) == true' failed.
    ./code_analysis_t: code_analysis_t.cpp:178: main Check `filename == "foo.cpp"' failed.
    ./code_analysis_t: code_analysis_t.cpp:180: main Check `analysis_language(request, filename) == "C++"' failed.
    Extension not supported
    Using stdin requires a declared language
    ./code_analysis_t: code_analysis_t.cpp:181: main Check `code_analysis(request) == true' failed.

## Test Oracle: code\_analysis.cpp
% cp ~collard/CodeAnalysisMetadataEvaluation/code_analysis.cpp  .  
% make

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ -std=c++11 -c get_language_from_filename.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    Undefined symbols for architecture x86_64:
      "extSupport(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&)", referenced from:
          _main in code_analysis_t.o
      "langSupport(analysis_request const&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&)", referenced from:
          _main in code_analysis_t.o
    ld: symbol(s) not found for architecture x86_64
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
    make: *** [code_analysis_t] Error 1

% make test

    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    Undefined symbols for architecture x86_64:
      "extSupport(std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&)", referenced from:
          _main in code_analysis_t.o
      "langSupport(analysis_request const&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&)", referenced from:
          _main in code_analysis_t.o
    ld: symbol(s) not found for architecture x86_64
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
    make: *** [code_analysis_t] Error 1

## Code
% srcml code_analysis.cpp code_analysis_t.cpp -o project.xml
% srcml --xpath="//src:function[src:name='code_analysis']" project.xml | srcml | cat -v

    bool code_analysis(const analysis_request& request) {
    
        auto filename = analysis_filename(request);
    
        auto url = analysis_url(request);
    
        auto language = analysis_language(request, filename);
    
        // code analysis processing that is not yet implemented
        if(!extSupport(language))
          std::cerr << "Extension not supported\n"; 
    
        if(!langSupport(request, language))
          std::cerr << "Using stdin requires a declared language\n";
    
        
        return false;
    }

% srcml --xpath="//src:function[src:name='analysis_filename']" project.xml | srcml | cat -v

    std::string analysis_filename(const analysis_request& request) {
    
        if(request.option_filename != "")
        {
          return request.option_filename;
        }
        else if(request.given_filename != "")
        {
          if(request.given_filename == "-")
            //throw error for stdin requires a declared language
            //********************************************************
            return ""; 
          else if(get_language_from_filename(request.given_filename) == "")
            return request.entry_filename; 
          return request.given_filename; 
        }
        else 
          return "";
    }

% srcml --xpath="//src:function[src:name='analysis_url']" project.xml | srcml | cat -v

    std::string analysis_url(const analysis_request& request) {
    
        if(request.option_url != "")
          return request.option_url;
        else if(request.given_url != "") 
          return request.given_url; 
        else
          return ""; 
    }

% srcml --xpath="//src:function[src:name='analysis_language']" project.xml | srcml | cat -v

    std::string analysis_language(const analysis_request& request, const std::string& filename) {
    
        if(request.option_language != "")
          //good place for extension not supported error handling
          //******************************************************
          return request.option_language; 
        else if(request.option_filename != "")
          return get_language_from_filename(request.option_filename);
        else if(request.given_filename != "") 
        {
          if(get_language_from_filename(request.given_filename) != "")
            return get_language_from_filename(request.given_filename);
        }
    
        return "";
    }

## Test Cases 
% srcml code_analysis_t.cpp --xpath="//src:function[src:name='main']/src:block" | srcml | cat -v

    {
    
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
        //test for stdin requires declared language
        {
            analysis_request request;
            request.given_filename  = "-";
            request.entry_filename  = "data";
            request.given_url       = "";
            request.option_filename = "";
            request.option_url      = "";
            request.option_language = "";
    
            auto filename = analysis_filename(request);
            auto language = analysis_language(request, filename);
            assert(filename == "");
            assert(analysis_language(request, filename) == "");
            assert(langSupport(request,language) == false);
            assert(code_analysis(request) == false);
        }
        //test for stdin requires declared language true case
        {
            analysis_request request;
            request.given_filename  = "-";
            request.entry_filename  = "data";
            request.given_url       = "";
            request.option_filename = "main.cpp";
            request.option_url      = "";
            request.option_language = "";
    
            auto filename = analysis_filename(request);
            auto language = analysis_language(request, filename);
            assert(filename == "main.cpp");
            assert(analysis_language(request, filename) == "C++");
            assert(langSupport(request,language) == true);
            assert(code_analysis(request) == false);
        }
    
    
    
    
        return 0;
    }

## Literal Values used in Testing
% srcml code\_analysis_t.cpp --xpath="//src:literal" | srcml | tr '\0' '\n' |grep '"' | sort -u | tr '\n' ','

    "-" "C++" "data" "different.tar.gz" "main.cpp" "project.tar.gz" 
    "www.facebook.com" "www.google.com" 

## Error Messages
% srcml code_analysis.cpp --xpath="//src:function[src:name='code_analysis']//src:expr[contains(., 'cerr')]//src:literal" | srcml | tr '\0'  '\n'

    "Extension not supported\n"
    "Using stdin requires a declared language\n"

## Commits

### Commit cd5680
% git checkout -q cd5680  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    g++ -std=c++11 -c get_language_from_filename_t.cpp
    g++ get_language_from_filename_t.o get_language_from_filename.o -o get_language_from_filename_t

% git show

    commit cd56804cf36fea8fbadde6eeb6ea6c2258c3c071
    Author: Matthew Schaub <mes100@zips.uakron.edu>
    Date:   Sun Apr 1 16:06:38 2018 -0400
    
        "added my name"
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index b874829..fee600f 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -1,4 +1,5 @@
     /*
    +  Matthew Schaub
       @file code_analysis.cpp
     
       Implementation of analysis requests

### Commit e552f9
% git checkout -q e552f9  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit e552f9b6221147d92eb480e5e8aa5682a6af97e2
    Author: Schaub <mes100@ules-imac-09.uanet.edu>
    Date:   Sun Apr 1 20:17:17 2018 -0400
    
        added case for explicitly given filename
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 820446d..dfb5230 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -28,5 +28,21 @@ int main() {
             assert(code_analysis(request) == false);
         }
     
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = request.option_filename;
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
    +
         return 0;
     }

### Commit 8d56a3
% git checkout -q 8d56a3  
% make  

    make: Nothing to be done for `all'.

% git show

    commit 8d56a3dca775933889f3020306fb32a02780b872
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Sun Apr 1 22:16:01 2018 -0400
    
        fails explicitly defined test
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index dfb5230..dcfc19a 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -27,22 +27,24 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -
    +    //filename is explicitly defined
         {
             analysis_request request;
             request.given_filename  = "";
             request.entry_filename  = "";
             request.given_url       = "";
    -        request.option_filename = "";
    +        request.option_filename = "main.cpp";
             request.option_url      = "";
             request.option_language = "";
     
    -        auto filename = request.option_filename;
    -        assert(filename == "");
    +        auto filename = analysis_filename(request);
    +        assert(filename == "main.cpp");
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    //given_filename is the name on the disk
    +
     
         return 0;
     }

### Commit 4e4714
% git checkout -q 4e4714  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 4e471463d0cb10bf883767a56a1ce2b4951272ed
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Sun Apr 1 22:20:02 2018 -0400
    
        Passes 'filename explicitly defined' test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index fee600f..c0c17b5 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -34,7 +34,10 @@ bool code_analysis(const analysis_request& request) {
      */
     std::string analysis_filename(const analysis_request& request) {
     
    -    return "";
    +    if(request.option_filename != "")
    +      return request.option_filename; 
    +    else
    +      return "";
     }
     
     /** URL extracted from the request

### Commit 39d04f
% git checkout -q 39d04f  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 39d04f9587066c37b1586e07ee1160d5eee76aaf
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Sun Apr 1 22:47:03 2018 -0400
    
        fails given_filename is name on disk
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index dcfc19a..fd0ebe9 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -43,7 +43,24 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -    //given_filename is the name on the disk
    +    //given_filename is name on the disk
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "project.tar.gz";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "main.cpp");
    +        assert(request.given_filename == "project.tar.gz");
    +        assert(request.entry_filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
     
     
         return 0;

### Commit d9b341
% git checkout -q d9b341  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit d9b341a423fdb5aa8bbe8ffab1f76549fe970bfb
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Sun Apr 1 23:04:00 2018 -0400
    
        Passes 'given_filename is name on disk' test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index c0c17b5..b74a91f 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -35,8 +35,14 @@ bool code_analysis(const analysis_request& request) {
     std::string analysis_filename(const analysis_request& request) {
     
         if(request.option_filename != "")
    -      return request.option_filename; 
    -    else
    +    {
    +      return request.option_filename;
    +    }
    +    else if(request.given_filename != "")
    +    {
    +      return request.given_filename; 
    +    }
    +    else 
           return "";
     }
     
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index fd0ebe9..8116c24 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -46,15 +46,15 @@ int main() {
         //given_filename is name on the disk
         {
             analysis_request request;
    -        request.given_filename  = "";
    +        request.given_filename  = "project.tar.gz";
             request.entry_filename  = "";
             request.given_url       = "";
    -        request.option_filename = "project.tar.gz";
    +        request.option_filename = "";
             request.option_url      = "";
             request.option_language = "";
     
             auto filename = analysis_filename(request);
    -        assert(filename == "main.cpp");
    +        assert(filename == "project.tar.gz");
             assert(request.given_filename == "project.tar.gz");
             assert(request.entry_filename == "");
             assert(analysis_url(request) == "");

### Commit e6a1f5
% git checkout -q e6a1f5  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit e6a1f5b0a05e583e8f410d7d2790f387fc79ee8e
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Sun Apr 1 23:25:50 2018 -0400
    
        fails 'given_filename is source code archive' test
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 8116c24..3c8a539 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -46,7 +46,7 @@ int main() {
         //given_filename is name on the disk
         {
             analysis_request request;
    -        request.given_filename  = "project.tar.gz";
    +        request.given_filename  = "main.cpp";
             request.entry_filename  = "";
             request.given_url       = "";
             request.option_filename = "";
    @@ -54,13 +54,31 @@ int main() {
             request.option_language = "";
     
             auto filename = analysis_filename(request);
    -        assert(filename == "project.tar.gz");
    -        assert(request.given_filename == "project.tar.gz");
    +        assert(filename == "main.cpp");
    +        assert(request.given_filename == "main.cpp");
             assert(request.entry_filename == "");
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    //given_filename is source code
    +    {
    +        analysis_request request;
    +        request.given_filename  = "project.tar.gz";
    +        request.entry_filename  = "different.tar.gz";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "different.tar.gz");
    +        assert(request.given_filename == "");
    +        assert(request.entry_filename == "project.tar.gz");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
     
     
         return 0;

### Commit 805e14
% git checkout -q 805e14  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 805e1489a16733e92bf8c6b62e69f8de3b755589
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 00:25:52 2018 -0400
    
        Passed given_filename is a sourcecode archive test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index b74a91f..82765dd 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -40,6 +40,8 @@ std::string analysis_filename(const analysis_request& request) {
         }
         else if(request.given_filename != "")
         {
    +      if(get_language_from_filename(request.given_filename) == "")
    +        return request.entry_filename; 
           return request.given_filename; 
         }
         else 
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 3c8a539..1a7b237 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -61,7 +61,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    -    //given_filename is source code
    +    //given_filename is source code archive
         {
             analysis_request request;
             request.given_filename  = "project.tar.gz";
    @@ -73,8 +73,8 @@ int main() {
     
             auto filename = analysis_filename(request);
             assert(filename == "different.tar.gz");
    -        assert(request.given_filename == "");
    -        assert(request.entry_filename == "project.tar.gz");
    +        assert(request.given_filename == "project.tar.gz");
    +        assert(request.entry_filename == "different.tar.gz");
             assert(analysis_url(request) == "");
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);

### Commit 3a3a1b
% git checkout -q 3a3a1b  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 3a3a1b6089c1c2bb1e3341bbd8d29e547c97dce3
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:07:45 2018 -0400
    
        existing code passes conditional tests for data file name
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 1a7b237..6b0e113 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -79,6 +79,24 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    //entry_filename is data
    +    {
    +        analysis_request request;
    +        request.given_filename  = "main.cpp";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "main.cpp");
    +        assert(request.given_filename == "main.cpp");
    +        assert(request.entry_filename == "data");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
     
     
         return 0;

### Commit eb799b
% git checkout -q eb799b  
% make  

    make: Nothing to be done for `all'.

% git show

    commit eb799baaea425364fa7d8432eb65544e7c1b443a
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:18:14 2018 -0400
    
        fails 'option url precedence' test
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 6b0e113..b739b82 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -97,6 +97,22 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    // option url precedence
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "www.google.com";
    +        request.option_filename = "";
    +        request.option_url      = "www.facebook.com";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "www.facebook.com");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
     
     
         return 0;

### Commit 08dee2
% git checkout -q 08dee2  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 08dee2f50549f93a9c25c428567ab954ef62880a
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:21:04 2018 -0400
    
        passes url precedence test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 82765dd..0152741 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -54,7 +54,12 @@ std::string analysis_filename(const analysis_request& request) {
      */
     std::string analysis_url(const analysis_request& request) {
     
    -    return "";
    +    if(request.option_url != "")
    +      return request.option_url;
    +    else if(request.given_url != "") 
    +      return request.given_url; 
    +    else
    +      return ""; 
     }
     
     /** Language extracted from the request and the filename

### Commit d360e0
% git checkout -q d360e0  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit d360e011930774601ced02d1d17ed7b5b9245e6f
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:23:27 2018 -0400
    
        passes given url test from existing coding
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index b739b82..42041a6 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -113,6 +113,22 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    // given url test
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "www.google.com";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "www.google.com");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
     
     
         return 0;

### Commit 58b324
% git checkout -q 58b324  
% make  

    make: Nothing to be done for `all'.

% git show

    commit 58b324fd6ac4f160ac237d579f1c8628cde19dbc
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:27:44 2018 -0400
    
        fails option_language test
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 42041a6..bd73ca9 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -129,6 +129,21 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "C++";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "C++");
    +        assert(code_analysis(request) == false);
    +    }
     
     
         return 0;

### Commit cba6b2
% git checkout -q cba6b2  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit cba6b27e78ac527d47b93cc54a35511addcf551f
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:31:40 2018 -0400
    
        passes language precedence test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 0152741..8372c5b 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -69,5 +69,8 @@ std::string analysis_url(const analysis_request& request) {
      */
     std::string analysis_language(const analysis_request& request, const std::string& filename) {
     
    +    if(request.option_language != "")
    +      //good place for extension not supported error handling
    +      return request.option_language; 
         return "";
     }

### Commit 806b66
% git checkout -q 806b66  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 806b66d687dada58b4ab26eb8d4d63905613f3ac
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:37:30 2018 -0400
    
        fails language from file test
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index bd73ca9..383aac4 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -129,6 +129,7 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    //language option precedence test
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -144,6 +145,23 @@ int main() {
             assert(analysis_language(request, filename) == "C++");
             assert(code_analysis(request) == false);
         }
    +    //language from file
    +    {
    +        analysis_request request;
    +        request.given_filename  = "main.cpp";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "C++");
    +        assert(code_analysis(request) == false);
    +    }
    +
     
     
         return 0;

### Commit a9c2b0
% git checkout -q a9c2b0  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit a9c2b05d75bf10581ca7944bfa544c8984afe872
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:46:35 2018 -0400
    
        passes language from option file test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 8372c5b..83251a3 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -72,5 +72,7 @@ std::string analysis_language(const analysis_request& request, const std::string
         if(request.option_language != "")
           //good place for extension not supported error handling
           return request.option_language; 
    +    else if(request.option_filename != "")
    +      return get_language_from_filename(request.option_filename); 
         return "";
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 383aac4..b4654f0 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -28,6 +28,7 @@ int main() {
             assert(code_analysis(request) == false);
         }
         //filename is explicitly defined
    +    //case overlap added language test
         {
             analysis_request request;
             request.given_filename  = "";
    @@ -40,7 +41,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "main.cpp");
             assert(analysis_url(request) == "");
    -        assert(analysis_language(request, filename) == "");
    +        assert(analysis_language(request, filename) == "C++");
             assert(code_analysis(request) == false);
         }
         //given_filename is name on the disk
    @@ -145,23 +146,6 @@ int main() {
             assert(analysis_language(request, filename) == "C++");
             assert(code_analysis(request) == false);
         }
    -    //language from file
    -    {
    -        analysis_request request;
    -        request.given_filename  = "main.cpp";
    -        request.entry_filename  = "";
    -        request.given_url       = "";
    -        request.option_filename = "";
    -        request.option_url      = "";
    -        request.option_language = "";
    -
    -        auto filename = analysis_filename(request);
    -        assert(filename == "");
    -        assert(analysis_url(request) == "");
    -        assert(analysis_language(request, filename) == "C++");
    -        assert(code_analysis(request) == false);
    -    }
    -
     
     
         return 0;

### Commit 48c770
% git checkout -q 48c770  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 48c770c31397f7e71870cb6fc216e80dda8538c5
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 01:58:56 2018 -0400
    
        fails to determine language from .given_filename
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index b4654f0..0fba0e2 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -59,7 +59,7 @@ int main() {
             assert(request.given_filename == "main.cpp");
             assert(request.entry_filename == "");
             assert(analysis_url(request) == "");
    -        assert(analysis_language(request, filename) == "");
    +        assert(analysis_language(request, filename) == "C++");
             assert(code_analysis(request) == false);
         }
         //given_filename is source code archive

### Commit 98aa9c
% git checkout -q 98aa9c  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 98aa9c9f3e05b6e55fa655c129bdf4d8540ee579
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 02:04:10 2018 -0400
    
        passes analysis language from .option_filename
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 83251a3..a6fabfd 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -73,6 +73,12 @@ std::string analysis_language(const analysis_request& request, const std::string
           //good place for extension not supported error handling
           return request.option_language; 
         else if(request.option_filename != "")
    -      return get_language_from_filename(request.option_filename); 
    +      return get_language_from_filename(request.option_filename);
    +    else if(request.given_filename != "") 
    +    {
    +      if(get_language_from_filename(request.given_filename) != "")
    +        return get_language_from_filename(request.given_filename);
    +    }
    +
         return "";
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 0fba0e2..8eb7936 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -95,7 +95,7 @@ int main() {
             assert(request.given_filename == "main.cpp");
             assert(request.entry_filename == "data");
             assert(analysis_url(request) == "");
    -        assert(analysis_language(request, filename) == "");
    +        assert(analysis_language(request, filename) == "C++");
             assert(code_analysis(request) == false);
         }
         // option url precedence

### Commit 675107
% git checkout -q 675107  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 67510746a0832498c87a939086a5d782e3a432c1
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Mon Apr 2 02:17:47 2018 -0400
    
        fails filename from std in test
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 8eb7936..7245d60 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -146,6 +146,38 @@ int main() {
             assert(analysis_language(request, filename) == "C++");
             assert(code_analysis(request) == false);
         }
    +    //filename from std in 
    +    {
    +        analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "main.cpp";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "main.cpp");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "C++");
    +        assert(code_analysis(request) == false);
    +    }
    +    //filename from std in 
    +    {
    +        analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(analysis_url(request) == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(code_analysis(request) == false);
    +    }
     
     
         return 0;

### Commit 15aecb
% git checkout -q 15aecb  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 15aecbe35400f1b1816c04253908530955089592
    Author: Schaub <mes100@ules-imac-08.uanet.edu>
    Date:   Mon Apr 2 11:29:11 2018 -0400
    
        Passes std in filename test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index a6fabfd..885f740 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -40,7 +40,9 @@ std::string analysis_filename(const analysis_request& request) {
         }
         else if(request.given_filename != "")
         {
    -      if(get_language_from_filename(request.given_filename) == "")
    +      if(request.given_filename == "-")
    +        return ""; 
    +      else if(get_language_from_filename(request.given_filename) == "")
             return request.entry_filename; 
           return request.given_filename; 
         }

### Commit 181546
% git checkout -q 181546  
% make  

    make: Nothing to be done for `all'.

% git show

    commit 18154664824bff8904ed64e8547e8072450674ad
    Author: Schaub <mes100@ules-imac-08.uanet.edu>
    Date:   Mon Apr 2 11:54:19 2018 -0400
    
        determining error handling locations
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 885f740..e9663b3 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -41,6 +41,8 @@ std::string analysis_filename(const analysis_request& request) {
         else if(request.given_filename != "")
         {
           if(request.given_filename == "-")
    +        //throw error for stdin requires a declared language
    +        //********************************************************
             return ""; 
           else if(get_language_from_filename(request.given_filename) == "")
             return request.entry_filename; 
    @@ -73,6 +75,7 @@ std::string analysis_language(const analysis_request& request, const std::string
     
         if(request.option_language != "")
           //good place for extension not supported error handling
    +      //******************************************************
           return request.option_language; 
         else if(request.option_filename != "")
           return get_language_from_filename(request.option_filename);

### Commit 8bb995
% git checkout -q 8bb995  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    code_analysis_t.cpp:193:16: error: use of undeclared identifier 'extSupport'
            assert(extSupport(filename) == false);
                   ^
    1 error generated.
    make: *** [code_analysis_t.o] Error 1

% git show

    commit 8bb995b2eee443ce733f9fac08417eeff5e6b0b7
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 19:54:14 2018 -0400
    
        adding test for extension not supported error
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 7245d60..d8973ca 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -178,6 +178,21 @@ int main() {
             assert(analysis_language(request, filename) == "");
             assert(code_analysis(request) == false);
         }
    +    //test for extension not supported error
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        assert(filename == "");
    +        assert(extSupport(filename) == false);
    +    }
    +
     
     
         return 0;

### Commit edcdd9
% git checkout -q edcdd9  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    code_analysis_t.cpp:193:16: error: use of undeclared identifier 'extSupport'
            assert(extSupport(filename) == false);
                   ^
    1 error generated.
    make: *** [code_analysis_t.o] Error 1

% git show

    commit edcdd970a8f4b9c4625fb22ab2c993f2b97ca2cb
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 20:07:06 2018 -0400
    
        added function prototypes for errors
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 885f740..6872ff4 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -7,7 +7,7 @@
     
     #include "code_analysis.hpp"
     #include "get_language_from_filename.hpp"
    -
    +#include <iostream>
     #include <string>
     
     /** Generate source analysis based on the request
    @@ -24,7 +24,12 @@ bool code_analysis(const analysis_request& request) {
         auto language = analysis_language(request, filename);
     
         // code analysis processing that is not yet implemented
    +    auto extSupported = extSupport(filename);
    +
    +    
    +    auto langSupported = langSupport(language);
     
    +    
         return false;
     }
     
    @@ -84,3 +89,9 @@ std::string analysis_language(const analysis_request& request, const std::string
     
         return "";
     }
    +bool extSupport(std::string& filename){
    +  return false; 
    +}
    +bool langSupport(std::string& s){
    +  return false; 
    +}

### Commit f73fc1
% git checkout -q f73fc1  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit f73fc18cd11c1ca81a4b5486a3c50bba52d72fb0
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 20:16:01 2018 -0400
    
        fails extension test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 6872ff4..38d927d 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -24,7 +24,7 @@ bool code_analysis(const analysis_request& request) {
         auto language = analysis_language(request, filename);
     
         // code analysis processing that is not yet implemented
    -    auto extSupported = extSupport(filename);
    +    auto extSupported = extSupport(language);
     
         
         auto langSupported = langSupport(language);
    @@ -90,7 +90,7 @@ std::string analysis_language(const analysis_request& request, const std::string
         return "";
     }
     bool extSupport(std::string& filename){
    -  return false; 
    +  return true;  
     }
     bool langSupport(std::string& s){
       return false; 
    diff --git a/code_analysis.hpp b/code_analysis.hpp
    index 4ad0f17..817f487 100644
    --- a/code_analysis.hpp
    +++ b/code_analysis.hpp
    @@ -37,4 +37,6 @@ std::string analysis_url(const analysis_request& request);
      */
     std::string analysis_language(const analysis_request& request, const std::string& filename);
     
    +bool extSupport(std::string&); 
    +bool langSupport(std::string&);
     #endif
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index d8973ca..a3beadb 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -191,6 +191,7 @@ int main() {
             auto filename = analysis_filename(request);
             assert(filename == "");
             assert(extSupport(filename) == false);
    +        assert(code_analysis(request) == false);
         }
     
     

### Commit 913782
% git checkout -q 913782  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 9137824290c8c79b9f8015dad7a294c9f0e2f41c
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 20:17:47 2018 -0400
    
        see previous comment
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 38d927d..c578eb6 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -90,7 +90,7 @@ std::string analysis_language(const analysis_request& request, const std::string
         return "";
     }
     bool extSupport(std::string& filename){
    -  return true;  
    +  return false;  
     }
     bool langSupport(std::string& s){
       return false; 

### Commit 39497b
% git checkout -q 39497b  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 39497bb6b104fa9cee5058b33911eadab20ea7b0
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 20:26:51 2018 -0400
    
        fails language ext test when language defined
    
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index a3beadb..b9af63c 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -189,8 +189,27 @@ int main() {
             request.option_language = "";
     
             auto filename = analysis_filename(request);
    +        auto language = analysis_language(request, filename);
             assert(filename == "");
    -        assert(extSupport(filename) == false);
    +        assert(analysis_language(request, filename) == "");
    +        assert(extSupport(language) == false);
    +        assert(code_analysis(request) == false);
    +    }
    +    //test when extension defined 
    +    {
    +        analysis_request request;
    +        request.given_filename  = "";
    +        request.entry_filename  = "";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "C++";
    +
    +        auto filename = analysis_filename(request);
    +        auto language = analysis_language(request, filename);
    +        assert(filename == "");
    +        assert(analysis_language(request, filename) == "C++");
    +        assert(extSupport(language) == true);
             assert(code_analysis(request) == false);
         }
     

### Commit 94ab05
% git checkout -q 94ab05  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 94ab054c66f8ec2807047bc5b05f6d2778c20e7b
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 20:40:37 2018 -0400
    
        passes extension defined test
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index c578eb6..23cd34c 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -89,7 +89,9 @@ std::string analysis_language(const analysis_request& request, const std::string
     
         return "";
     }
    -bool extSupport(std::string& filename){
    +bool extSupport(std::string& language){
    +  if(language != "")
    +    return true; 
       return false;  
     }
     bool langSupport(std::string& s){

### Commit 110ff8
% git checkout -q 110ff8  
% make  

    g++ -std=c++11 -c code_analysis_t.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t
    Undefined symbols for architecture x86_64:
      "langSupport(analysis_request const&, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >&)", referenced from:
          _main in code_analysis_t.o
    ld: symbol(s) not found for architecture x86_64
    clang: error: linker command failed with exit code 1 (use -v to see invocation)
    make: *** [code_analysis_t] Error 1

% git show

    commit 110ff88f0a76c8cb4f32b86a90969b84b3d62eae
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 20:49:39 2018 -0400
    
        written and passes false cae for declared language error handling. Fails true case
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index 23cd34c..a22226b 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -27,7 +27,7 @@ bool code_analysis(const analysis_request& request) {
         auto extSupported = extSupport(language);
     
         
    -    auto langSupported = langSupport(language);
    +    auto langSupported = langSupport(request, language);
     
         
         return false;
    @@ -94,6 +94,6 @@ bool extSupport(std::string& language){
         return true; 
       return false;  
     }
    -bool langSupport(std::string& s){
    +bool langSupport(const analysis_request& request, std::string& language){
       return false; 
     }
    diff --git a/code_analysis.hpp b/code_analysis.hpp
    index 817f487..0c86477 100644
    --- a/code_analysis.hpp
    +++ b/code_analysis.hpp
    @@ -38,5 +38,5 @@ std::string analysis_url(const analysis_request& request);
     std::string analysis_language(const analysis_request& request, const std::string& filename);
     
     bool extSupport(std::string&); 
    -bool langSupport(std::string&);
    +bool langSupport(const analysis_request& request, std::string&);
     #endif
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index b9af63c..86ce902 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -212,6 +212,41 @@ int main() {
             assert(extSupport(language) == true);
             assert(code_analysis(request) == false);
         }
    +    //test for stdin requires declared language
    +    {
    +        analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        auto language = analysis_language(request, filename);
    +        assert(filename == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(langSupport(request,language) == false);
    +        assert(code_analysis(request) == false);
    +    }
    +    //test for stdin requires declared language true case
    +    {
    +        analysis_request request;
    +        request.given_filename  = "-";
    +        request.entry_filename  = "data";
    +        request.given_url       = "";
    +        request.option_filename = "";
    +        request.option_url      = "";
    +        request.option_language = "";
    +
    +        auto filename = analysis_filename(request);
    +        auto language = analysis_language(request, filename);
    +        assert(filename == "");
    +        assert(analysis_language(request, filename) == "");
    +        assert(langSupport(request,language) == true);
    +        assert(code_analysis(request) == false);
    +    }
    +
     
     
     

### Commit 5fe509
% git checkout -q 5fe509  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit 5fe5098875f2db232985ff09ccc40c23750a3ee2
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 21:04:25 2018 -0400
    
        passes all tests, updated logic on lang support function
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index a22226b..716e583 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -95,5 +95,7 @@ bool extSupport(std::string& language){
       return false;  
     }
     bool langSupport(const analysis_request& request, std::string& language){
    -  return false; 
    +  if(request.given_filename == "-" && language == "")
    +    return false; 
    +  return true; 
     }
    diff --git a/code_analysis_t.cpp b/code_analysis_t.cpp
    index 86ce902..809a428 100644
    --- a/code_analysis_t.cpp
    +++ b/code_analysis_t.cpp
    @@ -235,14 +235,14 @@ int main() {
             request.given_filename  = "-";
             request.entry_filename  = "data";
             request.given_url       = "";
    -        request.option_filename = "";
    +        request.option_filename = "main.cpp";
             request.option_url      = "";
             request.option_language = "";
     
             auto filename = analysis_filename(request);
             auto language = analysis_language(request, filename);
    -        assert(filename == "");
    -        assert(analysis_language(request, filename) == "");
    +        assert(filename == "main.cpp");
    +        assert(analysis_language(request, filename) == "C++");
             assert(langSupport(request,language) == true);
             assert(code_analysis(request) == false);
         }

### Commit 37d903
% git checkout -q 37d903  
% make  

    make: Nothing to be done for `all'.

% git show

    commit 37d90389442e9f50cdd8c873915993600cbb74ed
    Merge: 1815466 5fe5098
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 21:10:09 2018 -0400
    
        Merge branch 'temp' into workingBranch
    

### Commit c3e98d
% git checkout -q c3e98d  
% make  

    g++ -std=c++11 -c code_analysis.cpp
    g++ code_analysis_t.o code_analysis.o get_language_from_filename.o -o code_analysis_t

% git show

    commit c3e98d25d7ca776c2792fe8ef77bf6e23004a538
    Author: MattSchaub <matthew.e.schaub@gmail.com>
    Date:   Fri Apr 6 21:25:37 2018 -0400
    
        added error handling
    
    diff --git a/code_analysis.cpp b/code_analysis.cpp
    index fc556bb..6adb64c 100644
    --- a/code_analysis.cpp
    +++ b/code_analysis.cpp
    @@ -24,10 +24,11 @@ bool code_analysis(const analysis_request& request) {
         auto language = analysis_language(request, filename);
     
         // code analysis processing that is not yet implemented
    -    auto extSupported = extSupport(language);
    +    if(!extSupport(language))
    +      std::cerr << "Extension not supported\n"; 
     
    -    
    -    auto langSupported = langSupport(request, language);
    +    if(!langSupport(request, language))
    +      std::cerr << "Using stdin requires a declared language\n";
     
         
         return false;

