/* 
 * File:   main.cpp
 * Author: Grant Kochmann and Maxwell Evans
 *
 * Created on March 6th, 2018, 4:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <MMU.h>
#include "PageFrameAllocator.h"
#include "ProcessTrace.h"


int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Unable to open trace file. Exiting..." << std::endl;
    exit(1);
  }
  
  mem::MMU memory(1024); // create an instance of the MMU class with 1024 (0x400) page frames
  PageFrameAllocator allocator(memory);
  ProcessTrace trace(memory, allocator, argv[1]);
  trace.Execute();
  return 0;
}
