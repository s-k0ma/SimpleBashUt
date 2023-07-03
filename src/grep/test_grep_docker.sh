#!/bin/bash
valg1="--leak-check=full --track-origins=yes -s"
out=">> /dev/null"
file1="test1.txt"
file2="test2.txt"
echo "\nc"
echo -e "############# Valgrind test ################"
valgrind $valg1 ./s21_grep str1 $file1 >> /dev/null 
valgrind $valg1 ./s21_grep -estr2 $file1 >> /dev/null 
valgrind $valg1 ./s21_grep -e str2 $file1 -e str23 >> /dev/null 
valgrind $valg1 ./s21_grep -estr2 $file1 -e str23 -estr11 $file2 >> /dev/null 
valgrind $valg1 ./s21_grep -eSTR2 $file1 -e sTr23 -estr11 $file2 -i >> /dev/null 
valgrind $valg1  ./s21_grep -ieSTR2 $file1 -e sTr23 -estr11 $file2 >> /dev/null 
valgrind $valg1 ./s21_grep -estr2 $file1 -iestr22 -c >> /dev/null 
valgrind $valg1 ./s21_grep -estr2 $file1 -iestr22 -cv >> /dev/null 
valgrind $valg1 ./s21_grep -estr2 $file1 -iestr22 -cv $file2 >> /dev/null 
valgrind $valg1 ./s21_grep -e Str2 $file1 -iv -e str22 $file2 >> /dev/null 
valgrind $valg1 ./s21_grep -estr2 $file1 -iestr22 $file2 -l >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 -estr2 $file1 $file2 -n >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 -estr2 $file1 -n >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 -estr2 $file1 $file2 -h >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 -f grep.patterns $file1 $file2 -h >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 -f grep.patterns1 $file1 $file2 -h >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 -estr2 $file1 $file2 -hc >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 -estr2 $file1 $file2 -hn >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 $file1 test99.txt test0.txt -s >> /dev/null 
valgrind $valg1 ./s21_grep -estr1 $file1 test99.txt test0.txt >> /dev/null 
valgrind $valg1 ./s21_grep -estr11 $file1 -o >> /dev/null
valgrind $valg1 ./s21_grep -estr11 -e aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa $file1 bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb -o >> /dev/null
valgrind $valg1 ./s21_grep -e char -e ar grep.c grep.h -hno >> /dev/null 
valgrind $valg1 ./s21_grep -e char -e ar grep.c grep.h -hnov >> /dev/null 
valgrind $valg1 ./s21_grep -e char -e ar grep.c grep.h -hnovc >> /dev/null 
valgrind $valg1 ./s21_grep -e char -e ar grep.c grep.h -hnovl >> /dev/null 
valgrind $valg1 ./s21_grep -e char -e ar nofile.txt -s >> /dev/null 
