// Прямоугольник. Хранит данные как координаты левой нижней вершины и длины сторон.

#pragma once

#include <utility>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "figure.hpp"

template <typename T>
class Rectangle : public Figure {
public:
	std::pair<T,T> x;
	T a;
	T b;

	Rectangle() = default;
	Rectangle(T x1, T x2, T a, T b) : x(x1,x2), a(a), b(b) {
		if (a <= 0 || b <= 0) {
			throw std::invalid_argument("Invalid rectangle parameters");
		}
	}
	~Rectangle() = default;

	void print(std::ostream& os) override {
		os << "(" << x.first << ", " << x.second << ") " << 
					"(" << x.first << ", " << x.second + b << ") " << 
					"(" << x.first + a << ", " << x.second + b << ") " <<
					"(" << x.first + a << ", " << x.second << ")" << std::endl;
	}

	Figures type() override {
		return Figures::rectangle;
	}

	void read(std::ifstream& ifs) override {
		ifs.read(reinterpret_cast<char*>(&x.first), sizeof(T));
		ifs.read(reinterpret_cast<char*>(&x.second), sizeof(T));
		ifs.read(reinterpret_cast<char*>(&a), sizeof(T));
		ifs.read(reinterpret_cast<char*>(&b), sizeof(T));
	}
	void write(std::ofstream& ofs) override {
		ofs.write(reinterpret_cast<char*>(&x.first), sizeof(T));
		ofs.write(reinterpret_cast<char*>(&x.second), sizeof(T));
		ofs.write(reinterpret_cast<char*>(&a), sizeof(T));
		ofs.write(reinterpret_cast<char*>(&b), sizeof(T));
	}

	template <class U>
	friend std::istream& operator>>(std::istream&, Rectangle<U>&);
};

template <class T>
std::istream& operator>>(std::istream& is, Rectangle<T>& rect) {
	is >> rect.x.first >> rect.x.second >> rect.a >> rect.b;
	if (rect.a <= 0 || rect.b <= 0) {
		throw std::invalid_argument("Invalid rectangle parameters");
	}
	return is;
}