#ifndef FUNCTION_ONE_H_
#define FUNCTION_ONE_H_

char * getDateString(){
	  time_t rawtime;
	  struct tm * timeinfo;
	  char* buffer;
	  time (&rawtime);
	  timeinfo = localtime (&rawtime);
	  strftime (buffer,80,"%d-%m-%Y",timeinfo);
	  return buffer;
}

char * getTimeString(){
	  time_t rawtime;
	  struct tm * timeinfo;
	  char* buffer;
	  time (&rawtime);
	  timeinfo = localtime (&rawtime);
	  strftime (buffer,80,"%H:%M",timeinfo);
	  return buffer;
}

void sepDate(char * pch[3],char * d){
	int j = 0,k = 0;
	for(int i = 0;i < strlen(d);i++){
		if(d[i] == '/'){
			pch[k][j] = '\0';
			j = 0;k++;
			continue;
		}
		pch[k][j] = d[i];j++;
	}
	pch[k][j] = '\0';
}

#endif
