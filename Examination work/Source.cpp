#include <iostream>
#include <chrono>

using namespace std;

class ParticCompetition {
protected:
	string name;
	static int count;
public:
	ParticCompetition() { this->count++; this->name = "Somebody Partic of Competition #" + to_string(count); }
	ParticCompetition(string name) { this->count++; this->name = name; }
	void print() { cout << this->name << endl; }
	bool operator==(const ParticCompetition&) const;
	istream& operator<<(istream&);
	friend ostream& operator<<(ostream&, const ParticCompetition&);
	~ParticCompetition() { this->count--; }
};

int ParticCompetition::count = 0;

class FootballTeam : public ParticCompetition {
private:
	int score_goal;
	int seq_number;
	string result;
public: 
	FootballTeam() :ParticCompetition() { this->score_goal = rand() % 10; this->seq_number = rand() % 40 + 1; this->result = to_string(rand() % 10) + to_string(rand() % 10); }
	void print() { cout << "Name: " << this->name << " Score goals: " << this->score_goal << endl; }
	FootballTeam operator+= (const FootballTeam&);
	FootballTeam operator+= (const int&);
	FootballTeam operator++(int);
	bool operator<(const FootballTeam&);
};

class Athlete : public ParticCompetition {
private:
	chrono::seconds time;
	chrono::seconds leader_time;
	chrono::seconds lag_leader;
	int place;
public:
	Athlete() :ParticCompetition() { this->time = chrono::seconds(rand() % 160 + 10); this->leader_time = chrono::seconds(rand() % 160 + 10); this->lag_leader = this->leader_time - this->time; this->place = (rand() % 10) + 1; }
	void print() { cout << "Time: " << this->time << endl; }
	istream& operator<<(istream&);
	friend ostream& operator<<(ostream&, const Athlete&);
};

FootballTeam FootballTeam::operator++(int notused) {

	this->score_goal++;
	return *this;
}

FootballTeam FootballTeam::operator+=(const FootballTeam& obj) {

	this->score_goal += obj.score_goal;
	return *this;
}

FootballTeam FootballTeam::operator+=(const int& i) {

	this->score_goal += i;
	return *this;
}

bool FootballTeam::operator<(const FootballTeam& obj) {

	if (this->score_goal < obj.score_goal) return true;
	else return false;
}

bool ParticCompetition::operator==(const ParticCompetition& obj) const {

	if (this->name == obj.name) return true;
	else return false;
}

istream& ParticCompetition::operator<<(istream& is) {
	
	cout << "Enter name: "; is >> this->name;
	return is;
}

ostream& operator<<(ostream& os, const ParticCompetition& obj) {

	os << "Name: " << obj.name << endl;
	return os;
}

istream& Athlete::operator<<(istream& is) {

	int tmp = 0;
	cout << "Enter name: "; is >> this->name;
	cout << "Enter time of Athlete (sec): "; is >> tmp; this->time = chrono::seconds(tmp);
	cout << "Enter time of Leader (sec): "; is >> tmp; this->leader_time = chrono::seconds(tmp);
	this->lag_leader = this->leader_time - this->time;
	return is;
}

ostream& operator<<(ostream& os, const Athlete& obj) {

	os << "Name: " << obj.name << "Time: " << obj.time << "Leader time: " << obj.leader_time << "Lag: " << obj.lag_leader << endl;
	return os;
}



int main() {
	srand(time(0));

	FootballTeam f1, f2;
	Athlete a1, a2;
	
	cout << "f1: "; f1.print();
	cout << "f2: "; f2.print();
	cout << "_________" << endl;

	f1++;
	cout << "f1 (after f1++): "; f1.print();
	cout << "f2 (f2 += f1): "; f2 += f1; f2.print();
	cout << "f1 (f1 += 3): "; f1 += 3; f1.print();
	cout << "f1 < f2 (scores goal)? ";
	if (f1 < f2) cout << "Yes!" << endl;
	else cout << "False!" << endl;
	cout << "_________" << endl;

	cout << "a2: "; a2.print();
	a2 << cin;
	cout << a2;

	return 0;
}