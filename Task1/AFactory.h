#pragma once
#include <iostream>
#include <vector>
using namespace std;

__interface Button
{
	void Press();
};
__interface Checkbox
{
	void Check();
};

class WinButton : public Button
{
private:
	string name = "Button";
public:
	WinButton() {}
	WinButton(string name) : name(name) {}
	void Press()
	{
		cout << "Winbutton " << name << " pressed." << endl;
	}
};
class MacButton : public Button
{
private:
	string name = "Button";
public:
	MacButton() {}
	MacButton(string name) : name(name) {}
	void Press()
	{
		cout << "Macbutton " << name << " pressed." << endl;
	}
};
class WinCheckbox : public Checkbox
{
private:
	bool checked = false;
	string name = "Checkbox";
public:
	void Check()
	{
		checked = !checked;
		cout << "Click. Wincheckbox " << name << " turned " << (checked ? "ON" : "OFF") << endl;
	}
	bool GetState()
	{
		return checked;
	}
};
class MacCheckbox : public Checkbox
{
private:
	bool checked = false;
	string name = "Checkbox";
public:
	void Check()
	{
		checked = !checked;
		cout << "Click. Maccheckbox " << name << " turned " << (checked ? "ON" : "OFF") << endl;
	}
	bool GetState()
	{
		return checked;
	}
};

__interface IGUIFactory
{
	Button* CreateButton();
	Checkbox* CreateCheckbox();
};

class WinFactory : public IGUIFactory
{
	Button* CreateButton()
	{
		return new WinButton();
	}
	Checkbox* CreateCheckbox()
	{
		return new WinCheckbox();
	}
};

class MacFactory : public IGUIFactory
{
	Button* CreateButton()
	{
		return new MacButton();
	}

	Checkbox* CreateCheckbox()
	{
		return new MacCheckbox();
	}
};

class Application
{
private:
	vector<Button> buttons;
	vector<Checkbox> checkboxes;
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
			factory = new WinFactory();
			break;
		case 2:
			factory = new MacFactory();
		}
	}
};