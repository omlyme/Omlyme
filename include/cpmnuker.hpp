#ifndef CPMNUKER_HPP
#define CPMNUKER_HPP

#include <iostream>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;

/**
      0: SUCCESSFUL
    100: EMAIL_NOT_FOUND
    101: INVALID_PASSWORD
    102: INSUFFICIENT_FUNDS
    103: INVALID_ACCESS_KEY
    104: MISSING_PARAMETERS
    105: EMAIL_EXISTS
    106: MISSING_PASSWORD
    107: INVALID_EMAIL
    108: MISSING_EMAIL
    109: ACCESS_KEY_BLOCKED
    404: UNKNOWN_ERROR
**/

class CPMNuker
{

public:
    CPMNuker(const std::string& access_key);
    int account_login(const std::string& email, const std::string& password);
    bool account_register(const std::string& email, const std::string& password);
    bool account_delete();
    bool account_set_data(json content);
    json account_get_data();
    bool account_set_rank();
    bool account_save_car(const std::string& car_id);
    json access_key_data();
    enum RESPONSE {
        SUCCESSFUL = 0,
        EMAIL_NOT_FOUND = 100,
        INVALID_PASSWORD = 101,
        INSUFFICIENT_FUNDS = 102,
        INVALID_ACCESS_KEY = 103,
        MISSING_PARAMETERS = 104,
        EMAIL_EXISTS = 105,
        MISSING_PASSWORD = 106,
        INVALID_EMAIL = 107,
        MISSING_EMAIL = 108,
        ACCESS_KEY_BLOCKED = 109,
        UNKNOWN_ERROR = 404
    };
    enum SERVICE {
        EXIT = 0,
        CHNAGE_MONEY = 1,
        CHANGE_COINS = 2,
        CHANGE_RANK = 3,
        CHANGE_USERID = 4,
        CHANGE_NAME = 5,
        CHANGE_NAME_RAINBOW = 6,
        UNLOCK_ALL_CARS = 7,
        ACCOUNT_DELETE = 8,
        ACCOUNT_REGISTER = 9
    };

private:
    std::string BASE_URL = "https://api.anasov.ly/v1/cpmnuker";
    std::string access_key;
    std::string auth_token;

};


#endif // CPMNUKER_HPP
