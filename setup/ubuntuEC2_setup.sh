#!/bin/bash -ex

###############################################################################
# ubuntuEC2_setup.sh
# 
# Setup script for installing Apache Traffic Server from source
# - code is cloned from GitHub into $STORAGE_DIR
# - Traffic Server is installed in $INSTALL_DIR
# - run with 'sudo ./ubuntuEC2_setup'
###############################################################################

STORAGE_DIR="/mnt"
INSTALL_DIR="/opt/ts"

REPO_URL="https://github.com/FlyingSquid/trafficserver.git"


# Update/download dependencies
apt-get update
apt-get upgrade -y
apt-get install -y git \
                   autoconf \
                   automake \
                   build-essential \
                   make \
                   pkg-config \
                   libtool \
                   libssl-dev \
                   tcl-dev \
                   libexpat-dev \
                   libpcre3 libpcre3-dev \
                   libcap-dev \
                   flex \
                   hwloc \
                   lua5.2 \
                   libncurses-dev \
                   curl

# Clone repo
mkdir -p $STORAGE_DIR
cd $STORAGE_DIR
git clone $REPO_URL
cd trafficserver

# Generate configure script
autoreconf -if

# Configure source tree (installs in /opt/ts)
./configure --prefix=$INSTALL_DIR

# Build with generate Makefiles
make
make check

# Install to configured location
make install

# Start proxy
$INSTALL_DIR/bin/trafficserver start
