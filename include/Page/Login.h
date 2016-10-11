#ifndef LOGIN_PAGE_H_
#define LOGIN_PAGE_H_

class Login:public Page{
		char username[50];
		char password[50];
		int wrongStat;
		int nextPageId;
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
					cout<<"*";
					i = getch();
					l++;
				}
			}
			this->password[l] = '\0';
			fflush(stdin);
		};
		void checkID(){
			if(this->username[0] == '\0' && this->password[0] == '\0'){
				strcpy(currentUsername,"anonymous");
				UserAuthority = 0;
				level = 3;
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
				if(strcmp(this->username,"admin") == 0){
					UserAuthority = 2;
				}else{
					UserAuthority = 1;
				}
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
			this->length = 0;
			this->neglength = 0;
			this->startH = 0;
			this->noAnimation = 0;
			this->nextPageId = 0;
			this->wrongStat = 0;
			this->username[0] = '\0';
			this->password[0] = '\0';
			currentUsername[0] = '\0';
		};
		void start(){
			clrscr();
			border.displayBorder();

			this->add("Login");
			this->add(" ");
			this->add(" ");
			this->add(" ");
			this->add("Username:                        ");
			this->add("Password:                        ");
			this->add("* For anonymous users leave username and password blank. ",2,windowHeight-1);

			this->displayCenter();
			while(this->nextPageId == 0){
				this->getID();
				this->checkID();
			}
			fflush(stdout);
		};
};

#endif
