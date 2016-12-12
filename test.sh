#!/bin/sh

runtest() {
  make test "$@" > /dev/null
  if test "$?" -ne 0; then
    echo "$@: FAILURE"
  else
    echo "$@: PASS"
  fi
}

runtest LNG=c STR=list IMP=array
runtest LNG=c STR=list IMP=linked
runtest LNG=c STR=stack IMP=array
runtest LNG=c STR=stack IMP=linked
runtest LNG=c STR=queue IMP=array
runtest LNG=c STR=queue IMP=linked

runtest LNG=cpp STR=queue IMP=array
runtest LNG=cpp STR=list IMP=linked