/*
Бирюков В.В. М8О-107Б-19
Спроектировать простейший «графический» векторный редактор.
Требование к функционалу редактора:
	создание нового документа.
	импорт документа из файла.
	экспорт документа в файл.
	создание графического примитива (согласно варианту задания).
	удаление графического примитива.
	отображение документа на экране (печать перечня графических объектов и их характеристик в std::cout).
	реализовать операцию undo, отменяющую последнее сделанное действие. Должно действовать для операций добавления/удаления фигур.
Требования к реализации:
	Создание графических примитивов необходимо вынести в отдельный класс – Factory. 
	Сделать упор на использовании полиморфизма при работе с фигурами.
	Взаимодействие с пользователем (ввод команд) реализовать в функции main.
Вариант 17: треугольник, квадрат, прямоугольник.
*/

#include <string>
#include <iostream>

#include "document.hpp"

int main() {
	std::string command;
	Document<int> document;
	std::cout << "> ";

	while (std::cin >> command && command != "exit") {
		try {
			if (command == "help") {
				std::cout << "Usage:\n"
						  << "help              show this message\n"
						  << "create            create new document\n"
						  << "add INDEX FIGURE  add figure to document\n"
						  << "remove INDEX      remove figure from document\n"
						  << "undo              cancel previous operation\n"
						  << "print             print list of figures\n"
						  << "save NAME         save document to file\n"
						  << "load NAME         load document from file\n"
						  << "exit              exit program\n"
						  << "FIGURE: TYPE COORDS\n"
						  << "TYPE:   triangle, square, rectangle\n"
						  << "COORDS: triangle: X Y A, square: X Y A, rectangle: X Y A B\n";
			}

			else if (command == "create") {
				document.create();
			}

			else if (command == "add") {
				int index;
				std::cin >> index;
				document.add(index);
			}

			else if (command == "remove") {
				int index;
				std::cin >> index;
				document.remove(index);
			}

			else if (command == "undo") {
				document.undo();
			}

			else if (command == "print") {
				document.print();
			}

			else if (command == "save") {
				std::string filename;
				std::cin >> filename;
				document.save(filename);
			}

			else if (command == "load") {
				std::string filename;
				std::cin >> filename;
				document.load(filename);
			}

			else {
				throw std::runtime_error("Unknown command");
			}

			std::cout << "> ";
		} catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
			std::cout << "> ";
		}
	}
}