#include <curl/curl.h>
#include "awscpp/aws.hpp"
#include <iostream>
#include <fstream>
#include <curl/curl.h>

int main() {

	// Any ostream will work here
	std::ofstream out ("sample.txt");

	AWS::S3::Connection s3("","");
	if (s3.get("test-flyingsquid", "/sample.txt", out)) {
	    std::cout << "Success!" << std::endl;
	} else {
	    std::cout << "Failure" << std::endl;
	}


	std::ifstream in ("blah.txt", std::ifstream::in);
	std::ofstream output ("foo.txt");
	std::size_t N = 10;

	if (s3.put("test-flyingsquid", "/blah.txt", in, 11, output, N)) {
	    std::cout << "Success!" << std::endl;
	} else {
	    std::cout << "Failure" << std::endl;
	}

}
