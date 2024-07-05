#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TradingSystem/JusikApplication.cpp"

using namespace std;
using namespace testing;

class BrockerMock : public StockBrocker {
public:
	MOCK_METHOD(void, selectStockBrocker, (string stockBrocker), (override));
	MOCK_METHOD(void, login, (string id, string pass), (override));
	MOCK_METHOD(int, getPrice, (string stock), (override));
	MOCK_METHOD(void, buy, (string stock, int price, int count), (override));
	MOCK_METHOD(void, sell, (string stock, int price, int count), (override));

protected:
	void SetUp() {
	}
};

class AppFixture : public testing::Test {
public:
	void login(string stockBrocker)
	{
		app.selectStockBrocker(stockBrocker);
		app.login("ATeam", "1234qwer");
	}

	NiceMock<BrockerMock> mk;
	StockBrocker brocker{ mk };
	JusikApplication app{ brocker };
};

TEST(ApplicationTest, StartApplication) {
	JusikApplication* appPointer = new JusikApplication();
	EXPECT_THAT(appPointer, NotNull());

	delete appPointer;
}

TEST_F(AppFixture, AppDefaultAPI) {
	JusikApplication app;

	app.selectStockBrocker("Kiwer");
	app.login("ATeam", "1234qwer");

	int currentPrice = app.getPrice("Samsung");
	EXPECT_THAT(currentPrice, Gt(0));

	app.buy("Samsung", 80000, 1);
	app.sell("Samsung", 100000, 1);
}

TEST_F(AppFixture, BuyingWithoutLogin) {
	app.selectStockBrocker("Nemo");

	EXPECT_THROW({
		app.buy("Samsung", 80000, 1);
		}, std::exception);
}

TEST_F(AppFixture, ZeroPriceBuying) {
	login("Nemo");

	EXPECT_THROW({
		app.buy("Samsung", 0, 1);
		}, std::exception);
}

TEST_F(AppFixture, ZeroPriceSelling) {
	login("Nemo");

	EXPECT_THROW({
		app.sell("Samsung", 0, 1);
		}, std::exception);
}

TEST_F(AppFixture, APIsCallingLogin) {

	EXPECT_CALL(mk, selectStockBrocker(_))
		.Times(1);

	EXPECT_CALL(mk, login(_, _))
		.Times(1);

	login("Nemo");
}
