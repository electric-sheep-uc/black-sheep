#!/bin/bash

screen -dm bash -c "socat -d -d pty,raw,echo=0 pty,raw,echo=0 & sleep 2; cat < /dev/pts/2" &
