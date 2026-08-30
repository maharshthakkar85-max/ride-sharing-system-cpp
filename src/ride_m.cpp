#include <iostream>
#include<vector>
#include<fstream>

using namespace std;

class user
{
    protected:
    string name;
    string city;

public:
    user()
    {
        name = "Unkown";
        city = "Unkown";
        // cout<<"h"<<endl;
    }
    void getData()
    {
        cout << "Enter the Name: ";
        cin >> name;
        cout << "Enter the City: ";
        cin >> city;
    }

    string return_name()
    {
        return name;
    }

    string return_city()
    {
        return city;
    }
    

    virtual void display()
    {
        cout << "\nName : " << name << "  City: " << city << endl;
    }

    friend class ride;
};













class rider : public user
{
    protected:
    string pickup;
    string drop;
    string preferredVehicle;

public:
    rider()
    {
        pickup = "Not set";
        drop = "Not set";
    }

    void set_pickup_drop()
    {
        cout << "Enter the pick up point: ";
        cin >> pickup;
        cout << "Enter the drop point: ";
        cin >> drop;
    }

    void chooseVehicle()
    {
        int choice;

        cout << "\nChoose Vehicle:\n";
        cout << "1. Car\n";
        cout << "2. Bike\n";
        cout << "3. SUV\n";
        cout << "4.Auto\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            preferredVehicle = "Car";
            break;

        case 2:
            preferredVehicle = "Bike";
            break;

        case 3:
            preferredVehicle = "Suv";
            break;
        case 4:
            preferredVehicle = "Auto";
            break;

        default:
            preferredVehicle = "Auto";
        }
    }

   string get_vehicalType()
    {
       return preferredVehicle;
    }
  
    string return_pickup()
    {
        return pickup;
    } 

    string return_drop()
    {
        return drop;
    }

    void request_ride()
    {
        cout << "Ride requested  from " << pickup << " to " << drop << endl;
    }

    void display()
    {
        user::display();
        cout << "Pick_up: " << pickup << "  Drop: " << drop << endl;
    }
    friend class ride;
};













class driver : public user
{
    protected:
    string license_num;
    string vehicalType;
    int rating;
    bool available;

public:
    driver()
    {
        license_num = "NONE";
        vehicalType = "Auto";
        rating = 5;
        available = true;
    }

    void add_details()
    {
        cout<<"Write lince_num: ";
        cin>>license_num;
        
        int choice;

        cout << "\nChoose Vehicle:\n";
        cout << "1. Car\n";
        cout << "2. Bike\n";
        cout << "3. Suv\n";
        cout << "4.Auto\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
               vehicalType = "Car";
            break;

        case 2:
               vehicalType = "Bike";
            break;

        case 3:
             vehicalType = "SUV";
            break;
        case 4:
            vehicalType = "Auto";
            break;

        default:
             vehicalType = "Auto";
        }    
    }

    bool is_Available()
    {
        return available;
    }

    string get_vehicalType()
    {
       return vehicalType;
    }

    string return_license()
    {
        return license_num;
    }

    void acceptRide()
    {  
        available=false;
        cout<<"Driver has accpect the ride"<<endl;
      
    }

    void display()
    {
        user::display();
        
        cout<<"License Number : "<<license_num<<endl;
        cout<<"vehicle : "<<vehicalType<<endl;
        cout<<"Rating : "<<rating<<endl;
    }
    friend class ride;
};








class FareCalculator
{
public:
    float calculate(string vehicle, float distance)
    {
        float rate;

        if(vehicle == "Bike") rate = 8;
        else if(vehicle == "Auto") rate = 10;
        else if(vehicle == "Car") rate = 15;
        else rate = 20;

        return 25 + (distance * rate);
    }
};







class ride  {

 rider r;
 vector<driver> d;
 bool ride_Status;
 int assign_index;
float fare;
 
  public:



    


   ride(rider r1)
   {
    r=r1;
     ride_Status=false;

    driver temp;
    try{
    ifstream fin("driver.txt");
    // Read from file
    if(!fin)
    throw runtime_error ("Driver.txt file is not exist ");

     while(fin >> temp.name >> temp.city >>temp.license_num>>temp.vehicalType >> temp.available)
     {
        d.push_back(temp);
     }
     
     if(d.size()==0)
     throw runtime_error("NO drivers available!");
  
    fin.close(); 
   
   }
   catch(const runtime_error &e)
{
   cout<<"Exception occur: "<<e.what()<<endl;   
}
 
   
        
    }

    void notification()
    {
        cout<<endl;
        cout<<"======== RIDE CONFORMED ========= "<<endl;

        cout<<"\nNotification to Rider: "<<endl;
        cout<<"Driver: "<<d[assign_index].return_name()<<endl;
        cout<<"License: "<<d[assign_index].return_license()<<endl;
        cout<<"Vehicle: "<<d[assign_index].get_vehicalType()<<endl;
        cout<<"Fare is : "<<fare<<endl;
        
        

        cout<<"\nNotification for Driver: "<<endl;
        cout<<"Rider Name: "<<r.return_name()<<endl;
        cout<<"Rider Pick_up Point: "<<r.return_pickup()<<endl;
        cout<<"Rider Drop Point: "<<r.return_drop()<<endl;

   
         bool is_Empty;
        ifstream fin("ride.txt");
        if(fin.peek()==EOF)
         is_Empty=1;
         else
         is_Empty=0;

         fin.close();


         ofstream fout("ride.txt",ios::app);
         if(is_Empty)
        {
          fout<<"Rider_Name"<<"\t"<<"Driver_Name"<<"\t"<<"Pick-UP"<<"\t"<<"Drop-Point"<<"\t"<<"Vechicle"<<"\t"<<"Fare"<<endl;
          fout<<"- - - - - - - - -  - - - -  - -  - -  - - -  - - -  - - -  - - - - - - - - - - - - -- -  - -- -  -- - - - - -  -"<<endl;
        }
                
         fout<<r.name<<"\t\t"<<d[assign_index].name<<"\t\t"<<"\t"<<r.pickup<<"\t"<<r.drop<<"\t\t"<<d[assign_index].vehicalType<<"\t\t"<<fare<<"\t"<<endl;
    
      fout.close();

    }
   
   void assignRide()
   {
      if(d.size()==0)
      return;
      
        
     for(int i=0;i<d.size();i++)
     {
      if(r.return_city()==d[i].return_city() && d[i].is_Available() && r.get_vehicalType()==d[i].get_vehicalType())
      {
         d[i].acceptRide();
         ride_Status=true;
         assign_index=i;
            
         float distance;
         cout<<"ENTER THE DISTANCE IN KM: ";
         cin>>distance;
         FareCalculator f1;
         fare=f1.calculate(r.get_vehicalType(),distance);

          notification();
         break;
      }
      
    } 
    if(!ride_Status)
      cout<<"Ride is not conformied"<<endl;
   }
};



















int main()
{
    bool is_EMPTY;
     rider r1;

    
     cout<<"\nEnter The details of Rider: \n";
    r1.getData();
    r1.set_pickup_drop();
    r1.chooseVehicle();

    
     ifstream fin("rider.txt");
   // check for file is empty or no
    if(fin.peek()==EOF )
    is_EMPTY=1;
    else
    is_EMPTY=0;

    fin.close();

   ofstream fout("rider.txt",ios::app);
     if(is_EMPTY)
       {
     fout<<"Name\t"<<"City\t"<<"Pick_Up\t"<<"Drop\t"<<"vechicle\t"<<endl;
     fout<<"- - - - - - - - - -  - - - - - - - - - - - - - - - - - - -  - -  - -  - -  - - - - - - - - - - - "<<endl;
       } 
     fout<<r1.return_name()<<"\t\t"<<r1.return_city()<<"\t\t"<<r1.return_pickup()<<"\t\t"<<r1.return_drop()<<"\t\t"<<r1.get_vehicalType()<<"\t\t"<<endl;
       
   
    

    // for(int i = 0; i < 5; i++)
    // {
    //     cout << "\nEnter details for Driver " << i+1 << endl;
    //     drivers[i].getData();
    //     drivers[i].add_details();
    // }

    ride ride1(r1);
    ride1.assignRide();
    return 0;
}
