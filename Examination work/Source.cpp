#include <iostream>
#include <chrono>

using namespace std;

class Meal {
private:
	static int count;
protected:
	string name;
	int price;	
public:
	Meal() { count++; this->price = (rand() % 500) + 1; this->name = "Something dish #" + to_string(count); }
	Meal operator+(const Meal&);
	Meal operator++(int);
	istream& operator<<(istream&);
	friend ostream& operator<<(ostream&, const Meal&);
	void Show() { cout << this->name << " " << this->price << endl; }
	~Meal() { this->count--; }
};

class ReadyMeal : public Meal {
private:
	int cooking_time;
	bool active_menu;
public:
	ReadyMeal() :Meal() { this->cooking_time = (rand() % 180) + 1; this->active_menu = true; }
	bool operator<(const ReadyMeal&);
	istream& operator<<(istream&);
	friend ostream& operator<<(ostream&, const ReadyMeal&);
};

class SemiFinProduct : public Meal {
private:
	chrono::year_month_day condition_life;
	int weight;
	string storage_conditions;
public:
	SemiFinProduct() :Meal() { this->condition_life = chrono::year(2024 + (rand() % 4)) / chrono::month(1 + (rand() % 12)) / chrono::day(1 + (rand() % 28)); this->weight = rand() % 100 + 1; this->storage_conditions = "Something about storage the prouct"; }
	bool operator==(const SemiFinProduct&) const;
};

int Meal::count = 0;

Meal Meal::operator+(const Meal& obj) {
	
	this->price += obj.price;
	return *this;
}

Meal Meal::operator++(int notused) {

	this->price++;
	return *this;
}

bool ReadyMeal::operator<(const ReadyMeal& obj) {

	if (this->cooking_time < obj.cooking_time) { cout << this->name << " is quicklest" << endl; return true; }
	else { cout << obj.name << " is quicklest" << endl; return false; }
}

bool SemiFinProduct::operator==(const SemiFinProduct& obj) const {

	if (this->condition_life == obj.condition_life) cout << "Condition life is equal" << endl;
	else return false;
	if (this->weight == obj.weight) cout << "Weight is equal" << endl;
	else return false;
	if (this->storage_conditions == obj.storage_conditions) cout << "Storage conditions is equal" << endl;
	else return false;

	return true;
}

istream& Meal::operator<<(istream& is) {

	cout << "Enter name of meal: "; is >> this->name;
	cout << "Enter price: "; is >> this->price;
	return is;
}

ostream& operator<<(ostream& os, const Meal& obj) {

	os << obj.name << " " << obj.price << '$' << endl;
	return os;
}

istream& ReadyMeal::operator<<(istream& is) {

	cout << "Enter name of meal: "; is >> this->name;
	cout << "Enter price: "; is >> this->price;
	cout << "Time cooking: "; is >> this->cooking_time;
	cout << "Active menu 1/0 : "; is >> this->active_menu;
	return is;
}

ostream& operator<<(ostream& os, const ReadyMeal& obj) {

	os << obj.name << " " << obj.price << '$' << endl;
	os << obj.cooking_time << " ";
	if (obj.active_menu) cout << "isActive" << endl;
	else cout << "NonActive" << endl;
	return os;
}

int main() {
	srand(time(0));

	Meal m;
	ReadyMeal r1, r2;
	SemiFinProduct s1, s2;

	if (r1 < r2) cout << "r1 < r2" << endl;
	cout << "___________________________" << endl;
	if (s1 == s2) cout << "s1 equal s2" << endl;
	else cout << "s1 not equal s2" << endl;
	cout << "___________________________" << endl;
	r1.Show();
	r1++;
	r1.Show();
	cout << "___________________________" << endl;
	m << cin;
	cout << "___________________________" << endl;
	cout << m;
	cout << "___________________________" << endl;
	r1 << cin;
	cout << "___________________________" << endl;
	cout << r1;

	return 0;
}