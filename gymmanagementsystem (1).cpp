#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

class alogin
{
	string admin;

public:
	int adlogin()
	{

		cout << "Enter the admin code : ";
		cin >> admin;
		if (admin == "admin")
		{
		pass_try_again:
			int p = getadpassword();
			if (p == 1)
			{
				cout << "Login Succesful !! WELCOME to Admin Mode" << endl;
				cout << "Press any key to continue........" << endl;
				getchar();
				return 1;
			}
			else
			{
				int choice;
				cout << "1.Try Again\n2.Go to main menu" << endl;
				cin >> choice;
				if (choice == 1)
				{
					goto pass_try_again;
				}
				else
				{
					cout << "Login Failed" << endl;
					return 0;
				}
			}
		}
		else
		{
			cout << "Admin Code is wrong" << endl;
			return 2;
		}
	}
	int getadpassword();
};

int alogin::getadpassword()
{
	string pw;
	cout << "Enter the Password : ";
	cin.sync();
	getline(cin, pw);
	if (pw == "admin")
	{
		return 1;
	}
	else
	{
		cout << "Entered Password is Incorrect !!" << endl;
		return 0;
	}
}
void allotment_gold(int gc, int sc)
{
	if (gc != 0)
	{
		cout << gc << endl;

		cout << "Trainer Alloted !!\n";
	}
	else
	{
		cout << "No Trainer Available !!\n";
	}
}

void allotment_silver(int gc, int sc)
{
	if (sc != 0)
	{
		cout << sc << endl;

		cout << "Trainer Alloted !!\n";
	}
	else
	{
		cout << "\nNo Trainer Available !!\n";
		if (gc != 0)
		{
			cout << "Enter  Another Class !!\n";
			allotment_gold(gc, sc);
		}
	}
}

int trainee_allotment(char *c)
{
	char class_type[10];
	int i, gold_class = 3, silver_class = 5;
	strcpy(class_type, c);

	if ((gold_class != 0) || (silver_class) != 0)
	{
		if (strcmp(class_type, "gold") == 0)
		{
			gold_class--;
			allotment_gold(gold_class, silver_class);
		}
		else if (strcmp(class_type, "silver") == 0)
		{
			silver_class--;
			allotment_silver(gold_class, silver_class);
		}
	}
	else
	{

		cout << "Sorry...No trainer available at the moment...Please contact Admin.\n";
		return 1;
	}
}

class member
{
	int member_number, j;
	char mem_name[50], classs[50], timings[50];
	float fee;
	long long contact;

public:
	int time_slots()
	{
		int k;

		cout << "Please select your preferred timings\n Press 1 for : Morning 6-7\n Press 2 for : Morning 7-8\nPress 3 for : Morning 8-9\n";
		cout << " Press 4 for : Evening 4-5\nPress 5 for : Evening 5-6\nPress 6 for : Evening 6-7\n";
	start:
		cin.sync();
		cin >> k;
		switch (k)
		{
		case 1:
			strcpy(timings, "6AM-7AM");
			break;
		case 2:
			strcpy(timings, "7AM-8AM");
			break;
		case 3:
			strcpy(timings, "8AM-9AM");
			break;
		case 4:
			strcpy(timings, "4PM-5PM");
			break;
		case 5:
			strcpy(timings, "5PM-6PM");
			break;
		case 6:
			strcpy(timings, "6PM-7PM");
			break;
		default:
			cout << "Enter Valid Choice ....." << endl;
			goto start;
			break;
		}
	}
	void create_mem()
	{
		int k, l, j;
		cout << endl
			 << "Please Enter The member Number : ";
		cin >> member_number;
		cout << endl
			 << "Please Enter The Name of The member : ";
		getchar();
		cin.getline(mem_name, 50);
		cout << endl
			 << "Please Enter The contact number : ";
		cin >> contact;
		cout << "1. <--  Gold Class  -->\n2. <-   Silver Class   ->\n";
		cout << "Enter Your Choice : ";
		cin.sync();
		cin >> k;
		switch (k)
		{
		case 1:
		{
			strcpy(classs, "gold");
			fee = 2500;
			cout << "Your monthly fees would be : " << fee << endl;
			l = trainee_allotment(classs);
		}
		break;
		case 2:
		{
			strcpy(classs, "silver");
			fee = 2000;
			cout << "Your monthly fees would be : " << fee << endl;
			l = trainee_allotment(classs);
		}
		break;
		}
		time_slots();
	}

	void show_mem()
	{
		cout << endl
			 << "Member Code : " << member_number;
		cout << endl
			 << "Name : " << mem_name;
		cout << endl
			 << "Category : " << classs;
		cout << endl
			 << "Fee : " << fee;
		cout << endl
			 << "Contact : " << contact;
		cout << endl
			 << "Timings : " << timings << endl;
	}

	int getmem()
	{
		return member_number;
	}

	float getfee()
	{
		return fee;
	}

	char *getName()
	{
		return mem_name;
	}

	float getcontact()
	{
		return contact;
	}
};

fstream fp;
member m1;

void save_member()
{
	fp.open("newdata2.dat", ios::out | ios::app);
	m1.create_mem();
	fp.write((char *)&m1, sizeof(m1));
	fp.close();
	cout << endl
		 << endl
		 << "The member has been succesfully added...";
	cin.sync();
	getchar();
}

void show_all()
{
	system("cls");
	cout << endl
		 << "\t\t-- ALL RECORDS --";
	bool found = false;
	fp.open("newdata2.dat", ios::in);
	while (fp.read((char *)&m1, sizeof(m1)))
	{
		m1.show_mem();
		found = true;
		cout << endl
			 << "Press any key for next record >> ";
		cin.sync();
		getchar();
	}
	if (found == false)
	{
		cout << "\n\nNo records Exist";
		cin.sync();
		getchar();
	}
	fp.close();
}

void display_record(int num)
{
	bool found = false;
	fp.open("newdata2.dat", ios::in);
	while (fp.read((char *)&m1, sizeof(m1)))
	{
		if (m1.getmem() == num)
		{
			system("cls");
			m1.show_mem();
			found = true;
		}
	}

	fp.close();
	if (found == false)
		cout << "\n\nNo record found";
	cin.sync();
	getchar();
}

void edit_member()
{
	int num;
	bool found = false;
	system("cls");
	cout << endl
		 << endl
		 << "\tPlease Enter The member number: ";
	cin >> num;

	fp.open("newdata2.dat", ios::in | ios::out);
	while (fp.read((char *)&m1, sizeof(m1)) && found == false)
	{
		if (m1.getmem() == num)
		{
			m1.show_mem();
			cout << "\nPlease Enter The New details of the member: " << endl;
			m1.create_mem();
			int pos = 1 * sizeof(m1);
			fp.seekp(pos, ios::cur);
			fp.write((char *)&m1, sizeof(m1));
			cout << endl
				 << endl
				 << "\t Record Successfully Updated...";
			found = true;
		}
	}
	fp.close();
	if (found == false)
		cout << endl
			 << endl
			 << "Record Not Found...";
	getchar();
}

void delete_member()
{
	int num;
	system("cls");
	cout << endl
		 << endl
		 << "Please Enter The member number: ";
	cin >> num;
	fp.open("newdata2.dat", ios::in | ios::out);
	fstream fp2;
	fp2.open("Temp2.dat", ios::out);
	fp.seekg(0, ios::beg);
	while (fp.read((char *)&m1, sizeof(m1)))
	{
		if (m1.getmem() != num)
		{
			fp2.write((char *)&m1, sizeof(m1));
		}
	}
	fp2.close();
	fp.close();
	remove("newdata2.dat");
	rename("Temp2.dat", "newdata2.dat");
	cout << endl
		 << endl
		 << "\tRecord Deleted...";
	cin.sync();
	getchar();
}

void fnmanage()
{
	for (;;)
	{

		system("cls");
		int option;
		cout << "\t***********************************************";
		cout << "\n\tPress 1 to CREATE MEMBER";
		cout << "\n\tPress 2 to DISPLAY ALL RECORDS";
		cout << "\n\tPress 3 to SEARCH FOR A PARTICULAR RECORD ";
		cout << "\n\tPress 4 to EDIT MEMBER DETAILS";
		cout << "\n\tPress 5 to DELETE MEMBER";
		cout << "\n\tPress 6 to GO BACK TO MAIN MENU";
		cout << "\n\t**********************************************";

		cout << "\n\n\tOption: ";
		cin >> option;
		switch (option)
		{
		case 1:
			system("cls");
			save_member();
			break;

		case 2:
			show_all();
			break;

		case 3:
			int num;
			system("cls");
			cout << "\n\n\tPlease Enter The Member Number : ";
			cin >> num;
			display_record(num);
			break;

		case 4:
			edit_member();
			break;

		case 5:
			delete_member();
			break;

		case 6:
			system("cls");
			return;
			break;

		default:
			fnmanage();
		}
	}
}
void fnuser()
{
	for (;;)
	{
		int m;
		cout << "1.Join Gym\n2.Quit Gym\n3.Edit Your Profile\n4.Return to Main Menu\n";
		cout << endl
			 << "Enter your choice --> ";
		cin >> m;
		switch (m)
		{
		case 1:
			system("cls");
			save_member();
			break;
		case 2:
			delete_member();
			break;
		case 3:
			edit_member();
			break;
		case 4:
			return;
		}
	}
}

int main()
{

	int i, k;
	string name, code;
	cout << "\n\n ----  << SRM Gym Management System >>  ----" << endl;
label:
	cout << endl
		 << "SELECT MODE" << endl
		 << "1.User" << endl
		 << "2.Admin" << endl
		 << "3.Exit" << endl
		 << endl
		 << "Enter Choice -> ";
	cin >> i;

	if (i == 1)
	{
		cout << endl
			 << " ---- You are in USER MODE ----" << endl
			 << endl;
		fnuser();
		goto label;
	}
	else if (i == 2)
	{
		cout << endl
			 << " ---- You are in ADMIN MODE ----" << endl
			 << endl;

		alogin ad;
		k = ad.adlogin();
		if (k == 1)
		{
			fnmanage();
			goto label;
		}
		else
		{
			goto label;
		}
	}
	else if (i == 3)
	{
		cout << endl
			 << "Thank You for using SRM Gym -- Fitness Forever." << endl;
	}
	else
	{
		cout << endl
			 << "Invalid Choice !! Enter valid Option " << endl;
		goto label;
	}
	return 0;
}
