#include <iostream>
#include <fstream>
#include <string>

class ToFile : public std::ofstream {
    private:
        std::string src;
        std::ofstream file;

    public:
        ToFile(std::string link) {
            src = link;
            
            file.open(src);
        }

        ~ToFile() {
            file.close();
        }

        void write(std::string data) {
            file << data << std::endl;
        }
};