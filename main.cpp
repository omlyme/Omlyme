#include <iostream>
#include <termcolor/termcolor.hpp>
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
    sleep(milliseconds); // takes microseconds
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

        colorIndex++;  // Simply increment the index for each character
        colorIndex %= sizeof(rainbowColors) / sizeof(rainbowColors[0]); // Wrap around when reaching the end
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
        bool login_status = cpm->account_login(account_email, account_password);
        if(!login_status){
            std::cout << termcolor::bold << termcolor::red << "FAILED." << termcolor::reset << std::endl;
            csleep(3);
            continue;
        } else {//RUJHYZ1BTL
            std::cout << termcolor::bold << termcolor::green << "SUCCESS." << termcolor::reset << std::endl;
            csleep(2);
            while(true){
                banner();
                std::cout << termcolor::bold << termcolor::cyan << "[1]: Increase Money." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "[2]: Increase Coins." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "[3]: King Rank." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "[4]: Change ID." << termcolor::reset << std::endl;
                std::cout << termcolor::bold << termcolor::cyan << "[5]: Rainbow Name." << termcolor::reset << std::endl;
                std::cout << std::endl;
                std::string service = asker::input("Select a Service [1-5]:", true);
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
                default: { continue; }
                }
                break;
            }
        }
        break;
    }
    return 0;
}
