// Класс, содержащий функции для ввода/вывода фигур в различные виды стандартных потоков.

#pragma once

#include <memory>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "figure.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "rectangle.hpp"

template <class T>
class Factory {
public:
	std::shared_ptr<Figure> create(std::istream& is) const {
		std::string type;
		is >> type;
		std::shared_ptr<Figure> figure;
		if (type == "triangle") {
			Triangle<T>* tr = new Triangle<T>;
			is >> *tr;
			figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(tr));
		}

		else if (type == "square") {
			Square<T>* sq = new Square<T>;
			is >> *sq;
			figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(sq));
		}

		else if (type == "rectangle") {
			Rectangle<T>* rect = new Rectangle<T>;
			is >> *rect;
			figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(rect));
		}

		else {
			throw std::runtime_error("Unknown figure type");
		}
		return figure;
	}

	void print(const std::shared_ptr<Figure>& figure, std::ostream& os) {
		switch (figure->type()) {
			case Figures::triangle:
				os << "Triangle:\n";
				break;
			case Figures::square:
				os << "Square:\n";
				break;
			case Figures::rectangle:
				os << "Rectangle:\n";
				break;
		}
		figure->print(os);
	}

	std::shared_ptr<Figure> load(std::ifstream& ifs) const {
		if (!ifs) {
			throw std::runtime_error("File is over");
		}
		int type;
		ifs.read(reinterpret_cast<char*>(&type), sizeof(type));
		std::shared_ptr<Figure> figure;
		switch (type) {
			case Figures::triangle: {
				Triangle<T>* tr = new Triangle<T>;
				tr->read(ifs);
				figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(tr));
				break;
			}

			case Figures::square: {
				Square<T>* sq = new Square<T>;
				sq->read(ifs);
				figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(sq));
				break;
			}

			case Figures::rectangle: {
				Rectangle<T>* rect = new Rectangle<T>;
				rect->read(ifs);
				figure = std::shared_ptr<Figure>(reinterpret_cast<Figure*>(rect));
				break;
			}
		}
		return figure;
	}

	void save(const std::shared_ptr<Figure>& figure, std::ofstream& ofs) const {
		int type = figure->type();
		ofs.write(reinterpret_cast<char*>(&type), sizeof(type));
		figure->write(ofs);
	}

	Factory() = default;
	~Factory() = default;
};
