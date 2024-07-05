#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TradingSystem/JusikApplication.cpp"

using namespace std;
using namespace testing;

TEST(ApplicationTest, StartApplication) {
	JusikApplication app;

	EXPECT_THAT(&app, NotNull());
}

TEST(ApplicationTest, AppDefaultAPI) {
	JusikApplication app;

	app.selectStockBrocker("Kiwer");
	app.login("ATeam", "1234qwer");

	int currentPrice = app.getPrice("Samsung");
	EXPECT_THAT(currentPrice, Ge(0));

	app.buy("Samsung", 80000);
	app.sell("Samsung", 100000);
}
