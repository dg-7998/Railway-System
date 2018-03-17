// Railway Ticket Reservation System
#include<iostream>
#include<algorithm>
#include<string.h>
#include<cmath>
#include<fstream>
#include<vector>
using namespace std;
#define for(i,a,b) for(int i=a;i<b;i++)
char filename[]="/home/nikmul19/Desktop/extra.txt";
class Train;
class User
{
	
	public:
        char source[20],destination[20],date[20];
		void getdata()
		{
            //--------------------take the user input query--------------------------
			cout<<"Enter Source Station: ";
			cin>>source;
			cout<<"Enter Destination Station: ";
			cin>>destination;
			cout<<"Enter Date: ";
			cin>>date;
		}
        friend void matchTrains(User);
};

class Train
{
    
    public:
        char train_name[20],arr_t[10],source[20],dest[20],dep_t[10];
        int train_no,fare[6],availability[6],c_cat[6];
    
    void getdata()
    {
        int i;
        Train t;
        cout<<"--------------------------------enter data--------------------------------\n";
        cin.ignore(1);                   //ignores the newline character stored in the stream
        cout<<"enter train_name:";  
        cin.getline(train_name,20);

        cout<<"enter arrival time:";
        cin.getline(arr_t,10);
        cout<<"enter departure time:";
        cin.getline(dep_t,10);

        cout<<"enter source:";
        cin.getline(source,20);
        cout<<"enter dest:";
        cin.getline(dest,20);
        cout<<"enter categories:";
        //-----------------------------enter categories as 0 for NOT THERE and 1 for THERE---------------------------
        for(i,0,6)cin>>c_cat[i];
        cout<<"enter train no:"; cin>>train_no;
        //cin.ignore(1);
        cout<<"enter availability:";
        //-----------------------------Set availability to -999 if no such category----------------------------------
        for(i,0,6)if(c_cat[i]==0)availability[i]=-999;
        //-----------------------------Check again and if class is there take input from admin------------------------    
        for(i,0,6)if(availability[i]!=-999)cin>>availability[i];
        cout<<"enter fares:"; 
        for(i,0,6)cin>>fare[i];
    }

    void insert()
    {
        int n,i;
        cout<<"\n----------------enter number of trains to be inserted-------------------\n";
        cin>>n;
        fstream f1;
        f1.open(filename,ios::app|ios::binary);
        Train t[n];
        for(i,0,n)
            {
                t[i].getdata();
                f1.write((char *)&t[i],sizeof(t[i]));
            }
        f1.close();
    }
    
    void putdata()
    {
        cout<<train_no<<" "<<train_name<<" "<<arr_t<<" "<<dep_t<<" "<<c_cat<< " ";
        for(i,0,6)cout<<fare[i]<<" ";
        cout<<endl;
        cout<<"--------------------------------------------------\n";

    }
    
    friend void matchTrains(User);
    

};
void matchTrains(User query)
    {
        int count=0,waiting=0,index,category,passengers,choice;
        fstream f1;
        f1.open(filename,ios::in|ios::binary);
        Train tr;
        vector<Train> t;   //-----------------vector of trains matching user choice--------------------------
        char ch;
        while(f1.read((char *)&tr,sizeof(tr)))
            {
                if(strcmp(tr.source,query.source)==0 && strcmp(tr.dest,query.destination)==0 )
                {
                    count++;
                    //--------------------displays only those trains with matching source and destination-----------------------
                    t.push_back(tr);
                    cout<<count<<". ";
                    tr.putdata();
                    cout<<endl;
                }
            }

        if(count>0)
        {
            cout<<"Enter number of passengers";
            cin>>passengers;
            while(1)
            {
                cout<<"Select the index of train (Ex:1,2,3):";
                cin>>index;
                
                for(i,0,6)cout<<t[index-1].availability[i]<<" ";

                cout<<"\n Enter category 1)SL 2)CC 3)1A 4)2A 5)3A 6)2S";
                cin>>category;
                cout<<"Do you want to book in this train? (1.YES 2.NO) :";
                cin>>choice;
                if(choice==0)continue;
                //----------------------------book the tickets and display the status (WL OR CNF)-------------------------------------
                if(passengers>t[index-1].availability[category-1])
                    {
                        waiting=passengers-t[index-1].availability[category-1];
                    }   
                t[index-1].availability[category-1]-=passengers;
                cout<<"waiting: "<<waiting<<" Confirmed:"<<t[index-1].availability[category-1];
            }
        }
        else
        {
            cout<<"\nSorry no trains matching your query"<<endl;
        }
        f1.close();
        
    }
int main()
{
	User U;
    U.getdata();
    Train t;
    t.insert();
	return 0;
}
