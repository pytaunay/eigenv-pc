#!/bin/bash

for i in $(seq 1 100) 
do
	./bin/proc | grep timing 
done | awk -v FS=")" '{sum += $2} END {print sum/NR}' 
