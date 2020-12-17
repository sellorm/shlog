#!/usr/bin/env bash

# ALL < trace < DEBUG < INFO < WARN < ERROR < FATAL < OFF.

SHLOG_PATH=./shlog

function test_shlog(){
    echo "LOGLEVEL is ${LOGLEVEL}"

for i in trace TRACE debug DEBUG info INFO warn WARN error ERROR fatal FATAL
do
    ${SHLOG_PATH} ${i} "this message is ${i}"
done
}


#----------

export LOGLEVEL=all

test_shlog


#----------

export LOGLEVEL=ALL

test_shlog


#----------

export LOGLEVEL=trace

test_shlog


#----------

export LOGLEVEL=TRACE

test_shlog

#----------

export LOGLEVEL=debug

test_shlog

#----------

export LOGLEVEL=DEBUG

test_shlog

#----------

export LOGLEVEL=info

test_shlog

#----------

export LOGLEVEL=INFO

test_shlog

#--------

export LOGLEVEL=warn

test_shlog

#--------

export LOGLEVEL=WARN

test_shlog

#--------

export LOGLEVEL=error

test_shlog

#--------

export LOGLEVEL=ERROR

test_shlog

#-----------

export LOGLEVEL=fatal

test_shlog

#-----------

export LOGLEVEL=FATAL

test_shlog
#-----------

export LOGLEVEL=off

test_shlog

#-----------

export LOGLEVEL=OFF

test_shlog

