#include<iostream>
#include<string>
#include<vector>


#include"convay_game.h"

int main(int argc, char const* argv[]) {

	std::size_t const size{ 10 };
	std::size_t const generations{ 200};

	ConvayGame game{ size,generations };

	game.play();


	std::cin.get();
	std::cin.get();
	return 0;
}