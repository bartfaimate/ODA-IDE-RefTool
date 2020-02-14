#include <iostream>
#include <regex>
#include <string>
#include <map>
#include <fstream>
using namespace std;

const string keyWords[] = {"alignas", "alignof", "and", "and_eq", "asm",
"atomic_cancel", "atomic_commit", "atomic_noexcept", "auto", "bitand",
"bitor", "bool", "break", "case", "catch", "char", "char8_t", "char16_t",
"char32_t", "class", "compl", "concept", "const", "consteval", "constexpr",
"constinit", "const_cast", "continue", "co_await", "co_return", "co_yield",
"decltype", "default", "delete", "do", "double", "dynamic_cast", "else",
"enum", "explicit", "export", "extern", "false", "float", "for", "friend",
"goto", "if", "inline", "int", "long", "mutable", "namespace", "new", 
"noexcept", "not", "not_eq", "nullptr", "operator", "or", "or_eq", "private",
"public", "protected", "register", "reinterpret_cast", "requires", "return",
"short", "signed", "sizeof", "static", "static_assert", "static_cast", "struct",
"switch", "synchronized", "template", "this", "thread_local", "throw", "true",
"try", "typedef", "typeid", "typename", "union", "unsigned", "using", "virtual",
"void", "volatile", "wchar_t", "while", "xor", "xor_eq"};

/*****************************************************************************
 * function declaration : <type_mod> type_spec function_name( <parameters> );
 *  function definition: <type_mod> type_spec function_name (<parameters>) { <body>}
 ******************************************************************************/

map<string, string> argparse(char* argv[]);
void help();

int main(int argc, char* argv[]) {
    if(argc < 3) {
        help();
        return 0;
    } 

    map<string,string> arguments = argparse(argv);
    cout << "ARGUMENTS: " << arguments["input"] << " " << arguments["output"];
    cout << endl;


    cout << "[INFO] Starting..." << endl;
    try {
        std::ifstream inFile(arguments["input"], ifstream::in);
        char line[512];
        const regex rex("([a-zA-Z0-9_]+)\\(([a-zA-Z0-9_&*]*\\s*\\,?)*\\)");
        int linecntr = 1;
        while(!inFile.eof()) {
            inFile.getline(line, 512);
           // cout << line << endl;
            string s_line(line);
            
            if(regex_match(line, rex) )
            std::cout << linecntr << " "<< line << ": -- " << regex_match(line, rex) << '\n';
            linecntr++;
        }   
        
        /*close file */
        inFile.close();
    } catch (...) {
        cout << "Something went wrong with opening the file" << endl;
        exit(-1);
    }
    #if 0
    for(auto key: keyWords) {
        cout << key << endl;
    }
    #endif 
    cout << "[INFO] Ended" << endl;
}

map<string,string> argparse(char* argv[]) {
    map <string, string> arguments;
    arguments["input"] = argv[1];
    arguments["output"] = argv[2];

    return arguments;
}

void help(){
    cout << "USAGE: ./regex <input_file> <output_file>" << endl;
}


/**
 * 
 * c function call ([a-zA-Z0-9_]+)\(([a-zA-Z0-9_&*]*\s*\,?)*\) 
 * c function header ([a-zA-Z0-9]+)\s+([a-zA-Z0-9_]+)\(([a-zA-Z0-9_&*]*\s*\,?)*\)
 */