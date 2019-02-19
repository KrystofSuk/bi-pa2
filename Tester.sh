#!/bin/bash
PROG=C:/Users/sukkr/source/repos/Progtest/$1/prog.exe
TEST=C:/Users/sukkr/source/repos/Progtest/$1/TESTDATA

GREEN='\033[0;32m'
RED='\033[0;31m'
GR='\033[1;30m'
OR='\033[1;31m'
NC='\033[0m'

for IN_FILE in $TEST/*$2_in.txt
  do    
  REF_FILE=`echo  $IN_FILE | sed -e 's/_in\(.*\)$/_out_win\1/'`
  $PROG < $IN_FILE > out.txt
  if ! diff $REF_FILE out.txt
  then        
    echo -e "${RED}Fail: ${OR}$IN_FILE | $REF_FILE";
  else
    echo -e "${GREEN}OK ${GR}$IN_FILE";
  fi
  rm "out.txt"
done