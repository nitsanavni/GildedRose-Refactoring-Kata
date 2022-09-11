git clone https://github.com/cpputest/cpputest.git CppUTest
cd CppUTest/cpputest_build
autoreconf ../ -i
cd ..
./configure
make
