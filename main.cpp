/* 
 * File:   main.cpp
 * Author: Grant Kochmann and Maxwell Evans
 *
 * Created on March 6th, 2018, 4:52 PM
 */

#include <cstdlib>
#include <iostream>
#include <string>
#include <sstream>
#include <MMU.h>
#include "PageFrameAllocator.h"
#include "ProcessTrace.h"

int main(int argc, char* argv[]) {
    std::cout << argv[0] << std::endl;
  if (argc < 2) {
    std::cerr << "Unable to open trace file. Exiting..." << std::endl;
    exit(1);
  }
  int timeSlice;
  std::istringstream(argv[1]) >> timeSlice;
  std::cout << timeSlice << std::endl;
  
  std::vector<std::string> fileNames;
  for (int i = 2; i < argc; i++)
      fileNames.push_back(argv[i]);
  
  mem::MMU memory(1024); // create an instance of the MMU class with 1024 (0x400) page frames
  PageFrameAllocator allocator(memory);
  
  std::vector<ProcessTrace*> processes;
  ProcessTrace* tempProcess;
  for (int i = 0; i < fileNames.size(); i++) {
      tempProcess = new ProcessTrace(memory, allocator, fileNames.at(i));
      processes.push_back(tempProcess);
  }
  
  for (int i = 0; i < processes.size(); i++) {
      tempProcess = processes.at(i);
      tempProcess->Execute();
      std::cout << i << ":TERMINATED" << std::endl;
  }
  
  return 0;
}
