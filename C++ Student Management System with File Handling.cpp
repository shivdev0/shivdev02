#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

class Student{
public:
int roll;
char name[50];
float marks;

void input(){
cout<<"Enter Roll No: ";
cin>>roll;
cout<<"Enter Name: ";
cin>>name;
cout<<"Enter Marks: ";
cin>>marks;
}

void show(){
cout<<"Roll No: "<<roll<<"\n";
cout<<"Name: "<<name<<"\n";
cout<<"Marks: "<<marks<<"\n";
cout<<"----------------------\n";
}
};

void addStudent(){
Student s;
ofstream file("students.dat",ios::binary|ios::app);
s.input();
file.write((char*)&s,sizeof(s));
file.close();
}

void showAll(){
Student s;
ifstream file("students.dat",ios::binary);
while(file.read((char*)&s,sizeof(s))){
s.show();
}
file.close();
}

void searchStudent(){
Student s;
int roll;
cout<<"Enter Roll No to Search: ";
cin>>roll;
ifstream file("students.dat",ios::binary);
bool found=false;
while(file.read((char*)&s,sizeof(s))){
if(s.roll==roll){
s.show();
found=true;
}
}
file.close();
if(!found)cout<<"Record not found\n";
}

void deleteStudent(){
Student s;
int roll;
cout<<"Enter Roll No to Delete: ";
cin>>roll;

ifstream in("students.dat",ios::binary);
ofstream out("temp.dat",ios::binary);

while(in.read((char*)&s,sizeof(s))){
if(s.roll!=roll){
out.write((char*)&s,sizeof(s));
}
}

in.close();
out.close();
remove("students.dat");
rename("temp.dat","students.dat");

cout<<"Record Deleted\n";
}

void updateStudent(){
Student s;
int roll;
cout<<"Enter Roll No to Update: ";
cin>>roll;

fstream file("students.dat",ios::binary|ios::in|ios::out);
bool found=false;

while(file.read((char*)&s,sizeof(s))){
if(s.roll==roll){
cout<<"Enter New Details:\n";
s.input();
int pos=-1*sizeof(s);
file.seekp(pos,ios::cur);
file.write((char*)&s,sizeof(s));
found=true;
break;
}
}

file.close();

if(!found)cout<<"Record not found\n";
}

int main(){
int choice;

while(true){
cout<<"\n1.Add Student\n2.Show All\n3.Search\n4.Delete\n5.Update\n6.Exit\n";
cout<<"Enter choice: ";
cin>>choice;

switch(choice){
case 1:addStudent();break;
case 2:showAll();break;
case 3:searchStudent();break;
case 4:deleteStudent();break;
case 5:updateStudent();break;
case 6:return 0;
default:cout<<"Invalid choice\n";
}
}
}
