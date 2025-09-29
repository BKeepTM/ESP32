
#include <vector>
#include <string>
#include "mbedtls/md.h"
class Dispatcher {
    private: 
        std::vector<unsigned char> hashKey; // kljuc pri zahtevkih
        
    public: 
        Dispatcher(std::vector<unsigned char> hashKey);
        bool postWeight(float weight);
        
};