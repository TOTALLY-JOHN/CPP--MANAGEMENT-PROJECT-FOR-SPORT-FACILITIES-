#include <iostream>
#include <set>
#include <iterator>
#include <map>
#include <fstream>
#include <string>
#include <cstdlib>
#include <queue>

using namespace std;

/*template <typename T, typename U>
void print_set(multiset<T, U>& s)
{
	for (const auto& elem : s)
	{
		cout << elem << endl;
	}
}*/

class SportFacility
{


private:
	int id;
	string desc;
	int capacity;
	string indicator;
	int duration;
	string startTime;
	double rentalFee;

public:
	SportFacility()
	{
		id = 0;
		desc = "";
		capacity = 0;
		indicator = "EMPTY";
		duration = 0;
		startTime = "";
		rentalFee = 0.0;
	}
	SportFacility(int id, string desc, int capacity, string indicator, int duration, string startTime, double rentalFee) : id(id), desc(desc), capacity(capacity), indicator(indicator), duration(duration), startTime(startTime), rentalFee(rentalFee) {}
	void setAll(int id, string desc, int capacity, string indicator, int duration, string startTime, double rentalFee)
	{
		this->id = id;
		this->desc = desc;
		this->capacity = capacity;
		this->indicator = indicator;
		this->duration = duration;
		this->startTime = startTime;
		this->rentalFee = rentalFee;
	}



	int getId() const
	{
		return id;
	}
	string getDesc() const
	{
		return desc;
	}
	int getCapacity() const
	{
		return capacity;
	}
	string getIndicator() const
	{
		return indicator;
	}
	int getDuration() const
	{
		return duration;
	}
	string getStartTime() const
	{
		return startTime;
	}
	double getRentalFee() const
	{
		return rentalFee;
	}
	bool operator<(const SportFacility& sf) const
	{
		if (desc.compare(sf.desc) < 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	friend ostream& operator<<(ostream& os, const SportFacility& sf);

};
ostream& operator<<(ostream& os, const SportFacility& sf)
{
	os << "FACILITY INFORMATION" << endl << "FACILITY ID : " << sf.id << endl << "FACILITY DESCRIPTION : " << sf.desc << endl << "FACILITY INDICATOR : " << sf.indicator << endl << "FACILITY DURATION : " << sf.duration << " hours" << endl << "FACILITY START TIME : " << sf.startTime << endl << "FACILITY RENTAL FEE : " << sf.rentalFee << endl << endl;
	return os;
}

class Member
{
private:
	string name;
	int id;

public:
	Member()
	{
		name = "";
		id = 0;
	}
	Member(string name, int id) : name(name), id(id) {}
	void setAll(string name, int id)
	{
		this->name = name;
		this->id = id;
	}
	string getName()
	{
		return name;
	}
	int getId()
	{
		return id;
	}
	friend ostream& operator<<(ostream& os, const Member& m);
};
ostream& operator<<(ostream& os, const Member& m)
{
	os << "MEMBER INFORMATION" << endl << "MEMBER NAME : " << m.name << endl << "MEMBER ID : " << m.id << endl << endl;
	return os;
}
struct compareId
{
	//using is_transparent = void;

	bool operator()(SportFacility const& sf1, SportFacility const& sf2) const
	{
		return sf1.getId() < sf2.getId();
	}
	bool operator()(int id, SportFacility const& sf) const
	{
		return id < sf.getId();
	}
	bool operator()(SportFacility const& sf, int id) const
	{
		return sf.getId() < id;
	}
};

int main()
{
	multiset<SportFacility, compareId> sfList;
	queue<Member> memberQueue;
	map<Member, int> bookingMap;
	int input;

	sfList.insert(SportFacility(1000, "BEDMINTON COURT", 30, "EMPTY", 12, "08:00 AM", 150.25));
	sfList.insert(SportFacility(1001, "FUTSAL COURT", 30, "EMPTY", 12, "08:00 AM", 150.25));
	sfList.insert(SportFacility(1002, "SWIMMING POOL", 100, "EMPTY", 14, "06:00 AM", 50.5));

	cout << "DISPLAY MULTISET " << endl;
	//print_set(sfList);

	do
	{
		cout << "Choose a menu, please." << endl;
		cout << "1) MEMBER ARRIVAL" << endl;
		cout << "2) BOOKING OF SPORT FACILITY" << endl;
		cout << "3) LEAVING THE SPORT FACILITY" << endl;
		cout << "4) DISPLAY ALL SPORT FACILITIES" << endl;
		cout << "5) EXIT THE PROGRAM" << endl;
		cout << "> ";
		cin >> input;

		switch (input)
		{
		case 1: // MEMBER ARRIVAL
		{
			// INPUT MEMBER'S INFORMATION
			string memberName;
			int memberId;
			cout << "Input a member name : ";
			cin >> memberName;
			cout << "Input a member ID : ";
			cin >> memberId;

			// CREATE A MEMBER OBJECT
			Member member(memberName, memberId);

			// PUSH IT INTO THE QUEUE
			memberQueue.push(member);
			break;
		}

		case 2: // BOOKING OF SPORT FACILITY
		{
			int searchValue;
			cout << "Input a sport facility ID : ";
			cin >> searchValue;

			// SEARCH FOR THE SPORT FACILITY RECORD ACCORDING TO USER INPUT
			// CHECK WHETHER THIS FACILITY IS OCCUPIED OR NOT
			// IF IT IS EMPTY, THE INDICATOR IS CHANGED INTO 'OCCUPIED'
			
			if (sfList.find(searchValue)->getIndicator().compare("EMPTY") == 0)
			{
				int id = sfList.find(searchValue)->getId();
				string desc = sfList.find(searchValue)->getDesc();
				int capacity = sfList.find(searchValue)->getCapacity();
				int duration = sfList.find(searchValue)->getDuration();
				string startTime = sfList.find(searchValue)->getStartTime();
				double rentalFee = sfList.find(searchValue)->getRentalFee();
				sfList.erase(sfList.find(searchValue));
				sfList.insert(SportFacility(id, desc, capacity, "OCCUPIED", duration, startTime, rentalFee));

				// AND REMOVE THE MEMBER FROM THE QUEUE AND ADD A NEW BOOKING RECORD TO MAP
				memberQueue.pop();
				bookingMap.insert(make_pair(memberQueue.front(), id));
				cout << "BOOKING COMPLETE." << endl;
			}
			else
			{
				cout << "DATA IS NOT FOUND OR OCCUPIED" << endl;
			}
			break;
		}

		case 3: // LEAVING THE SPORT FACILITY
		{
			int searchValue;
			string memberName;
			int memberId;

			cout << "Input a sport facility ID : ";
			cin >> searchValue;
			cout << "Input a member name : ";
			cin >> memberName;
			cout << "Input a member ID : ";
			cin >> memberId;


			if (sfList.find(searchValue)->getIndicator().compare("OCCUPIED") == 0)
			{
				int id = sfList.find(searchValue)->getId();
				string desc = sfList.find(searchValue)->getDesc();
				int capacity = sfList.find(searchValue)->getCapacity();
				int duration = sfList.find(searchValue)->getDuration();
				string startTime = sfList.find(searchValue)->getStartTime();
				double rentalFee = sfList.find(searchValue)->getRentalFee();
				sfList.erase(sfList.find(searchValue));
				sfList.insert(SportFacility(id, desc, capacity, "EMPTY", duration, startTime, rentalFee));

				// AND REMOVE THE MEMBER FROM THE QUEUE AND ADD A NEW BOOKING RECORD TO MAP
				bookingMap.erase(bookingMap.find(Member(memberName, memberId)));
				
				memberQueue.pop();
				bookingMap.insert(make_pair(memberQueue.front(), id));
				cout << "BOOKING COMPLETE." << endl;
			}
			else
			{
				cout << "DATA IS NOT FOUND OR OCCUPIED" << endl;
			}
			break;
		}

		case 4: // DISPLAY ALL SPORT FACILITIES
		{
			print_set(sfList);
			break;
		}

		case 5: // EXIT THE PROGRAM
		{
			cout << "Thank you for using our program. End the program." << endl;
			break;
		}

		default: // VALIDATE THE USER INPUT
		{
			cout << "Your input is wrong!" << endl;
		}
		}
	} while (input != 5);
	return 0;
}
