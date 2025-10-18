// encrypt_file.cpp -- quick utility for encrypting input files.

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <random>

namespace po = boost::program_options;
using i64 = int64_t;


int main(int argc, char* argv[]) {
   std::string infile = "";
   std::string outfile = "";
   std::string password = "";
   
   po::options_description desc("Allowed options");
   desc.add_options()
       ("help,h", "produce help message")
       ("input,i", po::value<std::string>(&infile)->required(), "Input file")
       ("output,o", po::value<std::string>(&outfile)->required(), "Output file")
       ("password,P", po::value<std::string>(&password)->default_value(""), "Password for encryption")
   ;
   
   po::variables_map vm;
   try {
      po::store(po::parse_command_line(argc, argv, desc), vm);
      if (vm.count("help")) {
         std::cout << desc << std::endl;
         return 0;
      }
      po::notify(vm);
   }
   catch (const po::error &ex) {
      std::cerr << ex.what() << std::endl;
      std::cerr << desc << std::endl;
      return 1;
   }
   
   if (password.empty()) {
      const char* passenv = std::getenv("AOC_PASSWORD");
      if (passenv) {
         password = passenv;
      } else {
         std::cerr << "Password must be provided for encryption." << std::endl;
         return 1;
      }
   }

   // Open input and output files
   std::ifstream infd(infile, std::ios::binary);
   if (!infd) {
      std::cerr << "Error opening input file: " << infile << std::endl;
      return 1;
   }
   std::ofstream outfd(outfile, std::ios::binary);
   if (!outfd) {
      std::cerr << "Error opening output file: " << outfile << std::endl;
      return 1;
   }
   
   // Simple XOR encryption for demonstration purposes
   std::mt19937 rng(std::hash<std::string>{}(password));
   char buffer[4096];
   while (infd.read(buffer, sizeof(buffer)) || infd.gcount() > 0) {
      std::streamsize bytesRead = infd.gcount();
      for (std::streamsize i = 0; i < bytesRead; ++i) {
         buffer[i] ^= static_cast<unsigned char>(rng());
      }
      outfd.write(buffer, bytesRead);
   }
   
   infd.close();
   outfd.close();
   
   std::cout << "File encrypted successfully: " << outfile << std::endl;
   return 0;
}