/*
  Matthew Schaub
  @file code_analysis.cpp

  Implementation of analysis requests
*/

#include "code_analysis.hpp"
#include "get_language_from_filename.hpp"
#include <iostream>
#include <string>

/** Generate source analysis based on the request
 * @param request Data that forms the request
 * @retval true   Valid request
 * @retval false  Invalid filename or unable to deduce language
 */
bool code_analysis(const analysis_request& request) {

    auto filename = analysis_filename(request);

    auto url = analysis_url(request);

    auto language = analysis_language(request, filename);

    // code analysis processing that is not yet implemented
    auto extSupported = extSupport(language);

    
    auto langSupported = langSupport(request, language);

    
    return false;
}

/** Filename extracted from the request
 * @param  request Data that forms the request
 * @retval filename
 */
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

/** URL extracted from the request
 * @param  request Data that forms the request
 * @retval URL
 */
std::string analysis_url(const analysis_request& request) {

    if(request.option_url != "")
      return request.option_url;
    else if(request.given_url != "") 
      return request.given_url; 
    else
      return ""; 
}

/** Language extracted from the request and the filename
 * @param  request Data that forms the request
 * @param  filename Filename extracted from the request
 * @retval language
 */
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
bool extSupport(std::string& language){
  if(language != "")
    return true; 
  return false;  
}
bool langSupport(const analysis_request& request, std::string& language){
  if(request.given_filename == "-" && language == "")
    return false; 
  return true; 
}
