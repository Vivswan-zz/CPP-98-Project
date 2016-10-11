#ifndef BUYMED_PAGE_H_
#define BUYMED_PAGE_H_

class BuyMed: private EditPage {
	public:
		void start(){
			this->intial();
			this->display("Leave the Med ID blank for exit.");
			char * u = this->get("Enter Med ID:");
			if(u[0] == '\0'){
				level = 3;
				return;
			}
			while(!stock.isMedID(u)){
				this->display("Med ID not found.");
				char * u = this->get("Please Re-Enter Med ID:");
				if(u[0] == '\0'){
					level = 3;
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

			char *x;
			strcpy(x,this->get("Enter number of item in stock:"));
			if(x[0] != '\0'){
				int i = atoi(x),j = atoi(mr.inStock),p = atoi(mr.mrp);
				i = j - i >= 0 ? i : -1;
				j = j - i;
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
			fflush(stdout);
			level = 3;
		};
};

#endif
