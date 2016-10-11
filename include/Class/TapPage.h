#ifndef CLASS_TAPPAGE_H_
#define CLASS_TAPPAGE_H_

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
			gotoxy((int)((textWidth-strlen(this->str[this->length - 1]))/2 + 18),(textHeight-(this->length+this->neglength))/2+(this->length+this->neglength-1)+this->startH);
			char a[2];
			a[0] = getch();
			a[1] = '\0';
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
				level = this->tap[this->nextPageId];
				this->nextPageId = 1;
			}
		};

		void addTap(int i,int j){this->tap[i] = j;};
};

#endif

