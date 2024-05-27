#pragma once

#include "AVL-Tree.hpp"
#include "BinarySearchTree.hpp"

enum class Menu
{
	AVL = 1 ,BINARY, EXIT
};

class UserInterface
{
private:
	AVLTree m_avl_tree;
	BinaryTree m_binary_tree;

	void show_avl()
	{
		m_avl_tree.insert();
	}

	void show_binary()
	{
		m_binary_tree.add(41);
		m_binary_tree.add(20);
		m_binary_tree.add(11);
		m_binary_tree.add(29);
		m_binary_tree.add(32);
		m_binary_tree.add(65);
		m_binary_tree.add(50);
		m_binary_tree.add(91);
		m_binary_tree.add(72);
		m_binary_tree.add(99);

		std::cout << "\n\t\t\t\t����� ������ � ������������ ������� (����� �������): B, A, C - ��������� �����: \n" << std::endl;
		m_binary_tree.showSymmetricalOrder();

		std::cout << "\n\t\t\t\t�������� ������ ������ ����� �������� ���������:\n" << std::endl;

		m_binary_tree.erase(20);
		m_binary_tree.erase(65);
		m_binary_tree.showSymmetricalOrder();

		std::cout << "50: ";		m_binary_tree.search(50);
		std::cout << "20: ";		m_binary_tree.search(20);
		std::cout << "11: ";		m_binary_tree.search(11);
		std::cout << "41: ";		m_binary_tree.search(41);
	}

public:
	UserInterface()
	{

	}

	void run()
	{
		setlocale(0, "");
		std::cout << "����� ����������!\n";

		int answer{};
		while (answer != (int)Menu::EXIT)
		{
			std::cout
				<< "\n� ��� ������?\n"
				<< "1) � AVL ���������!\n"
				<< "2) � �������� ������� ������!\n"
				<< "3) � �� ���� ������(((\n\n"
				<< "�����: ";
			std::cin >> answer;

			switch (answer)
			{
			case((int)Menu::AVL):
				show_avl();
				break;

			case((int)Menu::BINARY):
				show_binary();
				break;

			case((int)Menu::EXIT):
				break;

			default:
				std::cout << "�������� ������!";
				break;
			}

		}
	
	}
};