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

struct retrieve_faculty
{
	int id;
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

void valid_count(int &num)
{
	while (!cin.good())
	{
		cin.clear();
		while ((cin.get() != '\n'));
		cout << endl << "Enter valid count" << endl << "ENTER AGAIN: ";
		cin >> num;
		cout << endl;
	}
}

void valid_id(int& num)
{
	while (!cin.good() || (!(num >= 1000 && num <= 9999)))
	{
		cin.clear();
		while ((cin.get() != '\n'));
		cout << endl << "Enter a valid 4-digit id " << endl << "ENTER AGAIN: ";
		cin >> num;
	}
}

bool id_validation(int &id)
{
	InventoryItem item;
	ifstream valid("inventory_item_data.txt");
	while (getline(valid, item.Name))
	{
		valid >> item.Item_Id;
		valid >> item.Category;
		valid >> item.Item_count;
		valid.ignore();
		if (item.Item_Id == id)
			return 1;
	}
	return 0;
}

void display_item_name_id()
{
	InventoryItem item;
	ifstream display("inventory_item_data.txt");
	while (getline(display, item.Name))
	{
		display >> item.Item_Id;
		display.ignore();
		getline(display, item.Category);
		display >> item.Item_count;
		display.ignore();

		cout << left << setw(7) << "Name" << ": " << item.Name << endl;
		cout << left << setw(7) << "Item_Id" << ": " << item.Item_Id << endl << endl;
	}
	display.close();
}

void showFacList(int id)
{
	int id_fac = 0;
	char a;
	Faculty show_list;
	ifstream show_fac("Faculty_data.txt");
	cout << endl;
	while (show_fac >> id_fac)
	{
		getline(show_fac, show_list.Name, '\t');
		getline(show_fac, show_list.subject, '\t');
		show_fac >> show_list.join_year;
		getline(show_fac, show_list.designation);
		if (id_fac == id)
		{
			cout << left;
			cout << setw(11) << "Name" << ": " << show_list.Name << endl;
			cout << setw(11) << "Subject" << ": " << show_list.subject << endl;
			cout << setw(11) << "Join year" << ": " << show_list.join_year << endl;
			cout << setw(11) << "Designation" << ": " << show_list.designation << endl << endl;
		}
	}
	show_fac.close();
}

bool string_compare(string s1, string s2)
{
	int l1 = s1.length();
	int l2 = s2.length();
	if (l1 == l2)
	{
		for (int i = 0; i < l1; i++)
		{
			if (s1[i] >= 65 && s1[i] <= 90)
			{
				s1[i] += 32;
			}
			if (s2[i] >= 65 && s2[i] <= 90)
			{
				s2[i] += 32;
			}
			if (s1[i] != s2[i])
			{
				return 0;
			}
		}
	}
	else if (l1 != l2)
	{
		return 0;
	}
	return 1;
}

int assign_retrieve_count(InventoryItem* Assign_item_count, int id, int num)
{
	int i = 0;
	int t = 100;
	ifstream Assign_count("inventory_item_data.txt");
	while (getline(Assign_count, Assign_item_count[i].Name))
	{
		Assign_count >> Assign_item_count[i].Item_Id;
		Assign_count >> Assign_item_count[i].Category;
		Assign_count >> Assign_item_count[i].Item_count;
		Assign_count.ignore();
		if (id == Assign_item_count[i].Item_Id)
		{
			if (Assign_item_count[i].Item_count <= 0)
			{
				cout << "No items in stock." << endl;
				if (num == -1)
				return 0;
			}
			Assign_item_count[i].Item_count = Assign_item_count[i].Item_count + num;
		}
		i++;
		if (i > t)
		{
			InventoryItem* Assign_item_count = new InventoryItem[t + 100];
		}
	}
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
	return i;

	Assign_count.close();
}

//*************************************************************

void Add_Item()
{
	InventoryItem item;
	cin.ignore();
	cin.ignore();
	cout << "\t\t\t*********ITEM DETAIL*********" << endl << endl;
	cout << left;
	cout << setw(8)<< "Name" <<": "; getline(cin, item.Name);
	cout << setw(8) << "Id" << ": "; cin >> item.Item_Id;
	valid_id(item.Item_Id);
	cin.ignore();
	cout << setw(8) << "Category" << ": "; getline(cin, item.Category);
	cout << setw(8) << "Count" << ": "; cin >> item.Item_count;
	valid_count(item.Item_count);
	ofstream Add("inventory_item_data.txt", ios::app);
	Add << item.Name << endl; //FORMATTING
	Add << item.Item_Id << endl;
	Add << item.Category << endl;
	Add << item.Item_count << endl;
	Add.close();
}

void show_inventory_items()
{
	InventoryItem show_item;
	ifstream Show("inventory_item_data.txt");
	while (getline(Show, show_item.Name))
	{
		Show >> show_item.Item_Id;
		Show >> show_item.Category;
		Show >> show_item.Item_count;
		Show.ignore();
		cout << left << setw(10) << "Name" << ": " << show_item.Name << endl << setw(10) << "Item Id" << ": " << show_item.Item_Id << endl << setw(10) << "Category" << ": " << show_item.Category
			<< endl << setw(10) << "Item Count" << ": " << show_item.Item_count << endl << endl;
	}
	Show.close();
}

void search_inventory_item()
{
	display_item_name_id();
	bool item_find = 0;
	InventoryItem search_item;
	string item_name;
	cin.ignore();
	cout << "Name of the item to search: "; getline(cin, item_name);
	
	ifstream search_invent_item("inventory_item_data.txt");
	while (getline(search_invent_item, search_item.Name))
	{
		search_invent_item >> search_item.Item_Id;
		search_invent_item >> search_item.Category;
		search_invent_item >> search_item.Item_count;
		search_invent_item.ignore();
		if (string_compare(item_name, search_item.Name))
		{
			cout << endl << "\t\t\t*************ITEM DETAIL*************" << endl;
			cout << left << setw(10) << "Name" << ": " << search_item.Name << endl;
			cout << left << setw(10) << "Item Id" << ": " << search_item.Item_Id << endl;
			cout << left << setw(10) << "Category" << ": " << search_item.Category << endl;
			cout << left << setw(10) << "Item count" << ": " << search_item.Item_count << endl;
			item_find = 1;
		}
	}
	if (item_find == 0)
	{
		cout << "Item not found" << endl;
	}
}

void edit_inventory_item()
{
	display_item_name_id();
	int id = 0;
	cout << "ID of item to be edited: "; cin >> id;
	valid_id(id);
	if (id_validation(id))
	{
		InventoryItem item1;
		int count = 100;
		int i = 0;
		InventoryItem* edit_item = new InventoryItem[count];
		ifstream file_edit("inventory_item_data.txt");
		while (getline(file_edit, edit_item[i].Name))
		{
			file_edit >> edit_item[i].Item_Id;
			file_edit >> edit_item[i].Category;
			file_edit >> edit_item[i].Item_count;
			file_edit.ignore();
			if (id == edit_item[i].Item_Id)
			{
				cout << endl << "\t\t\t*******EDITED INFORMATION*******" << endl;
				cin.ignore();
				cout << left << setw(10) << "Name" << ": "; getline(cin, edit_item[i].Name);
				cout << left << setw(10) << "Item ID" << ": "; cout << edit_item[i].Item_Id << endl;
				cout << left << setw(10) << "Category" << ": "; cin >> edit_item[i].Category;
				cout << left << setw(10) << "Item count" << ": "; cin >> edit_item[i].Item_count;
				valid_count(edit_item->Item_count);
			}
			i++;
		}
		file_edit.close();
		ofstream file_rewrite("inventory_item_data.txt");
		int j = 0;
		while (j < i)
		{
			file_rewrite << edit_item[j].Name << endl;
			file_rewrite << edit_item[j].Item_Id << endl;
			file_rewrite << edit_item[j].Category << endl;
			file_rewrite << edit_item[j].Item_count << endl;
			j++;
		}
	}
	else
		cout << endl << "**********INVALID ID. ITEM NOT FOUND**********" << endl;
}

void delete_inventory_item()
{
	display_item_name_id();

	int id = 0;
	cout << "ID of item to be deleted: "; cin >> id;
	valid_id(id);
	if (id_validation(id))
	{
		int count = 100;
		int i = 0;
		InventoryItem* edit_item = new InventoryItem[count];
		ifstream file_edit("inventory_item_data.txt");
		while (getline(file_edit, edit_item[i].Name))
		{
			file_edit >> edit_item[i].Item_Id;
			file_edit >> edit_item[i].Category;
			file_edit >> edit_item[i].Item_count;
			file_edit.ignore();
			if (id == edit_item[i].Item_Id)
			{
				edit_item[i].Name = "$$$$";
				edit_item[i].Item_Id = -1;
				edit_item[i].Category = "$$$$";
				edit_item[i].Item_count = -1;
			}
			i++;
			if (i > count)
				InventoryItem* edit_item = new InventoryItem[count + 100];
		}
		ofstream file_rewrite("inventory_item_data.txt");
		int j = 0;
		while (j < i)
		{
			if (edit_item[j].Name != "$$$$")
				file_rewrite << edit_item[j].Name << endl;
			if (edit_item[j].Item_Id != -1)
				file_rewrite << edit_item[j].Item_Id << endl;
			if (edit_item[j].Category != "$$$$")
				file_rewrite << edit_item[j].Category << endl;
			if (edit_item[j].Item_Id != -1)
				file_rewrite << edit_item[j].Item_count << endl;
			j++;
		}
	}
	else
		cout << "**********INVALID ID. ITEM NOT FOUND**********" << endl;
}

int Assign()
{
	display_item_name_id();
	cout << endl << "Item ID to be assigned: " << endl;
	int id;
	ifstream count_check("inventory_item_data.txt");
	Faculty assign;
	ofstream Assign_item("Faculty_data.txt", ios::app);
	cin >> id;
	valid_id(id);
	if (id_validation(id))
	{
		cout << endl << "\t\t\t**********FACULTY DETAIL**********" << endl;
		int t = 100;
		InventoryItem* Assign_item_count = new InventoryItem[t];
		int value = assign_retrieve_count(Assign_item_count, id, -1);
		if (value == 0)
			return 0;
		else
		{
			cin.ignore();
			cout << left;
			cout << setw(11) << "Name" << ": "; getline(cin, assign.Name);
			cout << setw(11) << "Subject" << ": "; getline(cin, assign.subject);
			cout << setw(11) << "Join year" << ": "; cin >> assign.join_year;
			valid_count(assign.join_year);
			cin.ignore();
			cout << setw(11) << "Designation" << ": "; getline(cin, assign.designation);
			Assign_item << id << " " << assign.Name << "\t" << assign.subject
				<< "\t" << assign.join_year << "\t" << assign.designation << endl;
			Assign_item.close();
		}
		delete[] Assign_item_count;
	}
	else
		cout << "**********INVALID ID. ITEM NOT FOUND**********" << endl;
}

void Retrieve()
{
	display_item_name_id();
	int id;
	cout << "Item ID you want to retrieve: "; cin >> id;
	while (!cin.good() || (!(id >= 1000 && id <= 9999)))
	{
		cin.clear();
		while ((cin.get() != '\n'));
		cout << endl << "Enter a valid 4-digit id " << endl << "ENTER AGAIN: ";
		cin >> id;
		cout << endl;
	}
	if (id_validation(id))
	{
		int t = 100, i = 0, j = 0;

		InventoryItem* Assign_item_count = new InventoryItem[t];
		assign_retrieve_count(Assign_item_count, id, 1);

		retrieve_faculty* fac_list = new retrieve_faculty[t];
		retrieve_faculty* fac_not_found = new retrieve_faculty[t];
		ifstream faculty_retrieve("Faculty_data.txt");
		int a = 0;
		//STORING ALL FACULTY MEMBERS HAVING THAT ITEM AND THOSE NOT HAVING IN SEPARATE ARRAYS
		while (faculty_retrieve >> fac_list[i].id)
		{
			if (id == fac_list[i].id)
			{
				cin.ignore();
				getline(faculty_retrieve, fac_list[i].Name, '\t');
				getline(faculty_retrieve, fac_list[i].subject, '\t');
				faculty_retrieve >> fac_list[i].join_year;
				getline(faculty_retrieve, fac_list[i].designation, '\n');
				i++;
			}
			else
			{
				fac_not_found[a].id = fac_list[i].id;
				getline(faculty_retrieve, fac_not_found[a].Name, '\t');
				getline(faculty_retrieve, fac_not_found[a].subject, '\t');
				faculty_retrieve >> fac_not_found[a].join_year;
				getline(faculty_retrieve, fac_not_found[a].designation, '\n');
				a++;
			}
		}
		faculty_retrieve.close();

		//DISPLAYING FACULTY MEMBERS HAVING THAT ITEM
		cout << left;
		cout << endl << "\t\t**********FACULTY DESCRIPTION**********" << endl << endl;
		cout << setw(10) << "ITEM ID" << setw(16) << "NAME" << setw(23) << "SUBJECT" << setw(15) << "JOIN YEAR" << "DESIGNATION" << endl << endl;
		while (j < i)
		{
			cout << left << setw(9) << fac_list[j].id;
			cout << left << setw(17) << fac_list[j].Name;
			cout << left << setw(23) << fac_list[j].subject;
			cout << left << setw(10) << fac_list[j].join_year;
			cout << fac_list[j].designation;
			cout << endl;
			j++;
		}

		int k = 0;
		string name1, name2;
		cout << endl << "Teacher from whom u want to retrieve item: "; getline(cin, name1);
		name1.erase(std::remove_if(name1.begin(), name1.end(), ::isspace), name1.end());

		//ELIMINATING THE DATA OF MATCHING FACULTY MEMBER
		while (k < i)
		{
			name2 = fac_list[k].Name;
			fac_list[k].Name.erase(std::remove_if(fac_list[k].Name.begin(), fac_list[k].Name.end(), ::isspace), fac_list[k].Name.end());
			if (string_compare(name1, fac_list[k].Name))
			{
				fac_list[k].id = -1;
				fac_list[k].Name = "$$$$";
				fac_list[k].subject = "$$$$";
				fac_list[k].join_year = -1;
				fac_list[k].designation = "$$$$";
			}
			else
			{
				fac_list[k].Name = name2;
			}
			k++;
		}

		ofstream fac_data_overwrite("Faculty_data.txt");
		int b = 0;

		//THOSE WHO DIDN'T HAVE THAT ITEM ARE WRITTEN BACK TO FILE
		while (b < a)
		{
			fac_data_overwrite << fac_not_found[b].id;
			fac_data_overwrite << fac_not_found[b].Name << "\t";
			fac_data_overwrite << fac_not_found[b].subject << "\t";
			fac_data_overwrite << fac_not_found[b].join_year;
			fac_data_overwrite << fac_not_found[b].designation << "\n";
			b++;
		}
		//THOSE WHO HAD THE ITEM AND DIDN'T MATCH THE NAME ENTERED BY USER ARE BEING WRITTEN BACK TO FILE
		j = 0;
		while (j < i)
		{
			if (fac_list[j].id != -1)
				fac_data_overwrite << fac_list[j].id << " ";
			if (fac_list[j].Name != "$$$$")
				fac_data_overwrite << fac_list[j].Name << "\t";
			if (fac_list[j].subject != "$$$$")
				fac_data_overwrite << fac_list[j].subject << "\t";
			if (fac_list[j].join_year != -1)
				fac_data_overwrite << fac_list[j].join_year;
			if (fac_list[j].designation != "$$$$")
				fac_data_overwrite << fac_list[j].designation << "\n";
			j++;
		}
		fac_data_overwrite.close();
		delete[] fac_list;
		delete[] fac_not_found;
	}
	else
	{
		cout << "**********INVALID ID. ITEM NOT FOUND**********" << endl;
	}
}

void fac_list_borrowed_item()
{
	int fac_list_id;
	display_item_name_id();
	cout << "Enter item ID for faculty data: "; cin >> fac_list_id;
	valid_id(fac_list_id);
	if (id_validation(fac_list_id))
		showFacList(fac_list_id);
	else
		cout << "**********INVALID ID! ITEM NOT FOUND**********" << endl;
}

int main()
{
	cout << endl << "\t\t\t\tPUNJAB UNIVERSITY OF INFORMATION TECHNOLOGY" << endl;
	cout << "\t\t\t\t\t  INVENTORY MANAGEMENT SYSTEM" << endl;
	cout << "\t\t\t\t\t\t  WELCOME" << endl;
	cout << endl << endl;
	int option = 0;
	do
	{
		cout << "Enter 1 to Add inventory items" << endl;
		cout << "Enter 2 to View all inventory items" << endl;
		cout << "Enter 3 to Search inventory item" << endl;
		cout << "Enter 4 to Edit inventory item (Including item count)" << endl;
		cout << "Enter 5 to Delete inventory item" << endl;
		cout << "Enter 6 to Assign inventory item" << endl;
		cout << "Enter 7 to Retrieve inventory item" << endl;
		cout << "Enter 8 to View the list of faculty members who have borrowed a specific item" << endl;
		cout << "Enter 0 to quit" << endl;
		cout << "Enter your option: "; cin >> option;
		while (!cin.good())
		{
			cin.clear();
			while ((cin.get() != '\n'));
			cout << endl << "Enter an integer" << endl << "ENTER AGAIN: ";
			cin >> option;
		}

		//Input validation
		while (option != 1 && option != 2 && option != 3 && option != 4 && option != 5
			&& option != 6 && option != 7 && option != 8 && option != 0)
		{
			cout << endl << "Please enter a valid choice(1-9): ";
			cin >> option;
		}
		if (option == 0)
		{
			cout << endl << "\t\t\t\t*******THANK YOU! HAVE A NICE DAY*******" << endl;
			return 0;
		}
		cout << "\t\t\t\t\t\t*****************************" << endl;
		switch (option)
		{
		case 1:
		{
			Add_Item();
			break;
		}
		case 2:
		{
			show_inventory_items();
			break;
		}
		case 3:
		{
			search_inventory_item();
			break;
		}
		case 4:
		{
			edit_inventory_item();
			break;
		}
		case 5:
		{
			delete_inventory_item();
			break;
		}
		case 6:
		{
			Assign();
			break;
		}
		case 7:
		{
			Retrieve();
			break;
		}
		case 8:
		{
			fac_list_borrowed_item();
			break;
		}
		}
		cout << endl << endl;
	} while (option != 0);
	return 0;
}