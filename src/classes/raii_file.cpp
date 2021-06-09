#include "raii_file.h"
#include <cstdio>
raii_file::raii_file(const char *file_name) : file(std::fopen(file_name, "w+")) {
    // if ( !file_) {
    //  throw except...
    // }
}

raii_file::~raii_file() {
    std::fclose(file);
}

void raii_file::write(char const* str ) {
    std::fputs(str, file);
}