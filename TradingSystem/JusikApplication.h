#pragma once
#include <string>

class JusikApplication
{
public:
    JusikApplication();

    void selectStockBrocker(const std::string& stockBrocker);
    void login(const std::string& id, const std::string& pass);
    int getPrice(const std::string& stock);
    void buy(const std::string& stock, const int price);
    void throwExceptionWhenNotLoggedIn();
    void throwExceptionWhenZeroPriceTrade(const int price);
    void sell(const std::string& stock, const int price);
private:
    bool isLoggedIn_;
};