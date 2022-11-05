#!/bin/sh

TEST_BIN_PATH=test/bin
FILES=`ls $TEST_BIN_PATH`

for f in $FILES
do
  ./$TEST_BIN_PATH/$f
  echo "\n"
done

