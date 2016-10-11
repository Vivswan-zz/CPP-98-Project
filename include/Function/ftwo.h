#ifndef FUNCTION_TWO_H_
#define FUNCTION_TWO_H_

void processing(){
	while(level != -1){
		if(level == 0){
			Welcome i;         i.start();
		}else if(level == 1){
			SiginPage i;
			i.admin = 1;
			i.start();
			UserAuthority = 2;
		}else if(level == 2){
			Login i;           i.start();
		}else if(level == 3){
			MainPage i;        i.start();
		}else if(level == 4){
			StockPage i;       i.start();
		}else if(level == 5){
			UserPage i;        i.start();
		}else if(level == 6){
			UserManagePage i;  i.start();
		}else if(level == 7){
			DisplayMed i;      i.start();
		}else if(level == 8){
			AddMed i;          i.start();
		}else if(level == 9){
			DeleteMed i;       i.start();
		}else if(level == 10){
			EditMed i;         i.start();
		}else if(level == 11){
			SearchMed i;       i.start();
		}else if(level == 12){
			OutMed i;          i.start();
		}else if(level == 13){
			ChangeUsername i;  i.start();
		}else if(level == 14){
			ChangePassword i;  i.start();
		}else if(level == 15){
			DisplayUser i;     i.start();
		}else if(level == 16){
			SiginPage i;       i.start();
		}else if(level == 17){
			EditUser i;        i.start();
		}else if(level == 18){
			DeleteUser i;      i.start();
		}else if(level == 19){
			BuyMed i;          i.start();
		}else{
			level = -1;
		}
		fflush(stdin);fflush(stdout);
	};
}

#endif
