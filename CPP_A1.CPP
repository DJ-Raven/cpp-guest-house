#include<fstream.h>
#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<stdlib.h>
// Mouse Function
void createmouse()
{
	_AX=0;
	geninterrupt(0x33);
}
void showmouse()
{
	_AX=1;
	geninterrupt(0x33);
}

void hidemouse()
{
	_AX=2;
	geninterrupt(0x33);
}

void allowmouse(int x1,int y1,int x2,int y2)
{
	_AX=7;
	_CX=x1;
	_DX=x2;
	geninterrupt(0x33);
	_AX=8;
	_CX=y1;
	_DX=y2;
	geninterrupt(0x33);
}
void getmouse(int *button,int *x,int *y)
{
	_AX=3;
	geninterrupt(0x33);
	*button=_BX;
	*x=_CX;
	*y=_DX;
}

void setmouse(int x,int y)
{
	_AX=4;
	_CX=x;
	_DX=y;
	geninterrupt(0x33);
}
int checkmouse(int mx,int my,int x,int y,int x1,int y1){
	x=x*8-9;
	x1*=8;
	y=y*8-9;
	y1*=8;
	if(mx>x&&mx<x1&&my>y&&my<y1)
		return 1;
	else
		return 0;
}
void pixtoxy(int &x,int &y){
	int i=0;
	int j=0;
	do{
		i++;
		j+=8;

	}while(j<=x);
	x=i;
	i=0;
	j=0;
	do{
		i++;
		j+=8;

	}while(j<=y);
	y=i;
}
void windowFull(){
	window(1,1,80,25);
}
int BG=1;
int TEXT=0;
void setBackground(int bg){
	windowFull();
	BG=bg;
	textbackground(BG);
	clrscr();
}
int getBackground(){
	return BG;
}
void setTextColor(int col){
	TEXT=col;
	textcolor(TEXT);
	clrscr();
}
int getTextColor(){
	return TEXT;
}
// Class to User
class Label{
	private:
		char text[80];
		int x;
		int y;
		int bgColor;
		int color;
	public:
		Label(){
			strcpy(text,"Label C++");
			bgColor=getBackground();
			color=getTextColor();
		}
		Label(int x,int y){
			this->x=x;
			this->y=y;
			bgColor=getBackground();
			color=getTextColor();
		}
		Label(int x,int y,char text[80]){
			hidemouse();
			this->x=x;
			this->y=y;
			bgColor=getBackground();
			color=getTextColor();
			strcpy(this->text,text);
			show();
			showmouse();
		}
		void setText(char text[80]){
			hide();
			strcpy(this->text,text);
			show();
		}
		void setBgColor(int bg){
			bgColor=bg;
			show();
		}
		void setColor(int col){
			color=col;
			show();
		}
		void setLocation(int x,int y){
			hide();
			this->x=x;
			this->y=y;
			show();
		}
		void hide(){
			int len=strlen(text);
			window(x,y,x+len,y);
			textbackground(getBackground());
			clrscr();
			windowFull();

		}
	private:
		void show(){
			windowFull();
			hidemouse();
			textbackground(bgColor);
			textcolor(color);
			gotoxy(x,y);
			cprintf("%s",text);
			showmouse();
		}

};
class TextField{
	protected:
		int x;
		int y;
		int width;
		int xx;
		int yy;
		int len;
		int bgColor;
		int textColor;
		int action;
		char text[50];
		long number;
	public:
		TextField(){
			text[0]='\0';
			bgColor=7;
			textColor=0;
			len=20;
			xx=1;
			yy=1;
			action=1;
			number=-123;
		}
		void setText(char txt[80]){
			strcpy(text,txt);
			show();
		}
		void setNumber(long number){
			this->number=number;
		}
		void setNumberNull(){
			number=-123;
		}
		int isNull(){
			if(number==-123){
				return 1;
			}else{
				return 0;
			}
		}
		long getNumber(){
			return number;
		}
		void setLocation(int x,int y,int width){
			this->x=x;
			this->y=y;
			this->len=width;
			this->width=width;
		}
		void setMaxText(int len){
			if(len>width||len<=1){
				len=width;
			}
			this->len=len;
		}
		void setBgColor(int col){
			this->bgColor=col;
		}
		void hide(){
			window(x,y,x+width,y);
			textbackground(getBackground());
			clrscr();
			windowFull();
		}
		void setEdit(){
			action=1;
		}
		void setNotEdit(){
			action=0;
		}
		void show(){
			hidemouse();
			window(x,y,x+width,y);
			textbackground(bgColor);
			clrscr();
			gotoxy(2,1);
			cout<<text;
			showmouse();
		}
		void showNumber(){
			hidemouse();
			window(x,y,x+width,y);
			textbackground(bgColor);
			clrscr();
			gotoxy(2,1);
			if(number==-123)
				cout<<"";
			else
				cout<<number;
			showmouse();
		}
		int input();
		void insertText(char,int);
		void deleteText(int);
		char* getText(){
		return text;
	}
};
int TextField::input(){
 if(action==0)
	return 0;
 window(x+1,y,x+width,y);
 textbackground(bgColor);
 textcolor(0);
 hidemouse();
 clrscr();
 cout<<text;
 showmouse();
 _setcursortype(2);
 int m=strlen(text);
 xx=m+1;
 gotoxy(xx,yy);
 char ch;
 int c,x,y;
 do{
	getmouse(&c,&x,&y);
	if(c==1)
		if(!checkmouse(x,y,this->x,this->y,this->x+width,this->y)){
			_setcursortype(0);
			break;
		}else{
			int l=strlen(text);
			int x1=x,y1=y;
			pixtoxy(x1,y1);
			x1=x1-this->x;
			if(x1==0){
				xx=1;
			}else if(x1<=l+1){
				xx=x1;
			}else{
				xx=l+1;
			}
			gotoxy(xx,yy);

		}
	if(kbhit()){
		ch=getch();
		if(ch==13||ch==9){
			_setcursortype(0);
			return 13;
		}
		if(ch==0){
			ch=getch();
			if(ch==75){
				if(xx!=1){
					xx--;
					gotoxy(xx,yy);
				}
			}else if(ch==77){
				 m=strlen(text);
				if(xx!=m+1){
					xx++;
					gotoxy(xx,yy);
				}

			}
		}else if(ch==8){
			if(xx!=1){
				hidemouse();
				deleteText(xx-2);
				window(x+1,y,x+len+1,y);
				clrscr();
				cout<<text;
				gotoxy(xx,yy);
				showmouse();
			}
		}else{
			m=strlen(text);
			if(m<len-1){
				hidemouse();
				insertText(ch,xx-1);
				xx++;
				window(x+1,y,x+len+1,y);
				clrscr();
				gotoxy(x+1,y);
				cout<<text;
				gotoxy(xx,yy);
				showmouse();
			}
		}
	}
	delay(10);
 }while(1);
	_setcursortype(0);
	return 0;
}
void TextField::insertText(char st,int index){
	int max=strlen(text);
	for(int i=max;i>=index;i--){
		text[i+1]=text[i];
	}
	text[index]=st;
}
void TextField::deleteText(int index){
	int max=strlen(text);
	for(int i=index;i<max;i++){
		text[i]=text[i+1];
	}
	xx--;
}
class PasswordField:public TextField{
	protected:
		char icon;
	public:
		PasswordField(){
			icon='*';
		}
		void setIcon(char ic){
			icon=ic;
		}
		int input();
};
int PasswordField::input(){
 if(action==0)
	return 0;
 window(x+1,y,x+width,y);
 textbackground(bgColor);
 textcolor(0);
 hidemouse();
 clrscr();
 int m=strlen(text);
 for(int i=0;i<m;i++){
	cout<<icon;
 }
 showmouse();
 _setcursortype(2);
 xx=m+1;
 gotoxy(xx,yy);
 char ch;
 int c,x,y;
 do{
	getmouse(&c,&x,&y);
	if(c==1)
		if(!checkmouse(x,y,this->x,this->y,this->x+width,this->y)){
			_setcursortype(0);
			break;
		}else{
			int l=strlen(text);
			int x1=x,y1=y;
			pixtoxy(x1,y1);
			x1=x1-this->x;
			if(x1==0){
				xx=1;
			}else if(x1<=l+1){
				xx=x1;
			}else{
				xx=l+1;
			}
			gotoxy(xx,yy);
		}
	if(kbhit()){
		ch=getch();
		if(ch==13||ch==9){
			_setcursortype(0);
			return 13;
		}
		if(ch==0){
			ch=getch();
			if(ch==75){
				if(xx!=1){
					xx--;
					gotoxy(xx,yy);
				}
			}else if(ch==77){
				 m=strlen(text);
				if(xx!=m+1){
					xx++;
					gotoxy(xx,yy);
				}
			}
		}else if(ch==8){
			if(xx!=1){
				hidemouse();
				deleteText(xx-2);
				window(x+1,y,x+len+1,y);
				clrscr();
				m=strlen(text);
				for(int i=0;i<m;i++){
					cout<<icon;
				 }
				gotoxy(xx,yy);
				showmouse();
			}
		}else{
			m=strlen(text);
			if(m<len-1){
				hidemouse();
				insertText(ch,xx-1);
				xx++;
				window(x+1,y,x+len+1,y);
				clrscr();
				gotoxy(x+1,y);
				for(int i=0;i<=m;i++){
					cout<<icon;
				}
				gotoxy(xx,yy);
				showmouse();
			}
		}
	}
	delay(10);
 }while(1);
	_setcursortype(0);
	return 0;
}
class Room{
	private:
		int roomNumber;
		int status;
	public:
		Room(){}
		Room(int roomNum,int status){
			roomNumber=roomNum;
			this->status=status;
		}
		void setRoomNumber(int room){
			roomNumber=room;
		}
		int getRoomNumber(){
			return roomNumber;
		}
		void setStatus(int s){
			status=s;
		}
		int getStatus(){
			return status;
		}
};
class Date{
	private:
		int day;
		int month;
		int year;
	public:
		Date(){}
		Date(int day,int month,int year){
			this->day=day;
			this->month=month;
			this->year=year;
		}
		void setDay(int day){
			this->day=day;
		}
		void setMonth(int month){
			this->month=month;
		}
		void setYear(int year){
			this->year=year;
		}
		int getDay(){
			return day;
		}
		int getMonth(){
			return month;
		}
		int getYear(){
			return year;
		}
};
class Data{
	private:
		int id;
		char name[20];
		Date dateIn;
		Date dateOut;
		int roomNumber;
		int totalDay;
		double price;
	public:
		Data(){}
		Data(int id,char name[],Date dateIn,Date dateOut,int roomNumber,int totalDay,double price){
		this->id=id;
		strcpy(this->name,name);
		this->dateIn=dateIn;
		this->dateOut=dateOut;
		this->roomNumber=roomNumber;
		this->totalDay=totalDay;
		this->price=price;
		}
		void outPut(){
			char type[10];
			if(roomNumber>400)
				strcpy(type,"VIP");
			else
				strcpy(type,"Simple");
			cout<<id<<"    "<<name<<"    "<<dateIn.getDay()<<"-"<<dateIn.getMonth()<<"-"<<dateIn.getYear()<<"    "<<dateOut.getDay()<<"-"<<dateOut.getMonth()<<"-"<<dateOut.getYear()<<"    "<<totalDay<<"    "<<type<<"    "<<roomNumber<<"    "<<price;
		}
		Date getDateIn(){
			return dateIn;
		}
		Date getDateOut(){
			return dateOut;
		}
		double getPrice(){
			return price;
		}
		int getTotalDay(){
			return totalDay;
		}
		int getId(){
			return id;
		}
		char* getName(){
			return name;
		}
		long getRoomNumber(){
			return roomNumber;
		}
};
// Prototype Funtion
int dayInMonth(int m);
int viewRoom(int &i1,int &i2,int &i3,int o,int out);
void setRoom();
void checkData();
void checkOut();
void report();
void viewPrice();
void viewDetail(int i1,int i2,int i3);
int calculatDay(int d_in,int m_in,int y_in,int d_out,int m_out,int y_out);
int convertDate(Date *obj,char date[]);
void logIn();
void showGroup();
void startApp();
void checkIn();
void box(int col,int x,int y,int x1,int y1);
Data data[100];
Room room[4][3][5];
int recode=-1;
void main(){
 ofstream outFile("mydata.txt",1);
 ofstream outFile1("myroom.txt",1);
 setBackground(1);
 _setcursortype(0);
 createmouse();
 showmouse();
 setRoom();
 checkData();
 showGroup();
 startApp();
 getch();
 hidemouse();
}
void checkData(){
 ifstream inFile("mydata.txt");
 ifstream inFile1("mydata.txt");
 char id[20],roomNumber[20],totalDay[5],dIn[5],mIn[5],yIn[5],dOut[5],mOut[5],yOut[5];
 char name[30];
 char price[10];
 Date dateIn,dateOut;
 int count=0;
 while(!inFile1.eof()){
	char ch;
	inFile1.get(ch);
	count++;
 }
 inFile1.close();
 if(count>1){
	while(!inFile.eof()){
		inFile.getline(id,100);
		inFile.getline(name,100);
		inFile.getline(roomNumber,100);
		inFile.getline(totalDay,100);
		inFile.getline(price,100);
		inFile.getline(dIn,100);
		inFile.getline(mIn,100);
		inFile.getline(yIn,100);
		inFile.getline(dOut,100);
		inFile.getline(mOut,100);
		inFile.getline(yOut,100);
		dateIn=Date(atoi(dIn),atoi(mIn),atoi(yIn));
		dateOut=Date(atoi(dOut),atoi(mOut),atoi(yOut));
		data[++recode]=Data(atoi(id),name,dateIn,dateOut,atoi(roomNumber),atoi(totalDay),atof(price));
	}
	recode--;
 }
 inFile.close();
}
void setDataInFile(){
 ofstream outFile("mydata.txt",1);
 int id,roomNumber,totalDay,dIn,mIn,yIn,dOut,mOut,yOut;
 char name[30];
 double price;
 Date dateIn,dateOut;
 for(int i=0;i<=recode;i++){
	id=data[i].getId();
	strcpy(name,data[i].getName());
	int roomNumber=data[i].getRoomNumber();
	int totalDay=data[i].getTotalDay();
	price=data[i].getPrice();
	dateIn=data[i].getDateIn();
	dateOut=data[i].getDateOut();
	dIn=dateIn.getDay();
	mIn=dateIn.getMonth();
	yIn=dateIn.getYear();
	dOut=dateOut.getDay();
	mOut=dateOut.getMonth();
	yOut=dateOut.getYear();
	outFile<<id<<"\n"<<name<<"\n"<<roomNumber<<"\n"<<totalDay<<"\n"<<price<<"\n"<<dIn<<"\n"<<mIn<<"\n"<<yIn<<"\n"<<dOut<<"\n"<<mOut<<"\n"<<yOut<<endl;
 }
 outFile.close();
}
void updateRoom(){
 ofstream outFile("myRoom.txt",1);
 int status;
 for(int j=0;j<4;j++){
	for(int k=0;k<3;k++){
		for(int l=0;l<5;l++){
			status=room[j][k][l].getStatus();
			outFile<<status<<endl;
		}
	}
 }
 outFile.close();
}
void setRoom(){
 int have=0;
 ifstream inRoom("myroom.txt");
 char ch;
 while(!inRoom.eof()){
	inRoom.get(ch);
	have++;
 }
 inRoom.close();
 if(have<5){
	for(int i=0;i<4;i++){
		int n=1;
		for(int j=0;j<3;j++){
			for(int k=0;k<5;k++){
				room[i][j][k]=Room(((i+1)*100)+n++,1);
			}
		}
	}
	ofstream outRoom("myroom.txt");
	int status;
	for(int j=0;j<4;j++){
		for(int k=0;k<3;k++){
			for(int l=0;l<5;l++){
				status=room[j][k][l].getStatus();
				outRoom<<status<<endl;
			}
		}
	 }
	 outRoom.close();
 }else{
	ifstream inRoom1("myroom.txt");
	char st[50];
	for(int i=0;i<4;i++){
		int n=1;
		for(int j=0;j<3;j++){
			for(int k=0;k<5;k++){
				inRoom1.getline(st,100);
				room[i][j][k]=Room(((i+1)*100)+n++,atoi(st));
			}
		}
	}
	inRoom1.close();
 }
}
void logIn(){
 box(3,20,10,60,20);
 box(5,20,10,60,10);
 textcolor(7);
 gotoxy(21,10);
 cprintf("LogIn");
 textbackground(4);
 gotoxy(58,10);
 cprintf(" X ");
 gotoxy(25,13);
 textbackground(3);
 textcolor(0);
 cprintf("User Name :");
 gotoxy(25,15);
 cprintf("Password  :");
 TextField txtUser;
 PasswordField txtPass;
 windowFull();
 Label cmdOk=Label(37,17," OK ");
 Label cmdCancel=Label(48,17," Cancel ");
 cmdOk.setBgColor(2);
 cmdCancel.setBgColor(2);
 txtUser.setLocation(37,13,18);
 txtPass.setLocation(37,15,18);

 txtUser.show();
 txtPass.show();
 int x,y,c;
 do{
	getmouse(&c,&x,&y);
	if(c==1){
		if(checkmouse(x,y,37,13,37+18,13)){
			inputUser:
			if(txtUser.input()==13){
				goto inputPass;
			}
		}else if(checkmouse(x,y,37,15,37+18,15)){
			inputPass:
			if(txtPass.input()==13){
				goto OK;
			}
		}else if(checkmouse(x,y,37,17,37+3,17)){
			cmdOk.setBgColor(1);
			delay(100);
			cmdOk.setBgColor(2);
			OK:
			char name[20];
			char pass[20];
			strcpy(name,txtUser.getText());
			strcpy(pass,txtPass.getText());
			int r;
			r=strcmp(name,"sm6");
			if(r==0){
				r=strcmp(pass,"setec");
				if(r==0){
					return;
				}else{
					txtPass.setText("");
					goto inputPass;
				}
			}else{
			txtUser.setText("");
			goto inputUser;
			}
		}else if(checkmouse(x,y,58,10,58+2,10)||checkmouse(x,y,48,17,48+7,17)){
			exit(0);
		}




	}// endl if click

 }while(1);
}
void box(int col,int x,int y,int x1,int y1){
 window(x,y,x1,y1);
 textbackground(col);
 hidemouse();
 clrscr();
 showmouse();
 windowFull();
}
void startApp(){             			//  Funtcion Start aPP
 setBackground(1);
 window(1,25,80,25);
 textbackground(7);
 clrscr();
 window(1,1,80,1);
 textbackground(7);
 clrscr();
 Label lb1=Label(3,1," Check IN ");
 Label lb2=Label(17,1," Check Out ");
 Label lb3=Label(32,1," Report ");
 Label lb4=Label(44,1," View Room ");
 Label cPrice=Label(59,1," Price ");
 Label logOut(70,1," LogOut ");
 lb1.setBgColor(7);
 lb2.setBgColor(7);
 lb3.setBgColor(7);
 lb4.setBgColor(7);
 cPrice.setBgColor(7);
 logOut.setBgColor(7);
 logOut.setColor(4);
 int x,y,c;
 logIn();
 box(1,10,5,70,23);
  do{
  getmouse(&c,&x,&y);
  if(c==1){
	if(checkmouse(x,y,3,1,3+9,1)){
		lb1.setBgColor(2);
		checkIn();
		lb1.setBgColor(7);
	}else if(checkmouse(x,y,17,1,17+11,1)){
		lb2.setBgColor(2);
		checkOut();
		lb2.setBgColor(7);
	}else if(checkmouse(x,y,32,1,32+7,1)){
		lb3.setBgColor(2);
		report();
		lb3.setBgColor(7);
	}else if(checkmouse(x,y,44,1,44+10,1)){
		int a1,a2,a3;
		lb4.setBgColor(2);
		viewRoom(a1,a2,a3,0,0);
		lb4.setBgColor(7);
	}else if(checkmouse(x,y,70,1,70+7,1)){
		box(1,1,2,80,24);
		logIn();
		box(1,1,2,80,24);
	}else if(checkmouse(x,y,59,1,59+6,1)&&recode!=-1){
		cPrice.setBgColor(2);
		viewPrice();
		cPrice.setBgColor(7);
	}

  }
  delay(5);
  }while(1);



}
void checkIn(){
	TextField txtId,txtName,txtDateIn,txtDateOut,txtRoom;
	int dateIn=0;
	struct date d;
	int i1,i2,i3;
	getdate(&d);
	int day=int(d.da_day);
	int mon=int(d.da_mon);
	int year=int(d.da_year);
	ag:
	box(3,10,5,70,5);
	box(6,10,6,70,22);
	gotoxy(68,5);
	textbackground(4);
	cprintf(" X ");
	gotoxy(11,5);
	textbackground(3);
	textcolor(0);
	cprintf("Check In Form");
	textbackground(6);
	gotoxy(15,9);
	cprintf("Id        :");
	gotoxy(15,11);
	cprintf("Name      :");
	gotoxy(15,13);
	cprintf("Date in   :");
	gotoxy(15,15);
	cprintf("Date out  :");
	gotoxy(15,17);
	cprintf("Room      :");
	gotoxy(28,13);
	Label cmdOk=Label(27,20," OK ");
	Label cmdCancel=Label(40,20," Cancel ");
	Label cmdFind=Label(42,17," Find ");
	cmdFind.setBgColor(5);
	cmdOk.setBgColor(2);
	cmdCancel.setBgColor(2);
	txtId.setLocation(27,9,20);
	txtName.setLocation(27,11,20);
	txtDateIn.setLocation(27,13,20);
	txtDateOut.setLocation(27,15,20);
	txtRoom.setLocation(27,17,10);
	txtId.show();
	txtName.show();
	txtDateIn.show();
	textbackground(7);
	cprintf("%d-%d-%d",day,mon,year);
	txtDateOut.show();
	txtRoom.showNumber();
	int x,y,c;
	do{
		getmouse(&c,&x,&y);
		if(c==1){
			if(checkmouse(x,y,27,9,27+20,9)){
				inputId:
				if(txtId.input()==13){
					goto inputName;
				}
			}else if(checkmouse(x,y,27,11,27+20,11)){
				inputName:
				if(txtName.input()==13){
					if(dateIn){
						goto inputDateIn;
					}else{
						goto inputDateOut;
					}
				}
			}else if(checkmouse(x,y,27,13,27+20,13)){
				if(dateIn){
					inputDateIn:
					if(txtDateIn.input()==13){
						goto inputDateOut;
					}
				}
			}else if(checkmouse(x,y,27,15,27+20,15)){
				inputDateOut:
				if(txtDateOut.input()==13){
					goto viewRoomAg;
				}
			}else if(checkmouse(x,y,42,17,42+5,17)){
				cmdFind.setBgColor(2);
				delay(100);
				cmdFind.setBgColor(5);
				viewRoomAg:
				if(viewRoom(i1,i2,i3,1,0)){
					windowFull();
					gotoxy(28,17);
					txtRoom.setNumber(room[i1][i2][i3].getRoomNumber());
					txtRoom.showNumber();
				}
				goto ag;
			}else if(checkmouse(x,y,68,5,70,5)){
				box(getBackground(),10,5,70,22);
				return;
			}else if(checkmouse(x,y,27,20,30,20)){
				cmdOk.setBgColor(1);
				delay(100);
				cmdOk.setBgColor(2);
				Ok:
				// set data
				int cc=strcmp(txtId.getText(),"");
				if(cc==0){
					goto inputId;
				}else{
					if(atoi(txtId.getText())<=0){
						txtId.setText("");
						cout<<txtId.getText();
						goto inputId;
					}else{
						cc=strcmp(txtName.getText(),"");
						if(cc==0){
							goto inputName;
						}else{

						}
					}
				}
				char name[20];
				int id=atoi(txtId.getText());
				for(int z=0;z<=recode;z++){
					if(id==data[z].getId()){
						goto inputId;
					}
				}
				strcpy(name,txtName.getText());
				Date dayIn=Date(day,mon,year);
				Date dayOut;
				if(!convertDate(&dayOut,txtDateOut.getText())){
					txtDateOut.setText("");
					goto inputDateOut;
				}
				if(year>dayOut.getYear()){
					txtDateOut.setText("");
					goto inputDateOut;
				}else if(year==dayOut.getYear()){
					if(mon>dayOut.getMonth()){
						txtDateOut.setText("");
						goto inputDateOut;
					}else if(mon==dayOut.getMonth()){
						if(day>dayOut.getDay()){
							txtDateOut.setText("");
							goto inputDateOut;
						}
					}
				}
				if(txtRoom.isNull()){
					goto viewRoomAg;
				}
				long roomNumber=txtRoom.getNumber();
				hidemouse();
				box(1,25,7,55,15);
				box(3,25,7,55,7);
				gotoxy(26,7);
				cout<<"Save ID "<<id;
				gotoxy(28,9);
				cout<<"Are you sure to save now ?";
				gotoxy(30,11);
				cout<<"Stay about  : ";
				gotoxy(30,12);
				cout<<"Total Price : ";
				gotoxy(45,11);
				textcolor(4);
				textbackground(1);
				int totalDay=calculatDay(day,mon,year,dayOut.getDay(),dayOut.getMonth(),dayOut.getYear());
				if(totalDay==0)
					totalDay=1;
				cprintf("%d day",totalDay);
				gotoxy(45,12);
				double total;
				if(roomNumber>400)
					total=totalDay*20;
				else
					total=totalDay*10;
				cout<<total<<" $";
				Label cmdOk1=Label(28,14," Save ");
				Label cmdCancel1=Label(45,14," Cancel ");
				cmdOk1.setBgColor(2);
				cmdCancel1.setBgColor(2);
				showmouse();
				do{
					delay(5);
					getmouse(&c,&x,&y);
					if(c==1){
						if(checkmouse(x,y,45,14,52,14)){
							cmdCancel1.setBgColor(4);
							delay(100);
							cmdCancel1.setBgColor(2);
							goto ag;
						}else if(checkmouse(x,y,28,14,33,14)){
							cmdOk1.setBgColor(4);
							delay(100);
							cmdOk1.setBgColor(2);
							double amount;
							if(roomNumber>400)
								amount=totalDay*20;
							else
								amount=totalDay*10;
							// save Data
							data[++recode]=Data(id,name,dayIn,dayOut,roomNumber,totalDay,amount);
							room[i1][i2][i3].setStatus(0);
							setDataInFile();
							updateRoom();
							txtId.setText("");
							txtName.setText("");
							txtDateOut.setText("");
							txtRoom.setNumberNull();
							goto ag;

						}
					}

				}while(1);
			}else if(checkmouse(x,y,40,20,47,20)){
				cmdCancel.setBgColor(1);
				delay(100);
				cmdCancel.setBgColor(2);
				box(getBackground(),10,5,70,22);
				return;
			}


		}

	}while(1);


}
int dayInMonth(int m){
 int day;
 if(m==1||m==3||m==5||m==7||m==8||m==10||m==12){
	day=31;
 }else if(m==2){
	day=28;
 }else{
	day=30;
 }
 return day;
}
int calculatDay(int d_in,int m_in,int y_in,int d_out,int m_out,int y_out){
 int total=0;
 int mIn=m_in;
 int yIn=y_in;
 int i=0;
 do{
	if(mIn==m_out&&yIn==y_out){
		total+=d_out-d_in;
		i=1;
	}else if(mIn==m_out-1&&yIn==y_out){
		int dayIn=dayInMonth(mIn)-d_in;
		dayIn+=d_out;
		total+=dayIn;
		i=1;
	 }else{
		int day=dayInMonth(mIn);
		total+=day;
		if(mIn==12){
			mIn=1;
			yIn++;
		}else{
			mIn++;
		}
	 }
 }while(i==0);
 return total;
}
int convertDate(Date *obj,char date[]){
 int len=strlen(date);
 char r[5];
 int in=-1;
 int c=0;
 int con;
 for(int i=0;i<len;i++){
	if(date[i]=='-'){
		r[++in]='\0';
		if(c==0){
		       con=atoi(r);
		       if(con==0||con<1){
				return 0;
		       }
		       (*obj).setDay(atoi(r));
			c=1;
		}else{
			con=atoi(r);
			if(con==0||con>12||con<1){
				return 0;
			}
			(*obj).setMonth(atoi(r));
		}
		in=-1;
		c++;
		continue;
	}
	r[++in]=date[i];
 }
 r[++in]='\0';
 con=atoi(r);
 if(con==0){
	return 0;
 }
 if(c!=3)
	return 0;
 if((*obj).getDay()>dayInMonth((*obj).getMonth())){
	return 0;
 }
 (*obj).setYear(atoi(r));
 return 1;
}
int viewRoom(int &i1,int &i2,int &i3,int o,int out){
 int lv=1;
 int rr=-1,cc=-1;
 again:
 box(3,6,4,74,24);
 box(3,6,4,74,4);
 textbackground(4);
 textcolor(0);
 gotoxy(72,4);
 cprintf(" X ");
 gotoxy(7,4);
 cout<<"View Room";
 box(6,7,6,73,23);
 Label lv1=Label(7,5," Level 1 ");
 Label lv2=Label(16,5," Level 2 ");
 Label lv3=Label(25,5," Level 3 ");
 Label lv4=Label(34,5," Level 4 VIP ");
 Label cmdOk=Label(15,22,"   OK   ");
 Label cmdDetail=Label(54,22,"   Delail   ");
 cmdOk.setBgColor(3);
 cmdDetail.setBgColor(3);
 ag:
 if(lv==1){
	lv1.setColor(0);
	lv1.setBgColor(6);
 }else{
	lv1.setColor(7);
	lv1.setBgColor(0);
 }
 if(lv==2){
	lv2.setColor(0);
	lv2.setBgColor(6);
 }else{
	lv2.setBgColor(0);
	lv2.setColor(7);
 }
 if(lv==3){
	lv3.setColor(0);
	lv3.setBgColor(6);
 }else{
	lv3.setBgColor(0);
	lv3.setColor(7);
 }
 if(lv==4){
	lv4.setColor(0);
	lv4.setBgColor(6);
 }else{
	lv4.setBgColor(0);
	lv4.setColor(7);
 }
 showAg:
 hidemouse();
 int xx=9,yy=8;
 int rooms=1;
 for(int i=0;i<3;i++){
	for(int j=0;j<5;j++){
		window(xx,yy,xx+10,yy+2);
		if(room[lv-1][i][j].getStatus()){
			if(lv==4){
				textcolor(0);
			}else{
				textcolor(7);
			}
			if(i==rr&&j==cc){
				textbackground(2);
			}else{
				textbackground(1);
			}
			clrscr();
			gotoxy(2,2);
			cout<<"Room :"<<rooms+(lv*100);
		}else{
			if(i==rr&&j==cc){
				textbackground(2);
				textcolor(0);
			}else{
				textbackground(0);
				textcolor(7);
			}
			clrscr();
			gotoxy(2,2);
			cout<<"Room :"<<rooms+(lv*100);
			gotoxy(4,3);
			cout<<":Busy";
		}
	       xx+=13;
	       rooms++;
	}
	xx=9;
	yy+=5;

 }
 showmouse();
 int x,y,c;
 do{
	getmouse(&c,&x,&y);
	if(c==1){
		if(checkmouse(x,y,72,4,74,4)){
			break;
		}else if(checkmouse(x,y,7,5,7+8,5)&&lv!=1){
			lv=1;
			rr=-1;
			cc=-1;
			goto ag;
		}else if(checkmouse(x,y,16,5,16+8,5)&&lv!=2){
			lv=2;
			rr=-1;
			cc=-1;
			goto ag;
		}else if(checkmouse(x,y,25,5,25+8,5)&&lv!=3){
			lv=3;
			rr=-1;
			cc=-1;
			goto ag;
		}else if(checkmouse(x,y,34,5,34+12,5)&&lv!=4){
			lv=4;
			rr=-1;
			cc=-1;
			goto ag;
		}else if(checkmouse(x,y,15,22,15+7,22)){
			if(o==0){
				box(1,5,3,75,24);
				return 0;
			}
			cmdOk.setBgColor(5);
			delay(100);
			cmdOk.setBgColor(3);
			if(rr!=-1){
				if(out==0){
					if(room[lv-1][rr][cc].getStatus()){
						i1=lv-1;
						i2=rr;
						i3=cc;
						box(1,5,3,75,24);
						return 1;
					}
				}else{
					if(!room[lv-1][rr][cc].getStatus()){
						i1=lv-1;
						i2=rr;
						i3=cc;
						box(1,5,3,75,24);
						return 1;
					}

				}
			}
		}else if(checkmouse(x,y,54,22,54+11,22)){
			cmdDetail.setBgColor(5);
			delay(100);
			cmdDetail.setBgColor(3);
			if(rr!=-1){
				viewDetail(lv-1,rr,cc);
				goto again;
			}
		}else{
			int x1=9,y1=8;
			int r=1;
			for(int i=0;i<3;i++){
				for(int j=0;j<5;j++){
					if(checkmouse(x,y,x1,y1,x1+10,y1+2)){
						if(rr!=i||cc!=j){
							rr=i;
							cc=j;
							goto showAg;
						}
					}
					x1+=13;
					r++;
				}
				x1=9;
				y1+=5;
			}


		}


	}


	delay(5);
 }while(1);
 box(1,5,3,75,24);
 return 0;
}
void report(){
 int start=0;
 box(6,3,4,78,23);
 box(3,3,4,78,4);
 box(3,3,23,78,23);
 gotoxy(4,4);
 cout<<"Report";
 gotoxy(76,4);
 textcolor(0);
 textbackground(4);
 cprintf(" X ");
 box(7,3,6,78,22);
 window(4,6,77,6);
 textbackground(1);
 textcolor(7);
 clrscr();
 gotoxy(2,1);
 cout<<"ID";
 gotoxy(9,1);
 cout<<"Name";
 gotoxy(23,1);
 cout<<"RNum";
 gotoxy(30,1);
 cout<<"Type";
 gotoxy(37,1);
 cout<<"Date In";
 gotoxy(50,1);
 cout<<"Date Out";
 gotoxy(63,1);
 cout<<"Day";
 gotoxy(69,1);
 cout<<"Price";
 window(4,7,77,21);
 textbackground(7);
 textcolor(0);
 clrscr();
 window(3,5,78,23);
 int xx[9]={1,8,22,29,36,49,62,68,76};
 for(int i=1;i<=75;i++){
	gotoxy(i,1);
	textcolor(1);
	textbackground(6);
	cprintf("%c",205);
	gotoxy(i,18);
	cprintf("%c",205);
 }
 for(i=0;i<9;i++){
	for(int j=1;j<=18;j++){
		gotoxy(xx[i],j);
		textcolor(1);
		textbackground(6);
		cprintf("%c",186);
	}
	if(i>0&&i<8){
		gotoxy(xx[i],1);
		cprintf("%c",203);
		gotoxy(xx[i],18);
		cprintf("%c",202);
	}
 }
 gotoxy(1,1);
 cprintf("%c",201);
 gotoxy(1,18);
 cprintf("%c",200);
 gotoxy(76,1);
 cprintf("%c",187);
 gotoxy(76,18);
 cprintf("%c",188);
 int x,y,c;
 Label cmdNext=Label(62,23," Next Record >> ");
 Label cmdBack=Label(4,23," << Back Record ");
 cmdNext.setBgColor(3);
 cmdBack.setBgColor(3);
 // Display Data --------------------->
 display:
 window(4,7,77,21);
 Date obj;
 int yy=1;
 int count=1;
 for(int v=0;v<15;v++){
	gotoxy(2,yy);
	cout<<"    ";
	gotoxy(9,yy);
	cout<<"           ";
	gotoxy(23,yy);
	cout<<"   ";
	gotoxy(30,yy);
	cout<<"    ";
	gotoxy(37,yy);
	cout<<"          ";
	gotoxy(50,yy);
	cout<<"          ";
	gotoxy(63,yy);
	cout<<"   ";
	gotoxy(69,yy);
	cout<<"     ";
	yy++;
 }
 yy=1;
 for(int a=start;a<=recode+start;a++){
	if(count==16)
		break;
	count++;
	gotoxy(2,yy);
	cout<<data[a].getId();
	gotoxy(9,yy);
	cout<<data[a].getName();
	gotoxy(23,yy);
	cout<<data[a].getRoomNumber();
	gotoxy(30,yy);
	if(data[a].getRoomNumber()>400){
		textcolor(5);
		textbackground(7);
		cprintf("VIP");
	}else{
		cout<<"Sim";
	}
	gotoxy(37,yy);
	obj=data[a].getDateIn();
	cout<<obj.getDay()<<"-"<<obj.getMonth()<<"-"<<obj.getYear();
	gotoxy(50,yy);
	obj=data[a].getDateOut();
	int tf=1;
	struct date dat;
	getdate(&dat);
	int d1=(int)dat.da_day;
	int m1=(int)dat.da_mon;
	int y1=(int)dat.da_year;
	if(y1>obj.getYear()){
		tf=0;
	}else if(y1==obj.getYear()){
		if(m1>obj.getMonth()){
			tf=0;
		}else if(m1==obj.getMonth()){
			if(d1>obj.getDay()){
				tf=0;
			}else if(d1==obj.getDay()){
				tf=3;
			}else{
				tf=1;
			}
		}else{
			tf=1;
		}
	}else{
		tf=1;
	}
	if(tf==0){
		textcolor(4);
		cprintf("%d-%d-%d",obj.getDay(),obj.getMonth(),obj.getYear());
	}else if(tf==3){
		textcolor(6);
		cprintf("%d-%d-%d",obj.getDay(),obj.getMonth(),obj.getYear());
	}else{
		cout<<obj.getDay()<<"-"<<obj.getMonth()<<"-"<<obj.getYear();
	}
	gotoxy(63,yy);
	cout<<data[a].getTotalDay();
	gotoxy(69,yy);
	cout<<data[a].getPrice();
	yy++;
 }
 do{
	getmouse(&c,&x,&y);
	if(c==1){
		if(checkmouse(x,y,76,4,79,4)){
			break;
		}else if(checkmouse(x,y,62,23,62+15,23)){
			cmdNext.setBgColor(2);
			delay(100);
			cmdNext.setBgColor(3);
			if(start<recode-14){
				start++;
				goto display;
			}
		}else if(checkmouse(x,y,4,23,4+15,23)){
			cmdBack.setBgColor(2);
			delay(100);
			cmdBack.setBgColor(3);
			if(start!=0){
				start--;
				goto display;
			}
		}


	}
	if(kbhit()){
		char ch=getch();
		if(ch==0){
			ch=getch();
			if(ch==80||ch==77){
				if(start<recode-14){
					start++;
					goto display;
				}
			}else if(ch==72||ch==75){
				if(start!=0){
					start--;
					goto display;
				}
			}
		}
	}
 delay(5);
 }while(1);
 box(1,3,4,78,23);
}
void viewDetail(int i1,int i2,int i3){
 box(5,20,9,60,21);
 box(3,20,9,60,9);
 gotoxy(21,9);
 cout<<"View Detail";
 textbackground(4);
 gotoxy(58,9);
 cprintf(" X ");
 window(20,9,50,21);
 if(room[i1][i2][i3].getStatus()){
	gotoxy(7,4);
	cout<<"Status      :";
	textcolor(4);
	textbackground(5);
	cprintf("      Free");
	gotoxy(7,5);
	int rn=room[i1][i2][i3].getRoomNumber();
	cout<<"Room Number :      "<<rn;
	gotoxy(7,6);
	if(rn>400)
		cout<<"Room Type   :      VIP";
	else
		cout<<"Room Type   :      Simple";
	gotoxy(7,7);
	cout<<"Level       :      "<<i1+1;
 }else{
	gotoxy(7,4);
	cout<<"Status      :";
	textcolor(4);
	textbackground(5);
	cprintf("      Busy");
	gotoxy(7,5);
	int rn=room[i1][i2][i3].getRoomNumber();
	cout<<"Room Number :      "<<rn;
	gotoxy(7,6);
	if(rn>400)
		cout<<"Room Type   :      VIP";
	else
		cout<<"Room Type   :      Simple";
	gotoxy(7,7);
	cout<<"Level       :      "<<i1+1;
	gotoxy(7,8);
	char gName[20];
	Date din,dout;
	for(int s=0;s<=recode;s++){
		if(data[s].getRoomNumber()==rn){
			strcpy(gName,data[s].getName());
			din=data[s].getDateIn();
			dout=data[s].getDateOut();
			break;
		}
	}
	cout<<"Guest Name  :      "<<gName;
	gotoxy(7,9);
	cout<<"Date In     :      "<<din.getDay()<<"-"<<din.getMonth()<<"-"<<din.getYear();
	gotoxy(7,10);
	cout<<"Date Out    :      "<<dout.getDay()<<"-"<<dout.getMonth()<<"-"<<dout.getYear();

 }
 int x,y,c;
 do{
	getmouse(&c,&x,&y);
	if(c==1){
		if(checkmouse(x,y,58,9,60,9)){
			break;
		}

	}

 delay(5);
 }while(1);
 box(5,20,9,60,21);
 delay(200);
}
void checkOut(){
 TextField txtRoom;
 txtRoom.setLocation(28,8,20);
 int roomN=0;
 ag:
 box(6,15,5,65,20);
 box(3,15,5,65,5);
 gotoxy(63,5);
 textcolor(0);
 textbackground(4);
 cprintf(" X ");
 gotoxy(16,5);
 textcolor(0);
 textbackground(3);
 cprintf("Check Out");

 Label cmdFind=Label(28,10," Find ");
 Label cmdOut=Label(20,16," Check out now ");
 cmdOut.setBgColor(5);
 cmdFind.setBgColor(1);
 gotoxy(20,8);
 textbackground(6);
 textcolor(0);
 cprintf("Room  : ");
 gotoxy(20,10);
 cprintf("Find  : ");
 txtRoom.show();
 if(!roomN==0){
	gotoxy(29,8);
	cout<<roomN;
 }
 int x,y,c;
 int i1,i2,i3;
 do{
	getmouse(&c,&x,&y);
	if(c==1){
		if(checkmouse(x,y,28,10,33,10)){
			cmdFind.setBgColor(2);
			delay(100);
			cmdFind.setBgColor(1);

			if(viewRoom(i1,i2,i3,1,1)){
				roomN=room[i1][i2][i3].getRoomNumber();
			}
			goto ag;
		}else if(checkmouse(x,y,63,5,65,5)){
			box(1,15,5,65,20);
			break;
		}else if(checkmouse(x,y,20,16,20+14,16)&&roomN!=0){
			cmdOut.setBgColor(2);
			delay(100);
			cmdOut.setBgColor(5);
			box(3,30,8,50,15);
			box(1,30,8,50,8);
			textcolor(0);
			textbackground(4);
			gotoxy(48,8);
			cprintf(" X ");
			gotoxy(34,10);
			textcolor(0);
			textbackground(3);
			cprintf("Are you sure ?");
			Label cmdOk=Label(38,13," OK ");
			cmdOk.setBgColor(1);
			do{
				getmouse(&c,&x,&y);
				if(c==1){
					if(checkmouse(x,y,48,8,50,8)){
						break;
					}else if(checkmouse(x,y,38,13,41,13)){
						cmdOk.setBgColor(2);
						delay(100);
						cmdOk.setBgColor(1);
						for(int i=0;i<=recode;i++){
							if(roomN==data[i].getRoomNumber()){
								for(int k=i;k<=recode;k++){
									data[k]=data[k+1];
								}
								for(int l=0;l<4;l++){
									for(int m=0;m<3;m++){
										for(int n=0;n<5;n++){
											if(room[l][m][n].getRoomNumber()==roomN){
												room[l][m][n].setStatus(1);
												break;
											}
										}
									}
								}
								ofstream file("mydata.txt");
								file.close();
								recode--;
								updateRoom();
								setDataInFile();
								break;
							}
						}
						roomN=0;
						break;
						// delete---------------->
					}
				}
				delay(5);
			}while(1);
			goto ag;
		}

	}
	delay(5);
 }while(1);

}
void viewPrice(){
 int s=0;
 Date obj[50];
 Date getDate;
 int act;
 int dd,mm,yy,dd1,mm1,yy1;
 for(int i=0;i<=recode;i++){
	act=1;
	getDate=data[i].getDateIn();
	for(int ii=0;ii<s;ii++){
		dd=obj[ii].getDay();
		mm=obj[ii].getMonth();
		yy=obj[ii].getYear();
		if(dd==getDate.getDay()&&mm==getDate.getMonth()&&yy==getDate.getYear()){
			act=0;
			break;
		}
	}
	if(act){
		obj[s++]=getDate;
	}
 }
 double price;
 box(6,15,5,65,17);
 box(3,15,5,65,5);
 Label cmdBack=Label(23,15," previous ");
 Label cmdNext=Label(48,15," Next ");
 cmdBack.setBgColor(3);
 cmdNext.setBgColor(3);
 textbackground(4);
 gotoxy(63,5);
 cprintf(" X ");
 gotoxy(16,5);
 cout<<"View Price";
 int x,y,c;
 gotoxy(18,8);
 textbackground(6);
 cprintf("Date        : ");
 gotoxy(18,10);
 cprintf("Total Room  : ");
 gotoxy(18,12);
 cprintf("Total Price : ");
 //--------------------->
 int index=0;
 ag:
 int totalRoom=0;
 double totalPrice=0;
 dd=obj[index].getDay();
 mm=obj[index].getMonth();
 yy=obj[index].getYear();
 for(int o=0;o<=recode;o++){
	getDate=data[o].getDateIn();
	if(dd==getDate.getDay()&&mm==getDate.getMonth()&&yy==getDate.getYear()){
		totalRoom++;
		totalPrice+=data[o].getPrice();
	}
 }
 gotoxy(33,8);
 textbackground(7);
 cprintf("                    ");
 gotoxy(34,8);
 cout<<dd<<"-"<<mm<<"-"<<yy;
 gotoxy(33,10);
 cprintf("                    ");
 gotoxy(34,10);
 cout<<totalRoom;
 gotoxy(33,12);
 cprintf("                    ");
 gotoxy(34,12);
 cout<<totalPrice;
 do{
	getmouse(&c,&x,&y);
	if(c==1){
		if(checkmouse(x,y,63,5,65,5)){
			break;
		}else if(checkmouse(x,y,23,15,23+9,15)&&index!=0){
			cmdBack.setBgColor(2);
			delay(200);
			cmdBack.setBgColor(3);
			index--;
			goto ag;
		}else if(checkmouse(x,y,48,15,48+5,15)&&index<s-1){
			cmdNext.setBgColor(2);
			delay(200);
			cmdNext.setBgColor(3);
			index++;
			goto ag;
		}

	}
	delay(5);
 }while(1);
 box(1,15,5,65,17);

}
void showGroup(){
 windowFull();
 textbackground(7);
 clrscr();
 window(3,2,78,24);
 textbackground(1);
 clrscr();
 textcolor(7);
 gotoxy(27,2);
 cprintf("_____________________");
 gotoxy(27,5);
 cprintf("_____________________");
 gotoxy(30,4);
 textcolor(2);
 cprintf("SETEC INSTITUTE");
 gotoxy(27,7);
 textcolor(6);
 cprintf("Teacher : Lim kimkhun");
 gotoxy(32,9);
 textcolor(0);
 cprintf("Guest House");
 gotoxy(33,11);
 textcolor(8);
 cprintf("Group SM6");
 gotoxy(7,13);
 textcolor(5);
 cprintf("1. Laing Raven");
 gotoxy(30,13);
 cprintf("2. Nhem Piseth");
 gotoxy(57,13);
 cprintf("3. Rin Pisey");
 gotoxy(7,15);
 cprintf("4. Roung Ravy");
 gotoxy(30,15);
 cprintf("5. Pouch Soksungvarith");
 gotoxy(57,15);
 cprintf("6. Chan Trean");
 gotoxy(7,17);
 cprintf("7. Song Sokheang");
 gotoxy(57,17);
 cprintf("8. Heng Sophearoth");
 getch();
}