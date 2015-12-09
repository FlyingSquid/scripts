#include "s3.hpp"

#include <iostream>
#include <fstream>
#include <streambuf>

int main(int argc, char** argv) {
    AWS::S3::Connection conn("", "");

    apathy::Path localpath("sample2.txt");
    std::ifstream in(localpath.string());
    std::string inString ((std::istreambuf_iterator<char>(in)),
                           std::istreambuf_iterator<char>());

    /*if (conn.put("flyingsquid2", "/sample2.txt", inString)) {
        std::cout << "Success!" << std::endl;
    } else {
        std::cout << "Failure" << std::endl;
    }*/

    conn.put("flyingsquid2", "/sample2.txt", inString);

    std::ofstream out("sample.txt");
    if (conn.get("flyingsquid2", "/sample.txt", out)) {
        std::cout << "We fetched a page!" << std::endl;
        return 0;
    } else {
        std::cout << "We failed fetching a page!" << std::endl;
        return 1;
    }
}
