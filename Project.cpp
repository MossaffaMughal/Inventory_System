#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int count_item = 0;

struct Faculty
{
	string Name;
	string subject;
	int join_year;
	string designation;
};

struct InventoryItem
{
	string Name;
	int Item_Id;
	string Category;
	int Item_count;

};

void display_item_name_id()
{
	InventoryItem item;
	ifstream display("inventory_item_data.txt");
	while (!(display.eof()))
	{
		getline(display, item.Name);
		display >> item.Item_Id;
		display.ignore();
		getline(display, item.Category);
		display >> item.Item_count;
		display.ignore();
		
		cout << "Name: " << item.Name << endl;
		cout << "Item_Id: " << item.Item_Id << endl << endl;
	}
	display.close();
}

void Add_Item()
{
	InventoryItem item;
	cin.ignore();
	//item.p_faculty = new Faculty[5];
	cin.ignore();
	cout << "Item Name: "; getline(cin, item.Name);
	cout << "Item Id: "; cin >> item.Item_Id;
	cin.ignore();
	cout << "Item Category: "; getline(cin, item.Category);
	cout << "Item count: "; cin >> item.Item_count;
	ofstream Add("inventory_item_data.txt", ios::app);
	Add << item.Name << endl;
	Add << item.Item_Id << endl;
	Add << item.Category << endl;
	Add << item.Item_count << endl;
	Add.close();
}

int Assign()
{
	display_item_name_id();
	cout << endl << "Enter the id of the item you want to assign and faculty detail: " << endl;
	int id;
	ifstream count_check("inventory_item_data.txt");
	Faculty assign;
	ofstream Assign_item("Faculty_data.txt", ios::app);
	cout << "Item Id: "; cin >> id;

	int i = 0;
	int t = 100;
	InventoryItem* Assign_item_count = new InventoryItem[t];
	ifstream Assign_count("inventory_item_data.txt");
	while (Assign_count >> Assign_item_count[i].Name)
	{
		Assign_count >> Assign_item_count[i].Item_Id;
		Assign_count >> Assign_item_count[i].Category;
		Assign_count >> Assign_item_count[i].Item_count;
		if (id == Assign_item_count[i].Item_Id)
		{
			if (Assign_item_count[i].Item_count <= 0)
			{
				cout << "Sorry. No items in stock." << endl;
				return 0;
			}
			Assign_item_count[i].Item_count--;
		}
		i++;
		if (i > t)
		{
			InventoryItem* Assign_item_count = new InventoryItem[t + 100];
		}
	}

	Assign_count.close();
	cin.ignore();
	cout << "Name: "; getline(cin, assign.Name);
	cout << "Subject: "; getline(cin, assign.subject);
	cout << "Join year: "; cin >> assign.join_year;
	cin.ignore();
	cout << "Designation: "; getline(cin, assign.designation);
	Assign_item << id << " " << assign.Name << "\t" << assign.subject 
		<< "\t" << assign.join_year  << "\t" << assign.designation << endl;
	Assign_item.close();


	ofstream Assign_invent_item("inventory_item_data.txt");
	int j = 0;
	while (j < i)
	{
		Assign_invent_item << Assign_item_count[j].Name << endl;
		Assign_invent_item << Assign_item_count[j].Item_Id << endl;
		Assign_invent_item << Assign_item_count[j].Category << endl;
		Assign_invent_item << Assign_item_count[j].Item_count << endl;
		j++;
	}
	Assign_invent_item.close();
	delete[] Assign_item_count;
}

void showFacList(int id)
{
	int id_fac = 0;
	Faculty show_list;
	ifstream show_fac("Faculty_data.txt");
	while (!(show_fac.eof()))
	{
		show_fac >> id_fac;
		getline(show_fac, show_list.Name, '\t');
		getline(show_fac, show_list.subject, '\t');
		show_fac >> show_list.join_year;
		getline(show_fac, show_list.designation);
		if (id_fac == id)
		{
			cout << "Name: " << show_list.Name << endl;
			cout << "Subject: " << show_list.subject << endl;
			cout << "Join year: " << show_list.join_year << endl;
			cout << "Designation: " << show_list.designation << endl << endl;
		}
	}
	show_fac.close();
}

void show_inventory_items()
{
	InventoryItem show_item;
	//InventoryItem* p_show = &show_item;
	ifstream Show("inventory_item_data.txt");
	//int c = 0; 
	while (!Show.eof())
	{
		Show >> show_item.Name;
		Show >> show_item.Item_Id;
		Show >> show_item.Category;
		Show >> show_item.Item_count;
		count_item++;
		cout << left << setw(10) << "Name" << ": " << show_item.Name << endl << setw(10) << "Item Id" << ": " << show_item.Item_Id << endl << setw(10) << "Category" << ": " << show_item.Category
			<< endl << setw(10) << "Item Count" << ": " << show_item.Item_count << endl << endl;
	}
	Show.close();
}

void search_inventory_item()
{
	InventoryItem search_item;
	string item_name;
	cout << "Enter name of the item you want to search for: "; cin >> item_name;
	ifstream search_invent_item("inventory_item_data.txt");
	search_invent_item >> search_item.Name;
	search_invent_item >> search_item.Item_Id;
	search_invent_item >> search_item.Category;
	search_invent_item >> search_item.Item_count;
}

void fac_list_borrowed_item()
{
	int fac_list_id;
	show_inventory_items();
	cout << "Enter item ID for faculty data: "; cin >> fac_list_id;
	showFacList(fac_list_id);
}

int main()
{
	cout << "Enter 1 to Add inventory items" << endl;
	cout << "Enter 2 to View all inventory items" << endl;
	cout << "Enter 3 to Search inventory item" << endl;
	cout << "Enter 4 to Edit inventory item (Including item count)" << endl;
	cout << "Enter 5 to Delete inventory item" << endl;
	cout << "Enter 6 to Assign inventory item" << endl;
	cout << "Enter 7 to Retrieve inventory item" << endl;
	cout << "Enter 8 to View the list of faculty members who have borrowed a specific item" << endl;
	cout << "Press Q to quit" << endl;
	
	char option = 0;
	cout << "Enter your option: "; cin >> option;
	
	//Input validation
	while (option != '1' && option != '2' && option != '3' && option != '4' && option != '5'
		&& option != '6' && option != '7' && option != '8' && option != 'q' && option != 'Q')
	{
		cout << endl << "Please enter a valid choice: ";
		cin >> option;
	}

	if (option == 'q' || option == 'Q') //To quit the program
	{
		return 0;
	}

	cout << "		******************************			" << endl;
	switch (option)
	{
	case '1':
	{
		Add_Item();
		break;
	}
	case '2':
	{
		show_inventory_items();
		break;
	}
	case '3':
	{
		break;
	}
	case '4':
	{
		break;
	}
	case '5':
	{
		break;
	}
	case '6':
	{
		Assign();
		break;
	}
	case '7':
	{
		break;
	}
	case '8':
	{
		fac_list_borrowed_item();
		break;
	}
	}

	return 0;
} 