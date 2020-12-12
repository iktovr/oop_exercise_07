// Треугольник. Хранит данные как координаты левой вершины и длину стороны.

#pragma once

#include <cmath>
#include <utility>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "figure.hpp"

template <typename T>
class Triangle : public Figure {
public:
	std::pair<T,T> x;
	T a;

	Triangle() = default;
	Triangle(T x1, T x2, T a) : x(x1,x2), a(a) {
		if (a <= 0) {
			throw std::invalid_argument("Invalid triangle parameters");
		}
	}
	~Triangle() = default;

	void print(std::ostream& os) override {
		os << "(" << x.first << ", " << x.second << ") " <<
					"(" << x.first + 1.0 / 2 * a << ", " << 
					x.second + sqrt(3) / 2 * a << ") " <<
					"(" << x.first + a << ", " << x.second << ")" << std::endl;
	}

	Figures type() override {
		return Figures::triangle;
	}

	void read(std::ifstream& ifs) override {
		ifs.read(reinterpret_cast<char*>(&x.first), sizeof(T));
		ifs.read(reinterpret_cast<char*>(&x.second), sizeof(T));
		ifs.read(reinterpret_cast<char*>(&a), sizeof(T));
	}
	void write(std::ofstream& ofs) override {
		ofs.write(reinterpret_cast<char*>(&x.first), sizeof(T));
		ofs.write(reinterpret_cast<char*>(&x.second), sizeof(T));
		ofs.write(reinterpret_cast<char*>(&a), sizeof(T));
	}

	template <class U>
	friend std::istream& operator>>(std::istream&, Triangle<U>&);
};

template <class T>
std::istream& operator>>(std::istream& is, Triangle<T>& tr) {
	is >> tr.x.first >> tr.x.second >> tr.a;
	if (tr.a <= 0) {
		throw std::invalid_argument("Invalid triangle parameters");
	}
	return is;
}