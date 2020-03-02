#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//============================================================================
// Name        : TicTacToeTests.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include <iostream>
#include <gtest/gtest.h>

#include "TicTacToe.h"

class TicTactToeTest: public ::testing::Test {
protected:
	// You should make the members protected s.t. they can be
	// accessed from sub-classes.

	// Declares the variables your tests want to use.
	TicTacToe ttt_;
};

// Tests the default constructor.
TEST_F(TicTactToeTest, DefaultConstructor) {
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
}

// Tests the "happy day" scenario
TEST_F(TicTactToeTest, HappyDay) {
	EXPECT_EQ(0, ttt_.nrOfMoves());
	EXPECT_TRUE(ttt_.notDone());
	while (ttt_.notDone()) {
		ttt_.doMove();
	};
	EXPECT_FALSE(ttt_.notDone());
	EXPECT_EQ(9, ttt_.nrOfMoves());
}

int main(int argc, char **argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

#pragma clang diagnostic pop