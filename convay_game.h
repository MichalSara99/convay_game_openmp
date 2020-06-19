#pragma once
#if !defined(_CONVAY_GAME)
#define _CONVAY_GAME

#include<stdlib.h>
#include<time.h>
#include<iostream>
#include<omp.h>


template< typename T >
void swap(T& a, T& b) {
	T t = a;
	a = b;
	b = t;
}

class ConvayGame {
private:
	std::size_t boardSize_;
	std::size_t generations_;

protected:
	void initBoard(short * board);
	void singleGeneration(short* board, short const* read_board);
	void print(short* board, long counter);
	short neighbours(short const* board, std::size_t tidx);

public:
	ConvayGame() = delete;
	explicit ConvayGame(std::size_t boardSize,std::size_t generations)
		:boardSize_{ boardSize },
		generations_{ generations }{}

	~ConvayGame(){}

	ConvayGame(ConvayGame const&) = delete;
	ConvayGame(ConvayGame&&) = delete;
	ConvayGame& operator=(ConvayGame const&) = delete;
	ConvayGame& operator=(ConvayGame&&) = delete;

	void play();
};

#endif ///_CONVAY_GAME