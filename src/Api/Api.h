#include <string>
#include "WiFi.h"
#include <HTTPClient.h>
class Api {
    private:
        std::string apiUrl;
        const char* ssid = "A1-0EE5E0"; // test 
        const char* password = "8UUNQN8P8G"; // test
    public: 
        void connect();
        Api(std::string apiUrl);
        bool postWeight(float weight);
};