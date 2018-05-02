# matthewschaub
Score: 90

* Adding those extra functions did not help. In fact, it makes the code more difficult to understand

## Files & Changed Files
* Only required files committed
* Why is the file ```code_analysis.hpp``` been changed?

## Build
* Successfully builds, no errors, no warnings

## Test
* Passes all user tests
* No extraneous output

## Test Oracle: code\_analysis\_t.cpp
* Fails quite a few tests in the oracle test suite with student's implementation.

## Test Oracle: code\_analysis.cpp
* Completely fails with oracle implementation. Unnecessary functions added to the testing.
* Added functions were not to be tested.

## Code
* Very strange commented out code in lines 10-11 of ```analysis_filename()```
* If any part of an if-then-else uses a block, the other part should also
* Nested if's where the then and the else have a return, does not need the else.
* Only place for error handling is in ```code_analysis()```. So therefore, it is **not** a good place for error handling in any of the ```analysis_*()```
* Inconsistent indentation. First 4 characters then 2?
* Line 15 of ```analysis_filename()``` will never be reached
* Why did you add your name? Did you write most of that code? You started with my code. This is part of a real system, not a CS 1 program.

## Test Cases
* Decent set of test cases
* Use a blank line between tests. Also, why the multiple blank lines at the end of the test program?

## Literal Values used in Testing
* Realistic values used based on the problem description

## Error Messages
* Proper error messages
* Messages written to proper output

## Commits
* All commit versions build successfully
* Good set of commits. TDD was followed.

