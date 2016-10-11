#ifndef USER_MANAGE_PAGES_H_
#define USER_MANAGE_PAGES_H_

class DisplayUser: private TabularPage {
	public:
		void start(){
			this->columnsD[0] = 40;
			this->columns[0] = 3;
			this->columns[1] = 43;
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
					if(i == 8 || i == 13)
						break;
					this->error(3);
					i = getch();
				}

				if(i == 13)
					break;

				if(i == 8 && l>0){
					gotoxy(wherex()-1,wherey());
					cout<<" ";
					gotoxy(wherex()-1,wherey());
					l--;
					continue;
				}
				if(i == 8)
					continue;
				if(l >= 32){
					this->error(4);
					continue;
				}

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
			int x = wherex(),
				y = wherey(),
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
			if(this->admin == 1){
				strcpy(this->username,"admin");
			}
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
			}else{
				level = 6;
			}
			fflush(stdout);
		};
};

class EditUser: private EditPage {
	public:
		void start(){
			this->intial();
			this->display("Leave the username blank for exit.");
			char * u = this->get("Enter Username:");
			if(u[0] == '\0'){
				level = 6;
				return;
			}
			while(!user.isUser(u)){
				this->display("Username not found.");
				char * u = this->get("Please Re-Enter Username:");
				if(u[0] == '\0'){
					level = 6;
					return;
				}
			}
			userID uid;
			user.userFile.seekg(0,ios::beg);
			while(user.getNext(uid)){
				if(strcmp(uid.username,u) == 0){
					break;
				}
			}
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
			if(u[0] == '\0'){
				level = 6;
				return;
			}
			while(!user.isUser(u)){
				this->display("Username not found.");
				char * u = this->get("Please Re-Enter Username:");
				if(u[0] == '\0'){
					level = 6;
					return;
				}
			}
			if(strcmp(u,"admin") != 0)
				user.removeUser(u);
			level = 6;
			fflush(stdout);
		}
};

#endif
