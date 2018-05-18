#include <boost/program_options.hpp>
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/Module.h"

#include <iostream>

#include "FunctionNames.h"

using namespace std;
using namespace llvm;

int main(int argc, char **argv) {
  namespace po = boost::program_options;
  po::options_description desc("Options");
  desc.add_options()
    ("help", "produce help message")
    //  ("command", po::value<string>()->required(), "Command (specs/handlers)")
    ("bitcode", po::value<string>()->required(), "Path to bitcode file");
  po::variables_map varmap;
  try {
    po::store(po::parse_command_line(argc, argv, desc), varmap);
    po::notify(varmap);
  } catch (po::error &e){
    cerr << "ERROR: " << e.what() << endl << endl;
    cerr << desc << endl;
    return 1;
  }

  //string command = varmap["command"].as<string>();
  //if (command != "cmd1" && command != "cmd2") {
  //  cerr << "Command must be 'cmd1' or 'cmd2'" << endl;
  //  return 1;
  //}

  string bitcode_path = varmap["bitcode"].as<string>();
  string function;
  if (varmap.count("function")) {
    function = varmap["function"].as<string>();
  }

  SMDiagnostic Err;
  unique_ptr<Module> Mod(parseIRFile(bitcode_path, Err, getGlobalContext()));
  if (!Mod) {
    cerr << "FATAL: Error parsing bitcode file: " << bitcode_path << endl;
    abort();
  }

  legacy::PassManager PM;
  // Add passes to run here
  PM.run(*Mod);

  return 0;
}
