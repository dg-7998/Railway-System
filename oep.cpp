// Railway Ticket Reservation System

#include<iostream>
#include<algorithm>
#include<string.h>
#include<cmath>

using namespace std;
class User
{
	char source[20],destination[20],date[20];
	public:
		void getdata()
		{
			cout<<"Enter Source Station: ";
			cin>>source;
			cout<<"Enter Destination Station: ";
			cin>>destination;
			cout<<"Enter Date: ";
			cin>>date;
		}	
};

class Train
{
	
};
int main()
{
	User U;
	U.getdata();
	return 0;
}
