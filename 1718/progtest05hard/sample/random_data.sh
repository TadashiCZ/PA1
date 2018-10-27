#!/bin/bash

printf "{" > FILE.txt
for i in {1..1500}
	do
		printf "$(($RANDOM$RANDOM%100000)), " >> FILE.txt
	done	
printf "}"	 >> FILE.txt

printf "\n"

for i in {1..10}
	do
		rand=$(printf "$(($RANDOM%750))")
		printf "$rand $((2*$rand)) \n" >> FILE.txt
	done	