#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TradingSystem/JusikApplication.cpp"
#include "../TradingSystem/StockerBrockerDriver.h"

using namespace std;
using namespace testing;

class BrockerMock : public StockerBrockerDriver {
public:
	MOCK_METHOD(void, logIn, (const std::string&, const std::string&), (override));
	MOCK_METHOD(void, buyStock, (const std::string&, const int, const int), (override));
	MOCK_METHOD(void, sellStock, (const std::string&, const int, const int), (override));
	MOCK_METHOD(int, getPrice, (const std::string&), (override));
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

	const int NICE_TIMING_CHECK_COUNT = 3;
	const int MY_BUDGET = 500000;
	const string STOCK_BROCKER_NEMO = "Nemo";
	const string STOCK_BROCKER_KIWER = "Kiwer";
	const string STOCK_SAMPLE_1 = "Samsung";
	const string STOCK_SAMPLE_2 = "Hynix";

	NiceMock<BrockerMock> mk;
	JusikApplication app;
};

TEST(ApplicationTest, StartApplication) {
	JusikApplication* appPointer = new JusikApplication();
	EXPECT_THAT(appPointer, NotNull());

	delete appPointer;
}

TEST_F(AppFixture, AppDefaultAPI) {
	JusikApplication app;

	app.selectStockBrocker(STOCK_BROCKER_KIWER);
	app.login("ATeam", "1234qwer");

	int currentPrice = app.getPrice(STOCK_SAMPLE_1);
	EXPECT_THAT(currentPrice, Gt(0));

	app.buy(STOCK_SAMPLE_1, 80000, 1);
	app.sell(STOCK_SAMPLE_1, 100000, 1);
}

TEST_F(AppFixture, BuyingWithoutLogin) {
	app.selectStockBrocker(STOCK_BROCKER_NEMO);

	EXPECT_THROW({
		app.buy(STOCK_SAMPLE_1, 80000, 1);
		}, std::exception);
}

TEST_F(AppFixture, ZeroPriceBuying) {
	login(STOCK_BROCKER_NEMO);

	EXPECT_THROW({
		app.buy(STOCK_SAMPLE_1, 0, 1);
		}, std::exception);
}

TEST_F(AppFixture, ZeroPriceSelling) {
	login(STOCK_BROCKER_NEMO);

	EXPECT_THROW({
		app.sell(STOCK_SAMPLE_1, 0, 1);
		}, std::exception);
}

TEST_F(AppFixture, APIsCallingLogin) {

	EXPECT_CALL(mk, logIn(_, _))
		.Times(1);

	login(STOCK_BROCKER_NEMO);
}

TEST_F(AppFixture, buyNiceTiming) {
	login(STOCK_BROCKER_NEMO);

	EXPECT_CALL(mk, getPrice(_))
		.Times(NICE_TIMING_CHECK_COUNT);

	app.buyNiceTiming(STOCK_SAMPLE_2, MY_BUDGET);
}

TEST_F(AppFixture, buyNiceTimingIncreaseStatus) {
	login(STOCK_BROCKER_NEMO);

	EXPECT_CALL(mk, getPrice(STOCK_SAMPLE_2))
		.Times(NICE_TIMING_CHECK_COUNT)
		.WillOnce(Return(40000))
		.WillOnce(Return(50000))
		.WillOnce(Return(60000));

	EXPECT_CALL(mk, buyStock(STOCK_SAMPLE_2, _, _))
		.Times(AtLeast(1));

	app.buyNiceTiming(STOCK_SAMPLE_2, MY_BUDGET);
}

TEST_F(AppFixture, SellNiceTiming) {
	login(STOCK_BROCKER_NEMO);

	EXPECT_CALL(mk, getPrice(_))
		.Times(NICE_TIMING_CHECK_COUNT);

	app.sellNiceTiming(STOCK_SAMPLE_2, 1);
}

TEST_F(AppFixture, SellNiceTimingDecreaseStatus) {
	login(STOCK_BROCKER_NEMO);

	EXPECT_CALL(mk, getPrice(STOCK_SAMPLE_2))
		.Times(NICE_TIMING_CHECK_COUNT)
		.WillOnce(Return(60000))
		.WillOnce(Return(50000))
		.WillOnce(Return(40000));

	EXPECT_CALL(mk, sellStock(STOCK_SAMPLE_2, _, _))
		.Times(AtLeast(1));

	app.sellNiceTiming(STOCK_SAMPLE_2, 1);
}