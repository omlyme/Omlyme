#include "include/cpmnuker.hpp"

CPMNuker::CPMNuker(const std::string& access_key) {
    this->access_key = access_key;
}

int CPMNuker::account_login(const std::string& email, const std::string& password)
{
    cpr::Response response = cpr::Post(
        cpr::Url{this->BASE_URL + "/account_login"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{
            {"account_email", email},
            {"account_password", password}
        }
    );
    json data = json::parse(response.text);
    if(data["ok"] && data["error"] == 0){
        this->auth_token = data["auth"];
        return 0;
    } else {
        return data["error"];
    }
}

bool CPMNuker::account_register(const std::string& email, const std::string& password)
{
    cpr::Response response = cpr::Post(
        cpr::Url{this->BASE_URL + "/account_register"},
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

bool CPMNuker::account_delete()
{
    cpr::Response response = cpr::Post(
        cpr::Url{this->BASE_URL + "/account_delete"},
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

bool CPMNuker::account_set_data(json content)
{
    cpr::Response response = cpr::Post(
        cpr::Url{this->BASE_URL + "/set_data"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{
            {"account_auth", this->auth_token},
            {"content", content.dump()}
        }
    );
    json data = json::parse(response.text);
    if(data["ok"]){
        return true;
    } else {
        return false;
    }
}

json CPMNuker::account_get_data()
{
    cpr::Response response = cpr::Post(
        cpr::Url{this->BASE_URL + "/get_data"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{{"account_auth", this->auth_token}}
    );
    json data = json::parse(response.text);
    return data["data"];
}

bool CPMNuker::account_set_rank()
{
    cpr::Response response = cpr::Post(
        cpr::Url{this->BASE_URL + "/set_rank"},
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

bool CPMNuker::account_save_car(const std::string& car_id)
{
    cpr::Response response = cpr::Post(
        cpr::Url{this->BASE_URL + "/unlock_car"},
        cpr::Parameters{{"key", this->access_key}},
        cpr::Payload{
            {"account_auth", this->auth_token},
            {"car_id", car_id}
        }
    );
    json data = json::parse(response.text);
    if(data["ok"]){
        return true;
    } else {
        return false;
    }
}

json CPMNuker::access_key_data()
{
    cpr::Response response = cpr::Get(cpr::Url{this->BASE_URL + "/get_key_data"}, cpr::Parameters{{"key", this->access_key}});
    json data = json::parse(response.text);
    return data;
}
