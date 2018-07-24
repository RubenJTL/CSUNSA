echo "Firs Even Sort"
rm runoddeven1
gcc -g -Wall -fopenmp oddeven1.c -o runoddeven1
echo "----------------------------"
echo "Second Even Sort"
rm runoddeven2
gcc -g -Wall -fopenmp oddeven2.c -o runoddeven2
echo "----------------------------"
echo "Matrix Vector"
rm runmatrixvector
gcc -g -Wall -fopenmp matrix_vector.c -o runmatrixvector
echo "----------------------------"
echo "StrTok"
rm runstrtok
gcc -g -Wall -fopenmp strtok.c -o runstrtok
echo "----------------------------"



