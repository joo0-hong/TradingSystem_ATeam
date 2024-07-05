#pragma once
#include <string>
#include "StockerBrockerDriver.h"

class JusikApplication
{
public:
    JusikApplication();

    void selectStockBrocker(const std::string& stockBrocker);
    void login(const std::string& id, const std::string& pass);
    int getPrice(const std::string& stock);
    void buy(const std::string& stock, const int price, const int amount);
    void throwExceptionWhenNotLoggedIn();
    void throwExceptionWhenZeroPriceTrade(const int price);
    void sell(const std::string& stock, const int price, const int amount);

private:
    bool isLoggedIn_;
    StockerBrockerDriver* brocker;

};