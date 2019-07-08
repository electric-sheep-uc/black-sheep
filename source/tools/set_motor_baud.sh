#!/bin/bash

echo "THIS IS DANGEROUS, PLEASE USE CAREFULLY!"

echo ">> USE DEFAULT BAUD RATE IN THE CONFIG! <<"

# Use broadcast ID
ID="FE"
LOC_BAUD="06"
LOC_LOCK="30"

cd ..

# Unlock EEPROM
./robot -m $ID 2 03 $LOC_LOCK 00 0

sleep 1

# Set baud rate to 1M
./robot -m $ID 2 03 $LOC_BAUD 00 0

sleep 1

# NOTE: We would do this, but it'll fail anyway if this command was successful.
## Lock EEPROM
#./robot -m $ID 2 03 $LOC_LOCK 01 1

echo ">> UPDATE YOUR BAUD RATE IN THE CONFIG! <<"
