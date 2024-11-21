#ifndef READER_H
#define READER_H

#include <string>     
#include <fstream>    

class Reader {
private:
    std::ifstream inputFile; 

public:
    explicit Reader(const std::string& filename);
    std::string getLine();
    void close();
    ~Reader();
};

#endif // READER_H