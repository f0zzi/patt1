#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <Windows.h>
using namespace std;

class Button abstract
{
private:
	string name;
public:
	Button() :Button("Button") {}
	Button(string name)
	{
		SetName(name);
	}
	string GetName() const
	{
		return name;
	}
	void SetName(string name)
	{
		if (name.size())
			this->name = name;
	}
	virtual void Press()
	{
		cout << "Button \"" << name << "\" pressed." << endl;
	}
};
class Checkbox abstract
{
private:
	bool checked;
	string name;
public:
	Checkbox() : Checkbox("Checkbox", false) {}
	Checkbox(string name, bool state = false) : checked(state)
	{
		SetName(name);
	}
	string GetName() const
	{
		return name;
	}
	void SetName(string name)
	{
		if (name.size())
			this->name = name;
	}
	virtual void Check()
	{
		checked = !checked;
	}
	bool GetState()
	{
		return checked;
	}
};

class WinButton : public Button 
{
public:
	WinButton() {}
	WinButton(string name) : Button(name) {}
	void Press()
	{
		cout << "Winbutton " << GetName() << " pressed." << endl;
	}
};
class MacButton : public Button
{
public:
	MacButton() {}
	MacButton(string name) : Button(name) {}
	void Press()
	{
		cout << "Macbutton " << GetName() << " pressed." << endl;
	}
};
class WinCheckbox : public Checkbox
{
public:
	WinCheckbox() {}
	WinCheckbox(string name, bool state = false) : Checkbox(name, state) {}
	void Check()
	{
		Checkbox::Check();
		cout << "Click. Wincheckbox " << GetName() << " turned " << (GetState() ? "ON" : "OFF") << endl;
	}
};
class MacCheckbox : public Checkbox
{
public:
	MacCheckbox() {}
	MacCheckbox(string name, bool state = false) : Checkbox(name, state) {}
	void Check()
	{
		Checkbox::Check();
		cout << "Click. Maccheckbox " << GetName() << " turned " << (GetState() ? "ON" : "OFF") << endl;
	}
};

__interface IGUIFactory
{
	Button* CreateButton(string name = "Button");
	Checkbox* CreateCheckbox(string name = "Checkbox");
};

class WinFactory : public IGUIFactory
{
private:
	WinFactory() {}
	static WinFactory* instance;
public:
	Button* CreateButton(string name = "Button")
	{
		return new WinButton(name);
	}
	Checkbox* CreateCheckbox(string name = "Checkbox")
	{
		return new WinCheckbox(name);
	}
	static WinFactory* GetInstance()
	{
		if (instance == nullptr)
			instance = new WinFactory;
		return instance;
	}
};
WinFactory* WinFactory::instance = nullptr;

class MacFactory : public IGUIFactory
{
private:
	MacFactory() {}
	static MacFactory* instance;
public:
	Button* CreateButton(string name = "Button")
	{
		return new MacButton(name);
	}
	Checkbox* CreateCheckbox(string name = "Checkbox")
	{
		return new MacCheckbox(name);
	}
	static MacFactory* GetInstance()
	{
		if (instance == nullptr)
			instance = new MacFactory;
		return instance;
	}
};
MacFactory* MacFactory::instance = nullptr;

class Application
{
private:
	vector<Button*> buttons;
	vector<Checkbox*> checkboxes;
	IGUIFactory* factory = nullptr;
public:
	Application()
	{
		int selection;
		do
		{
			cout << "Choose application platform:" << endl;
			cout << "1 - Windows.\n";
			cout << "2 - Macintosh.\n";
			cout << "Your selection: ";
			cin >> selection;
			if (selection != 1 && selection != 2)
				cout << "Invalid input. Try again.\n";
		} while (selection != 1 && selection != 2);
		switch (selection)
		{
		case 1:
			factory = WinFactory::GetInstance();
			break;
		case 2:
			factory = MacFactory::GetInstance();
			break;
		}
	}
	void AddButton()
	{
		string tmp;
		do
		{
			cout << "Enter button name: ";
			cin.ignore();
			getline(cin, tmp);
			if (!tmp.size())
				cout << "Invalid input try again." << endl;
		} while (!tmp.size());
		buttons.push_back(factory->CreateButton(tmp));
	}
	void AddCheckbox()
	{
		string tmp;
		do
		{
			cout << "Enter checkbox name: ";
			cin.ignore();
			getline(cin, tmp);
			if (!tmp.size())
				cout << "Invalid input try again." << endl;
		} while (!tmp.size());
		checkboxes.push_back(factory->CreateCheckbox(tmp));
	}
	void ShowButtons()
	{
		if (buttons.size())
		{
			cout << "Buttons:" << endl;
			for (size_t i = 0; i < buttons.size(); i++)
				cout << i + 1 << " - " << buttons[i]->GetName() << endl;
		}
		else
			cout << "There are no buttons is your app. You should add few." << endl;
	}
	void ShowCheckBoxes()
	{
		if (checkboxes.size())
		{
			cout << "Checkboxes:" << endl;
			for (size_t i = 0; i < checkboxes.size(); i++)
				cout << i + 1 << " - " << checkboxes[i]->GetName() << " is " << (checkboxes[i]->GetState() ? "ON" : "OFF") << endl;
		}
		else
			cout << "There are no checkboxes is your app. You should add few." << endl;
	}
	void Interact()
	{
		int selection;
		do
		{
			selection = -1;
			system("cls");
			ShowButtons();
			ShowCheckBoxes();
			cout << endl;
			cout << "Application menu:" << endl;
			cout << "1 - Add button." << endl;
			cout << "2 - Add checkbox." << endl;
			cout << "3 - Press button." << endl;
			cout << "4 - Press checkbox." << endl;
			cout << "0 - Exit." << endl;
			cout << "Make selection: ";
			cin >> selection;
			switch (selection)
			{
			case 1:
				AddButton();
				break;
			case 2:
				AddCheckbox();
				break;
			case 3:
				if (buttons.size())
				{
					do
					{
						cout << "Enter number of button to press: ";
						cin >> selection;
						if (selection - 1 >= buttons.size() || selection - 1 < 0)
							cout << "Invalid input. Try again." << endl;
					} while (selection - 1 >= buttons.size() || selection - 1 < 0);
					buttons[selection - 1]->Press();
				}
				else
					cout << "There are no buttons. You should add few." << endl;
				system("pause");
				break;
			case 4:
				if (checkboxes.size())
				{
					do
					{
						cout << "Enter number of checkbox to press: ";
						cin >> selection;
						if (selection - 1 >= checkboxes.size() || selection - 1 < 0)
							cout << "Invalid input. Try again." << endl;
					} while (selection - 1 >= checkboxes.size() || selection - 1 < 0);
					checkboxes[selection - 1]->Check();
				}
				else
					cout << "There are no checkboxes. You should add few." << endl;
				system("pause");
				break;
			case 0:
				cout << "Have a nice day." << endl;
				system("pause");
				break;
			default:
				cout << "Invalid input. Try again." << endl;
				system("pause");
				break;
			}
		} while (selection);
	}
};