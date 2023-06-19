#include <iostream>
#include <thread>
#include <random>
#include <mutex>
using namespace std;

mutex m;
int table;
int flag = 0;


class Master{
public:
	int id;
	Master(int i){
		id = i;
	}
	void delay(){
		cout << "Dungeon Master put " << id << endl;
	}

	void check(){
		const lock_guard<mutex> lock(m);
		if (id+table==6 && flag == 1){

			flag = 0;
			delay();
		}
	}
};

class Creature{
public:

	int give(){
		int table1, table2;
		srand(time(NULL));
		table1 = rand() % 3 + 1;
		table2 = rand() % 3 + 1;
		if (table1 == table2){
			table1 = (table1 + 1)%3;
			if (table1 == 0) table1+=1;
		}

		return table1+table2;
	}
};

int main(){

	vector<thread> vec;
	Creature C;
	table = C.give();
	std::cout << "Creature put " << table << endl;

	flag = 1;

	vec.push_back(std::thread([](){
		Master M1(1);
		while(true)
			M1.check();
	}));

	vec.push_back(std::thread([](){
		Master M2(2);
		while(true)
			M2.check();
	}));

	vec.push_back(std::thread([](){
		Master M3(3);
		while(true)
			M3.check();
	}));

	this_thread::sleep_for(1000ms);

	for(int i = 1; true; i++)
	{	
		table = C.give();
		std::cout << "Creature put " << table << endl;
		flag = 1;		
		this_thread::sleep_for(1000ms);	
	}

	for(int i =0; i < 3; i++)
		vec[i].join();

	return 0;
}