#ifndef TAP_PAGES_H_
#define TAP_PAGES_H_

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
		this->terminate();
		fflush(stdout);
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
		this->terminate();
		fflush(stdout);
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
		this->terminate();
		fflush(stdout);
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
		this->terminate();
		fflush(stdout);
	}
};

#endif
