//input output stream header files
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <fstream.h>
#include <dos.h>
#include <ctype.h>
#include <string.h>
#include <graphics.h>
#include <time.h>

#define UDFaddress "userData"
#define RFaddress "record"
#define DELAYBORDER 5

struct userID{char username[33];char password[33];};
struct medicineRecord{
	char id[11];char name[11];
	char mfg[11];char exp[11];
	char mrp[6];char inStock[6];
};

int windowHeight = 24, windowWidth = 80;
int textHeight = 22, textWidth = 78;
int displayBorderAni = 0, UserAuthority = 0,level = 0;
char currentUsername[32];
char * getDateString(){
	  time_t rawtime;
	  struct tm * timeinfo;char* buffer;
	  time (&rawtime);
	  timeinfo = localtime (&rawtime);
	  strftime (buffer,80,"%d-%m-%Y",timeinfo);
	  return buffer;
}
char * getTimeString(){
	  time_t rawtime;
	  struct tm * timeinfo;char* buffer;
	  time (&rawtime);
	  timeinfo = localtime (&rawtime);
	  strftime (buffer,80,"%H:%M",timeinfo);
	  return buffer;
}
void sepDate(char * pch[3],char * d){
	int j = 0,k = 0;
	for(int i = 0;i < strlen(d);i++){
		if(d[i] == '/'){
			pch[k][j] = '\0';
			j = 0;k++;continue;
		}pch[k][j] = d[i];j++;
	}pch[k][j] = '\0';
}
class Console {
public:
	void write(char * u){
		for(int j=0;j < strlen(u);j++){
			cout<<u[j];
			if(u[j]!=' ') delay(10);
		}
		fflush(stdout);
	};
	void writexy(char * u,int x,int y){
		gotoxy(x,y);this->write(u);
		fflush(stdout);
	};
	void writexyn(char * u,int x,int y,int n){
		gotoxy(x,y);
		for(int i=0;i < n;i++) this->write(u);
		fflush(stdout);
	};
}console;
class Border{
private:
	void bTLFirst(int c){
		if(c < windowWidth){
			gotoxy(c,1);cout<<this->bT;
		}else if(c == windowWidth){
			gotoxy(windowWidth,1);cout<<this->bTR;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(windowWidth,c-windowWidth+1);
			cout<<this->bR;
		}
		this->bTLSecond(c);
	};
	void bTLSecond(int c){
		int e = 1;
		if(c < windowHeight){
			gotoxy(1,c);cout<<this->bL;
		}else if(c == windowHeight){
			gotoxy(1,windowHeight);cout<<this->bBL;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(c-windowHeight+1,windowHeight);cout<<this->bB;
		}else
			e = 0;
		delay(DELAYBORDER);
		if(e == 1){c++;this->bTLFirst(c);}
	};
	void bTRFirst(int c){
		if(c < windowWidth){
			gotoxy(windowWidth - c + 1,1);
			cout<<this->bT;
		}else if(c == windowWidth){
			gotoxy(1,1);cout<<this->bTL;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(1,c - windowWidth + 1);cout<<this->bL;
		}
		this->bTRSecond(c);
	};
	void bTRSecond(int c){
		int e = 1;
		if(c < windowHeight){
			gotoxy(windowWidth,c);cout<<this->bR;
		}else if(c == windowHeight){
			gotoxy(windowWidth,windowHeight);cout<<this->bBR;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(windowWidth + windowHeight - c,windowHeight);
			cout<<this->bB;
		}else
			e = 0;
		delay(DELAYBORDER);
		if(e == 1){c++;this->bTRFirst(c);}
	};
	void bBRFirst(int c){
		if(c < windowHeight){
			gotoxy(windowWidth,windowHeight - c + 1);
			cout<<this->bR;
		}else if(c == windowHeight){
			gotoxy(windowWidth,1);cout<<this->bTR;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(windowWidth - (c - windowHeight),1);
			cout<<this->bT;
		}
		this->bBRSecond(c);
	};
	void bBRSecond(int c){
		int e = 1;
		if(c < windowWidth){
			gotoxy(windowWidth - c + 1,windowHeight);
			cout<<this->bB;
		}else if(c == windowWidth){
			gotoxy(1,windowHeight);cout<<this->bBL;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(1,windowHeight - c + windowWidth);
			cout<<this->bR;
		}else
			e = 0;
		delay(DELAYBORDER);
		if(e == 1){c++;this->bBRFirst(c);}
	};
	void bBLFirst(int c){
		if(c < windowWidth){
			gotoxy(c,windowHeight);
			cout<<this->bB;
		}else if(c == windowWidth){
			gotoxy(windowWidth,windowHeight);
			cout<<this->bBR;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(windowWidth,windowHeight - (c - windowWidth));
			cout<<this->bR;
		}
		this->bBLSecond(c);
	};
	void bBLSecond(int c){
		int e = 1;
		if(c < windowHeight){
			gotoxy(1,windowHeight - c + 1);
			cout<<this->bL;
		}else if(c == windowHeight){
			gotoxy(1,1);
			cout<<this->bTL;
		}else if(c < windowWidth + windowHeight - 1){
			gotoxy(c - windowHeight + 1,1);
			cout<<this->bT;
		}else
			e = 0;
		delay(DELAYBORDER);
		if(e == 1){c++;this->bBLFirst(c);}
	};
	void displayTLBorder(){
		gotoxy(1,1);cout<<this->bTL;
		delay(DELAYBORDER);
		this->bTLFirst(2);
		gotoxy(windowWidth,windowHeight);cout<<this->bBR;
	};
	void displayTRBorder(){
		gotoxy(windowWidth,1);cout<<this->bTR;
		delay(DELAYBORDER);
		this->bTRFirst(2);
		gotoxy(1,windowHeight);cout<<this->bBL;
	};
	void displayBRBorder(){
		gotoxy(windowWidth,windowHeight);cout<<this->bBR;
		delay(DELAYBORDER);
		this->bBRFirst(2);
		gotoxy(1,1);cout<<this->bTL;
	};
	void displayBLBorder(){
		gotoxy(1,windowHeight);cout<<this->bBL;
		delay(DELAYBORDER);
		this->bBLFirst(2);
		gotoxy(windowWidth,1);cout<<this->bTR;
	};
public:
	char bTL,bTR,bBR,bBL,bT,bR,bB,bL;
	Border(){
		this->bTL = 201;
		this->bTR = 187;
		this->bBR = 188;
		this->bBL = 200;
		this->bT = 205;
		this->bR = 186;
		this->bB = 205;
		this->bL = 186;
	};
	void displayBorder(int noAnimation = 0){
		if(noAnimation == 0){
			if(displayBorderAni == 0)
				this->displayTLBorder();
			else if(displayBorderAni == 1)
				this->displayTRBorder();
			else if(displayBorderAni == 2)
				this->displayBRBorder();
			else
				this->displayBLBorder();
			displayBorderAni++;
			if(displayBorderAni > 3)displayBorderAni = 0;
		}else{
			int i;
			gotoxy(1,1);
			cout<<this->bTL;
			gotoxy(windowWidth,1);
			cout<<this->bTR;
			gotoxy(1,windowHeight);
			cout<<this->bBL;
			gotoxy(windowWidth,windowHeight);
			cout<<this->bBR;
			for(i = 2;i<windowHeight;i++){
				gotoxy(1,i);cout<<this->bL;
				gotoxy(windowWidth,i);cout<<this->bR;
			}
			for(i = 2;i<windowWidth;i++){
				gotoxy(i,1);cout<<this->bT;
				gotoxy(i,windowHeight);cout<<this->bB;
			}
		}
		fflush(stdout);
	};
}border;
class Page{
public:
	char str[25][100];
	int x[25], y[25],startH;
	long long int length, neglength, noAnimation;
	Page(){
		this->length = this->neglength = this->startH = this->noAnimation = 0;
		for(int i=0; i < 25; i++){x[i] = y[i] = 0;str[i][0] = '\0';}
	};
	void add(char * s,int x = 0, int y = 0){
		strcpy(this->str[this->length],s);
		this->x[this->length] = x;
		this->y[this->length] = y;
		this->length++;
		if(x != 0 || y != 0) this->neglength--;
	};
	void displayCenter(){
		int startH=(textHeight- (this->length + this->neglength))/2 + this->startH;
		for(long long int i=0; i < this->length; i++){
			if(this->x[i] == 0 && this->y[i] == 0){
				gotoxy((int)((textWidth - strlen(this->str[i]))/2),startH);
				if(this->noAnimation == 0)
					console.write(this->str[i]);
				else
					cout<<this->str[i];
				startH++;
			}else{
				gotoxy(this->x[i],this->y[i]);
				if(this->noAnimation == 0)
					console.write(this->str[i]);
				else
					cout<<this->str[i];
			}
		}
		fflush(stdout);
	};
};
class TapPage: public Page{
public:
	int wrongStat;
	int nextPageId;
	int tap[10];

	TapPage(){
		this->length = 0;
		this->neglength = 0;
		this->nextPageId = 0;
		this->wrongStat = 0;
		this->startH = 0;
		this->noAnimation = 0;
		for (int i = 0; i < 10; ++i)
			this->tap[i] = 0;
	};
	void initial(){
		clrscr();
		border.displayBorder();
		this->startH = 3;
		this->add("P H A R M A C Y  S T O R E",(int)((textWidth - 25)/2),2);
		this->add(" ");
		this->add(" ");
		this->add("Username: ",3,5);
		this->add(currentUsername,13,5);
		this->add(getDateString(),windowWidth - 11,5);
		this->add(getTimeString(),windowWidth - 6,6);
	};

	void terminate(){
		this->add(" ");
		this->add("Enter your choice: ");
		this->displayCenter();
		while(this->nextPageId == 0){
			this->getInput();
			this->setLevel();
		}
	};

	void getInput(){
gotoxy((int)((textWidth-strlen(this->str[this->length-1]))/2+18),(textHeight-(this->length+this->neglength))/2+(this->length+this->neglength-1)+this->startH);
		char a[2];a[0] = getch();a[1] = '\0';
		this->nextPageId = atoi(a);
		fflush(stdin);
	};

	void setLevel(){
		if(this->tap[this->nextPageId] == 0){
			if(this->wrongStat != 1){
				console.writexy("Wrong Input! Please try again.",(int)((textWidth-30)/2),(textHeight-(this->length+this->neglength))/2+this->startH);
				this->wrongStat = 1;
			}
			this->nextPageId = 0;
		}else{
			level = this->tap[this->nextPageId];this->nextPageId = 1;
		}
	};

	void addTap(int i,int j){this->tap[i] = j;};
};
class TabularPage {
public:
	int columnsD[10], columns[10],column, row;

	TabularPage(){
		for(int i = 0;i < textWidth;i++)
			this->columnsD[i] = this->columns[i] = 0;
		this->row = 4;this->column = 0;
	};
	void setHeaders(char * a[]){
		for(int i = 0;i < this->column; i++)
			console.writexy(a[i],this->columns[i],2);
	};
	void add(char * a[]){
		for(int i = 0;i < this->column; i++)
			console.writexy(a[i],this->columns[i],this->row);
		this->row++;
		if(this->row == windowHeight){
			getch();
			this->row = 4;
			while(this->row != windowHeight){
				for(int i = 0;i < this->column; i++){
console.writexyn(" ",this->columns[i],this->row,i==0?this->columns[i+1]-7:this->columns[i]-this->columns[i-1]-3);
				}
				this->row++;
			}
			this->row = 4;
		}
	};
	void intial(){
		clrscr();
		border.displayBorder();
		gotoxy(2,3);
		int i;
		for(i = 0;i < textWidth;i++){delay(5);cout<<"-";}
		for(i = 0;i < 10 && this->columnsD[i] != 0;i++){
			for(int j = 1;j <= textHeight;j++){
				gotoxy(this->columnsD[i],j+1);
				delay(5);cout<<"|";
			}
			this->column++;
		}
		this->column++;
	};
	void terminate(){getch();};
};
class EditPage {
public:
	void intial(){
		clrscr();
		border.displayBorder();
		gotoxy(2,2);
	};
	void reintial(){
		if(wherey() >= windowHeight){clrscr();border.displayBorder(1);gotoxy(2,2);}
	};
	void display(char * d){
		gotoxy(2,wherey());
		console.write(d);
		cout<<endl;
		this->reintial();
		fflush(stdout);
	};
	char * get(char * d){
		gotoxy(2,wherey());
		char *i;
		console.write(d);
		gets(i);
		cout<<endl;
		this->reintial();
		fflush(stdin);
		return i;
	};
	char * getDefault(char * d,char * g){
		gotoxy(2,wherey());char *i;
		console.write(d);console.write("(");
		console.write(g);console.write(") :");
		gets(i);
		cout<<endl;
		this->reintial();
		fflush(stdin);
		return i[0] == '\0'? g : i;
	};
};
class UserID {
public:
	fstream userFile;
	UserID(){this->userFile.open(UDFaddress,ios::in | ios::out | ios::binary );};
	~UserID(){this->userFile.flush();this->userFile.close();};
	int isEmpty(){
		this->userFile.seekg(0,ios::end);
		int i = this->userFile.tellg();
		return i == 0 ? 1 : 0;
	};
	void insert(char * u,char * p){
		this->userFile.seekg(-1,ios::end);
		this->userFile << u << ":" << p << ";?";
		this->userFile.flush();this->userFile.sync();
	};
	void removeUser(char * u){
		int c = 0;userID uid;
		this->userFile.seekg(0,ios::beg);
		while(this->getNext(uid)){
			if (strcmp(uid.username, u) == 0) { c = 1;break; }
		}
		if(c == 1){
			c = strlen(uid.username) + strlen(uid.password) + 2;
			this->userFile.seekg(-c,ios::cur);
			for(int i=0;i < c;i++){this->userFile<<" ";}
		}
		this->userFile.flush();this->userFile.sync();
	};
	int isUser(char * u){
		userID uid;
		int c = 0;
		this->userFile.seekg(0,ios::beg);
		while(this->getNext(uid)){
			if (strcmp(uid.username, u) == 0) { c = 1;break; }
		}
		return c;
	};
	int check(char * u,char * p){
		userID uid;
		int c = 0;
		this->userFile.seekg(0,ios::beg);
		while(this->getNext(uid)){
			if(strcmp(uid.username,u) == 0){
				c=(strcmp(uid.password,p)==0);break;
			}
		}return c;
	};
	int getNext(userID & uid){
		char a;
		int i = 0,j = 0,c = 0;
		while(c == 0){
			this->userFile.get(a);
			if(a == ' ')continue;
			if(a == '?')break;
			if(a == ';'){c = 1;uid.password[i] = '\0';break;}
			if(a == ':'){uid.username[i]='\0';j++;i = 0;continue;}
			if(j == 0) uid.username[i] = a;
			else       uid.password[i] = a;
			i++;
		}
		return c;
	};
}user;
class Stock {
public:
	fstream recordsFile;
	Stock(){this->recordsFile.open(RFaddress,ios::in | ios::out | ios::binary );};
	~Stock(){this->recordsFile.flush();this->recordsFile.close();};
	int isEmpty(){
		int x = this->recordsFile.tellg();
		this->recordsFile.seekg(0, ios::end);
		int i = this->recordsFile.tellg();
		this->recordsFile.seekg(x, ios::beg);
		return i == 0 ? 1 : 0;
	};
	void insert(medicineRecord & m){
		this->recordsFile.seekg(-1,ios::end);
		this->recordsFile <<m.id <<":"<<m.name<<":"<<m.mrp<<":"<<m.mfg<<":"<<m.exp<<":"<<m.inStock<<";?";
		this->recordsFile.flush();this->recordsFile.sync();
	};
	void removeStockID(char * n){
		int c = 0;
		medicineRecord m;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(m)){
			if(strcmp(m.id,n) == 0){
				c = strlen(m.id) + strlen(m.name) + strlen(m.mrp) + strlen(m.mfg) + strlen(m.exp) + strlen(m.inStock) + 6;
				this->recordsFile.seekg(-c,ios::cur);
				for(int i=0;i < c;i++) this->recordsFile<<" ";
				break;
			}
		}
		this->recordsFile.flush();this->recordsFile.sync();
	};
	void removeStockName(char * n){
		int c = 0;
		medicineRecord m;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(m)){
			if(strcmp(m.name,n) == 0){
				c = strlen(m.id) + strlen(m.name) + strlen(m.mrp) + strlen(m.mfg) + strlen(m.exp) + strlen(m.inStock) + 6;
				this->recordsFile.seekg(-c,ios::cur);
				for(int i=0;i < c;i++) this->recordsFile<<" ";
				break;
			}
		}
		this->recordsFile.flush();this->recordsFile.sync();
	};
	int isMedID(char * n){
		medicineRecord mr;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(mr)){
			if(strcmp(mr.id,n) == 0)
				return 1;
		}
		return 0;
	};
	int isMedName(char * n){
		medicineRecord mr;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(mr)){
			if(strcmp(mr.name,n) == 0)
				return 1;
		}
		return 0;
	};
	int getNext(medicineRecord & mr){
		if (this->isEmpty()) {return 0;}
		char a;
		int i = 0, j = 0, c = 0;
		while(c == 0){
			this->recordsFile.get(a);
			if(a == ' ') continue;
			if(a == '?') break;
			if (a == ';') { c = 1;mr.inStock[i] = '\0';break; }
			if(a == ':') a = '\0';
			if(j == 0) mr.id[i] = a;
			else if(j == 1) mr.name[i] = a;
			else if(j == 2) mr.mrp[i] = a;
			else if(j == 3) mr.mfg[i] = a;
			else if(j == 4) mr.exp[i] = a;
			else if(j == 5) mr.inStock[i] = a;
			i++;
			if(a == '\0'){i = 0;j++;}
		}
		return c;
	};
	char * getNextID(){
		int max = 0;medicineRecord mr;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(mr)){
			if(max < atoi(mr.id)){max = atoi(mr.id);}
		}
		max++;
		char * a;itoa(max,a,10);
		return a;
	};
}stock;
class Welcome:public Page{
public:void start(){
		clrscr();
		border.displayBorder();
		this->add("W E L C O M E  T O  P H A R M A C Y   S T O R E");
		this->add(" ");
		this->add("Made by:-");
		this->add(" ");
		this->add("Vivswan Shah");
		this->add(" ");
		this->add("Press any key to continue...",windowWidth - 30,windowHeight-1);
		this->displayCenter();
		if(user.isEmpty())
			level = 1;
		else
			level = 2;
		getch();
		fflush(stdout);
	}
};
class Login:public Page{
	char username[50], password[50];
	int wrongStat, nextPageId;
	void getID(){
		console.writexyn(" ",(int)((textWidth-strlen(this->str[4]))/2 + 9),(textHeight-(this->length + this->neglength))/2+(4)+this->startH,32);
		console.writexyn(" ",(int)((textWidth-strlen(this->str[5]))/2 + 9),(textHeight-(this->length + this->neglength))/2+(5)+this->startH,32);
		gotoxy((int)((textWidth-strlen(this->str[4]))/2 + 9),(textHeight-(this->length + this->neglength))/2+(4)+this->startH);
		gets(this->username);
		gotoxy((int)((textWidth-strlen(this->str[5]))/2 + 9),(textHeight-(this->length + this->neglength))/2+(5)+this->startH);
		int i = getch(),l = 0;
		while(i!=13){
			if(i==8){
				l--;
				gotoxy(wherex()-1,wherey());
				cout<<" ";
				gotoxy(wherex()-1,wherey());
				i = getch();
			}else{
				this->password[l] = (char)i;
				cout<<"*";i = getch();l++;
			}
		}
		this->password[l] = '\0';
		fflush(stdin);
	};
	void checkID(){
		if(this->username[0] == '\0' && this->password[0] == '\0'){
			strcpy(currentUsername,"anonymous");
			UserAuthority = 0;level = 3;
			this->nextPageId = 1;
		}else if(this->username[0] != '\0' && this->password[0] == '\0'){
			if(this->wrongStat != 4){
				console.writexy("                Password was blank!               ",(int)((textWidth-50)/2),(textHeight-(this->length+this->neglength))/2+this->startH+2);
				this->wrongStat = 4;
			}
		}else if(this->username[0] == '\0' && this->password[0] != '\0'){
			if(this->wrongStat != 3){
				console.writexy("                Username was blank!               ",(int)((textWidth-50)/2),(textHeight-(this->length+this->neglength))/2+this->startH+2);
				this->wrongStat = 3;
			}
		}else if(user.check(this->username,this->password)){
			strcpy(currentUsername,this->username);
			level = 3;
			if(strcmp(this->username,"admin") == 0)
				UserAuthority = 2;
			else
				UserAuthority = 1;
			this->nextPageId = 1;
		}else if(user.isUser(this->username)){
			if(this->wrongStat != 1){
				console.writexy("       Password was wrong please try again!       ",(int)((textWidth-50)/2),(textHeight-(this->length+this->neglength))/2+this->startH+2);
				this->wrongStat = 1;
			}
		}else{
			if(this->wrongStat != 2){
				console.writexy("Username and password were wrong please try again!",(int)((textWidth-50)/2),(textHeight-(this->length+this->neglength))/2+this->startH+2);
				this->wrongStat = 2;
			}
		}
	};
public:
	Login(){
		this->length= this->neglength= this->startH= this->noAnimation = 0;
		this->nextPageId = this->wrongStat = 0;
		this->username[0] = this->password[0] = currentUsername[0] = '\0';
	};
	void start(){
		clrscr();
		border.displayBorder();
		this->add("Login");
		this->add(" ");this->add(" ");this->add(" ");
		this->add("Username:                        ");
		this->add("Password:                        ");
		this->add("* For anonymous users leave username and password blank. ",2,windowHeight-1);
		this->displayCenter();
		while(this->nextPageId == 0){this->getID();this->checkID();}
		fflush(stdout);
	};
};
class MainPage : private TapPage {
public:
	void start(){
		this->initial();
		if(UserAuthority == 1){
			this->add("1.Medicine         ");this->addTap(1,4);
			this->add("2.Buy Medicine     ");this->addTap(2,19);
			this->add("3.User details     ");this->addTap(3,5);
			this->add("4.Logout           ");this->addTap(4,2);
			this->add("5.Exit             ");this->addTap(5,-1);
		}else if(UserAuthority == 2){
			this->add("1.Medicine         ");this->addTap(1,4);
			this->add("2.Buy Medicine     ");this->addTap(2,19);
			this->add("3.Change password  ");this->addTap(3,14);
			this->add("4.User Management  ");this->addTap(4,6);
			this->add("5.Logout           ");this->addTap(5,2);
			this->add("6.Exit             ");this->addTap(6,-1);
		}else{
			this->add("1.Display Medicine ");this->addTap(1,7);
			this->add("2.Buy Medicine     ");this->addTap(2,19);
			this->add("3.Logout           ");this->addTap(3,2);
			this->add("4.Exit             ");this->addTap(4,-1);
		}
		this->terminate();fflush(stdout);
	}
};
class StockPage : private TapPage {
public:
	void start(){
		this->initial();
		this->add("0.Back to main menu");this->addTap(0,3);
		this->add("1.Display medicine ");this->addTap(1,7);
		this->add("2.Add medicine     ");this->addTap(2,8);
		this->add("3.Delete medicine  ");this->addTap(3,9);
		this->add("4.Edit medicine    ");this->addTap(4,10);
		this->add("5.Search medicine  ");this->addTap(5,11);
		this->add("6.Out of stock     ");this->addTap(6,12);
		this->add("7.Logout           ");this->addTap(7,2);
		this->add("8.Exit             ");this->addTap(8,-1);
		this->terminate();fflush(stdout);
	}
};
class UserPage : private TapPage {
public:
	void start(){
		this->initial();
		this->add("0.Back to main menu");this->addTap(0,3);
		this->add("1.Change Name      ");this->addTap(1,13);
		this->add("2.Change Password  ");this->addTap(2,14);
		this->add("3.Logout           ");this->addTap(3,2);
		this->add("4.Exit             ");this->addTap(4,-1);
		this->terminate();fflush(stdout);
	}
};
class UserManagePage : private TapPage {
public:
	void start(){
		this->initial();
		this->add("0.Back to main menu");this->addTap(0,3);
		this->add("1.Display Users    ");this->addTap(1,15);
		this->add("2.Add Users        ");this->addTap(2,16);
		this->add("3.Edit Users       ");this->addTap(3,17);
		this->add("4.Delete Users     ");this->addTap(4,18);
		this->add("5.Logout           ");this->addTap(5,2);
		this->add("6.Exit             ");this->addTap(6,-1);
		this->terminate();fflush(stdout);
	}
};
class BuyMed: private EditPage {
public:
	void start(){
		this->intial();
		this->display("Leave the Med ID blank for exit.");
		char * u = this->get("Enter Med ID:");
		if(u[0] == '\0'){level = 3;	return;	}
		while(!stock.isMedID(u)){
			this->display("Med ID not found.");
			char * u = this->get("Please Re-Enter Med ID:");
			if(u[0] == '\0'){level = 3;	return;	}
		}
		medicineRecord mr;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(mr)){
			if(strcmp(mr.id,u) == 0){break;}
		}

		char *x;strcpy(x,this->get("Enter number of item in stock:"));
		if(x[0] != '\0'){
			int i = atoi(x),j = atoi(mr.inStock),p = atoi(mr.mrp);
			i = j - i >= 0 ? i : -1;j = j - i;
			if(i != -1){
				stock.removeStockID(mr.id);
				gotoxy(2,wherey());
				cout<<"Total amount: Rs."<<(i * p)<<"."<<endl;
				itoa(j,x,10);
				strcpy(mr.inStock,x);
				stock.insert(mr);
				this->display("Thank you For Shopping.");
			}else{
				this->display("Out of stock!");
			}
			getch();
		}
		fflush(stdout);level = 3;
	};
};
class DisplayMed: private TabularPage {
public:
	void start(){
		this->columnsD[0] = 14;this->columnsD[1] = 28;
		this->columnsD[2] = 41;this->columnsD[3] = 54;
		this->columnsD[4] = 67;
		this->columns[0] = 3;this->columns[1] = 16;
		this->columns[2] = 30;this->columns[3] = 43;
		this->columns[4] = 56;this->columns[5] = 69;
		this->intial();
		char *h[] = {"ID","Name","MRP","MFD","EXP","In Stock"};
		this->setHeaders(h);
		medicineRecord mr;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(mr)){
		char *a[] = {mr.id,mr.name,mr.mrp,mr.mfg,mr.exp,mr.inStock};this->add(a);
		}
		this->terminate();
		if(strcmp(currentUsername,"anonymous") == 0) level = 3;
		else level = 4;
		fflush(stdout);
	};
};
class AddMed: private EditPage {
	char * getCom(char * d){
		char *i;
		do{ i = this->get(d); }while(i[0] == '\0');
		fflush(stdin);return i;
	}
	char * getNum(char * d){
		char *i;
		do{ i = this->get(d); }while(i[0] == '\0' || atoi(i)== 0);
		fflush(stdin);return i;
	}
	char * getNumDefault(char * d,char *g){
		char *i;
		do{ i = this->getDefault(d,g); }while(i[0] == '\0' || atoi(i)== 0);
		fflush(stdin);return i;
	}
public:
	void start(){
		this->intial();
		medicineRecord m;
		char *z = this->getNumDefault("Enter Id",stock.getNextID());
		while(stock.isMedID(z)){
			this->display("This id is already been used.");
			z = this->getNumDefault("Enter Id",stock.getNextID());
		}
		strcpy(m.id,z);
		strcpy(m.name,this->getCom("Enter name of med: "));
		strcpy(m.mrp,this->getNum("Enter price of med: "));
		strcpy(m.mfg,this->getNum("Enter date of med made: "));strcat(m.mfg,"/");
		strcat(m.mfg,this->getNum("Enter month of med made: "));strcat(m.mfg,"/");
		strcat(m.mfg,this->getNum("Enter year of med made: "));
		strcpy(m.exp,this->getNum("Enter date of med will expire: "));strcat(m.exp,"/");
		strcat(m.exp,this->getNum("Enter month of med will expire: "));strcat(m.exp,"/");
		strcat(m.exp,this->getNum("Enter year of med will expire: "));
		strcpy(m.inStock,this->getNum("Enter number of med present in stock(min 1): "));
		stock.insert(m);
		level = 4;
		fflush(stdout);
	};
};
class DeleteMed: private EditPage {
public:
	void start(){
		this->intial();
		this->display("1.by Id.");
		this->display("2.by Name.");
		char * i = this->getDefault("Enter ","1");
		int j = atoi(i);
		if(j == 2){
			this->display("Leave the Med name blank for exit.");
			char * u = this->get("Enter Med name:");
			if(u[0] == '\0'){level = 4; return;	}
			while(!stock.isMedName(u)){
				this->display("Med name not found.");
				char * u = this->get("Please Re-Enter Med name:");
				if(u[0] == '\0'){level = 4;	return;	}
			}
			stock.removeStockName(u);
		}else{
			this->display("Leave the Med ID blank for exit.");
			char * u = this->get("Enter Med ID:");
			if(u[0] == '\0'){level = 4;	return;	}
			while(!stock.isMedID(u)){
				this->display("Med ID not found.");
				char * u = this->get("Please Re-Enter Med ID:");
				if(u[0] == '\0'){level = 4;	return;}
			}
			stock.removeStockID(u);
		}
		fflush(stdout);level = 4;
	};
};
class EditMed: private EditPage {
	char * getNumDefault(char * d,char *g){
		char *i;
		do{
			i = this->getDefault(d,g);
		}while(i[0] == '\0' || (atoi(i)== 0 && strcmp(i,g) != 0));
		fflush(stdin);return i;
	}
public:
	void start(){
		this->intial();
		this->display("Leave the Med ID blank for exit.");
		char * u = this->get("Enter Med ID:");
		if(u[0] == '\0'){level = 4;	return;}
		while(!stock.isMedID(u)){
			this->display("Med ID not found.");
			char * u = this->get("Please Re-Enter Med ID:");
			if(u[0] == '\0'){level = 4;return;}
		}
		medicineRecord mr;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(mr)){
			if(strcmp(mr.id,u) == 0){break;}
		}
		stock.removeStockID(mr.id);
		strcpy(mr.id,this->getNumDefault("Enter new Id",mr.id));
		strcpy(mr.name,this->getDefault("Enter new Name",mr.name));
		strcpy(mr.mrp,this->getNumDefault("Enter new Price",mr.mrp));
		char * pch[3];
		sepDate(pch,mr.mfg);
		strcpy(mr.mfg,this->getDefault("Enter new mfg Date",pch[0]));strcat(mr.mfg,"/");
		strcat(mr.mfg,this->getDefault("Enter new mfg Month",pch[1]));strcat(mr.mfg,"/");
		strcat(mr.mfg,this->getDefault("Enter new mfg Year",pch[2]));
		sepDate(pch,mr.exp);
		strcpy(mr.exp,this->getDefault("Enter new exp Date",pch[0]));strcat(mr.exp,"/");
		strcat(mr.exp,this->getDefault("Enter new exp Month",pch[1]));strcat(mr.exp,"/");
		strcat(mr.exp,this->getDefault("Enter new exp Year",pch[2]));
		strcpy(mr.inStock,this->getNumDefault("Enter number of item in stock(min 1)",mr.inStock));
		stock.insert(mr);
		fflush(stdout);
		level = 4;
	};
};
class SearchMed: private EditPage {
public:
	void start(){
		this->intial();
		this->display("1.by Id.");
		this->display("2.by Name.");
		char * i = this->getDefault("Enter ","1");
		int j = atoi(i),c = 0 ;
		medicineRecord mr;
		if(j == 2){
			this->display("Leave the Med name blank for exit.");
			char * u = this->get("Enter Med name:");
			if(u[0] == '\0'){level = 4;return;}
			while(!stock.isMedName(u)){
				this->display("Med name not found.");
				char * u = this->get("Please Re-Enter Med name:");
				if(u[0] == '\0'){level = 4;return;}
			}
			stock.recordsFile.seekg(0,ios::beg);
			while(stock.getNext(mr)){
				if (strcmp(mr.name, u) == 0) { c = 1;break; }
			}
		}else{
			this->display("Leave the Med ID blank for exit.");
			char * u = this->get("Enter Med ID:");
			if(u[0] == '\0'){level = 4;	return;	}
			while(!stock.isMedID(u)){
				this->display("Med ID not found.");
				char * u = this->get("Please Re-Enter Med ID:");
				if(u[0] == '\0'){level = 4;return;}
			}
			stock.recordsFile.seekg(0,ios::beg);
			while(stock.getNext(mr)){
				if(strcmp(mr.id,u) == 0){c = 1;break;}
			}
		}
		clrscr();
		border.displayBorder(1);gotoxy(2,2);
		if(c == 1){
			gotoxy(2,wherey());
			cout<<"ID: "<<mr.id<<endl;
			gotoxy(2,wherey());
			cout<<"Name: "<<mr.name<<endl;
			gotoxy(2,wherey());
			cout<<"Price: "<<mr.mrp<<endl;
			gotoxy(2,wherey());
			cout<<"Date Of Manufacture: "<<mr.mfg<<endl;
			gotoxy(2,wherey());
			cout<<"Expire Date: "<<mr.exp<<endl;
			gotoxy(2,wherey());
			cout<<"Medicine present in Stock: "<<mr.inStock<<endl;
		}else{cout<<"Not found.";}
		getch();
		level = 4;
		fflush(stdout);
	};
};
class OutMed: public TabularPage {
public:
	void start(){
		this->columnsD[0] = 14;this->columnsD[1] = 28;
		this->columnsD[2] = 41;this->columnsD[3] = 54;
		this->columnsD[4] = 67;
		this->columns[0] = 3;this->columns[1] = 16;
		this->columns[2] = 30;this->columns[3] = 43;
		this->columns[4] = 56;this->columns[5] = 69;
		this->intial();
		char *h[] = {"ID","Name","MRP","MFD","EXP","In Stock"};
		this->setHeaders(h);
		medicineRecord mr;
		stock.recordsFile.seekg(0,ios::beg);
		while(stock.getNext(mr)){
			char *a[] = {mr.id,mr.name,mr.mrp,mr.mfg,mr.exp,mr.inStock};
			if(atoi(mr.inStock) == 0){this->add(a);}
		}
		this->terminate();
		level = 4;
		fflush(stdout);
	};
};
class ChangeUsername: private EditPage {
public:
	void start(){
		this->intial();
		userID uid;
		user.userFile.seekg(0,ios::beg);
		while(user.getNext(uid)){
			if(strcmp(uid.username,currentUsername) == 0){break;}
		}

		this->display("Leave the username blank for exit.");
		char * u = this->get("Enter New Username:");
		if(u[0] == '\0'){level = 5;return;}
		while(user.isUser(u)){
			this->display("Username is already in use.");
			char * u = this->get("Please Re-Enter New Username:");
			if(u[0] == '\0'){level = 5;return;}
		}

		user.removeUser(currentUsername);
		user.insert(u,uid.password);
		strcpy(currentUsername,u);
		fflush(stdout);
		level = 5;
	}
};
class ChangePassword: private EditPage {
public:
	void start(){
		this->intial();
		userID uid;
		user.userFile.seekg(0,ios::beg);
		while(user.getNext(uid)){
			if(strcmp(uid.username,currentUsername) == 0){break;}
		}
		user.removeUser(uid.username);
		user.insert(uid.username,this->getDefault("Enter Password",uid.password));
		if(strcmp(uid.username,"admin")==0)
			level = 3;
		else
			level = 5;
		fflush(stdout);
	}
};
class DisplayUser: private TabularPage {
public:
	void start(){
		this->columnsD[0] = 40;
		this->columns[0] = 3;this->columns[1] = 43;
		this->intial();
		char *h[] = {"Username","Password"};
		this->setHeaders(h);
		userID uid;
		user.userFile.seekg(0,ios::beg);
		while(user.getNext(uid)){
			char *a[] = {uid.username,uid.password};
			this->add(a);
		}
		this->terminate();
		level = 6;
		fflush(stdout);
	};
};
class SiginPage: public Page{
	char username[32];
	char password[32];
	char repassword[32];
	int wrongStat;
	int valid;
	void getInput(char * u,int h = 0){
		int i = 0,l = 0;
		while(1){
			i = getch();
			while(!isalnum(i)){
				if(i == 8 || i == 13) break;
				this->error(3);
				i = getch();
			}
			if(i == 13)	break;
			if(i == 8 && l>0){
				gotoxy(wherex()-1,wherey());
				cout<<" ";
				gotoxy(wherex()-1,wherey());
				l--;
				continue;
			}
			if(i == 8) continue;
			if(l >= 32){this->error(4);	continue;}

			u[l] = (char)i;
			if(h == 1)
				cout<<"*";
			else
				cout<<u[l];
			l++;
		}
		u[l] = '\0';
		fflush(stdin);
	};
	void getUsername(){
console.writexyn(" ",(int)((textWidth-strlen(this->str[4]))/2 + 9),(textHeight-(this->length+this->neglength))/2+(4)+this->startH,32);
gotoxy((int)((textWidth-strlen(this->str[4]))/2 + 9),(textHeight-(this->length+this->neglength))/2+(4)+this->startH);
		this->getInput(this->username);
		if(this->username[0] == '\0')
			this->error(1);
		else if(!user.isUser(this->username))
			this->valid = 1;
		else
			this->error(6);
	};
	void getPassword(){
console.writexyn(" ",(int)((textWidth-strlen(this->str[5]))/2 + 9),(textHeight-(this->length+this->neglength))/2+(5)+this->startH,32);
console.writexyn(" ",(int)((textWidth-strlen(this->str[6]))/2 + 17),(textHeight-(this->length+this->neglength))/2+(6)+this->startH,32);
gotoxy((int)((textWidth-strlen(this->str[5]))/2 + 9),(textHeight-(this->length+this->neglength))/2+(5)+this->startH);
		this->getInput(this->password,1);
		if(this->password[0] == '\0')
			this->error(2);
		else if(strlen(this->password) < 4)
			this->error(5);
		else
			this->valid = 1;
		if(this->valid == 1)
			this->getRePassword();
	};
	void getRePassword(){
		this->valid = 0;
		console.writexyn(" ",(int)((textWidth-strlen(this->str[6]))/2 + 17),(textHeight-(this->length+this->neglength))/2+(6)+this->startH,32);
		gotoxy((int)((textWidth-strlen(this->str[6]))/2 + 17),(textHeight-(this->length+this->neglength))/2+(6)+this->startH);
		this->getInput(this->repassword,1);
		if(strcmp(this->password,this->repassword) != 0)
			this->error(7);
		else
			this->valid = 1;
		while(this->valid == 0)
			this->getPassword();
	};
	void error(int e){
		int x = wherex(),y = wherey(),
			x1 = (textWidth-42)/2,
			y1 = (textHeight-(this->length+this->neglength))/2 + this->startH + 2;
		if(e == this->wrongStat)
			return ;
		if(e == 1)
			console.writexy("            Username is blank!            ",x1,y1);
		else if(e == 2)
			console.writexy("            Password is blank!            ",x1,y1);
		else if(e == 3)
			console.writexy("     Symbols, spaces are not allowed.     ",x1,y1);
		else if(e == 4)
			console.writexy("    It should not exceed 32 character!    ",x1,y1);
		else if(e == 5)
			console.writexy("    Password length must be 4 or more!    ",x1,y1);
		else if(e == 6)
			console.writexy("  Sorry! Username has already been used.  ",x1,y1);
		else if(e == 7)
			console.writexy("Password and re-type password don't match!",x1,y1);
		this->wrongStat = e;
		gotoxy(x,y);
	};
public:
	int admin;
	SiginPage(){
		this->length = 0;
		this->neglength = 0;
		this->startH = 0;
		this->noAnimation = 0;
		this->username[0] = '\0';
		this->password[0] = '\0';
		this->repassword[0] = '\0';
		this->admin = 0;
		this->wrongStat = 0;
		this->valid = 0;
	};
	void start(){
		if(this->admin == 1)
			strcpy(this->username,"admin");		
		clrscr();
		border.displayBorder();
		if(this->admin == 1)
			this->add("admin Sign in");
		else
			this->add("Sign in");
		this->add(" ");
		this->add(" ");
		this->add(" ");
		if(this->admin == 1)
			this->add("Username:admin                ");
		else
			this->add("Username:                     ");
		this->add("Password:                     ");
		this->add("Re-type password:                            ");
		if(this->admin == 1)
			this->add("* \"admin\" account is the highest authoritative account. it can't be deleted.",2,windowHeight-1);
		this->displayCenter();
		while(this->valid == 0){
			if(this->admin == 1)
				break;
			else
				this->getUsername();
		}
		this->valid = 0;
		while(this->valid == 0)
			this->getPassword();
		user.insert(this->username,this->password);
		if(this->admin == 1){
			strcpy(currentUsername,this->username);
			level = 3;
		}else{level = 6;}
		fflush(stdout);
	};
};
class EditUser: private EditPage {
public:
	void start(){
		this->intial();
		this->display("Leave the username blank for exit.");
		char * u = this->get("Enter Username:");
		if(u[0] == '\0'){level = 6;return;}
		while(!user.isUser(u)){
			this->display("Username not found.");
			char * u = this->get("Please Re-Enter Username:");
			if(u[0] == '\0'){level = 6;return;}
		}
		userID uid;
		user.userFile.seekg(0,ios::beg);
		while(user.getNext(uid))
			if(strcmp(uid.username,u) == 0) break;
		user.removeUser(uid.username);
		user.insert(uid.username,this->getDefault("Enter Password",uid.password));
		level = 6;
		fflush(stdout);
	};
};
class DeleteUser: private EditPage {
public:
	void start(){
		this->intial();
		this->display("Leave the username blank for exit.");
		char * u = this->get("Enter Username:");
		if(u[0] == '\0'){level = 6;return;}
		while(!user.isUser(u)){
			this->display("Username not found.");
			char * u = this->get("Please Re-Enter Username:");
			if(u[0] == '\0'){level = 6;return;}
		}
		if(strcmp(u,"admin") != 0) user.removeUser(u);
		level = 6;
		fflush(stdout);
	}
};
void processing(){
	while(level != -1){
		if(level == 0){Welcome i;              i.start();
		}else if(level == 1){SiginPage i;
			i.admin = 1;
			i.start();
			UserAuthority = 2;
		}else if(level == 2){ Login i;         i.start();
		}else if(level == 3){ MainPage i;      i.start();
		}else if(level == 4){ StockPage i;     i.start();
		}else if(level == 5){ UserPage i;      i.start();
		}else if(level == 6){ UserManagePage i;i.start();
		}else if(level == 7){ DisplayMed i;    i.start();
		}else if(level == 8){ AddMed i;        i.start();
		}else if(level == 9){ DeleteMed i;     i.start();
		}else if(level == 10){EditMed i;       i.start();
		}else if(level == 11){SearchMed i;     i.start();
		}else if(level == 12){OutMed i;        i.start();
		}else if(level == 13){ChangeUsername i;i.start();
		}else if(level == 14){ChangePassword i;i.start();
		}else if(level == 15){DisplayUser i;   i.start();
		}else if(level == 16){SiginPage i;     i.start();
		}else if(level == 17){EditUser i;      i.start();
		}else if(level == 18){DeleteUser i;    i.start();
		}else if(level == 19){BuyMed i;        i.start();
		}else{level = -1;}
		fflush(stdin);fflush(stdout);
	};
}
void main(){processing();}
