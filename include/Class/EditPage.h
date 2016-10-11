#ifndef CLASS_EDITPAGE_H_
#define CLASS_EDITPAGE_H_

class EditPage {
	public:
		void intial(){
			clrscr();
			border.displayBorder();
			gotoxy(2,2);
		};
		void reintial(){
			if(wherey() >= windowHeight){
				clrscr();
				border.displayBorder(1);
				gotoxy(2,2);
			}
		};
		void display(char * d){
			gotoxy(2,wherey());
			console.write(d);
			cout<<endl;
			this->reintial();
			fflush(stdout);
		};
		char * get(char * d){
			gotoxy(2,wherey());
			char *i;
			console.write(d);
			gets(i);
			cout<<endl;
			this->reintial();
			fflush(stdin);
			return i;
		};
		char * getDefault(char * d,char * g){
			gotoxy(2,wherey());
			char *i;
			console.write(d);console.write("(");
			console.write(g);console.write(") :");
			gets(i);
			cout<<endl;
			this->reintial();
			fflush(stdin);
			return i[0] == '\0'? g : i;
		};
};

#endif
