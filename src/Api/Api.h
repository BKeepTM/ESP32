#include <string>
#include "WiFi.h"
#include <HTTPClient.h>
#include "time.h"

class Api {
    private:
        std::string apiUrl;
        const char* ssid = "A1-0EE5E0"; // test 
        const char* password = "8UUNQN8P8G"; // test
        const char* ntpServer = "pool.ntp.org";
        const long  gmtOffset_sec = 3600;
        const int   daylightOffset_sec = 3600;
    public: 
        void connect();
        Api(std::string apiUrl);
        bool postWeight(float weight);
        String printLocalTime();
};