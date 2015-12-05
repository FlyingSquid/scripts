#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <aws/core/auth/AWSCredentialsProvider.h>
#include <aws/core/utils/DateTime.h>
#include <aws/core/utils/HashingUtils.h>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <stdexcept>

using namespace Aws::Client;
using namespace Aws::S3;
using namespace Aws::S3::Model;
using namespace Aws::Auth;
using namespace Aws::Utils;

void setAwsCredentials()
{
    setenv("AWS_ACCESS_KEY_ID", "Access Key", 1);
    setenv("AWS_SECRET_KEY_ID", "Secret Key", 1);

    //std::shared_ptr<EnvironmentAWSCredentialsProvider> credentialsProvider (new EnvironmentAWSCredentialsProvider());
    //std::string key = credentialsProvider -> GetAWSCredentials().GetAWSAccessKeyId().c_str();
    //assert("Access Key" == credentialsProvider -> GetAWSCredentials().GetAWSAccessKeyId().c_str());
}

Aws::String CalculateBucketName(Aws::String bucketPrefix)
{
    Aws::String timeStamp = DateTime::CalculateGmtTimestampAsString("%Y%m%dt%H%M%Sz");
    return bucketPrefix + timeStamp;
}

int main()
{

    //setAwsCredentials();
    //Aws::String fullBucketName = CalculateBucketName("flyingsquid");
    S3Client s3Client;
    /*PutObjectRequest putObjectRequest;
    putObjectRequest.SetBucket(fullBucketName);
    putObjectRequest.SetKey("sample");

    std::shared_ptr<Aws::FStream> fileToUpload = Aws::MakeShared<Aws::FStream>("sample.txt",
    "sample.txt", std::ios_base::in);

    putObjectRequest.SetBody(fileToUpload);
    putObjectRequest.SetContentLength(static_cast<long>(putObjectRequest.GetBody()->tellp()));
    putObjectRequest.SetContentMD5(HashingUtils::Base64Encode(HashingUtils::CalculateMD5(*putObjectRequest.GetBody())));
    putObjectRequest.SetContentType("text/plain");

    PutObjectOutcome outcome = s3Client.PutObject(putObjectRequest);*/
   
    return 0;
}
