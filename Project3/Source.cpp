#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <memory>
using namespace std;

class base
{
public:
	static int people_on_base;
	static int vehicles_on_base;
	static double petrol_on_base;
	static double goods_on_base;
	static void showstatus()
	{
		cout << "=========current state of the database=========\n\n" << endl;
		cout << "people on base: " << people_on_base << endl;
		cout << "the machinery: " << vehicles_on_base << endl;
		cout << "the black oil: " << petrol_on_base << "litres..." << endl;
		cout << "the max weight wich urals (military machines) can get up: " << goods_on_base << "kilos..." << endl;
	}
};
int base::people_on_base = 50;
int base::vehicles_on_base = 9;
double base::petrol_on_base = 2341.0;
double base::goods_on_base = 125.5;
////////////////////////////////////////////////////////
class vehicle
{
protected:
	double petrol_amount;
	double tank_volume;
public:
	vehicle(double p, double t) : petrol_amount(p), tank_volume(t) {}
	double gettankvolume()
	{
		return tank_volume;
	}
	double getpetrolamount()
	{
		return petrol_amount;
	}
	virtual void arrive()
	{
		base::vehicles_on_base++;
	}
	virtual void leave()
	{
		return true;
	}
};
class bus : public vehicle
{
	int people;
	int max_people;
	double petrol;
	double max_petrol;
public:
	bus(int p, int max_p, double pet, double max_pet) : vehicle(pet, max_pet), people(p), max_people(max_p) {}
	int getpeoplecount()
	{
		return people;
	}
	int getmaxpeople()
	{
		return max_people;
	}
	void arrive() //приезд 
	{
		vehicle::arrive();
		base::people_on_base += people;
		people = 0;
	}
	bool leave() //выезд
	{
		double needed_petrol = tank_volume - petrol_amount;
		if (base::petrol_on_base < needed_petrol)
		{
			return false;
		}
		int needed_people = max_people - 1;
		if (base::people_on_base < needed_people)
		{
			people = base::people_on_base;
			base::people_on_base = 0;
		}
		else
		{
			people = needed_people;
			base::people_on_base -= needed_people;
		}
		base::petrol_on_base -= needed_petrol;
		petrol_amount = tank_volume;
		base::vehicles_on_base--;
		return true;
	}
};
class truck : vehicle
{
	double load;
	double max_load;
public:
	truck(double l, double max_l, double pet, double max_pet) : vehicle(pet, max_pet), load(l), max_load(max_l) {}
	int getcurrentload()
	{
		return load;
	}
	int getmaxload()
	{
		return max_load;
	}
	void arrive()
	{
		vehicle::arrive();
		base::people_on_base += load;
		load = 0;
	}
	bool leave()
	{
		double needed_petrol = tank_volume - petrol_amount;
		if (base::petrol_on_base < needed_petrol)
		{
			return false;
		}
		if (base::goods_on_base < max_load)
		{
			load = base::people_on_base;
			base::people_on_base = 0;
		}
		else
		{
			load = max_load;
			base::goods_on_base -= max_load;
		}
		base::petrol_on_base -= needed_petrol;
		petrol_amount = tank_volume;
		base::vehicles_on_base--;
		return true;
	}
};
int main()
{
	setlocale(lc_all, "russian");
	base::showstatus();
	bus bus(15, 30, 20.0, 100.0);
	bus.arrive();
	cout << "після приїзду автобуса:\n";
	base::showstatus();
	if (bus.leave())
	{
		cout << "автобус успішно покинув базу!\n";
	}
	else
	{
		cout << "автобус не зміг виїхати!\n";
	}
	base::showstatus();
	return 0;
}