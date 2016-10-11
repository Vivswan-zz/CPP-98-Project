#ifndef USER_DETAIL_PAGES_H_
#define USER_DETAIL_PAGES_H_

class ChangeUsername: private EditPage {
	public:
		void start(){
			this->intial();
			userID uid;
			user.userFile.seekg(0,ios::beg);
			while(user.getNext(uid)){
				if(strcmp(uid.username,currentUsername) == 0){
					break;
				}
			}

			this->display("Leave the username blank for exit.");
			char * u = this->get("Enter New Username:");
			if(u[0] == '\0'){
				level = 5;
				return;
			}
			while(user.isUser(u)){
				this->display("Username is already in use.");
				char * u = this->get("Please Re-Enter New Username:");
				if(u[0] == '\0'){
					level = 5;
					return;
				}
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
				if(strcmp(uid.username,currentUsername) == 0){
					break;
				}
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

#endif

