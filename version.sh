#!/bin/bash
OUTPUT_FILENAME=$1
GIT_HASH=`git rev-parse --short HEAD`
TIMESTAMP=`date --rfc-3339=seconds`
echo '#define VCS_REF "'$GIT_HASH'"' > $OUTPUT_FILENAME
echo '#define TIMESTAMP "'$TIMESTAMP'"' >> $OUTPUT_FILENAME
