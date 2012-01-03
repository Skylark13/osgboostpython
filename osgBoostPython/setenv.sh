#!/usr/bin/env bash
set PWD = `pwd`
export PYTHONPATH=${PYTHONPATH}:${PWD}/lib

: ${OSG_FILE_PATH?"You really should point OSG_FILE_PATH to the location of the OSG models."}
