#pragma once
#define interface struct
#include <string>

interface StockerBrockerDriver
{
	virtual void logIn(const std::string& id, const std::string& pass) = 0;
	virtual void buyStock(const std::string& stock, const int price, const int amount) = 0;
	virtual void sellStock(const std::string& stock, const int price, const int amount) = 0;
	virtual int getPrice(const std::string& stock) = 0;
};
