// The app to manage the library 
// It should be able to let student borrow, return and search that particular book.
#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>
#include<conio.h>
#define CLRSCR system("cls");
using namespace std;

// The classes of that are needed 

class Book {
    char bookname[100];
    char authorname[50];
    int borrowed;

    public:


    void create_book(){
        bool flag = true;
        while(flag){
            fflush(stdin);
            cout<<"\n What is the name of the book?";
            gets(bookname);
            cout<<"\n Do you want to confirm the book's name? (y/n)";
            char q;
            cin>>q;
            if (q == 'y'){
                fflush(stdin);
                cout<<"\n Now, enter the author name.";
                gets(authorname);
                cout<<"\n\n Book created!!";
                borrowed = 0;
                flag = false;
            }
        }
    }



    void show_book_details(){
        cout<<"\nbook name is ";
        puts(bookname);
        cout<<"author name is "<<authorname<<"||";
        
        if (borrowed==true){
            cout<<"\tnot available right now.";

        }
    
        else{
            cout<<"\tavailable.";
        }
        

    }



    void resetBorrowed(){
        borrowed = 0;
    }

    char* return_bname(){
        return bookname;
    }
    void addBorrowed(){
        borrowed=1;
    }
    bool return_borrowed(){
            return borrowed;
        }
    
};//end of Book class




class Student{


        char studentId[6];
        char studentName[100];
        int borrowed;
        char borrowedbook[100];
        public:

        void create_student(){char q;
            CLRSCR;
            cout<<"\n There is the id";
            borrowed = false;
            cin>>studentId;
            bool flag = true;
            while(flag){
            cout<<"\n What is the name of the student?";
            fflush(stdin);
            gets(studentName);
            borrowedbook[0] = '\0';
            cout<<"\n Do you want to confirm the student's name? (y/n)";
            cin>>q;
            
            if (q == 'y'){
                
                
                cout<<"\nCreated a student";
                
                flag = false;
            }
            
            }
    }

        void showStudentInformation(){
            cout<<"\n The name of the student is:";
            puts(studentName);
            cout<<"\n The student's id is:"<<studentId;
            cout<<"\n"<<borrowed;
            cout<<"\n"<<borrowedbook;
        }

        void resetBorrowed(){
            if(borrowed==1){
                borrowed = 0;
            }
            
        }
        char* show_bookName(){
            return borrowedbook;
        }
        void add_book(char bn[]){
            strcpy(borrowedbook, bn);


        }
        bool return_borrowed(){
            return borrowed;
        }

        char* return_stno(){
            return studentId;
        }


        int addBorrowed(){
            borrowed = 1;
            return borrowed;
        }
};//end of the book class


//functions to read and write from the file 

fstream fw;
fstream fp;
Book book;
Student student;




void make_book_record(){
    fw.open("book.dat", ios::out|ios::app);
    char ch;
    do{
        CLRSCR;

        book.create_book(); //to make the new record
        fw.write((char*)&book, sizeof(Book));
        cout<<"\n\nDo you want to add more record--(y/n)";
        cin>>ch;
    }while(ch=='y'|ch=='Y');
    fw.close();
    
}
//to read specific book information

void book_information(char s[]){
    CLRSCR;
    int flag=0;
    fp.open("book.dat", ios::in);
    cout<<"\n BOOK RECORD";
    while(fp.read((char*)&book, sizeof(book))){
        
        
        if(strcmp(book.return_bname(),s)==0)
        {
            
            book.show_book_details();
            flag=1;
        }
    }
    fp.close();
    if(flag==0){
        cout<<"\n Book record not found";
    
    }
    getch();
}


//to create new student record

void write_student(){
    char ch;
    fw.open("student.dat", ios::out|ios::app);
    do{
        CLRSCR;
        student.create_student();
        fw.write((char*)&student,sizeof(Student));
        cout<<"\n\nDo you want to add more record of the student--(y\n)?";
        cin>>ch;

    }while(ch=='y'|ch=='Y');
    fw.close();
}

void student_read_file(char s[]){
    CLRSCR;
    int flag=0;
    fp.open("student.dat", ios::in);
    cout<<"\nSTUDENT RECORD";
    while(fp.read((char*)&student, sizeof(Student))){
        
        
        if(strcmp(student.return_stno(),s)==0)
        {
            
            student.showStudentInformation();
            flag=1;
        }
    }
    fp.close();
    if(flag==0){
        cout<<"\n Student record not found";
    
    }
    getch();
}

//list  all the records of the students

void studentl_list(){
    CLRSCR;
    int flag=0;
    fp.open("student.dat", ios::in);
    cout<<"\nSTUDENT RECORD";
    while(fp.read((char*)&student, sizeof(Student))){
        student.showStudentInformation();
        cout<<"\n";
        flag=1;
        
    }
    fp.close();
    if(flag==0){
        cout<<"\n No students in the file";
    
    }
    getch();
}



//list  all the records of the books

void books_list(){
    CLRSCR;
    int flag=0;
    fp.open("book.dat", ios::in);
    cout<<"\n\tBOOK RECORD";
    while(fp.read((char*)&book, sizeof(book))){
        book.show_book_details();
        cout<<"\n";
        flag=1;
        
    }
    fp.close();
    if(flag==0){
        cout<<"\n No books in the file";
    
    }
    getch();
}

//borrow book by the student

void borrow(){
    CLRSCR;
    int found=0, flag=0;
    char id[6], bn[100];
    cout<<"Write the id of the student--";
    cin>>id;
    fp.open("student.dat", ios::out|ios::in);
        fw.open("book.dat", ios::out|ios::in);
        while(fp.read((char*)&student,sizeof(Student) ) && found==0){
            
                if (strcmp(student.return_stno(), id)==0){
                    found=1;
                    if(student.return_borrowed()==0){
                        cout<<"\n \n Enter the book name.";
                        cin>>bn;
                        while(fw.read((char*)&book, sizeof(Book)) && flag==0){
                            
                            if(strcmp(book.return_bname(),bn )==0){
                                
                                
                                
                                if(book.return_borrowed()==0){
                                book.show_book_details();
                                flag=1;
                                bool now = student.addBorrowed();
                                book.addBorrowed();
                                
                                student.add_book(bn);
                                int pos = -1* sizeof(student);
                                int pos1 = -1* sizeof(book);
                                fw.seekp(pos1, ios::cur);
                                fp.seekp(pos, ios::cur);
                                fp.write((char*)&student, sizeof(Student));
                                fw.write((char*)&book, sizeof(Book));

                                cout<<"Book can be borrowed now- record made!";                       
                                }
                                else{
                                    cout<<"Book not available right now!";
                                    flag = 1;
                                }



                            }
                        }
                        if (flag==0){
                            cout<<"Book does not exist";
                        
                        }
                    
                    }
                    else{
                            cout<<"\n You have not returned the book";

                        }
                }
            
        }
        if(found==0){
            cout<<"\nThe record does not exist...";
        }

    fp.close();
    fw.close();
    getch();  

}



void return_book(){
    CLRSCR;
    int found=0, flag=0;
    char id[6], bn[100];
    cout<<"Write the id of the student--";
    cin>>id;
    fp.open("student.dat", ios::out|ios::in);
        fw.open("book.dat", ios::out|ios::in);
        while(fp.read((char*)&student, sizeof(Student)) && found==0){
                

                if(strcmp(student.return_stno(),id)==0){
                    found=1;
                        
                        
                        
                       
                        while(fw.read((char*)&book, sizeof(Book)) && flag==0){
                            
                            cout<<student.show_bookName()<<"\n"<<"he"<<book.return_bname()<<"he"<<"\n";
                            
                            if(strcmp(book.return_bname(), student.show_bookName())==0){
                                flag=1;
                                student.resetBorrowed();
                                int pos = -1*sizeof(Student);
                                fp.seekp(pos, ios::cur);
                                fp.write((char*)&student, sizeof(Student));
                        
                                book.resetBorrowed();
                                int pos1 = -1 * sizeof(Book);
                                fw.seekp(pos1, ios::cur);
                                fw.write((char*)&book, sizeof(Book));
                                cout<<"Returned book successfully";
                            }
                        
                        
                        
                        }
                    




                }





        }
    fp.close();
    fw.close();
    getch();
}


int main(){
    char bor[10]={'a','b','c','d','e','f','g','h','i','j'};
    cout<<bor;
    cout<<"What do you want to do??";
    cout<<"\n1. Create Book";
    cout<<"\n2. create Student record";
    cout<<"\n3. Look at student record";
    cout<<"\n4. List all the students records";
    cout<<"\n5.Look at book record";
    cout<<"\n6. List all books";
    cout<<"\n7. Borrow a book ";
    cout<<"\n8. Return a book";
    int q;
    char bname[100];
    char st[6];
    cin>>q;
    if(q==2){
        write_student();
    }
    else if (q==1){
        make_book_record();

    }
    else if(q==3){
        cout<<"\n Enter the id of the student--";
        cin>>st;
        student_read_file(st);
    }
    else if(q==4){
        studentl_list();
    }
    else if(q==5){
        cout<<"\nEnter the book name--";
        cin>>bname;
        book_information(bname);
    }
    else if(q==6){
        books_list();
    }
    else if(q==7){
        borrow();
    }
    else if(q=8){
        return_book();
    }

    return 0;
}