#ifndef MED_PAGES_H_
#define MED_PAGES_H_

class DisplayMed: private TabularPage {
	public:
		void start(){
			this->columnsD[0] = 14;
			this->columnsD[1] = 28;
			this->columnsD[2] = 41;
			this->columnsD[3] = 54;
			this->columnsD[4] = 67;
			this->columns[0] = 3;
			this->columns[1] = 16;
			this->columns[2] = 30;
			this->columns[3] = 43;
			this->columns[4] = 56;
			this->columns[5] = 69;
			this->intial();
			char *h[] = {"ID","Name","MRP","MFD","EXP","In Stock"};
			this->setHeaders(h);

			medicineRecord mr;
			stock.recordsFile.seekg(0,ios::beg);
			while(stock.getNext(mr)){
				char *a[] = {mr.id,mr.name,mr.mrp,mr.mfg,mr.exp,mr.inStock};
				this->add(a);
			}
			this->terminate();
			if(strcmp(currentUsername,"anonymous") == 0)
				level = 3;
			else
				level = 4;
			fflush(stdout);
		};
};

class AddMed: private EditPage {
	char * getCom(char * d){
		char *i;
		do{
			i = this->get(d);
		}while(i[0] == '\0');
		fflush(stdin);
		return i;
	}
	char * getNum(char * d){
		char *i;
		do{
			i = this->get(d);
		}while(i[0] == '\0' || atoi(i)== 0);
		fflush(stdin);
		return i;
	}
	char * getNumDefault(char * d,char *g){
		char *i;
		do{
			i = this->getDefault(d,g);
		}while(i[0] == '\0' || atoi(i)== 0);
		fflush(stdin);
		return i;
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

			strcpy(m.mfg,this->getNum("Enter date of med made: "));
			strcat(m.mfg,"/");
			strcat(m.mfg,this->getNum("Enter month of med made: "));
			strcat(m.mfg,"/");
			strcat(m.mfg,this->getNum("Enter year of med made: "));

			strcpy(m.exp,this->getNum("Enter date of med will expire: "));
			strcat(m.exp,"/");
			strcat(m.exp,this->getNum("Enter month of med will expire: "));
			strcat(m.exp,"/");
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
				if(u[0] == '\0'){
					level = 4;
					return;
				}
				while(!stock.isMedName(u)){
					this->display("Med name not found.");
					char * u = this->get("Please Re-Enter Med name:");
					if(u[0] == '\0'){
						level = 4;
						return;
					}
				}
				stock.removeStockName(u);
			}else{
				this->display("Leave the Med ID blank for exit.");
				char * u = this->get("Enter Med ID:");
				if(u[0] == '\0'){
					level = 4;
					return;
				}
				while(!stock.isMedID(u)){
					this->display("Med ID not found.");
					char * u = this->get("Please Re-Enter Med ID:");
					if(u[0] == '\0'){
						level = 4;
						return;
					}
				}
				stock.removeStockID(u);
			}
			fflush(stdout);
			level = 4;
		};
};

class EditMed: private EditPage {
	char * getNumDefault(char * d,char *g){
		char *i;
		do{
			i = this->getDefault(d,g);
		}while(i[0] == '\0' || (atoi(i)== 0 && strcmp(i,g) != 0));
		fflush(stdin);
		return i;
	}
	public:
		void start(){
			this->intial();
			this->display("Leave the Med ID blank for exit.");
			char * u = this->get("Enter Med ID:");
			if(u[0] == '\0'){
				level = 4;
				return;
			}
			while(!stock.isMedID(u)){
				this->display("Med ID not found.");
				char * u = this->get("Please Re-Enter Med ID:");
				if(u[0] == '\0'){
					level = 4;
					return;
				}
			}
			medicineRecord mr;
			stock.recordsFile.seekg(0,ios::beg);
			while(stock.getNext(mr)){
				if(strcmp(mr.id,u) == 0){
					break;
				}
			}
			stock.removeStockID(mr.id);
			strcpy(mr.id,this->getNumDefault("Enter new Id",mr.id));
			strcpy(mr.name,this->getDefault("Enter new Name",mr.name));
			strcpy(mr.mrp,this->getNumDefault("Enter new Price",mr.mrp));

			char * pch[3];
			sepDate(pch,mr.mfg);
			strcpy(mr.mfg,this->getDefault("Enter new mfg Date",pch[0]));
			strcat(mr.mfg,"/");
			strcat(mr.mfg,this->getDefault("Enter new mfg Month",pch[1]));
			strcat(mr.mfg,"/");
			strcat(mr.mfg,this->getDefault("Enter new mfg Year",pch[2]));

			sepDate(pch,mr.exp);
			strcpy(mr.exp,this->getDefault("Enter new exp Date",pch[0]));
			strcat(mr.exp,"/");
			strcat(mr.exp,this->getDefault("Enter new exp Month",pch[1]));
			strcat(mr.exp,"/");
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
				if(u[0] == '\0'){
					level = 4;
					return;
				}
				while(!stock.isMedName(u)){
					this->display("Med name not found.");
					char * u = this->get("Please Re-Enter Med name:");
					if(u[0] == '\0'){
						level = 4;
						return;
					}
				}
				stock.recordsFile.seekg(0,ios::beg);
				while(stock.getNext(mr)){
					if(strcmp(mr.name,u) == 0){
						c = 1;
						break;
					}
				}
			}else{
				this->display("Leave the Med ID blank for exit.");
				char * u = this->get("Enter Med ID:");
				if(u[0] == '\0'){
					level = 4;
					return;
				}
				while(!stock.isMedID(u)){
					this->display("Med ID not found.");
					char * u = this->get("Please Re-Enter Med ID:");
					if(u[0] == '\0'){
						level = 4;
						return;
					}
				}
				stock.recordsFile.seekg(0,ios::beg);
				while(stock.getNext(mr)){
					if(strcmp(mr.id,u) == 0){
						c = 1;
						break;
					}
				}
			}
			clrscr();
			border.displayBorder(1);
			gotoxy(2,2);
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
			}else{
				cout<<"Not found.";
			}
			getch();
			level = 4;
			fflush(stdout);
		};
};

class OutMed: public TabularPage {
	public:
		void start(){
			this->columnsD[0] = 14;
			this->columnsD[1] = 28;
			this->columnsD[2] = 41;
			this->columnsD[3] = 54;
			this->columnsD[4] = 67;
			this->columns[0] = 3;
			this->columns[1] = 16;
			this->columns[2] = 30;
			this->columns[3] = 43;
			this->columns[4] = 56;
			this->columns[5] = 69;
			this->intial();
			char *h[] = {"ID","Name","MRP","MFD","EXP","In Stock"};
			this->setHeaders(h);

			medicineRecord mr;
			stock.recordsFile.seekg(0,ios::beg);
			while(stock.getNext(mr)){
				char *a[] = {mr.id,mr.name,mr.mrp,mr.mfg,mr.exp,mr.inStock};
				if(atoi(mr.inStock) == 0){
					this->add(a);
				}
			}
			this->terminate();
			level = 4;
			fflush(stdout);
		};
};

#endif
