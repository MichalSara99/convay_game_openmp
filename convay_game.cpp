#include"convay_game.h"


void ConvayGame::initBoard(short* board) {
	srand(time(NULL));
	std::size_t const totalSize = boardSize_ * boardSize_;

#pragma omp parallel for
	for (std::size_t t = 0; t < totalSize; ++t)
		board[t] = (rand() % 2);
}


void ConvayGame::print(short* board, long counter) {
	std::size_t const totalSize = boardSize_ * boardSize_;
	std::cout << counter << ".generation\n| ";
	for (std::size_t t = 0; t < totalSize; ++t) {
		if ((t > 0) && (t % boardSize_) == 0)
			std::cout << "|\n| ";
		std::cout << board[t] << " ";
	}
	std::cout << "|\n";
}


short ConvayGame::neighbours(short const* board, std::size_t tidx) {
	// total size of array:
	long const totalSize = boardSize_ * boardSize_;
	// find neighbouring indices:
	long leftIdx = tidx - 1;
	long rightIdx = tidx + 1;
	long bottomIdx = tidx + boardSize_;
	long bottomLeftIdx = bottomIdx - 1;
	long bottomRightIdx = bottomIdx + 1;
	long topIdx = tidx - boardSize_;
	long topLeftIdx = topIdx - 1;
	long topRightIdx = topIdx + 1;
	// counter of neighbours:
	short cnt = 0;

	// boundaries of the board:

	// top left corner:
	if (tidx == 0) {
		cnt += board[rightIdx] + board[bottomIdx] + board[bottomRightIdx];
		return cnt;
	}
	// bottom left corner:
	if (tidx == (totalSize - boardSize_)) {
		cnt += board[topIdx] + board[topRightIdx] + board[rightIdx];
		return cnt;
	}
	//	top right corner:
	if (tidx == (boardSize_ - 1)) {
		cnt += board[leftIdx] + board[bottomLeftIdx] + board[bottomIdx];
		return cnt;
	}
	//	bottom right corner:
	if (tidx == (totalSize - 1)) {
		cnt += board[topIdx] + board[topLeftIdx] + board[leftIdx];
		return cnt;
	}

	// left boundary of the board:
	if ((tidx % boardSize_) == 0) {
		cnt += board[topIdx] + board[topRightIdx]
			+ board[rightIdx] + board[bottomRightIdx] + board[bottomIdx];
		return cnt;
	}

	// top boundary of the board:
	if ((tidx >= 0) && (tidx <= (boardSize_ - 1))) {
		cnt += board[leftIdx] + board[bottomLeftIdx]
			+ board[bottomIdx] + board[bottomRightIdx] + board[rightIdx];
		return cnt;
	}

	// right boundary of the board:
	if (((tidx + 1) % boardSize_) == 0) {
		cnt += board[topIdx] + board[topLeftIdx]
			+ board[leftIdx] + board[bottomLeftIdx] + board[bottomIdx];
		return cnt;
	}

	// bottom boundary of the board:
	if ((tidx >= (totalSize - boardSize_)) && (tidx <= (totalSize - 1))) {
		cnt += board[leftIdx] + board[topLeftIdx]
			+ board[topIdx] + board[topRightIdx] + board[rightIdx];
		return cnt;
	}

	cnt += board[leftIdx] + board[topLeftIdx] + board[topIdx] + board[topRightIdx]
		+ board[rightIdx] + board[bottomRightIdx] + board[bottomIdx] + board[bottomLeftIdx];
	return cnt;
}


void ConvayGame::singleGeneration(short* board, short const* read_board) {
	std::size_t totalSize = boardSize_ * boardSize_;
	short neighbourCount = 0;

	for (std::size_t t = 0; t < totalSize; ++t) {
		neighbourCount = neighbours(read_board, t);
		if (read_board[t] == 0)
			board[t] = static_cast<short>(neighbourCount == 3);
		else
			board[t] = static_cast<short>((neighbourCount == 2) || (neighbourCount == 3));
	}
}

void ConvayGame::play() {
	// get total size of array:
	std::size_t const totalSize = boardSize_ * boardSize_;
	// dynamically allocate for flat 2-dimensional array:
	short* board = (short*)malloc(sizeof(short) * totalSize);
	short* ro_board = (short*)malloc(sizeof(short) * totalSize);

	// initialize the board:
	initBoard(board);

	// read-only board:
	memcpy(ro_board, board, sizeof(short) * totalSize);

	// generate through time:
	long gen = generations_;
	for (long g = 1; g <= gen; ++g) {
		print(ro_board, g);
		singleGeneration(board, ro_board);
		swap(board, ro_board);
	}

	if (board) free(board);
	if (ro_board) free(ro_board);
}

