#ifndef CLASS_BORDER_H_
#define CLASS_BORDER_H_

class Border{
	private:
		void bTLFirst(int c){
			if(c < windowWidth){
				gotoxy(c,1);
				cout<<this->bT;
			}else if(c == windowWidth){
				gotoxy(windowWidth,1);
				cout<<this->bTR;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(windowWidth,c-windowWidth+1);
				cout<<this->bR;
			}
			this->bTLSecond(c);
		};
		void bTLSecond(int c){
			int e = 1;
			if(c < windowHeight){
				gotoxy(1,c);
				cout<<this->bL;
			}else if(c == windowHeight){
				gotoxy(1,windowHeight);
				cout<<this->bBL;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(c-windowHeight+1,windowHeight);
				cout<<this->bB;
			}else
				e = 0;
			delay(DELAYBORDER);
			if(e == 1){
				c++;this->bTLFirst(c);
			}
		};
		void bTRFirst(int c){
			if(c < windowWidth){
				gotoxy(windowWidth - c + 1,1);
				cout<<this->bT;
			}else if(c == windowWidth){
				gotoxy(1,1);
				cout<<this->bTL;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(1,c - windowWidth + 1);
				cout<<this->bL;
			}
			this->bTRSecond(c);
		};
		void bTRSecond(int c){
			int e = 1;
			if(c < windowHeight){
				gotoxy(windowWidth,c);
				cout<<this->bR;
			}else if(c == windowHeight){
				gotoxy(windowWidth,windowHeight);
				cout<<this->bBR;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(windowWidth + windowHeight - c,windowHeight);
				cout<<this->bB;
			}else
				e = 0;
			delay(DELAYBORDER);
			if(e == 1){
				c++;this->bTRFirst(c);
			}
		};
		void bBRFirst(int c){
			if(c < windowHeight){
				gotoxy(windowWidth,windowHeight - c + 1);
				cout<<this->bR;
			}else if(c == windowHeight){
				gotoxy(windowWidth,1);
				cout<<this->bTR;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(windowWidth - (c - windowHeight),1);
				cout<<this->bT;
			}
			this->bBRSecond(c);
		};
		void bBRSecond(int c){
			int e = 1;
			if(c < windowWidth){
				gotoxy(windowWidth - c + 1,windowHeight);
				cout<<this->bB;
			}else if(c == windowWidth){
				gotoxy(1,windowHeight);
				cout<<this->bBL;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(1,windowHeight - c + windowWidth);
				cout<<this->bR;
			}else
				e = 0;
			delay(DELAYBORDER);
			if(e == 1){
				c++;this->bBRFirst(c);
			}
		};
		void bBLFirst(int c){
			if(c < windowWidth){
				gotoxy(c,windowHeight);
				cout<<this->bB;
			}else if(c == windowWidth){
				gotoxy(windowWidth,windowHeight);
				cout<<this->bBR;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(windowWidth,windowHeight - (c - windowWidth));
				cout<<this->bR;
			}
			this->bBLSecond(c);
		};
		void bBLSecond(int c){
			int e = 1;
			if(c < windowHeight){
				gotoxy(1,windowHeight - c + 1);
				cout<<this->bL;
			}else if(c == windowHeight){
				gotoxy(1,1);
				cout<<this->bTL;
			}else if(c < windowWidth + windowHeight - 1){
				gotoxy(c - windowHeight + 1,1);
				cout<<this->bT;
			}else
				e = 0;
			delay(DELAYBORDER);
			if(e == 1){
				c++;this->bBLFirst(c);
			}
		};
		void displayTLBorder(){
			gotoxy(1,1);cout<<this->bTL;
			delay(DELAYBORDER);
			this->bTLFirst(2);
			gotoxy(windowWidth,windowHeight);cout<<this->bBR;
		};
		void displayTRBorder(){
			gotoxy(windowWidth,1);cout<<this->bTR;
			delay(DELAYBORDER);
			this->bTRFirst(2);
			gotoxy(1,windowHeight);cout<<this->bBL;
		};
		void displayBRBorder(){
			gotoxy(windowWidth,windowHeight);cout<<this->bBR;
			delay(DELAYBORDER);
			this->bBRFirst(2);
			gotoxy(1,1);cout<<this->bTL;
		};
		void displayBLBorder(){
			gotoxy(1,windowHeight);cout<<this->bBL;
			delay(DELAYBORDER);
			this->bBLFirst(2);
			gotoxy(windowWidth,1);cout<<this->bTR;
		};
	public:
		char bTL;
		char bTR;
		char bBR;
		char bBL;
		char bT;
		char bR;
		char bB;
		char bL;
		Border(){
			this->bTL = 201;
			this->bTR = 187;
			this->bBR = 188;
			this->bBL = 200;
			this->bT = 205;
			this->bR = 186;
			this->bB = 205;
			this->bL = 186;
		};
		void displayBorder(int noAnimation = 0){
			if(noAnimation == 0){
				if(displayBorderAni == 0)
					this->displayTLBorder();
				else if(displayBorderAni == 1)
					this->displayTRBorder();
				else if(displayBorderAni == 2)
					this->displayBRBorder();
				else
					this->displayBLBorder();
				displayBorderAni++;
				if(displayBorderAni > 3)
					displayBorderAni = 0;
			}else{
				int i;
				gotoxy(1,1);
				cout<<this->bTL;
				gotoxy(windowWidth,1);
				cout<<this->bTR;
				gotoxy(1,windowHeight);
				cout<<this->bBL;
				gotoxy(windowWidth,windowHeight);
				cout<<this->bBR;
				for(i = 2;i<windowHeight;i++){
					gotoxy(1,i);
					cout<<this->bL;
					gotoxy(windowWidth,i);
					cout<<this->bR;
				}
				for(i = 2;i<windowWidth;i++){
					gotoxy(i,1);
					cout<<this->bT;
					gotoxy(i,windowHeight);
					cout<<this->bB;
				}
			}
			fflush(stdout);
		};
}border;

#endif
