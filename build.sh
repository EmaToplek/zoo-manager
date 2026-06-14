#!/bin/bash

cd build/
rm -f ./ZooManager 
cmake .. && make -j8 && ./zoo_test && ./ZooManager &  #bash doesn't wait for programm exit.
cd .. 

