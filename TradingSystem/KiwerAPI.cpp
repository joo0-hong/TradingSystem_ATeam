#pragma once
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;
class KiwerAPI {
public:
	void login(string ID, string password) {
		cout << ID << " login success\n";
	}

	void buy(string stockCode, int count, int price) {
		cout << stockCode << " : Buy stock ( " << price << " * " << count << ")\n";
	}

	void sell(string stockCode, int count, int price) {
		cout << stockCode << " : Sell stock ( " << price << " * " << count << ")\n";
	}

	int currentPrice(string stockCode) {
		srand(time(NULL));
		int ret = rand() % 10 * 100 + 5000;
		return ret;
	}
};