#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../SimpleCalculator.h" 
#include "../InMemoryHistory.h" 

using namespace calc;

TEST(SimpleCalculatorTest, Add5To4Equal9) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 5;
	int b = 4;
	int expectedResult = 9;

	ASSERT_EQ(calc.Add(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, AddZero) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 8;
	int b = 0;
	int expectedResult = 8;

	ASSERT_EQ(calc.Add(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, AddNegativeNumbers) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = -5;
	int b = -3;
	int expectedResult = -8;

	ASSERT_EQ(calc.Add(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, AddMaxValues) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = std::numeric_limits<int>::max();
	int b = 1;
	int expectedResult = std::numeric_limits<int>::max();

	ASSERT_EQ(calc.Add(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, AddMinValues) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = std::numeric_limits<int>::min();
	int b = 1;
	int expectedResult = std::numeric_limits<int>::min() + 1;

	ASSERT_EQ(calc.Add(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, AddDecimals) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	float a = 2.5;
	float b = 3.5;
	float expectedResult = 6;

	ASSERT_EQ(calc.Add(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, Subtract2From5Equal3) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 5;
	int b = 2;
	int expectedResult = 3;

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, Subtract11From2EqualMin9) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 2;
	int b = 11;
	int expectedResult = -9;

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, Subtract5From5Equal0) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 5;
	int b = 5;
	int expectedResult = 0;

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, SubtractZero) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 9;
	int b = 0;
	int expectedResult = 9;

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, SubtractNegativeNumbers) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = -5;
	int b = -2;
	int expectedResult = -7;

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, SubtractFromMaxValues) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = std::numeric_limits<int>::max();
	int b = 20;
	int expectedResult = std::numeric_limits<int>::max() - 20;

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, SubtractFromMinValues) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = std::numeric_limits<int>::min();
	int b = 5;
	int expectedResult = std::numeric_limits<int>::min();

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, SubtractDecimals) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	float a = 8.25;
	float b = 1.75;
	float expectedResult = 6.5;

	ASSERT_EQ(calc.Subtract(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, Multiply4And3Equal12) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 4;
	int b = 3;
	int expectedResult = 12;

	ASSERT_EQ(calc.Multiply(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, MultiplyByZero) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 0;
	int b = 32;
	int expectedResult = 0;

	ASSERT_EQ(calc.Multiply(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, MultiplyDecimals) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	float a = 2.5;
	float b = 3.5;
	float expectedResult = 8.75;

	ASSERT_EQ(calc.Multiply(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, Divide10By2Equal5) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 10;
	int b = 2;
	int expectedResult = 5;

	ASSERT_EQ(calc.Divide(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, DivideByZero) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = 10;
	int b = 0;

	EXPECT_THROW(calc.Divide(a, b), std::invalid_argument);
}

TEST(SimpleCalculatorTest, DivideDecimals) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	float a = 10.0;
	float b = 3.3;
	float expectedResult = 3.0303;

	ASSERT_EQ(calc.Divide(a, b), expectedResult);
}

TEST(SimpleCalculatorTest, LargeMultiplication) {

	InMemoryHistory history;
	SimpleCalculator calc(history);

	int a = std::numeric_limits<int>::max() / 2;
	int b = 2;
	int expectedResult = a * b;

	ASSERT_EQ(calc.Multiply(a, b), expectedResult);
}

//Mock для интерфейса IHistory
class IHistoryMock : public IHistory {
public:
	MOCK_METHOD(void, AddEntry, (const std::string& entry), (override));
	MOCK_METHOD((std::vector<std::string>), GetLastOperations, (size_t), (const, override));
};

//Mock для интерфейса ISimpleCalculator
class ISimpleCalculatorMock : public SimpleCalculator {
public:
	ISimpleCalculatorMock(IHistory& history) : SimpleCalculator(history) {}

	MOCK_METHOD(int, Add, (int a, int b), (override));
	MOCK_METHOD(int, Subtract, (int a, int b), (override));
	MOCK_METHOD(int, Multiply, (int a, int b), (override));
	MOCK_METHOD(int, Divide, (int a, int b), (override));
};

TEST(MockTest, SetHistory) {

	IHistoryMock newMockHistory;
	SimpleCalculator calc(newMockHistory);

	calc.SetHistory(newMockHistory);
	int a = 2;
	int b = 3;
	int expectedResult = 5;

	std::ostringstream str;
	str << a << " " << "+" << " " << b << " = " << expectedResult;
	EXPECT_CALL(newMockHistory, AddEntry(str.str()));

	ASSERT_EQ(calc.Add(a, b), expectedResult);
}

TEST(MockTest, HistoryLogging) {

	IHistoryMock newMockHistory;
	SimpleCalculator calc(newMockHistory);

	int a = 2;
	int b = 3;
	int expectedResult = 5;

	std::ostringstream str;
	str << a << " " << "+" << " " << b << " = " << expectedResult;

	EXPECT_CALL(newMockHistory, AddEntry(str.str()));

	calc.Add(a, b);
}

TEST(MockTest, AddTest) {

	IHistoryMock mockHistory;
	ISimpleCalculatorMock mockCalc(mockHistory);

	EXPECT_CALL(mockCalc, Add(2, 3))
		.Times(1)
		.WillOnce(::testing::Return(5));

	int result = mockCalc.Add(2, 3);

	ASSERT_EQ(result, 5);

	EXPECT_CALL(mockHistory, AddEntry(::testing::_)).Times(0);
}

TEST(MockTest, SubtractTest) {

	IHistoryMock mockHistory;
	ISimpleCalculatorMock mockCalc(mockHistory);

	EXPECT_CALL(mockCalc, Subtract(5, 2))
		.Times(1)
		.WillOnce(::testing::Return(3));

	int result = mockCalc.Subtract(5, 2);

	ASSERT_EQ(result, 3);

	EXPECT_CALL(mockHistory, AddEntry(::testing::_)).Times(0);
}

TEST(MockTest, MultiplyTest) {

	IHistoryMock mockHistory;
	ISimpleCalculatorMock mockCalc(mockHistory);

	EXPECT_CALL(mockCalc, Multiply(4, 6))
		.Times(1)
		.WillOnce(::testing::Return(24));

	int result = mockCalc.Multiply(4, 6);

	ASSERT_EQ(result, 24);
	EXPECT_CALL(mockHistory, AddEntry(::testing::_)).Times(0);
}

TEST(MockTest, DivideTest) {

	IHistoryMock mockHistory;
	ISimpleCalculatorMock mockCalc(mockHistory);

	EXPECT_CALL(mockCalc, Divide(10, 2))
		.Times(1)
		.WillOnce(::testing::Return(5));

	int result = mockCalc.Divide(10, 2);

	ASSERT_EQ(result, 5);
	EXPECT_CALL(mockHistory, AddEntry(::testing::_)).Times(0);
}

TEST(MockTest, HistoryIntegrationTest) {

	IHistoryMock mockHistory;
	SimpleCalculator calculator(mockHistory);

	int a = 2;
	int b = 3;
	int expectedResult = 5;

	std::ostringstream oss;
	oss << a << " + " << b << " = " << expectedResult;

	EXPECT_CALL(mockHistory, AddEntry(oss.str())).Times(1);

	calculator.Add(a, b);
}

TEST(HistoryTest, GetLastOperations) {

	IHistoryMock mockHistory;
	SimpleCalculator calculator(mockHistory);

	std::vector<std::string> expectedOperations = {
		"1 + 1 = 2",
		"2 * 3 = 6",
		"5 - 2 = 3"
	};

	EXPECT_CALL(mockHistory, GetLastOperations(3))
		.Times(1)
		.WillOnce(::testing::Return(expectedOperations));

	std::vector<std::string> actualOperations = mockHistory.GetLastOperations(3);

	ASSERT_EQ(actualOperations.size(), expectedOperations.size());
	for (size_t i = 0; i < actualOperations.size(); ++i) {
		ASSERT_EQ(actualOperations[i], expectedOperations[i]);
	}
}

TEST(HistoryTest, GetLastOperationsWithNoEntries) {

	IHistoryMock mockHistory;

	std::vector<std::string> expectedOperations = {};

	EXPECT_CALL(mockHistory, GetLastOperations(3))
		.Times(1)
		.WillOnce(::testing::Return(expectedOperations));

	SimpleCalculator calculator(mockHistory);

	std::vector<std::string> actualOperations = mockHistory.GetLastOperations(3);

	ASSERT_TRUE(actualOperations.empty());
}

TEST(HistoryTest, GetLastOperationsWithFewerEntriesThanRequested) {

	IHistoryMock mockHistory;
	SimpleCalculator calculator(mockHistory);

	std::vector<std::string> expectedOperations = {
		"1 + 1 = 2",
		"2 * 3 = 6"
	};

	EXPECT_CALL(mockHistory, GetLastOperations(5))
		.Times(1)
		.WillOnce(::testing::Return(expectedOperations));

	std::vector<std::string> actualOperations = mockHistory.GetLastOperations(5);

	ASSERT_EQ(actualOperations.size(), expectedOperations.size());
	for (size_t i = 0; i < actualOperations.size(); ++i) {
		ASSERT_EQ(actualOperations[i], expectedOperations[i]);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}