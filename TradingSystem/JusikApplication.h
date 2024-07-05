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
    void checkCanBuyState(const int price);
    void throwExceptionWhenNotLoggedIn();
    void sell(const std::string& stock, const int price);
    void throwExceptionWhenZeroPriceTrade(const int price);
private:
    bool isLogedIn_;
};