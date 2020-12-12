// Класс документа, хранит фигуры в списке.

#pragma once

#include <list>
#include <stack>
#include <memory>
#include <string>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "figure.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "rectangle.hpp"
#include "factory.hpp"

struct Action {
	virtual ~Action() = default;
	virtual void apply(std::list<std::shared_ptr<Figure>>&) = 0;
};

struct AddAction : public Action {
	std::shared_ptr<Figure> figure;
	size_t index;

	AddAction(std::shared_ptr<Figure> figure, size_t index) : figure(figure), index(index) {}
	~AddAction() = default;
	void apply(std::list<std::shared_ptr<Figure>>& figures) override {
		auto iter = figures.begin();
			while (index--) {
				iter++;
			}
			figures.insert(iter, figure);
	}
};

struct DelAction : public Action {
	size_t index;

	DelAction(size_t index) : index(index) {}
	~DelAction() = default;
	void apply(std::list<std::shared_ptr<Figure>>& figures) override {
		auto iter = figures.begin();
		for (size_t i = 0; i < index; ++i) {
			iter++;
		}
		figures.erase(iter);
	}
};

template <class T>
class Document {
private:
	std::list<std::shared_ptr<Figure>> figures;
	std::stack<std::shared_ptr<Action>> actions;
	Factory<T> factory;

public:
	void create() {
		figures.clear();
		while (!actions.empty()) {
			actions.pop();
		}
	}

	void add(int index) {
		if (index < 0) {
			throw std::out_of_range("Invalid index for insert");
		}

		std::shared_ptr<Figure> figure = factory.create(std::cin);
		actions.push(std::shared_ptr<Action>(new DelAction(std::min(index, (int)figures.size()))));

		if (index >= (int)figures.size()) {
			figures.push_back(figure);
		} else {
			auto iter = figures.begin();
			while (index--) {
				iter++;
			}
			figures.insert(iter, figure);
		}

	}

	void remove(int index) {
		if (index < 0 || index >= (int)figures.size()) {
			throw std::out_of_range("Invalid index for remove");
		}

		auto iter = figures.begin();
		for (int i = 0; i < index; ++i) {
			iter++;
		}

		actions.push(std::shared_ptr<Action>(new AddAction(*iter, index)));
		figures.erase(iter);
	}

	void undo() {
		if (actions.empty()) {
			std::cout << "Nothing to undo" << std::endl;
			return;
		}

		actions.top()->apply(figures);
		actions.pop();
	}

	void save(std::string& name) {
		std::ofstream ofs(name, std::ios::binary);
		if (ofs.fail()) {
			throw std::runtime_error("Error opening file");
		}
		size_t size = figures.size();
		ofs.write(reinterpret_cast<char*>(&size), sizeof(size));
		for (const std::shared_ptr<Figure>& figure : figures) {
			factory.save(figure, ofs);
		}
		ofs.close();
	}

	void load(std::string& name) {
		create();
		std::ifstream ifs(name, std::ios::binary);
		if (ifs.fail()) {
			throw std::runtime_error("Error opening file");
		}
		size_t size;
		ifs.read(reinterpret_cast<char*>(&size), sizeof(size));
		while (size--) {
			figures.push_back(factory.load(ifs));
		}
		ifs.close();
	}

	void print() {
		for (const std::shared_ptr<Figure>& figure : figures) {
			factory.print(figure, std::cout);
		}
	}

	Document() : figures(), actions(), factory() {};
	~Document() = default;
};
