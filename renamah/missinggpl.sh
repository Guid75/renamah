#! /bin/bash

TEMP_FILE=`mktemp`
for i in `grep "* This program" * | cut -d ":" -f 1`; do echo $i; done > $TEMP_FILE
for i in `ls *.{h,cpp}`; do if [ "`grep $i $TEMP_FILE`" = "" ]; then echo $i; fi; done

