#ifndef CPMNUKER_HPP
#define CPMNUKER_HPP

#include <iostream>
#include <cpr/cpr.h>
#include "json.hpp"

using json = nlohmann::json;

class CPMNuker
{

public:
    CPMNuker(const std::string& access_key);
    int account_login(const std::string& email, const std::string& password);
    bool account_register(const std::string& email, const std::string& password);
    bool account_change_data(const std::string& vname, const std::string& vvalue);
    bool account_save_car(const std::string& car_id);
    bool account_change_rating();
    bool account_delete();

private:
    std::string access_key;
    std::string auth_token;
};

#endif // CPMNUKER_HPP
