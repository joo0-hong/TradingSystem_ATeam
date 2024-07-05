#include "JusikApplication.h"

class LoginFailException : public std::exception {};
class ZeroPriceTradingException : public std::exception {};

JusikApplication::JusikApplication()
	: isLoggedIn_{ false }, brocker{nullptr}
{
}

void JusikApplication::selectStockBrocker(const std::string& stockBrocker)
{

}

void JusikApplication::login(const std::string& id, const std::string& pass)
{
	isLoggedIn_ = true;
}

int JusikApplication::getPrice(const std::string& stock)
{
	return 1;
}

void JusikApplication::buy(const std::string& stock, const int price, const int amount)
{
	throwExceptionWhenNotLoggedIn();
	throwExceptionWhenZeroPriceTrade(price);
}
void JusikApplication::throwExceptionWhenNotLoggedIn()
{
	if (isLoggedIn_ == false) {
		throw LoginFailException();
	}
}
void JusikApplication::throwExceptionWhenZeroPriceTrade(const int price)
{
	if (price <= 0) {
		throw ZeroPriceTradingException();
	}
}

void JusikApplication::sell(const std::string& stock, const int price, const int amount)
{
	throwExceptionWhenZeroPriceTrade(price);
}
