// Абстрактный класс фигуры, а также перечислимый тип со всеми фигурами.

#pragma once

#include <fstream>
#include <iostream>

enum Figures : int {
	triangle = 0,
	square = 1,
	rectangle = 2
};

class Figure {
public:
	virtual void print(std::ostream&) = 0;
	virtual void write(std::ofstream&) = 0;
	virtual void read(std::ifstream&) = 0;
	virtual Figures type() = 0;
	virtual ~Figure() = default;
};