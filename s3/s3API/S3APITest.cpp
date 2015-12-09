#include "S3API.h"

int main() {
    char accessKey[] = "YOUR_ACCESS_KEY";
    char secretKey[] = "YOUR_SECRET_KEY";
    const char host[] = "s3.amazonaws.com"; // US Standard End-point

    S3API api = S3API(accessKey, secretKey);
    api.createBucket(host, "flyingsquid2");
    api.listService(host); 
    api.putObject(host, "flyingsquid2", "sample.txt", "sample.txt");
    api.getObject(host, "flyingsquid2", "sample.txt");
    api.deleteObject(host, "flyingsquid2", "sample.txt");
    api.deleteBucket(host, "flyingsquid2");

    return 0;
}
