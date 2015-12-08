#include "S3API.h"

S3Status S3API::statusG;
char S3API::errorDetailsG[4096] = { 0 };

//---------------PUBLIC FUNCTIONS---------------//

S3API::S3API(char accessKey[], char secretKey[])
{
    this -> accessKey = accessKey;
    this -> secretKey = secretKey;
    this -> responseHandler = {
        &responsePropertiesCallback,
        &responseCompleteCallback
    };
}

S3API::~S3API()
{
    ;
}

void S3API::listService(const char host[])
{
    S3_initialize("s3", S3_INIT_ALL, host);

    bool headerPrinted = false;

    S3ListServiceHandler listServiceHandler = {
        responseHandler,
        &listServiceCallback
    };

    S3_list_service(S3ProtocolHTTP, accessKey, secretKey, NULL, NULL,
                                NULL, &listServiceHandler, &headerPrinted);
    
    if (statusG != S3StatusOK) {
        printError();
    }

    S3_deinitialize();
}

void S3API::putObject(const char host[], const char bucketName[],
                                const char key[], const char file[])
{
    S3_initialize("s3", S3_INIT_ALL, host);

    put_object_callback_data data;
    struct stat statbuf;

    if (stat(file, &statbuf) == -1) {
        fprintf(stderr, "\nERROR: Failed to stat file %s: ", file);
        perror(0);
        exit(-1);
    }

    int contentLength = statbuf.st_size;
    data.contentLength = contentLength;

    if (!(data.infile = fopen(file, "r"))) {
        fprintf(stderr, "\nERROR: Failed to open input file %s: ", file);
        perror(0);
        exit(-1);
    }

    const char contentType[] = "text/plain";
    
    S3BucketContext bucketContext = {
        host,
        bucketName,
        S3ProtocolHTTP,
        S3UriStylePath,
        accessKey,
        secretKey
    };

    S3PutObjectHandler putObjectHandler = {
        responseHandler,
        &putObjectDataCallback
    };

    S3_put_object(&bucketContext, key, contentLength, NULL, NULL,
                                            &putObjectHandler, &data);

    if (statusG != S3StatusOK) {
        printError();
    }

    S3_deinitialize();
}

void S3API::getObject(const char host[], const char bucketName[],
                                                    const char key[])
{
    S3_initialize("s3", S3_INIT_ALL, host);

    S3GetObjectHandler getObjectHandler = {
        responseHandler,
        &getObjectDataCallback
    };

    S3BucketContext bucketContext = {
        host,
        bucketName,
        S3ProtocolHTTP,
        S3UriStylePath,
        accessKey,
        secretKey
    };

    FILE *outfile = stdout;
    
    S3_get_object(&bucketContext, key, NULL, 0, 0, NULL,
                                        &getObjectHandler, outfile);
    if (statusG != S3StatusOK) {
        printError();
    }

    S3_deinitialize();
}

//---------------PRIVATE FUNCTIONS---------------//

S3Status S3API::responsePropertiesCallback(const S3ResponseProperties 
                                       *properties, void *callbackData)
{
        return S3StatusOK;
}

void S3API::responseCompleteCallback(S3Status status, const S3ErrorDetails
                                                *error, void *callbackData)
{
    (void) callbackData;
    statusG = status;
    int len = 0;

    if (error && error -> message) {
        len += snprintf(&(errorDetailsG[len]),
                sizeof(errorDetailsG) - len,
                "  Message: %s\n", error -> message);
    }
    if (error && error -> resource) {
        len += snprintf(&(errorDetailsG[len]),
                sizeof(errorDetailsG) - len,
                "  Resource: %s\n", error -> resource);
    }
    if (error && error -> furtherDetails) {
        len += snprintf(&(errorDetailsG[len]),
                sizeof(errorDetailsG) - len,
                "  Further Details: %s\n", error -> furtherDetails);
    }
    if (error && error -> extraDetailsCount) {
        len += snprintf(&(errorDetailsG[len]),
                sizeof(errorDetailsG) - len,
                                            "%s", "  Extra Details:\n");
        for (int i = 0; i < error -> extraDetailsCount; i++) {
            len += snprintf(&(errorDetailsG[len]), 
                            sizeof(errorDetailsG) - len,
                            "    %s: %s\n", error -> extraDetails[i].name,
                            error -> extraDetails[i].value);
        }
    }
}

void S3API::printError()
{
    if (statusG < S3StatusErrorAccessDenied) {
        fprintf(stderr, "\nERROR: %s\n",
                    S3_get_status_name(statusG));
    }
    else {
        fprintf(stderr, "\nERROR: %s\n",
                    S3_get_status_name(statusG));
        fprintf(stderr, "%s\n", errorDetailsG);
    }
}

S3Status S3API::listServiceCallback(const char *ownerId,
                    const char *ownerDisplayName, const char *bucketName,
                    int64_t creationDate, void *callbackData)
{
        bool *header_printed = (bool*) callbackData;

        if (!*header_printed) {
                *header_printed = true;
                printf("%-22s", "       Bucket");
                printf("  %-20s  %-12s", "     Owner ID", "Display Name");
                printf("\n");
                printf("----------------------");
                printf("  --------------------" "  ------------");
                printf("\n");
        }

        printf("%-22s", bucketName);
        printf("  %-20s  %-12s", ownerId ? ownerId : "",
                                ownerDisplayName ? ownerDisplayName : "");
        printf("\n");

        return S3StatusOK;
}

int S3API::putObjectDataCallback(int bufferSize, char *buffer,
                                                void *callbackData)
{
    put_object_callback_data *data =
                                (put_object_callback_data *) callbackData;
    int ret = 0;

    if (data -> contentLength) {
        int toRead = ((data -> contentLength > (unsigned) bufferSize) ?
                            (unsigned) bufferSize : data->contentLength);
        ret = fread(buffer, 1, toRead, data -> infile);
    }
    data -> contentLength -= ret;

    return ret;
}

S3Status S3API::getObjectDataCallback(int bufferSize, const char *buffer,
                                                        void *callbackData)
{
    FILE *outfile = (FILE *) callbackData;
    size_t wrote = fwrite(buffer, 1, bufferSize, outfile);

    return ((wrote < (size_t) bufferSize) ?
                    S3StatusAbortedByCallback : S3StatusOK);
}
