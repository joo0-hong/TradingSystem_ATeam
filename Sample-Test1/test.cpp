#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../TradingSystem/JusikApplication.cpp"

using namespace std;
using namespace testing;

TEST(TestCaseName, StartApplication) {
	JusikApplication app;

	EXPECT_THAT(&app, NotNull());
}

