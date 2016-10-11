#ifndef CLASS_CONSOLE_H_
#define CLASS_CONSOLE_H_

class Console {
public:
	void write(char * u){
		for(int j=0;j < strlen(u);j++){
			cout<<u[j];
			if(u[j]!=' ')
				delay(10);
		}
		fflush(stdout);
	};
	void writexy(char * u,int x,int y){
		gotoxy(x,y);
		this->write(u);
		fflush(stdout);
	};
	void writexyn(char * u,int x,int y,int n){
		gotoxy(x,y);
		for(int i=0;i < n;i++)
			this->write(u);
		fflush(stdout);
	};
}console;

#endif
