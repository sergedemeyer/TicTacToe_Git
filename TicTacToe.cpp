//============================================================================
// Name        : TicTacToe.cpp
// Author      : Serge Demeyer
// Version     :
// Copyright   : Project Software Engineering - BA1 Informatica - Serge Demeyer - University of Antwerp
// Description : TicTactToe in C++, Ansi-style
//============================================================================

#include "TicTacToe.h"
#include "DesignByContract.h"

TicTacToePlayer::TicTacToePlayer() {
	_initCheck = this;
	_marker = 'X';
	ENSURE(properlyInitialized(),
			"constructor must end in properlyInitialized state");
}

TicTacToePlayer::TicTacToePlayer(char marker) {
	REQUIRE(('X' == marker) || ('O' == marker),
			"Constructor requires 'X' or 'O' as marker");
	_initCheck = this;
	for (int i = 0; i <= maxMoves; i++) {
		_moves[i] = ' ';
	};
	_movesLength = 0;
	_currentMove = 0;
	ENSURE(properlyInitialized(),
			"constructor must end in properlyInitialized state");
}

bool TicTacToePlayer::properlyInitialized() {
	return _initCheck == this;
}

void TicTacToePlayer::setMoves(const std::string stringWithMoves) {
	REQUIRE(this->properlyInitialized(),
			"TicTacToePlayer wasn't initialized when calling setMoves");
	REQUIRE(TicTacToePlayer::legalMoves(stringWithMoves), "setMoves requires legalMoves");
	_movesLength = stringWithMoves.length();
	for (int i = 0; i < _movesLength; i++) {
		_moves[i] = stringWithMoves[i];
	}
	_currentMove = 0;
}

void TicTacToePlayer::doMove(TicTacToe& game) {
	REQUIRE(this->properlyInitialized(),
			"TicTacToePlayer wasn't initialized when calling doMove");
	REQUIRE(game.properlyInitialized(),
			"game wasn't initialized when passed to Player->doMove");
	if (_currentMove < _movesLength) {
		char col, row;
		col = _moves[_currentMove];
		row = _moves[_currentMove + 1];
		_currentMove = _currentMove + 2;
		game.setMark(col, row, _marker);
	}
}

void TicTacToePlayer::setMarker(char marker) {
	REQUIRE(this->properlyInitialized(),
			"TicTacToePlayer wasn't initialized when calling setMarker");
	REQUIRE(('X' == marker) || ('O' == marker),
			"setMarker requires 'X' or 'O' as marker");
	_marker = marker;
	ENSURE(getMarker() == marker, "setMarker post condition failure");
}

char TicTacToePlayer::getMarker() {
	char result;
	REQUIRE(this->properlyInitialized(),
			"TicTacToePlayer wasn't initialized when calling getMarker");
	result = _marker;
	ENSURE(('X' == result) || ('O' == result),
			"getMarker must return 'X' or 'O'");
	return result;
}


//Below is a static member function but one cannot repeat the static keyword in the implementation
bool TicTacToePlayer::legalMoves(const std::string stringWithMoves) {
	int movesLength;
	movesLength = stringWithMoves.length();
	if (movesLength > (maxMoves + 1)) {
		return false;
	}
	if (!((movesLength % 2) == 0)) {
		return false;
	} // length should be even
	for (int i = 0; i < movesLength; i += 2) {
		if ((stringWithMoves[i] != 'a') && (stringWithMoves[i] != 'b')
				&& (stringWithMoves[i] != 'c')) {
			return false;
		}
		if ((stringWithMoves[i + 1] != '1') && (stringWithMoves[i + 1] != '2')
				&& (stringWithMoves[i + 1] != '3')) {
			return false;
		}
	};
	return true;
}






//
//----------------------- TicTacToe
//

TicTacToe::TicTacToe() {
	int i, j;
	_initCheck = this;
	_nrOfMoves = 0;
	for (i = 0; i < maxCol - minCol + 1; i++)
		for (j = 0; j < maxRow - minRow + 1; j++) {
			_board[i][j] = ' ';
		};
	_players[0].setMarker('O');
	_players[0].setMoves("");
	_players[1].setMarker('X');
	_players[1].setMoves("");
	ENSURE(properlyInitialized(),
			"constructor must end in properlyInitialized state");
}

void TicTacToe::setMoves(const std::string oMoves, const std::string xMoves) {
	REQUIRE(this->properlyInitialized(), "TicTacToe wasn't initialized when calling setMoves");
	REQUIRE(TicTacToePlayer::legalMoves(oMoves), "TicTacToe::setMoves requires legal oMoves");
	REQUIRE(TicTacToePlayer::legalMoves(xMoves), "TicTacToe::setMoves requires legal xMoves");
	_players[0].setMoves(oMoves);
	_players[1].setMoves(xMoves);
}



bool TicTacToe::properlyInitialized() {
	return _initCheck == this;
}

bool TicTacToe::notDone() {
	REQUIRE(this->properlyInitialized(),
			"TicTacToe wasn't initialized when calling notDone");
	return _nrOfMoves < 9;
}

void TicTacToe::doMove() {
	REQUIRE(this->properlyInitialized(),
			"TicTacToe wasn't initialized when calling doMove");
	_players[_nrOfMoves % 2].doMove(*this);
	_nrOfMoves++;
}

int TicTacToe::nrOfMoves() {
	REQUIRE(this->properlyInitialized(),
			"TicTacToe wasn't initialized when calling nrOfMoves");
	return _nrOfMoves;
}

void TicTacToe::setMark(char col, char row, char marker) {
	REQUIRE(this->properlyInitialized(),
			"TicTacToe wasn't initialized when calling setMark");
	REQUIRE((minCol <= col) && (col <= maxCol),
			"col must be between 'a' and 'c'");
	REQUIRE((minRow <= row) && (row <= maxRow),
			"row must be between '1' and '3'");
	REQUIRE(('X' == marker) || ('O' == marker) || (' ' == marker),
			"marker must be 'X', 'O' or ' '");
	_board[(int) col - minCol][(int) row - minRow] = marker;
	ENSURE((getMark(col, row) == marker), "setMark postcondition failure");
}

char TicTacToe::getMark(char col, char row) {
	char result;
	REQUIRE(this->properlyInitialized(),
			"TicTacToe wasn't initialized when calling getMark");
	REQUIRE((minCol <= col) && (col <= maxCol),
			"col must be between 'a' and 'c'");
	REQUIRE((minRow <= row) && (row <= maxRow),
			"row must be between '1' and '3'");
	result = _board[(int) col - minCol][(int) row - minRow];
	ENSURE(('X' == result) || ('O' == result) || (' ' == result),
			"getMark must return 'X', 'O' or ' '");
	return result;
}

void TicTacToe::writeOn(std::ostream& onStream) {
	char col, row;
	REQUIRE(this->properlyInitialized(),
			"TicTacToe wasn't initialized when calling displayGame");
	onStream << "TicTacToe numberOfMoves = " << this->nrOfMoves() << std::endl;
	onStream << "    a   b   c   " << std::endl;
	onStream << "  ------------- " << std::endl;
	for (row = minRow; row <= maxRow; row++) {
		onStream << row;
		for (col = minCol; col <= maxCol; col++) {
			onStream << " | " << this->getMark(col, row);
		}
		onStream << " |" << std::endl;
	};
	onStream << "  ------------- " << std::endl;
}
