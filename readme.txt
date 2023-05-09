first run this 
        g++ -Wall -Werror -std=c++14 -O -o main ppd.cpp LinkedList.cpp Node.cpp Coin.cpp 
 then run this 
        valgrind ./main stock.dat coins.datvalgrind ./main stock.dat coins.dat

// Install valgrind to check  for memory leaks 
     step 1:
              sudo apt update

     step 2:
              sudo apt install valgrind
     step 3:
              valgrind --version

