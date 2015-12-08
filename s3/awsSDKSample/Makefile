CC=g++
DEFINES=-std=c++11
WARNINGS=-Wall -Wextra
DEBUG=-g
S3_INC_DIR=aws-sdk-cpp/aws-sdk-cpp/aws-cpp-sdk-s3/include/aws/s3
CORE_INC_DIR=aws-sdk-cpp/aws-sdk-cpp/aws-cpp-sdk-core/include/aws/core
LIBS=-laws-cpp-sdk-core -laws-cpp-sdk-s3
CFLAGS=$(DEBUG) $(DEFINES) $(WARNINGS) -c
LDFLAGS=$(DEBUG) $(DEFINES) $(WARNINGS) -o
SOURCES=s3.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=s3
DEPS= $(S3_INC_DIR)/S3Client.h $(S3_INC_DIR)/model/PutObjectRequest.h $(CORE_INC_DIR)/auth/AWSCredentialsProvider.h $(CORE_INC_DIR)/utils/HashingUtils.h $(CORE_INC_DIR)/utils/DateTime.h

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $@ $^ $(LIBS)

$(OBJECTS): $(SOURCES) $(DEPS)
	$(CC) $(CFLAGS) $<
