#include <iostream>
#include <termcolor/termcolor.hpp>
#include "include/cpmnuker.hpp"
#include "include/base64.hpp"
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

int main()
{
    while(true){
        banner();
        std::string account_email = asker::input("Account Email:", true);
        std::string account_password = asker::input("Account Password:", true);
        std::string access_key = asker::input("Access Key:", true);
        std::cout << termcolor::bold << termcolor::cyan << "↺ trying to login" << termcolor::reset << ": ";
        std::cout.flush();
        CPMNuker *cpm = new CPMNuker(access_key);
        int login_status = cpm->account_login(account_email, account_password);
        if(login_status == 0){
            std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl;
            csleep(2);
        } else if(login_status == 100) {
            std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
            std::cout << "==================================" << std::endl;
            bool answ = asker::confirm("Want to Register new Account ?");
            if(!answ) {
                std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
                csleep(2);
                continue;
            } else {
                std::cout << std::endl << termcolor::bold << termcolor::cyan << "↺ Creating new Account" << termcolor::reset << ": ";
                std::cout.flush();
                bool register_status = cpm->account_register(account_email, account_password);
                if(!register_status){
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
        } else if(login_status == 101) {
            std::cout << termcolor::bold << termcolor::red << "FAILED [INVALID PASSWORD]." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
            csleep(2);
            continue;
        } else if(login_status == 102) {
            std::cout << termcolor::bold << termcolor::red << "FAILED [INSUFFICIENT FUNDS]." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
            csleep(2);
            continue;
        } else if(login_status == 103) {
            std::cout << termcolor::bold << termcolor::red << "FAILED [INVALID ACCESS KEY]." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
            csleep(2);
            continue;
        } else {
            std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::yellow << "✶ Please try again." << termcolor::reset << std::endl;
            csleep(2);
            continue;
        }
        while(true){
            banner();
            std::cout << termcolor::bold << termcolor::cyan << "[1]: Increase Money." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[2]: Increase Coins." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[3]: King Rank." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[4]: Change ID." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[5]: Rainbow Name." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[6]: Delete Account." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::cyan << "[7]: New Account." << termcolor::reset << std::endl;
            std::cout << termcolor::bold << termcolor::red << "[0]: Exit." << termcolor::reset << std::endl;
            std::cout << std::endl;
            std::string service = asker::input("Select a Service [1-7]:", true);
            int service_int;
            try { service_int = std::stoi(service); } catch (std::invalid_argument e) { continue; }
            banner();
            switch(service_int){
            case 1: {
                std::cout << termcolor::bold << termcolor::cyan << "✶ Enter how much money do you want." << termcolor::reset << std::endl;
                std::string amount = asker::input("Amount:", true);
                std::cout << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "↺ saving your data" << termcolor::reset << ": ";
                std::cout.flush();
                bool service_status = cpm->account_change_data("money", amount);
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
            case 2: {
                std::cout << termcolor::bold << termcolor::cyan << "✶ Enter how many coins do you want." << termcolor::reset << std::endl;
                std::string amount = asker::input("Amount:", true);
                std::cout << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "↺ saving your data" << termcolor::reset << ": ";
                std::cout.flush();
                bool service_status = cpm->account_change_data("coin", amount);
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
            case 3: {
                std::cout << termcolor::bold << termcolor::red << "! King Rank will not work if you still logged in." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "↺ Giving you a King Rank" << termcolor::reset << ": ";
                std::cout.flush();
                bool service_status = cpm->account_change_rating();
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
            case 4: {
                std::cout << termcolor::bold << termcolor::cyan << "✶ Enter Your new ID" << termcolor::reset << std::endl;
                std::string changed_id = asker::input("ID:", true);
                std::cout << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "↺ saving your data" << termcolor::reset << ": ";
                std::cout.flush();
                bool service_status = cpm->account_change_data("localID", changed_id);
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
            case 5: {
                std::cout << termcolor::bold << termcolor::cyan << "✶ Enter Your Name to Color" << termcolor::reset << std::endl;
                std::string name = asker::input("Name:", true);
                std::string colored_name = colorizeNameRainbow(name);
                std::cout << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "↺ saving your data" << termcolor::reset << ": ";
                std::cout.flush();
                bool service_status = cpm->account_change_data("Name", colored_name);
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
            case 6: {
                std::cout << termcolor::bold << termcolor::red << "! After deleting your account there is no going back !!!." << termcolor::reset << std::endl;
                bool answer1 = asker::confirm("Are you sure ?");
                if(answer1){
                    std::cout << termcolor::bold << termcolor::cyan << "↺ Deleting Your Account" << termcolor::reset << ": ";
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
            case 7: {
                std::cout << termcolor::bold << termcolor::cyan << "✶ Enter Your New Accounts Info" << termcolor::reset << std::endl;
                std::string account_email = asker::input("Account Email:", true);
                std::string account_password = asker::input("Account Password:", true);
                std::cout << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "↺ Creating new Account" << termcolor::reset << ": ";
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
            case 0: {
                std::cout << termcolor::bold << termcolor::yellow << "✴ Thank You for using our tool, please join our telegram channel: " << termcolor::blue << "@CPMNuker" << termcolor::reset << "." << std::endl;
                break;
            }
            default: { continue; }
            }
            break;
        }
        break;
    }
    return 0;
}
