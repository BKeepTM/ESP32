
#include "Dispatcher.h"
//class Dispatcher {
//    private: 
//        unsigned char hashKey[32]; // kljuc pri zahtevkih
//    public: 
//        Dispatcher(unsigned char hashKey[32]);
//        bool postWeight(float weight);
//
//};
Dispatcher::Dispatcher(std::vector<unsigned char> hashKey) {
    this->hashKey = hashKey;
}
//Dispatcher::postWeight()