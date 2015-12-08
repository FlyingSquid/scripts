#ifndef S3_API_H
#define S3_API_H

#include "libs3.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sys/stat.h>

typedef struct put_object_callback_data
{
    FILE *infile;
    uint64_t contentLength;
} put_object_callback_data;

class S3API {
    public:
        S3API(char accessKey[], char secretKey[]);
        ~S3API();
        void listService(const char host[]);
        void putObject(const char host[], const char bucketName[],
                                const char key[], const char file[]);
        void getObject(const char host[], const char bucketName[],
                                                    const char key[]);

    private:
        static S3Status responsePropertiesCallback(
                const S3ResponseProperties *properties, void *callbackData);
        static void responseCompleteCallback(S3Status status,
                        const S3ErrorDetails *error, void *callbackData);
        void printError();
        static S3Status listServiceCallback(const char *ownerId,
                    const char *ownerDisplayName, const char *bucketName,
                    int64_t creationDate, void *callbackData);
        static int putObjectDataCallback(int bufferSize, char *buffer,
                                                    void *callbackData);
        static  S3Status getObjectDataCallback(int bufferSize,
                                const char *buffer, void *callbackData);

        char *accessKey; 
        char *secretKey;
        static S3Status statusG;
        static char errorDetailsG[4096];
        S3ResponseHandler responseHandler;

};

#endif
