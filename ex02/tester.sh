#!/bin/bash

green='\033[0;32m'
red='\033[0;31m'
clear='\033[0m'

values=(2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 30 100 101 500 501 1000 1001 2000 2001 3000)

for i in "${values[@]}"; do
	output=$(./PmergeMe `shuf -i 1-$i -n $i | tr "\n" " "`)

	numbers=$(echo "$output" | grep -oP 'After: \K.*')

	sorted_numbers=$(echo "$numbers" | tr " " "\n" | sort -n | tr "\n" " ")
	sorted_numbers="${sorted_numbers# }"

	if [ "$numbers" == "$sorted_numbers" ]; then
		echo -e "${green}for $i : Ok \xE2\x9C\x94${clear}"
	else
		echo -e "${red}for $i : Fail \xE2\x9D\x8C${clear}"
	fi
	# echo "$output"
done
