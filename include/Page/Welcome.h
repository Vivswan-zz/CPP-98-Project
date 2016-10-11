#ifndef WELCOME_PAGE_H_
#define WELCOME_PAGE_H_

class Welcome:public Page{
	public:
	void start(){
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
		if(user.isEmpty()){
			level = 1;
		}else{
			level = 2;
		}
		getch();
		fflush(stdout);
	}
};

#endif
