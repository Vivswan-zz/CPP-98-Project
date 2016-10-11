#ifndef CLASS_TABLE_PAGE_H_
#define CLASS_TABLE_PAGE_H_

class TabularPage {
	public:
		int columnsD[10];
		int columns[10];
		int column;
		int row;

		TabularPage(){
			for(int i = 0;i < textWidth;i++)
				this->columnsD[i] = this->columns[i] = 0;
			this->row = 4;
			this->column = 0;
		};
		void setHeaders(char * a[]){
			for(int i = 0;i < this->column; i++)
				console.writexy(a[i],this->columns[i],2);
		};
		void add(char * a[]){
			for(int i = 0;i < this->column; i++)
				console.writexy(a[i],this->columns[i],this->row);
			this->row++;
			if(this->row == windowHeight){
				getch();
				this->row = 4;
				while(this->row != windowHeight){
					for(int i = 0;i < this->column; i++){
						console.writexyn(" ",this->columns[i],this->row,i == 0?this->columns[i+1]-7:this->columns[i] - this->columns[i-1]-3);
					}
					this->row++;
				}
				this->row = 4;
			}
		};
		void intial(){
			clrscr();
			border.displayBorder();
			gotoxy(2,3);
			int i;
			for(i = 0;i < textWidth;i++){
				delay(5);cout<<"-";
			}
			for(i = 0;i < 10 && this->columnsD[i] != 0;i++){
				for(int j = 1;j <= textHeight;j++){
					gotoxy(this->columnsD[i],j+1);
					delay(5);cout<<"|";
				}
				this->column++;
			}
			this->column++;
		};
		void terminate(){getch();};
};

#endif
