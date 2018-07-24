echo "Hello World"
rm hw_run
gcc -g HelloWorld.c -o hw_run -lpthread
echo "----------------------------"
echo "Linked-List"
rm ll_run
gcc -g linked_list.c -o ll_run -lpthread
echo "----------------------------"
echo "Matrix-Vector Multiplications"
rm mv_run
gcc -g Pth_mat_vect.c -o mv_run -lpthread
echo "----------------------------"
echo "PI"
rm pi_run
gcc -g pi.c -o pi_run -lpthread
echo "----------------------------"
echo "StrTock"
rm strtok_run
gcc -g strtok.c -o strtok_run -lpthread
echo "----------------------------"
