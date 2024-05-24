#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
int i=0,j=0;
void open_account();
void deposit_money();
void withdraw_money();
void display_account();
void history_account();
struct Account {
    char  name[30];
    char address[50];
    string acc_type;
    string account_no;
    int pin ;
    float account_balance;
    float sending;
    float recive;
};

Account account_detail;



void open_account() {
    ofstream outputFile("file.txt", std::ios::app);
    if (outputFile.is_open()) {
        cout << "\n\n\n\n";
        cout << "\t**** WELCOME! FILL ALL DETAILS CAREFULLY ****\n";
        cout << "\n\tEnter The Account Holder Name: ";
        cin>>account_detail.name;
        fflush(stdin);
        cout << "\n\tEnter The CNIC Number (Your Account Number): ";
        cin >> account_detail.account_no;
        cout << "\n\tEnter your address: ";
        cin>>account_detail.address ;
        fflush(stdin);
        cout << "\n\tEnter Your Four Digits  PIN: ";
        cin >> account_detail.pin;
        fflush(stdin);
        cout << "\n\tEnter The Type of account you want to open (Saving or Current): ";
        cin >> account_detail.acc_type;
        do{
        	cout << "\n\tEnter the initial balance you want to deposit: ";
        cin >> account_detail.account_balance;
        if(account_detail.account_balance<0)
             cout<<"Invalid amount try again\n";
		}while(account_detail.account_balance <0);
        
        
        	
		
       
        outputFile << account_detail.name << " " << account_detail.account_no << " "
                   << account_detail.address << " " << account_detail.pin << " "
                   << account_detail.acc_type << " " << account_detail.account_balance <<
				   "\n";
        cout << "\n\tYou have created a Saving Account successfully.\n";
    
    } else {
        cout << "\n\tFailed to open the file.\n";
    }
}


void options(){
  int ch;
   system("cls");
            do {
                cout << std::endl;
                cout << "\n\t\t\n\t\t      $$   W E L C O M E   T O   Y O U R   A C C O U N T   $$\n";
                cout << "\n\n\t\t    MAIN    MENU\n";
                cout << "\t\t\t1. DEPOSIT AMOUNT\n";
                cout << "\t\t\t2. WITHDRAW AMOUNT\n";
                cout << "\t\t\t3. display account\n";
                cout << "\t\t\t4. History account\n";
                
                cout << "\t\t\t5. EXIT\n";
                cout << "\t\t\tSelect Your Option (1-5): ";
                cin >> ch;
                cout << endl;

                switch (ch) {
                    case 1:
                        deposit_money();
                        break;
                    case 2:
                        withdraw_money();
                        break;
                    case 3:
                        display_account();
                        break;
                         case 4:
					    history_account(); 
					     break;
                    case 5:
                        cout << "\n\t\tThank You for using World Bank.\n";
                        break;
                    default:
                        cout << "\n\tInvalid option.\n";
                        
           
                }
            } while (ch != 5);
            
        

            
   
}




void sign_up() {
    string acc_no;
    int pass_pin, flag = 0;

    cout << "\n\t\tEnter your account number: ";
    cin >> acc_no;
    cout << "\n\t\tEnter your 4-digit PIN code: ";
    cin >> pass_pin;

   ifstream Fileinput("file.txt");
   if (Fileinput.is_open()) {
    bool accountFound = false;
    while (Fileinput >> account_detail.name >> account_detail.account_no >> account_detail.address
           >> account_detail.pin >> account_detail.acc_type >> account_detail.account_balance) {
        cout << account_detail.name <<"  "<< account_detail.account_no<<" "<<endl;
		if (account_detail.account_no == acc_no) {
            accountFound = true; 
            break;
        }
    }
    Fileinput.close();

    if (accountFound) {
        if (account_detail.pin == pass_pin) {
            cout << "\n\t\tYou have been successfully signed in.\n";
            options();
        } else {
            cout << "\n\t\tIncorrect PIN.\n";
        }
    }
	else {
        cout << "\n\t\tAccount not found.\n";
    }
} else {
    cout << "\n\tFailed to open the file.\n";
}
    system("cls");

}
    

void deposit_money() {
    float deposit;
    
system("cls");
    cout << "\n\t\t\t**** W E L C O M E !   D E P O S I T   M O N E Y ****\n";
    
    fstream Fileinput("file.txt", std::ios::in | std::ios::out);
    if (Fileinput.is_open()) {
         do{
         	  cout << "\n\tEnter amount for deposit: ";
            cin >> deposit;
            if(deposit<0)
            cout<<"Invalid amount renter\n";
		 }while(deposit<0);
               
       
            
            account_detail.account_balance += deposit;
            ofstream outputFile("file.txt", std::ios::app);
            
            fstream filehistory("filehistory.txt", std::ios::app );
            Fileinput.seekp(-(sizeof(account_detail)), std::ios::cur);
            Fileinput << account_detail.name << " " << account_detail.account_no << " "
                       << account_detail.address << " " << account_detail.pin << " "
                       << account_detail.acc_type << " " << account_detail.account_balance <<" "
					   << "\n";
            cout << "\nYour Account Current Balance is: " << account_detail.account_balance << "\n";
      if(filehistory.is_open()){
      	filehistory<<account_detail.account_no<<" "<<deposit<<"\n";
	  }
	  filehistory.close();
        Fileinput.close(); 
}
  else
     cout << "\n\tFailed to open the file.\n";
}



void withdraw_money() {
    float withdraw;
    
system("cls");
    cout << "\n\t\t\t**** W E L C O M E !   W I T H D R A W     M O N E Y ****\n";
   
    fstream Fileinput("file.txt", std::ios::in | std::ios::out);
    fstream filehistory("filehistory.txt", std::ios::app );
    if (Fileinput.is_open()) {
     
            cout << "\n\tEnter amount for withdrawal: ";
            cin >> withdraw;
            if (withdraw <= account_detail.account_balance) {
                account_detail.account_balance -= withdraw;
                withdraw=0-withdraw;
                  
                  
                Fileinput.seekp(-(sizeof(account_detail)), std::ios::cur);
                Fileinput << account_detail.name << " " << account_detail.account_no << " "
                           << account_detail.address << " " << account_detail.pin << " "
                           << account_detail.acc_type << " " << account_detail.account_balance << " "
						   <<"\n";
                cout << "\nYour  Account  Current Balance is: " << account_detail.account_balance << "\n";
                if(filehistory.is_open()){
      	filehistory<<account_detail.account_no<<" "<<withdraw<<"\n";
	  }
	  filehistory.close();
            } else {
                cout << "\nInsufficient balance."<<account_detail.account_balance<<"\n";
            }
        } 
          else {
        cout << "\n\tFailed to open the file.\n";
        
    } 
        Fileinput.close();
    
}

void display_account() {
    
	ifstream Fileinput("file.txt");
    if (Fileinput.is_open()) {
        
            cout <<setw(15)<< "\n\tName: "<<setw(23) << account_detail.name << std::endl;
            cout <<setw(15)<< "\n\tAddress: "<<setw(22) << account_detail.address << std::endl;
            cout << setw(15)<<"\n\tPIN: "<<setw(23) << account_detail.pin << std::endl;
            cout << setw(15)<<"\n\tAccount Type: " <<setw(16)<< account_detail.acc_type << std::endl;
            cout << setw(15)<<"\n\tAvailable Balance: "<<setw(8) << account_detail.account_balance << std::endl;
         
       

            
        }
        else {
        cout << "\n\tFailed to open the file.\n";
    }
        Fileinput.close();
    } 


void history_account(){
	system("cls");
 	string acc_num;
 	float deposite;
 	   cout<<"\n\t\t****A C C O U N T   H I S T O R Y****\n";
 	ifstream filehistory;
	 filehistory.open("filehistory.txt", std::ios::in | std::ios::out);
 	if(filehistory.is_open()){
    while(filehistory >> acc_num >> deposite){
    	filehistory>>acc_num>>deposite;
    	if(account_detail.account_no==acc_num)
    	{             
    		if(deposite >0)
    				cout<<"\n\tAmount deposite\t"<<" "<<"  Rs. "<<deposite<<"\n";
    				
			
			else 
			   	cout<<"\n\tAmount withdraw\t"<<"  "<<" Rs. "<<deposite<<"\n";

    
    		cout<<endl;
		}
    	
    	
	}	
	 }
 	else 
 	    cout<<"File can't open\n";
 	
 		ifstream Fileinput;
	 Fileinput.open("file.txt", std::ios::in | std::ios::out);
 	if(Fileinput.is_open()){
 		cout<<"\n\tAccount Current Balannce : Rs. "<<account_detail.account_balance<<"\n";
 	}
 	  else {
        cout << "\n\tFailed to open the file.\n";
    }
        Fileinput.close();
 	
 }



int main() {
    int ch;
   
system("cls");
    do{
	
    cout << "\n\t\t\n\t\t      $$   W E L C O M E   T O   W O R L D   B A N K   $$\n";
    cout << "\n\n\t\t\t            ***# MAIN MENU #***\n";
    cout << "\n\t\t\tPress 1. SIGN IN\n";
    cout << "\t\t\tPress 2. NEW ACCOUNT\n";

    
    cout << "\t\t\tEnter Your Choice (1-2): ";
    cin >> ch;
    cout << endl;
    switch (ch) {
        case 1:
            sign_up();
            break;
        case 2:
            open_account();
            break;
     default:
                        cout << "\n\tInvalid option.\t"<<"  "<<" Try Again";
      
     } 
	 }while(ch !=2);
       system("cls");   	

  
    return 0;

}
