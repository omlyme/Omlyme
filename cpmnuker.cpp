#include "include/cpmnuker.hpp"

CPMNuker::CPMNuker(std::string access_key) {
    this->access_key = access_key;
}

bool CPMNuker::account_login(std::string email, std::string password)
{
    cpr::Response response = cpr::Post(
        cpr::Url{"https://api.anasov.ly/cpmnuker/login.php"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{
            {"account_email", email},
            {"account_password", password}
        }
    );
    json data = json::parse(response.text);
    if(data["ok"]){
        this->auth_token = data["auth"];
        return true;
    } else {
        return false;
    }
}

bool CPMNuker::account_register(std::string email, std::string password)
{
    cpr::Response response = cpr::Post(
        cpr::Url{"https://api.anasov.ly/cpmnuker/register.php"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{
            {"account_email", email},
            {"account_password", password}
        }
    );
    json data = json::parse(response.text);
    if(data["ok"]){
        this->auth_token = data["auth"];
        return true;
    } else {
        return false;
    }
}

bool CPMNuker::account_change_data(std::string vname, std::string vvalue)
{
    cpr::Response response = cpr::Post(
        cpr::Url{"https://api.anasov.ly/cpmnuker/save_data.php"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{
            {"account_auth", this->auth_token},
            {"var_name", vname},
            {"var_value", vvalue}
        }
    );
    json data = json::parse(response.text);
    if(data["ok"]){
        return true;
    } else {
        return false;
    }
}

bool CPMNuker::account_change_rating()
{
    cpr::Response response = cpr::Post(
        cpr::Url{"https://api.anasov.ly/cpmnuker/save_rating.php"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{{"account_auth", this->auth_token}}
    );
    json data = json::parse(response.text);
    if(data["ok"]){
        return true;
    } else {
        return false;
    }
}

bool CPMNuker::account_delete()
{
    cpr::Response response = cpr::Post(
        cpr::Url{"https://api.anasov.ly/cpmnuker/delete.php"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{{"account_auth", this->auth_token}}
    );
    json data = json::parse(response.text);
    if(data["ok"]){
        return true;
    } else {
        return false;
    }
}
