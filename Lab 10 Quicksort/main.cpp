//
//  main.cpp
//  Lab 10 QuickSort
//
//  Created by C/R

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "QuickSort.h"

int main(int argc, const char * argv[]) {
    //Checking for correct number of arguments
    if (argc < 3)
    {
        std::cerr << "Please provide the name of input and output files, thanks\n";
        return 1;
    }
       
    //Checking if input file opens
    std::ifstream in(argv[1]);
    if (!in)
    {
        std::cerr << "Failure to open input file: " << argv[1] << std::endl;
        return 2;
    }
       
    //Checking if output file opens
    std::ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        std::cerr << "Failure to open output file: " << argv[1] << std::endl;
        return 3;
    }
    
    //int valComm = 0;
    QuickSort<int> qs;

    for (std::string line; getline(in, line);)
    {
        std::string command = "";
        std::istringstream iss(line);
        iss >> command;
        
        if (command == "QuickSort")
        {
            out << line;
            size_t capacity = 0;
            iss >> capacity;
            qs.reset();
            qs.setCapacity(capacity);
            out << " OK";
        }
        
        else if (command == "Capacity")
        {
            out << line << " " << qs.capacity();
        }
           
        else if (command == "Clear" )
        {
            out << line;
            qs.clear();
            out << " OK";
        }
        
        else if (command == "AddToArray")
        {
            int num = 0;
            out << command << " ";
            std::ostringstream os;
            while (iss >> num)
            {
                qs.addElement(num);
                os << num << ",";
            }
            out << os.str().substr(0, os.str().size() - 1) << " OK";
        }
        
        else if (command == "Size")
        {
            out << line << " " << qs.size();
        }
        
        else if (command == "PrintArray")
        {
            if (qs.size() == 0) out << line << " Empty";
            else out << line << " " << qs;
        }
        
        else if (command == "MedianOfThree")
        {
            int left = 0;
            int right = 0;
            iss >> left;
            iss >> right;
            out << command << " " << left << "," << right << " = " << qs.medianOfThree(left, right);
        }
        
        else if (command == "Partition")
        {
            int left = 0;
            int right = 0;
            int p_index = 0;
            iss >> left;
            iss >> right;
            iss >> p_index;
            out << command << " " << left << "," << right << "," << p_index << " = " << qs.partition(left, right, p_index);
        }
        
        else if (command == "SortAll")
        {
            out << line;
            if (qs.sortAll()) out << " OK";
            else out << " Error";
        }
        
        else if (command == "Sort")
        {
            int left = 0;
            int right = 0;
            iss >> left;
            iss >> right;
            out << command << " " << left << "," << right;
            if (qs.sort(left, right)) out << " OK";
            else out << " Error";
        }
        
        else out << "Error: " << line;
        if (command != "") out << std::endl;
    }

    return 0;
}
