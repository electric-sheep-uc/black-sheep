#!/bin/bash

echo "THIS IS DANGEROUS, PLEASE USE CAREFULLY!"

DEF="01"
LOC_ID="05"
LOC_LOCK="30"

cd ..

# Read current ID
./robot -m $DEF 2 02 $LOC_ID 01 1

sleep 1

# Unlock EEPROM
./robot -m $DEF 2 03 $LOC_LOCK 00 1

sleep 1

# Write the motor ID
./robot -m $DEF 2 03 $LOC_ID $1 1

sleep 1

# Lock EEPROM
./robot -m $1 2 03 $LOC_LOCK 01 1
