#!/bin/bash

cd src
for F in $(ls *.[ch]); do
	indent -linux $F
done
cd - 1>/dev/null
