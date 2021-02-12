#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <conio.h>
#include <string>
#include <stdio.h> 
#include <string.h> 

using namespace std; 

static const char alphnum[]="0123456789" "!@%&*" "ABCDEFGHIJKLMNOPQRSTUVWXYZ" "abcdefghijklmnopqrstuvwxyz"; 
int strLen=sizeof(alphnum)-1; 

void cursor(int cursor, int point)
{
	if(cursor == point)
		cout << "-- ->- ";
	else
		cout << "       ";
}

void savePasswd(string description, string passwd)
{
	ofstream file("passwds.txt", ios::app);
	file << description << ":" << passwd << endl;
	file.close();
}

void readFile()
{
	string line = "";
	ifstream file("passwds.txt");
	if(file.is_open())
	{
		while(getline(file, line))
			cout << line << endl;
	}
	file.close();	
}

bool control(string search, string line)
{
	for(int i=0; i<search.length(); i++)
		if(search[i] != line[i])
			return false;
	return true;
}

void search(string description)
{
	string line = "";
	ifstream file("passwds.txt");
	if(file.is_open())
	{
		while(getline(file, line))
		{
			if(control(description, line))
			{
				cout << line;
				break;
			}
		}
	}
	file.close();
	
}

char GenRand()
{ 
	return alphnum[rand()%strLen]; 
} 

string passwdGenerate(int length)
{
	int c=0,s=0;
	srand(time(0));
	N:
	char C;
	string D;
	for(int z=0; z < length; z++) 
	{ 
		C=GenRand();
		D+=C;
		if(isdigit(C))
		{
			c++;
		}
		if(C=='!' || C=='@' || C=='$' || C=='%' ||  C=='^' || C=='&'|| C=='*'|| C=='#')
		{
			s++;
		}
	}
	if(length>2 && (s==0 || c==0))
	{
		goto N; 
	}
	return D;
	
}

void passwd()
{
	int length;
	string description;
	string passwd;
	char c;
	
	cout << "Description: ";
	cin >> description;
	cout <<"Enter the length of the password required:";
	cin >>length;
	while(1)
	{
		passwd = passwdGenerate(length);
		cout <<"Your Password: " << passwd << endl;
		cout << "New Password? (y/n)";
		cin >> c;
		if(c == 'n')
		{
			savePasswd(description, passwd);
			break;
		}
	}
}

void menu()
{
	int c = 0;
	int key;
	string des;
	while(1)
	{
		system("cls");
		cursor(c, 0); cout << "List of Passwords" << endl;
		cursor(c, 1); cout << "Search" << endl;
		cursor(c, 2); cout << "Add Passwords" << endl;
		key = getch();
					
		if(key == 80 && c != 2)
			c ++;
		else if(key == 80 && c == 2)
			c = 0;
		else if(key == 72 && c != 0)
			c --;
		else if(key == 72 && c == 0)
			c = 2;
		else if(key == 13)
		{
			system("cls");
			switch(c)
			{
				case 0:
					readFile();
					break;
				case 1:
					cout << "Search description: ";
					cin >> des;
					search(des);
					break;
				case 2:
					passwd();
					break;
			}
			printf("\n\nPress any key to return to the menu...");
			key = getch();
		}
	}
}

int main() 
{ 
	menu();
	return 0; 
}
