#!/bin/bash

cd build/
rm ./ZooManager 
cmake .. && make -j8 && ./ZooManager &  #bash doesn't wait for programm exit.
cd .. 

