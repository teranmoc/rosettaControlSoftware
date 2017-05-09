#!/bin/bash


cp ../Embedded/Soft /usr/sbin/soft
chmod 755 /usr/sbin/soft
update-rc.d soft defaults


