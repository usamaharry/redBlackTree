#include"rbt.h"
#include<fstream>



//Usama Javed L1F18BSCS0322
//AHMED KHAN L1F18BSCS0345
//ALI AHMED

int main()
{
	char* filename = new char[20];

	int input = 0;
	int value = 0;
	rbt RBT;

	

	while (true)
	{
			cout << "***PRESS 1 TO INSERT VALUE***" << endl;
			cout << "***PRESS 2 TO SEARCH VALUE***" << endl;
			cout << "***PRESS 3 FOR PRE ORDER TRAVERSAL NLR***" << endl;
			cout << "***PRESS 4 FOR IN ORDER TRAVERSAL LNR***" << endl;
			cout << "***PRESS 5 FOR POST ORDER TRAVERSAL LRN***" << endl;
			cout << "***PRESS 6 FOR PRE ORDER TRAVERSAL NRL***" << endl;
			cout << "***PRESS 7 FOR IN ORDER TRAVERSAL RNL***" << endl;
			cout << "***PRESS 8 FOR POST ORDER TRAVERSAL RLN***" << endl;
			cout << "***PRESS 9 FOR PRINTING PARENT OF A NODE***" << endl;
			cout << "***PRESS 10 TO READ VALUES FROM A FILE***" << endl;
			cout << "***PRESS 11 TO DELETE DUPLICATE VALUES***" << endl;
			cout << "***PRESS 12 TO DESTROY COMPLETE TREE***" << endl;
			cout << "***PRESS 13 TO  EXIT***" << endl;
			cin >> input;

			system("cls");

			if (input == 1)
			{
				system("cls");
				cout << "Enter value to insert: " << endl;
				cin >> value;
				RBT.insert(value);
			}
			if (input == 2)
			{
				system("cls");
				cout << "Enter value to search: " << endl;
				cin >> value;
				if (RBT.search(value))
					cout << "Value " << value << " is present in the Tree." << endl;
				else
					cout << "Value " << value << " is not present in the Tree." << endl;
			}
			if (input == 3)
			{
				system("cls");
				RBT.preOrderNLR();
			}
			if (input == 4)
			{
				system("cls");
				RBT.inOrderLNR();
			}
			if (input == 5)
			{
				system("cls");
				RBT.postOrderLRN();
			}
			if (input == 6)
			{
				system("cls");
				RBT.preOderNRL();
			}
			if (input == 7)
			{
				system("cls");
				RBT.inOrderRNL();
			}
			if (input == 8)
			{
				system("cls");
				RBT.postOrderRLN();
			}
			if (input == 9)
			{
				system("cls");
				cout << "Enter value to print its parent: " << endl;
				cin >> value;
				RBT.printParent(value);

			}
			if (input == 10)
			{
				system("cls");

				cout << "Enter Filename: " << endl;
				cin >> filename;
				ifstream fin(filename);

				while (!fin.eof())
				{
					fin >> value;
					RBT.insert(value);
				}
				cout << "***INSERTED" << endl;	
			}
			if (input == 11)
			{
				system("cls");
				RBT.deleteDuplicated();
			}
			if (input == 12)
			{
				system("cls");
				RBT.destroyTree();
			}
			if (input == 13)
			{
				system("cls");
				break;
			}

	}

	cout << "THE END!" << endl;
	

	return 0;
}