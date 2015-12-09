#include <curl/curl.h>
#include "awscpp/aws.hpp"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

int main() {

	// Any ostream will work here
	std::ofstream out;

	AWS::S3::Connection s3("ACCESS_KEY_ID", "SECRET_ACCESS_KEY");
	if (s3.get("test-flyingsquid", "/sample.txt", out)) {
	    std::cout << "Success!" << std::endl;
	} else {
	    std::cout << "Failure" << std::endl;
	}

}
