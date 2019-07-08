#!/bin/bash

DEF="FE"
LOC_ID="05"
LOC_LOCK="30"

cd ..

# Read current ID
./robot -m $DEF 2 02 $LOC_ID 01 1
