#include<bits\stdc++.h>
using namespace std;
string get_date(){
    time_t pres_time= time(0);
    tm *itm=localtime(&pres_time);
    char buffer[11];
    strftime(buffer,sizeof(buffer),"%d-%m-%Y",itm);

    return string(buffer);
}
class users{
    private:
    int user_choice;
    string role,current_id,current_username;
    public:
    void dash_board(){
    cout<<"--------Library Management System--------\n"<<endl;
    cout<<"[1] Login\n";
    cout<<"[2] New Registeration\n";
    cin>>user_choice;
    switch(user_choice){
        case 1:
            // login(role,current_id,current_username);
            break;
        case 2:
            reg_func();
            break;
        default:
            cout<<"Invalid choice";
    }
}
    bool reg_func(){
    ifstream user("user.txt");
    ifstream stud("student.txt");
    string line,username,password,dep,phone_no,userid,user_name,pass;
    int id=000,n;
    
    bool found= false;
    cout<<"Enter Username to register : ";
    cin>>username;
    cout<<"Set your Password : ";
    cin>>password;
    cout<<"Enter Department : ";
    cin>>dep;
    cout<<"Enter Phone_no : ";
    cin>>phone_no;
    while(getline(user,line)){
        stringstream ss(line);
        getline(ss,userid,'|');
        getline(ss,user_name,'|');
        getline(ss,pass,'|');

        if(username == user_name && pass == password){
            cout<<"username already registered please login..";
            found=true;
        }
       if (!userid.empty()) {
            try {
                id = stoi(userid); 
            } catch (...) {
                
            }
        }
    }

    ofstream nuser("user.txt",ios::app);
    ofstream nstud("student.txt",ios::app);

    if(!found){
            id+=1;
            cout<<endl;
            nuser<<id<<"|"<<username<<"|"<<password<<"|"<<"user"<<endl;
            nstud<<id<<"|"<<username<<"|"<<dep<<"|"<<phone_no<<endl;
            cout<<"Registered Succeessfully\n";

        }
    else{
        cout<<"something went wrong try again.....";
    }
   
    user.close();
    stud.close();
     return true;
}

bool login(string &role,string &current_id,string &current_username){
    string username,password;
    cout<<"Enter Username : ";
    cin>>username;
    cout<<"Enter Password : ";
    cin>>password;
    ifstream file("user.txt");
    if(!file) { cout << "user.txt missing!"; return false; }
    string line,fileuser,filepass,filerole,fileid;
    while(getline(file,line)){
        stringstream ss(line);
        getline(ss, fileid, '|');
        getline(ss, fileuser, '|');
        getline(ss, filepass, '|');
        getline(ss, filerole, '|');

        if(username == fileuser && password == filepass )
        {
            role = filerole;
            current_id = fileid;
            current_username= fileuser;
           return true;
        }
    }
    return false;
}
};
class admin{
    private:
        int book_id;
        string book_name;
        string author;
        int quantity;
    public:
        void dashboard_admin(){  
            int choice;

        while(true){
        cout<<"\n===== ADMIN DASHBOARD =====\n";
        cout<<"[1] Add Book\n";
        cout<<"[2] Delete Book\n";
        cout<<"[3] Search Book\n";
        cout<<"[4] View Books\n";
        cout<<"[5] View All Issued Books\n";
        cout<<"[6] Logout\n";
        cout<<"Enter choice: ";
        cin>>choice;
        
        switch(choice){
            case 1:
                add_books();
                break;

            case 2:
                del_Book();
                break;

            case 3:
                search_book();
                break;

            case 4:
                view_book();
                break;
            case 5:
                viewIssued_books();
                break;
            case 6:
                cout<<"Logging out...\n";
                return; 

            default:
                cout<<"Invalid choice!\n";
        }
    }
}
        
        void add_books(){
            ofstream Book("book.txt",ios::app);
            if(!Book){
                cout<<"file not found";
            }
            cout<<" Enter Book ID : ";
            cin>>book_id;   
            cin.ignore(); 

            cout<<"Enter Book Name : ";
            getline(cin,book_name);
            cout<<"Enter Author : ";
            getline(cin,author);
            cout<<"Enter Quantity : ";
            cin>>quantity;
            cin.ignore(); 
            Book<<book_id<<"|"<<book_name<<"|"<<author<<"|"<<quantity<<endl;
            Book.close();
            cout<<"\n Book Added Successfully";
            
        }
        void view_book(){
            ifstream Book("book.txt");
            if(!Book){
                cout<<"file not found";
            }
            string line;
            while(getline(Book,line)){
                cout<<line<<endl;
            }
            Book.close();
        }
        void del_Book(){
            ifstream Book("book.txt",ios::in);
            ofstream temp("temp.txt",ios::app);
            string line;
            bool found = false;
            string temp_bookid,id;
            cout<<"Enter Book ID to Delete : ";
            cin>>temp_bookid;
            cin.ignore();
             while(getline(Book,line)){
                stringstream ss(line);
                getline(ss,id,'|');
                if(id!= temp_bookid){
                    temp<<line<<endl;
                }
                else{
                    found = true;
                }
            }
            Book.close();
            temp.close();
            remove("book.txt");
            rename("temp.txt","book.txt");
            if(found){
                cout<<"Book Deleted";
        }
            else{
                cout<<"Book not found";
            }
        }
        void search_book(){
            bool found=false;
            string book_n,line,id,bookn,authorn,quantityn;
            fstream file("book.txt");
            if(!file){
            cout<<"Error opening file\n";
              return;
            }
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            cout<<"Enter Book Name to Search a Book : ";
            
            getline(cin,book_n);
            while(getline(file,line)){
                if (line.empty()) continue; 
                stringstream ss(line);
                getline(ss,id,'|');
                getline(ss,bookn,'|');
                getline(ss,authorn,'|');
                getline(ss,quantityn);
                if(bookn == book_n){
                    cout<<"book found\n";
                    cout<<"Bookid"<<" | Bookname"<<" | Author"<<" | Quantity"<<endl;
                    cout<<id<<"|"<<bookn<<"|"<<authorn<<"|"<<quantityn;
                    found = true;
                }
             }
             if(!found){
                cout<<"Invalid Book name....\n";
          }   
          file.close();   
        }
        void viewIssued_books(){
            ifstream file("iss_ret.txt");
            if (file.peek() == ifstream::traits_type::eof()) {
                cout << "No Book Issued yet!";
            }
            else{
            bool found = false;
            string line;
            while(getline(file,line)){
                stringstream ss(line);
                cout<<line<<endl;
                found = true;
            }
        }
            
        }
    };
class user{ //User Class
    public:
    void dashboard_user(string current_id,string current_username,string date){
            int choice;
        while(true){
        cout<<"\n===== USER DASHBOARD =====\n";
        cout<<"[1] Issue Book\n";
        cout<<"[2] Search Book\n";
        cout<<"[3] Return BOOK\n";
        cout<<"[4] My Isuued Books\n";
        cout<<"[5] Logout\n";
        cout<<"Enter choice: ";
        cin>>choice;
        switch(choice){
            case 1:
                issue_book(current_id,current_username,date);
                break;
            case 2:
                search_book();
                break;
            case 3:
                return_book(current_id,date);
                break;
            case 4:
                myissued_books(current_id)  ; 
                break; 
            case 5:
                cout<<"Logging out...\n";
                return; 
            default:
                cout<<"Invalid choice!\n";
        }
    }

    }
    void issue_book(string current_id,string current_username,string date){
    fstream file("book.txt");
    ofstream issue("issue.txt", ios::app);
    ofstream temp("temp.txt");
    ofstream issret("iss_ret.txt",ios::app);
    // ofstream isstemp("isstemp.txt");
    long long int isssec=time(0);
    string inputBookName,Author,qty;
    int new_qty;
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    cout<<"Enter Book name To Issue a BOOK: ";
    getline(cin, inputBookName);
    string line, bookID, bookName;
    bool found = false;
    while(getline(file, line)){
        stringstream ss(line);
        getline(ss, bookID, '|');   // book ID
        getline(ss, bookName, '|'); // book name
        getline(ss, Author, '|'); 
        getline(ss, qty);
        
        if(bookName == inputBookName){
            new_qty=stoi(qty);
            if(new_qty>0){
                new_qty--;
                cout<<endl;
            issue << current_id << "|" <<current_username<<"|"<<bookName<<"|"<< bookID<<"|"<<date<<"|"<<isssec<< endl;
            issret << current_id << "|" <<current_username<<"|"<<bookName<<"|"<< bookID<<"|"<<date<< endl;

            cout<<"Book Issued Successfully\n";
            found = true;
            temp<<bookID<<"|"<<bookName<<"|"<<Author<<"|"<<new_qty<<endl;
            
            }
            else{
                cout<<"Book is Not available this time, try again later";
                temp<<line<<endl;
                found = true;
            }
        }
        else{
            temp<<line<<endl;
        }
        
    }
    if(!found){
        cout<<"Invalid Book Name";
    }
    file.close();
    temp.close();
    remove("book.txt");
    rename("temp.txt","book.txt");
    remove("iss_ret.txt");
    rename("isstemp.txt","iss_ret.txt");
}
    void search_book(){
            bool found=false; 
            string book_name,line,id,bookn;
            ifstream file("book.txt");
            cout<<"Enter Book Name to Search a Book : ";
            getline(cin,book_name);
             while(getline(file,line)){
                stringstream ss(line);
                getline(ss,id,'|');
                getline(ss,bookn,'|');
                if(bookn == book_name){
                    cout<<line<<endl;
                    found=true;
                    break;
             }
        }
        if(!found){
            cout<<"Book Not found";
        }
    }
    void return_book(string current_id, string date) {
    ifstream file("issue.txt");
    ofstream temp("temp.txt");
    
    ifstream issret("iss_ret.txt");
    ofstream tempo("tempo.txt");

    long long int retsec = time(0);
    string bookname, line, ip_book, studentname, studentid, bookid, issdate, iss_sec;
    bool found = false;
    long long int isssec, current_sec, day;
    int limit = 2, fine = 0;
    string target_bookid = ""; 
    cout << "Enter Book Name to return a Book: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, ip_book);

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        getline(ss, studentid, '|');
        getline(ss, studentname, '|');
        getline(ss, bookname, '|');
        getline(ss, bookid, '|');
        getline(ss, issdate, '|');
        getline(ss, iss_sec);

        if (bookname == ip_book && current_id == studentid) {
            found = true;
            target_bookid = bookid; 
            
            isssec = stoll(iss_sec);
            current_sec = retsec - isssec;
            day = (current_sec) / 86400;

            if (day <= limit) {
                fine = 0;
                cout << "You have no fine yet. Thank You\n";
            } else {
                fine = (day - limit) * 5;
                cout << "You have " << fine << "rs yet. Thank You\n";
            }
            cout << "Book Has Been Returned Successfully\n";
        } else {
            temp << line << endl;
        }
    }
    file.close();
    temp.close();

    if (found) {
        remove("issue.txt");
        rename("temp.txt", "issue.txt");

        string h_line, h_sid, h_sname, h_bname, h_bid, h_idate;
        while (getline(issret, h_line)) {
            if (h_line.empty()) continue;
            stringstream ss2(h_line);
            getline(ss2, h_sid, '|');
            getline(ss2, h_sname, '|');
            getline(ss2, h_bname, '|');
            getline(ss2, h_bid, '|');
            getline(ss2, h_idate, '|');

            if (h_sid == current_id && h_bid == target_bookid) {
                tempo << h_sid << "|" << h_sname << "|" << h_bname << "|" << h_bid << "|" << h_idate << "|" << date << "|" << fine << endl;
            } else {
                tempo << h_line << endl;
            }
        }
        issret.close();
        tempo.close();
        remove("iss_ret.txt");
        rename("tempo.txt", "iss_ret.txt");

        
        ifstream bfile("book.txt");
        ofstream btemp("btemp.txt");
        string bline, bid, bname, bauth, bqty;

        while (getline(bfile, bline)) {
            if (bline.empty()) continue;
            stringstream bss(bline);
            getline(bss, bid, '|');
            getline(bss, bname, '|');
            getline(bss, bauth, '|');
            getline(bss, bqty);

            if (bid == target_bookid) { 
                int q = stoi(bqty) + 1; 
                btemp << bid << "|" << bname << "|" << bauth << "|" << q << endl;
            } else {
                btemp << bline << endl;
            }
        }
        bfile.close();
        btemp.close();
        remove("book.txt");
        rename("btemp.txt", "book.txt");

    } else {
        
        issret.close();
        tempo.close();
        remove("tempo.txt");
        cout << "Invalid book name or you haven't issued this book!\n";
        remove("temp.txt");
    }
}
        
        void myissued_books(string current_id){
            ifstream file("iss_ret.txt");
            bool found=false;
            string line,id,name,bookname,bookid;
            while(getline(file,line)){
                stringstream ss(line);
                getline(ss,id,'|');
                getline(ss,name,'|');
                getline(ss,bookname,'|');
                getline(ss,bookid,'|');
                if(current_id==id){
                    cout<<id<<"|"<<bookname<<"|"<<bookid<<endl;
                    found=true;
                }
            }
            if(!found){
                cout<<"No Books Issued Yet";
            }
            file.close();
        }
};


int main(){
    string role,current_id,current_username;
    users a;
    string date = get_date();
    a.dash_board();
    if(a.login(role,current_id,current_username)){
        cout<<"Login Successful\n";
        if(role=="admin"){
            cout<<"Welcome Admin";
            //system("start_admin_dashboard.html");
            admin A;
            A.dashboard_admin();
            
            
        }

        else{
            cout<<"Welcome User";
            //system("start_user_dashboard.html");
            user U;
            U.dashboard_user(current_id,current_username,date);
        }
    }
    else{
        cout<<"invalid username or password";
    }
    
    return 0;
}