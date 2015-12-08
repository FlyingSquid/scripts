#include "S3API.h"

int main() {
    char accessKey[] = "YOUR_ACCESS_KEY";
    char secretKey[] = "YOUR_SECRET_KEY";
    const char host[] = "s3-us-west-2.amazonaws.com"; // Oregon End-point

    S3API api = S3API(accessKey, secretKey);
    api.listService(host); 
    api.putObject(host, "flyingsquid", "sample2.txt", "sample2.txt");
    api.getObject(host, "flyingsquid", "sample.txt");

    return 0;
}
