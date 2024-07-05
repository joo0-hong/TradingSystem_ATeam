#include "JusikApplication.h"

class LoginFailException : public std::exception {};
class ZeroPriceTradingException : public std::exception {};

JusikApplication::JusikApplication()
	: isLogedIn_{ false }
{
}

void JusikApplication::selectStockBrocker(const std::string& stockBrocker)
{

}

void JusikApplication::login(const std::string& id, const std::string& pass)
{
	isLogedIn_ = true;
}

int JusikApplication::getPrice(const std::string& stock)
{
	return 1;
}

void JusikApplication::buy(const std::string& stock, const int price)
{
	checkCanBuyState(price);
}
void JusikApplication::checkCanBuyState(const int price)
{
	throwExceptionWhenNotLoggedIn();
	throwExceptionWhenZeroPriceTrade(price);
}
void JusikApplication::throwExceptionWhenNotLoggedIn()
{
	if (isLogedIn_ == false) {
		throw LoginFailException();
	}
}
void JusikApplication::throwExceptionWhenZeroPriceTrade(const int price)
{
	if (price <= 0) {
		throw ZeroPriceTradingException();
	}
}

void JusikApplication::sell(const std::string& stock, const int price)
{
	throwExceptionWhenZeroPriceTrade(price);
}
