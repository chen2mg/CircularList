#include<iostream>
#include "CircularList.hpp"
using namespace std;


int main(){
	
	
	CircularList<int> mylist = CircularList<int>();
	
	for (int i = 0; i < 10; i++){
		mylist.emplace_back(i);
	}

	
	system("pause");
	return 0;
}
