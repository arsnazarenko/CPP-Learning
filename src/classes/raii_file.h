#ifndef RAII_FILE
#define RAII_FILE

#include <cstdio>

class raii_file{
    public:
    raii_file(raii_file const& file) = delete;
        raii_file operator=(raii_file const& file) = delete;
        explicit raii_file(const char *file_name);
        ~raii_file();
        void write(char const* str );
    private:

        std::FILE* file;

};
#endif