#!/usr/bin/env bash


if [ "${DOCKER}" != "true" ]; then
    docker run --rm -ti -e DOCKER=true -v /${PWD}:/build sellorm/build1804 /build/build.sh
    docker run --rm -ti -e DOCKER=true -v /${PWD}:/build sellorm/build2004 /build/build.sh
    exit 0
fi

echo "STEP: change to build dir"
cd /build

echo "STEP: make the install path"
mkdir -p /tmp/src/usr/bin

echo "STEP: create output directory"
source /etc/os-release
mkdir -p /build/output/${VERSION_CODENAME}

echo "STEP: build shlog"
gcc shlog.c -o /tmp/src/usr/bin/shlog

echo "STEP: package"
fpm -s dir \
    -t deb \
    -n shlog \
    -v 0.0.1 \
    --vendor "sellorm.com" \
    --deb-priority "optional" \
    --deb-field 'Bugs: https://github.com/sellorm/shlog/issues' \
    --url "https://shlog.sellorm.com" \
    --description "Shell script log handler" \
    --maintainer "sellorm.com https://github.com/sellorm/shlog" \
    --license "MIT" \
    --package /build/output/${VERSION_CODENAME} \
    --no-depends \
    --iteration 3 \
    --package-name-suffix ${VERSION_CODENAME} \
    /tmp/src/=/
