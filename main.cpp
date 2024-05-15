#include <iostream>
#include <termcolor/termcolor.hpp>
#include "include/progressbar.hpp"
#include "include/cpmnuker.hpp"
#include "include/asker.hpp"

#ifdef _WIN32
#include <windows.h>

void csleep(unsigned milliseconds)
{
    Sleep(milliseconds);
}
#else
#include <unistd.h>

void csleep(unsigned milliseconds)
{
    sleep(milliseconds);
}
#endif

std::string colorizeNameRainbow(const std::string& name) {
    std::string rainbowColors[] = { "FF0000", "FFFF00", "00FF00", "00FFFF", "0000FF", "FF00FF" };
    std::string coloredName;
    int colorIndex = 0;
    for (char c : name) {
        if(c == ' ') {
            coloredName.push_back(toupper(c));
            continue;
        }
        coloredName.append("[" + rainbowColors[colorIndex] + "]");
        coloredName.push_back(toupper(c));
        colorIndex++;
        colorIndex %= sizeof(rainbowColors) / sizeof(rainbowColors[0]);
    }
    return coloredName;
}

void banner()
{
    std::system("clear");
    std::cout << termcolor::bold << termcolor::green << "⟡ CPMNuker" << termcolor::reset << ": Car Parking Multiplayer Hacking ToolKit." << std::endl;
    std::cout << termcolor::bold << termcolor::green << "⟡ Telegram" << termcolor::reset << ": " << termcolor::blue << "@ItzAnasov" << termcolor::reset << " or " << termcolor::blue << "@CPMNuker" << termcolor::reset << "."  << std::endl;
    std::cout << termcolor::bold << termcolor::green <<"⟡ Website" << termcolor::reset  << " : " << termcolor::blue << "https://anasov.ly" << termcolor::reset << std::endl;
    std::cout << "=========================================================" << std::endl;
    std::cout << termcolor::bold << termcolor::yellow << "! Note" << termcolor::reset << ": Logout from the account before using this tool !." << std::endl << std::endl;
}

void loadData(CPMNuker* cpm)
{
    json data = cpm->account_get_data();
    std::string name = data.contains("Name")? data["Name"] : "UNDEFINED";
    std::string localID = data.contains("localID")? data["localID"] : "UNDEFINED";
    std::string money = data.contains("money")? data["money"] : "UNDEFINED";
    std::string coin = data.contains("coin")? data["coin"] : "UNDEFINED";

    std::cout << termcolor::bold << termcolor::red << "========[" << termcolor::white << " Player Information " << termcolor::red << "]========" << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::green << "⟡" << termcolor::cyan << " Name    : " << termcolor::white << name << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::green << "⟡" << termcolor::cyan << " User ID : " << termcolor::white << localID << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::green << "⟡" << termcolor::cyan << " Money   : " << termcolor::white << money << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::green << "⟡" << termcolor::cyan << " Coins   : " << termcolor::white << coin << termcolor::reset << std::endl;
    std::cout << termcolor::bold << termcolor::red << "=============[" << termcolor::white << " SERVICE " << termcolor::red << "]==============" << termcolor::reset << std::endl;
}

int main()
{
    while(true){
        banner();
        std::string account_email = asker::input("Account Email:", true);
        std::string account_password = asker::input("Account Password:", true);
        std::string access_key = asker::input("Access Key:", true);
        std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " trying to login: " << termcolor::reset;
        std::cout.flush();
        CPMNuker *cpm = new CPMNuker(access_key);
        int login_status = cpm->account_login(account_email, account_password);
        switch (login_status) {
            case CPMNuker::RESPONSE::SUCCESSFUL:
                std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl;
                csleep(2);
                break;

            case CPMNuker::RESPONSE::EMAIL_NOT_FOUND: {
                std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                std::cout << "==================================" << std::endl;
                bool answ = asker::confirm("Want to Register new Account ?");
                if (!answ) {
                    std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                    csleep(2);
                    continue;
                } else {
                    std::cout << std::endl << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " Creating new Account" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool register_status = cpm->account_register(account_email, account_password);
                    if (!register_status) {
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(2);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::red << "! You've been automatically signed in as (" << account_email << ") !!!" << termcolor::reset << std::endl;
                        csleep(3);
                    }
                }
                break;
            }

            case CPMNuker::RESPONSE::INVALID_PASSWORD:
                std::cout << termcolor::bold << termcolor::red << "FAILED [INVALID PASSWORD]." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                csleep(2);
                continue;

            case CPMNuker::RESPONSE::INSUFFICIENT_FUNDS:
                std::cout << termcolor::bold << termcolor::red << "FAILED [INSUFFICIENT FUNDS]." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                csleep(2);
                continue;

            case CPMNuker::RESPONSE::INVALID_ACCESS_KEY:
                std::cout << termcolor::bold << termcolor::red << "FAILED [INVALID ACCESS KEY]." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                csleep(2);
                continue;

            default:
                std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                csleep(2);
                continue;
        }
        while(true){
            banner();
            loadData(cpm);
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "01" << termcolor::cyan << "]" << termcolor::white << ": Change Money." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "02" << termcolor::cyan << "]" << termcolor::white << ": Change Coins." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "03" << termcolor::cyan << "]" << termcolor::white << ": Change Rank [King Rank]." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "04" << termcolor::cyan << "]" << termcolor::white << ": Change User ID." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "05" << termcolor::cyan << "]" << termcolor::white << ": Change Name." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "06" << termcolor::cyan << "]" << termcolor::white << ": Change Name [Rainbow]." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "07" << termcolor::cyan << "]" << termcolor::white << ": Unlock All Cars." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "08" << termcolor::cyan << "]" << termcolor::white << ": Account Delete." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "09" << termcolor::cyan << "]" << termcolor::white << ": Account Register [New]." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[" << termcolor::green << "00" << termcolor::cyan << "]" << termcolor::white << ": Exit." << termcolor::reset << std::endl;
            std::cout << std::endl;
            std::string service = asker::input("Select a Service [1-9 or 0]:", true);
            int service_int;
            try { service_int = std::stoi(service); } catch (std::invalid_argument e) { continue; }
            banner();
            switch(service_int){
                case CPMNuker::SERVICE::CHNAGE_MONEY: {
                    std::cout << termcolor::bold << termcolor::cyan << "✶ Enter how much money do you want." << termcolor::reset << std::endl;
                    std::string amount = asker::input("Amount:", true);
                    std::cout << std::endl;
                    std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " saving your data" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool service_status = cpm->account_set_data("money", amount);
                    if(!service_status){
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                        csleep(1);
                        continue;
                    }
                }
                case CPMNuker::SERVICE::CHANGE_COINS: {
                    std::cout << termcolor::bold << termcolor::cyan << "✶ Enter how many coins do you want." << termcolor::reset << std::endl;
                    std::string amount = asker::input("Amount:", true);
                    std::cout << std::endl;
                    std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " saving your data" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool service_status = cpm->account_set_data("coin", amount);
                    if(!service_status){
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                        csleep(1);
                        continue;
                    }
                }
                case CPMNuker::SERVICE::CHANGE_RANK: {
                    std::cout << termcolor::bold << termcolor::red << "! King Rank will not work if you still logged in." << termcolor::reset << std::endl;
                    std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " Giving you a King Rank" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool service_status = cpm->account_set_rank();
                    if(!service_status){
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                        csleep(1);
                        continue;
                    }
                }
                case CPMNuker::SERVICE::CHANGE_USERID: {
                    std::cout << termcolor::bold << termcolor::cyan << "✶ Enter Your new ID" << termcolor::reset << std::endl;
                    std::string changed_id = asker::input("ID:", true);
                    std::cout << std::endl;
                    std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " saving your data" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool service_status = cpm->account_set_data("localID", changed_id);
                    if(!service_status){
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                        csleep(1);
                        continue;
                    }
                }
                case CPMNuker::SERVICE::CHANGE_NAME: {
                    std::cout << termcolor::bold << termcolor::cyan << "✶ Enter Your Name" << termcolor::reset << std::endl;
                    std::string name = asker::input("Name:", true);
                    std::cout << std::endl;
                    std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " saving your data" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool service_status = cpm->account_set_data("Name", name);
                    if(!service_status){
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                        csleep(1);
                        continue;
                    }
                }
                case CPMNuker::SERVICE::CHANGE_NAME_RAINBOW: {
                    std::cout << termcolor::bold << termcolor::cyan << "✶ Enter Your Name to Color" << termcolor::reset << std::endl;
                    std::string name = asker::input("Name:", true);
                    std::string colored_name = colorizeNameRainbow(name);
                    std::cout << std::endl;
                    std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " saving your data" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool service_status = cpm->account_set_data("Name", colored_name);
                    if(!service_status){
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                        csleep(1);
                        continue;
                    }
                }
                case CPMNuker::SERVICE::UNLOCK_ALL_CARS: {
                    continue;
                    // std::cout << termcolor::bold << termcolor::red << "! King Rank will not work if you still logged in." << termcolor::reset << std::endl;
                    // std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " Giving you a King Rank ..." << termcolor::reset << std::endl;
                    // progressbar bar(202);
                    // int service_failed = 0;
                    // int service_success = 0;
                    // for(int i = 0; i < 202; i++){
                    //     bool service_status = cpm->account_save_car(std::to_string(i));
                    //     if(service_status) service_success++;
                    //     else service_failed++;
                    //     bar.update();
                    // }
                    // if(service_failed != 0 && service_success == 0) {
                    //     std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                    //     std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                    //     csleep(1);
                    //     continue;
                    // } else if(service_failed == 0 && service_success != 0){
                    //     std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                    //     csleep(1);
                    //     continue;
                    // } else {
                    //     std::cout << termcolor::bold << termcolor::yellow << "SUCCESS [NOT ALL CARS]." << termcolor::reset << std::endl;
                    //     std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                    //     csleep(1);
                    //     continue;
                    // }
                }
                case CPMNuker::SERVICE::ACCOUNT_DELETE: {
                    std::cout << termcolor::bold << termcolor::red << "! After deleting your account there is no going back !!!." << termcolor::reset << std::endl;
                    bool answer1 = asker::confirm("Are you sure ?");
                    if(answer1){
                        std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " Deleting Your Account" << termcolor::reset << ": ";
                        std::cout.flush();
                        bool service_status = cpm->account_delete();
                        if(!service_status){
                            std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                            std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                            csleep(1);
                            continue;
                        } else {
                            std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl << std::endl;
                            std::cout << "==================================" << std::endl;
                            std::cout << termcolor::bold << termcolor::yellow << "✴ Thank You for using our tool, please join our telegram channel: " << termcolor::blue << "@CPMNuker" << termcolor::reset << "." << std::endl;
                            break;
                        }
                    } else {
                        std::cout << termcolor::bold << termcolor::cyan << "✶ You can use another service instead :)." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    }
                }
                case CPMNuker::SERVICE::ACCOUNT_REGISTER: {
                    std::cout << termcolor::bold << termcolor::cyan << "✶ Enter Your New Accounts Info" << termcolor::reset << std::endl;
                    std::string account_email = asker::input("Account Email:", true);
                    std::string account_password = asker::input("Account Password:", true);
                    std::cout << std::endl;
                    std::cout << termcolor::bold << termcolor::green << "↺" << termcolor::cyan << " Creating new Account" << termcolor::reset << ": ";
                    std::cout.flush();
                    bool service_status = cpm->account_register(account_email, account_password);
                    if(!service_status){
                        std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                        csleep(1);
                        continue;
                    } else {
                        std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl;
                        std::cout << termcolor::bold << termcolor::red << "! You've been automatically signed in as (" << account_email << ") !!!" << termcolor::reset << std::endl << std::endl;
                        std::cout << "==================================" << std::endl;
                        bool answer = asker::confirm("Do You want to Exit ?");
                        if(!answer){
                            continue;
                        } else {
                            std::cout << termcolor::bold << termcolor::yellow << "✴ Thank You for using our tool, please join our telegram channel: " << termcolor::blue << "@CPMNuker" << termcolor::reset << "." << std::endl;
                            break;
                        }
                    }
                }

                case CPMNuker::SERVICE::EXIT:
                    std::cout << termcolor::bold << termcolor::yellow << "✴ Thank You for using our tool, please join our telegram channel: " << termcolor::blue << "@CPMNuker" << termcolor::reset << "." << std::endl;
                    break;

                default:
                    continue;
            }
            break;
        }
        break;
    }
    return 0;
}
