#ifndef INITAL_H_
#define INITAL_H_

#define UDFaddress "userData"
#define RFaddress "record"
#define DELAYBORDER 5

struct userID{char username[33];char password[33];};
struct medicineRecord{
	char id[11];
	char name[11];
	char mfg[11];
	char exp[11];
	char mrp[6];
	char inStock[6];
};

//UserAuthority 0 : anonymous
//				1 : user
//				2 : admin
//level -1: exit
//		 0: Welcome
//		 1: First login
//		 2: Login
//		 3: Main page
//		 4: Medicine
//		 5: User Details
//		 6: User Management
//		 7: Display medicine
//		 8: Add medicine
//		 9: Delete medicine
//		 10: Edit medicine
//		 11: Search medicine
//		 12: Out of Stock
//		 13: Change Username
//		 14: Change Password
//		 15: Display User
//		 16: Add User
//		 17: Edit User
//		 18: Delete User
//$		 19: Buy medicine
int windowHeight = 24;
int windowWidth = 80;
int textHeight = windowHeight - 2;
int textWidth = windowWidth - 2;
int displayBorderAni = 0;
int UserAuthority = 0,level = 0;
char currentUsername[32];


#endif
