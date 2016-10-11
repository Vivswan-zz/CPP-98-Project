#ifndef CLASS_FILES_H_
#define CLASS_FILES_H_

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
		int c = 0;
		userID uid;
		this->userFile.seekg(0,ios::beg);
		while(this->getNext(uid)){
			if(strcmp(uid.username,u) == 0){
				c = 1;
				break;
			}
		}
		if(c == 1){
			c = strlen(uid.username) + strlen(uid.password) + 2;
			this->userFile.seekg(-c,ios::cur);
			for(int i=0;i < c;i++){
				this->userFile<<" ";
			}
		}
		this->userFile.flush();this->userFile.sync();
	};
	int isUser(char * u){
		userID uid;
		int c = 0;
		this->userFile.seekg(0,ios::beg);
		while(this->getNext(uid)){
			if(strcmp(uid.username,u) == 0){
				c = 1;
				break;
			}
		}
		return c;
	};
	int check(char * u,char * p){
		userID uid;
		int c = 0;
		this->userFile.seekg(0,ios::beg);
		while(this->getNext(uid)){
			if(strcmp(uid.username,u) == 0){
				c = (strcmp(uid.password,p) == 0);
				break;
			}
		}
		return c;
	};
	int getNext(userID & uid){
		char a;
		int i = 0,j = 0,c = 0;
		while(c == 0){
			this->userFile.get(a);
			if(a == ' ')
				continue;
			if(a == '?')
				break;
			if(a == ';'){
				c = 1;
				uid.password[i] = '\0';
				break;
			}
			if(a == ':'){
				uid.username[i] = '\0';
				j++;
				i = 0;
				continue;
			}
			if(j == 0)
				uid.username[i] = a;
			else
				uid.password[i] = a;
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
					for(int i=0;i < c;i++)
						this->recordsFile<<" ";
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
					for(int i=0;i < c;i++)
						this->recordsFile<<" ";
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
			if (this->isEmpty()) {
				return 0;
			}
			char a;
			int i = 0, j = 0, c = 0;
			while(c == 0){
				this->recordsFile.get(a);
				if(a == ' ')
					continue;
				if(a == '?')
					break;
				if(a == ';'){
					c = 1;
					mr.inStock[i] = '\0';
					break;
				}
				if(a == ':')
					a = '\0';
				if(j == 0)
					mr.id[i] = a;
				else if(j == 1)
					mr.name[i] = a;
				else if(j == 2)
					mr.mrp[i] = a;
				else if(j == 3)
					mr.mfg[i] = a;
				else if(j == 4)
					mr.exp[i] = a;
				else if(j == 5)
					mr.inStock[i] = a;
				i++;
				if(a == '\0'){
					i = 0;j++;
				}
			}
			return c;
		};
		char * getNextID(){
			int max = 0;
			medicineRecord mr;
			stock.recordsFile.seekg(0,ios::beg);
			while(stock.getNext(mr)){
				if(max < atoi(mr.id)){max = atoi(mr.id);}
			}
			max++;
			char * a;itoa(max,a,10);
			return a;
		};
}stock;

#endif
