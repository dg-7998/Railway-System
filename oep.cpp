// Railway Ticket Reservation System
#include<iostream>
#include<algorithm>
#include<string.h>
#include<cmath>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;
#define for(i,a,b) for(i=a;i<b;i++)
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
        int train_no,c_cat[6],fare[6],availability[6];

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
        cout<<"enter source:";
        cin.getline(source,20);
        cout<<"enter dest:";
        cin.getline(dest,20);
        cout<<"enter departure time:";
        cin.getline(dep_t,10);
        cout<<"enter train no:"; cin>>train_no;

        //-----------------------------enter categories as 0 for NOT THERE and 1 for THERE---------------------------

        //cin.ignore(1);
        cout<<"enter categories:";
        for(i,0,6)cin>>c_cat[i];

        cout<<"enter fares:";
        for(i,0,6)if(c_cat[i]==1)cin>>fare[i]; else continue;

        cout<<"enter availability:";
        //-----------------------------Set availability to -999 if no such category----------------------------------
        for(i,0,6)if(c_cat[i]==0)availability[i]=-999; else availability[i]=0;
        //-----------------------------Check again and if class is there take input from admin------------------------
        for(i,0,6)if(availability[i]!=-999)cin>>availability[i];
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
       // printFile();
    }

    void printFile()
    {
        Train t;
        fstream f1;
        f1.open(filename,ios::in|ios::binary);
        while(f1.read((char *)&t,sizeof(t)))
        {
            f1.read((char *)&t,sizeof(t));
            t.putdata();
        }
        f1.close();
    }

    void putdata()
    {
        int i;
        cout<<"Train Name: "<<"\e[1m"<<train_name<<"\e[0m"<<endl;
        cout<<"Arrival Time: "<<"\e[1m"<<arr_t<<"\e[0m"<<endl;
        cout<<"Departure Time: "<<"\e[1m"<<dep_t<<"\e[0m"<<endl;
        cout<<"Source Station: "<<"\e[1m"<<source<<"\e[0m"<<endl;
        cout<<"Destination Station: "<<"\e[1m"<<dest<<"\e[0m"<<endl;
        cout<<"Train No: "<<"\e[1m"<<train_no<<"\e[0m"<<endl;
        cout<<"Fares: ";
        for(i,0,6)cout<<"\e[1m"<<fare[i]<<"\e[0m"<<" ";
        cout<<endl;
        cout<<"Seat Availabity: ";
        for(i,0,6)cout<<"\e[1m"<<availability[i]<<"\e[0m"<<" ";
        cout<<endl;
        cout<<"Categories: ";
        for(i,0,6)cout<<"\e[1m"<<c_cat[i]<<"\e[0m"<<" ";
        cout<<endl;
        cout<<"--------------------------------------------------\n";
    }

    void update(Train match)
    {
        int n,i;
        fstream f1;
        Train obj; 
        f1.open(filename,ios::out|ios::binary);
        while(f1.read((char *)&obj,sizeof(obj)))
        {
            if(obj.train_no==match.train_no)
                {
                    f1.write((char*)&(match),sizeof(obj));
                }

        }
        
        f1.close();
    }
    
    friend void matchTrains(User);
};

void matchTrains(User query)
    {
        int count=0,waiting=0,position,index,category,passengers,choice,i;
        vector <int> Indexes;
        fstream f1;
        f1.open(filename,ios::in|ios::binary|ios::out);
        Train tr;
        vector<Train> matching;   //-----------------vector of trains matching user choice--------------------------
        vector<Train> allTrains;
        char ch;
        while(f1.read((char *)&tr,sizeof(tr)))
            {
                allTrains.push_back(tr);//-----------------data of all 
                i++;
                if(strcmp(tr.source,query.source)==0 && strcmp(tr.dest,query.destination)==0)
                {
                    count++;
                    Indexes.push_back(i);  //-------------indexes of trains matching-------------------------------------------
                    //--------------------displays only those trains with matching source and destination-----------------------
                    matching.push_back(tr);
                    cout<<count<<". "<<endl;
                    tr.putdata();
                    cout<<endl;
                }
            }
        f1.seekg(0),f1.seekp(0);

        if(count>0)
        {
            cout<<"Enter number of passengers: ";
            cin>>passengers;
            while(1)
            {
                cout<<"Select the index of train (Ex:1,2,3): ";
                cin>>index;
                for(i,0,6)cout<<matching[index-1].availability[i]<<" ";

                cout<<"\nEnter category 1)SL 2)CC 3)1A 4)2A 5)3A 6)2S: ";
                cin>>category;
                cout<<"Do you want to book in this train? (1.YES 2.NO): ";
                cin>>choice;
                if(choice==0)continue;
                //----------------------------book the tickets and display the status (WL OR CNF)-------------------------------------
                if(passengers>matching[index-1].availability[category-1])
                    {
                        waiting=passengers-matching[index-1].availability[category-1];
                    }
                matching[index-1].availability[category-1]-=passengers;
                cout<<"waiting: "<<waiting<<endl<<"Confirmed.Ticket Booked"<<endl;
                
                tr.update(matching[index-1]); //-----------updates the file-----------------
                break;
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
    //t.insert();
    //t.printFile();
    matchTrains(U);
    return 0;
}
