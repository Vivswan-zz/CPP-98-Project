#ifndef CLASS_PAGE_H_
#define CLASS_PAGE_H_

class Page{
	protected:
	public:
		char str[25][100];
		int x[25];
		int y[25];
		long long int length;
		long long int neglength;
		long long int noAnimation;
		int startH;
		Page(){
			this->length = 0;
			this->neglength = 0;
			this->startH = 0;
			this->noAnimation = 0;
			for(int i=0; i < 25; i++){
				x[i] = y[i] = 0;
				str[i][0] = '\0';
			}
		};
		void add(char * s,int x = 0, int y = 0){
			strcpy(this->str[this->length],s);
			this->x[this->length] = x;
			this->y[this->length] = y;
			this->length++;
			if(x != 0 || y != 0)
				this->neglength--;
		};
		void displayCenter(){
			int startH = (textHeight - (this->length + this->neglength))/2 + this->startH;
			for(long long int i=0; i < this->length; i++){
				if(this->x[i] == 0 && this->y[i] == 0){
					gotoxy((int)((textWidth - strlen(this->str[i]))/2),startH);
					if(this->noAnimation == 0)
						console.write(this->str[i]);
					else
						cout<<this->str[i];
					startH++;
				}else{
					gotoxy(this->x[i],this->y[i]);
					if(this->noAnimation == 0)
						console.write(this->str[i]);
					else
						cout<<this->str[i];
				}
			}
			fflush(stdout);
		};
};

#endif
