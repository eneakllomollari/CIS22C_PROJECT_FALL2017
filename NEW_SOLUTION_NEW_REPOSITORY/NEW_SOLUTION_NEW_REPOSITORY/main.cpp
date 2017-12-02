#include <iostream>
#include "HeadNode.h"


//Need to remove the inline functions from the stack and put them separately
int main()
{
	std::cout << std::fixed << std::setprecision(2);

	HeadNode mainHeadNode;

	int choice;

	try
	{
		//MENU STARTS HERE 
		// MAKE THIS A FUNCTION
		//MAIN MENU OF THE PROGRAM
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Welcome to World Cup Soccer Stats " << std::endl << std::endl;

		do {
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "The list of possible operations\n" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "1) Add a new year stats" << std::endl; //this is <add new data>
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "2) Remove a year" << std::endl; //this is <delete data>
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "3) Find and display one data record of a year" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "4) List data in hash table sequence" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "5) List sorted data" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "6) Print indented tree" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "7) Undo Delete " << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "8) Save Changes/Clear the Recovery Stack" << std::endl;
			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "9) Efficency " << std::endl;

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "0) EXIT\n";

			std::cout << std::setw(WIDTH_BTW_LINES) << "" << "Enter your choice: ";
			std::cin >> choice;

			std::cout << "\n\n";
			switch (choice)
			{
			case 1:
				system("CLS");
				mainHeadNode.addManager();
				system("CLS");
				break;
			case 2:
				system("CLS");
				mainHeadNode.removeManager();
				system("CLS");
				break;
			case 3:
				system("CLS");
				mainHeadNode.displayKeyManager();
				system("CLS");
				break;
			case 4:
				system("CLS");
				mainHeadNode.displayTableManager();
				system("CLS");
				break;
			case 5:
				system("CLS");
				mainHeadNode.sortManager();
				system("CLS");
				break;
			case 6:
				system("CLS");
				mainHeadNode.printIndentedTree();
				system("CLS");
				break;
			case 7:
				system("CLS");
				mainHeadNode.undoDeleteManager();
				system("CLS");
				break;
			case 8:
				mainHeadNode.saveToInputFileManager();
				mainHeadNode.clearRecycleStacksManager();
				system("CLS");
				std::cout << std::endl << std::endl << std::endl;
				std::cout << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "OPERATION SUCCESFUL!" << std::endl;
				std::cout << std::endl << std::endl << std::endl;
				std::cout << std::setw(WIDTH_BTW_LINES) << "";
				system("pause");
				system("CLS");
				break;
			case 9:
				system("CLS");
				//Since we are using tree hash tables, but with the same key the data of one tree is sufficent
				mainHeadNode.efficencyManager();
				std::cout << std::endl;
				system("pause");
				system("CLS");
				break;
			case 0:
				system("pause");
				system("CLS"); break;
			default:
				system("CLS");
				std::cout << std::setw(WIDTH_BTW_LINES) << "" << "INVALID CHOICE. Please enter a number 1 - 8!" << std::endl;
				break;
			}
			std::cin.clear();             //it takes care of the strings entered
			std::cin.ignore(INT_MAX, '\n');

			std::cout << std::endl << std::endl;
		} while (choice != 0);	//End of main do while loop
	}
	catch (char *msg)
	{
		std::cout << std::setw(WIDTH_BTW_LINES) << "" << msg << "\n";
	}
	catch (...)
	{
		std::cout << "DEFAULT CATCHER" << std::endl;
	}

	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	std::cout << std::endl << std::setw(WIDTH_BTW_LINES + 10) << "" << "\"GOODBYE\"" << std::endl << std::endl << std::endl << std::endl << std::endl;
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n";

	system("pause");
	return 0;
}