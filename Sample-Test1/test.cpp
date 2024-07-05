#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TradingSystem/JusikApplication.cpp"

using namespace std;
using namespace testing;

class AppFixture : public testing::Test {
public:
	JusikApplication app;
};

TEST(ApplicationTest, StartApplication) {
	JusikApplication* appPointer = new JusikApplication();
	EXPECT_THAT(appPointer, NotNull());
}

TEST_F(AppFixture, AppDefaultAPI) {
	JusikApplication app;

	app.selectStockBrocker("Kiwer");
	app.login("ATeam", "1234qwer");

	int currentPrice = app.getPrice("Samsung");
	EXPECT_THAT(currentPrice, Gt(0));

	app.buy("Samsung", 80000);
	app.sell("Samsung", 100000);
}

TEST_F(AppFixture, BuyingWithoutLogin) {
	app.selectStockBrocker("Nemo");

	EXPECT_THROW({
		app.buy("Samsung", 80000);
		}, std::exception);
}

TEST_F(AppFixture, ZeroBuying) {
	app.selectStockBrocker("Nemo");
	app.login("ATeam", "1234qwer");

	EXPECT_THROW({
		app.buy("Samsung", 0);
		}, std::exception);
}

TEST_F(AppFixture, ZeroSelling) {
	app.selectStockBrocker("Nemo");
	app.login("ATeam", "1234qwer");

	EXPECT_THROW({
		app.sell("Samsung", 0);
		}, std::exception);
}


