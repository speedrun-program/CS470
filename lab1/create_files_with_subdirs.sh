#!/bin/bash

date_string=$(date +"%Y-%m-%d_%H:%M:%S")

mkdir -p "$date_string"

# an array of strings containing the test which will be put in the files
languages=("python" "c++" "java" "c" "c#" "javascript" "go" "sql" "visual basic" "fortran")

# make ten subdirectories, and in each one, make a txt file with a language in it
for ((i = 1; i <= 10; i++));
do
    subdirectory=$(printf "%s/file1%02d" $date_string $i)
    mkdir -p "$subdirectory"
    
    for ((j = 1; j <= 10; j++));
    do
        new_file=$(printf "%s/tuser5%02d.txt" $subdirectory $j)
        echo "${languages[$((j-1))]}" > "$new_file"
    done
done

