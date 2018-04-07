/*
  @file code_analysis.hpp

  Header for analysis requests
*/

#ifndef INCLUDE_CODE_ANALYSIS_HPP
#define INCLUDE_CODE_ANALYSIS_HPP

#include "analysis_request.hpp"

#include <string>

/** Generate source analysis based on the request
 * @param request Data that forms the request
 * @retval true   Valid request
 * @retval false  Invalid filename or unable to deduce language
 */
bool code_analysis(const analysis_request& request);

/** Filename extracted from the request
 * @param  request Data that forms the request
 * @retval filename
 */
std::string analysis_filename(const analysis_request& request);

/** URL extracted from the request
 * @param  request Data that forms the request
 * @retval URL
 */
std::string analysis_url(const analysis_request& request);

/** Language extracted from the request and the filename
 * @param  request Data that forms the request
 * @param  filename Filename extracted from the request
 * @retval language
 */
std::string analysis_language(const analysis_request& request, const std::string& filename);

bool extSupport(std::string&); 
bool langSupport(const analysis_request& request, std::string&);
#endif
