#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>
//#include<unistd.h>
#define SIZE 26
#define CHART_LENGTH 35
#define CHART_WIDTH 125

char chart[CHART_LENGTH][CHART_WIDTH];
int chartColor[CHART_LENGTH][CHART_WIDTH];
int i = 1; //linked list ccounter -> dipakai di generateChartContent()
bool isTradeActive = false;
bool isTradeOnGoing = false;
bool isLogOut = false;
int tradeStatus = -1;

struct transaction{
	int value;
	int position;
	int takeProfit;
	int stopLoss;
	int reward;
	transaction *next;
};

struct chartContent{
	int open;
	int lowest;
	int highest;
	int close;
	int color;
	chartContent *next;
	chartContent *prev;
}*head = NULL, *tail = NULL, *start = NULL;

struct userData{
	
	char username[50];
	char email[50];
	char password[50];
	int currency;
	transaction *data;
	userData *next;
	
	
}*list[SIZE], *user = NULL;

void mainMenu();
void mainMenuInput();

void logIn();
void registerAccount();
void exitApp();

int validateEmailLogIn(char email[]);
int validateEmailRegister(char email[]);
int validateUsername(char username[]);
int validatePassword(char password[]);
void error(char variable[], int errNum);

void userMenuPage();
void userMenuPageInput();
void homePage();
void homePageInput();
void generateChart();
void generateChartContent(chartContent *position); 
void printChart();

void newDay();
void previous();
void next();
void logOut();
void updateTransactionPositionBar();
void transactionPage(int status);
void longTransaction(int value, int position, int tp, int sl);
void shortTransaction(int value, int position, int tp, int sl);
void countReward(int reward);
void insertToHistory(transaction *new_data);
void viewTradeHistory();
void viewGuidePage();


transaction *createTransactionData(int value, int position,int takeProfit, int stopLoss,int reward);
userData *createHashData(char username[], char email[], char password[], int currency);
chartContent *createChart(int open, int lowest, int highest, int close, int color);
void insertToHashTable(char username[], char email[], char password[], int currency);
void insertToTxt(char username[], char email[], char password[], int currency);
void insertTxtToHashTable();
userData *search(char email[]);

void insertToTransaction(transaction *root, int value, int position,int takeProfit, int stopLoss,int reward);
void makeChartContent();
void insertContentToChart(int open, int close, int highest, int lowest,int color);

int countClosePrice(int open);
int countHighestPrice(int num);
int countLowestPrice(int num);

int hash(char username[]);
void updateTxt();

void print(){
	userData *curr;
	for(int i = 0; i < SIZE; i++){
		printf("%d. ", i+1);
		
		curr = list[i];
		while(curr){
			printf("%s - %s - %s - %d | ",curr->username, curr->email, curr->password, curr->currency);
			curr = curr->next;
		}
		if(curr == NULL){
			printf("NULL\n");
		}
	}
}


userData *cari(char name[]){
	
	int idx = hash(name);
	
	if(strcmp(list[idx]->username, name) == 0){
		return list[idx];
	}
	
	return NULL;
}

int main(){
	
//	insertTxtToHashTable();

//	while(1){
//		
//		
//		menuInput();
//	}

	
//	print();
//	generateChart();
//	printChart();

//	generateChart();
//	generateChartContent(start);
//	puts("");
////	printf("\nCurr content: %d %d\n", head->open,head->lowest);
//	printChart();
	
//	insertToHashTable("Hendra","hendra","1234",10000);
//	user = cari("Hendra");
//	homePageInput();
		insertTxtToHashTable();
		generateChart();
		generateChartContent(start);
	while(1){
		
		mainMenuInput();
		
	}
	
	
	
	
//	chartContent * curr = head;
//	puts("");
//	while(curr){
//		
//		printf("%d %d\n",curr->open, curr->close);
//		if(curr == tail)
//			printf(" tail\n");
//		curr = curr->next;
//	}
	//makeChartContent();

	
	return 0;
}

void mainMenu(){
	system("cls");
	printf("METAFI\n");
	printf("========================\n");
	printf("1. Log In to Trade\n");
	printf("2. Register Account\n");
	printf("3. Exit Application\n");
	

}
void mainMenuInput(){
	
	mainMenu();
	
	int in;
	
	do{
		printf(">> ");
		scanf("%d", &in);getchar();
		
	}while(in < 0 || in > 3);
	
	switch(in){
		case 1:
			logIn();
			break;
			
		case 2:
			registerAccount();
			break;
		
		case 3:
			exitApp();
			break;
			
	}
}

void userMenuPage(){
	system("cls");
	printf("MetaFi - User's Menu\n");
	printf("1. Start Trade\n");
	printf("2. Trade Hsitory\n");
	printf("3. Guide\n");
	printf("4. Log Out\n");

}

void userMenuPageInput(){
	userMenuPage();
	
	int in;
	do{
		printf(">> ");
		scanf("%d", &in);getchar();
	}while(in > 4 || in < 1);
	
	switch(in){
		case 1:
			homePageInput();
			break;
			
		case 2:
			viewTradeHistory();
			break;
		
		case 3:
			viewGuidePage();
			break;
		case 4:
			logOut();
			return;	
			
	}
}
int val, pos, tp, sl;
void homePage(){
	printf("1. New Day\t3. Next\t\t5. Short\t\tWelcome: %s\n", user->username);
	printf("2. Previous\t4. Long\t\t6.Log Out >> ");
	return;
}

void homePageInput(){
	
	while(1){
		system("cls");
		
		printChart();
		printf("\nValue: %d | POS: %d | TP: %d | SL: %d | Close: %d\t\t", val, pos,tp,sl,tail->close*10);
		printf("Trade Status: %s \033[0m| On Going: %s\t\t", isTradeActive == true? "\033[0;32mActive" : "\033[0;31mInactive", isTradeOnGoing == true? "\033[0;32mYes": "\033[0;31mNO");
		printf("\033[0mCurrency: $\033[0;36m%d\n\n", user->currency);
		
		printf("\033[0m");
		homePage();
		
		int in;
		
		do{
			scanf("%d",&in); getchar();
		}while(in < 1 || in> 6);
		
		switch(in){
			case 1:
				newDay();
				break;
			
			case 2:
				previous();
				break;
				
			case 3:
				next();
				break;
			
			case 4:
				if(isTradeOnGoing){
					printf("Another trade is still Active.."); getchar();
				}else{
					transactionPage(1);
				}
				
				break;
				
			case 5:
				if(isTradeOnGoing){
					printf("Another trade is still Active.."); getchar();
				}else{
					transactionPage(0);
				}
				break;
				
			case 6:
				logOut();
				return;
		}
	}
	
}


void newDay(){
	
	makeChartContent();
	updateTransactionPositionBar();
	generateChartContent(tail);
	
	if(tradeStatus == -1)
		return;
		
	else if(tradeStatus == 1){
		longTransaction(val,pos,tp,sl);
		
	}else if(tradeStatus == 0){
		shortTransaction(val,pos,tp,sl);
	}
	
	return;
	
}
void previous(){
	
	if(start == head){
		return;
	}
	
	start = start->prev;
	generateChart();
	memset(chartColor, -1, sizeof(chartColor));
	i = 1;
	updateTransactionPositionBar();
	generateChartContent(start);
	
	return;
}
void next(){
	
	if(start == tail){
		return;
	}
	
	start = start->next;
	generateChart();
	memset(chartColor, -1, sizeof(chartColor));
	updateTransactionPositionBar();
	i = 1;
	generateChartContent(start);
	
	return;
}

void logOut(){
//	userData *found = search(user->email);
//	found->data = queue;
	//user = NULL;
	//queue = NULL;
	updateTxt();
	isLogOut = true;
	return;
}
void updateTransactionPositionBar(){ 
	
	if(!isTradeOnGoing){
		return;
	}
	//int arr[] = {pos, sl, tp};
	int POS = 34 - (pos/10);
	int SL = 34 - (sl/10);
	int TP = 34 - (tp/10);
	for(int i = 1; i < CHART_WIDTH-1;i++){							
			
		if(chart[POS][i] == '-' ){
			chartColor[POS][i] = 3;
				
		}
		if(chart[TP][i] == '-' ){
			chartColor[TP][i] = 2;
			
		}
		if(chart[SL][i] == '-' ){
			chartColor[SL][i] = 4;
			
		}
			
			
	}
	
	
}
void transactionPage(int status){
		
	
	
	if(status == 1){
		
		do{
			printf("Value[10 - %d]: ", user->currency);
			scanf("%d", &val);getchar();
			
		}while(val < 10 || val > user->currency);
		
	
		do{
			printf("Position[20 - 320] [MULTIPLE OF TEN]: ");
			
			scanf("%d", &pos);getchar();
		}while(pos < 20 || pos > 320 || pos%10 != 0);
		
		
		do{
			printf("Take Profit[HIGHER THAN POSITION] [MULTIPLE OF TEN] [10 - 330]: ");
			scanf("%d", &tp);getchar();
			
		}while(tp < 10 || tp > 330 || tp <= pos || tp%10 != 0);
		
		
		do{
			printf("Stop Loss[LOWER THAN POSITION] [MULTIPLE OF TEN] [10 - 330]: ");
			scanf("%d", &sl); getchar();
		}while(sl < 10 || sl > 330 || sl >= pos || sl%10 != 0);
		//newDay();
		//longTransaction(val,pos,tp,sl);
		tradeStatus = 1;
	}
	
	else if(status == 0){
		
		
		do{
			printf("Value[10 - %d]: ", user->currency);
			scanf("%d", &val);getchar();
			
		}while(val < 10 || val > user->currency);
		
		
		do{
			printf("Position[20 - 320] [MULTIPLE OF TEN]: ");
			scanf("%d", &pos);getchar();
		}while(pos < 20 || pos > 320 || pos%10 != 0);
		
		
		do{
			printf("Take Profit[LOWER THAN POSITION] [MULTIPLE OF TEN] [10 - 330]: ");
			scanf("%d", &tp);getchar();
			
		}while(tp < 10 || tp > 330 || tp >= pos || tp%10 != 0);
		
		
		do{
			printf("Stop Loss[HIGHER THAN POSITION] [MULTIPLE OF TEN] [10 - 330]: ");
			scanf("%d", &sl); getchar();
		}while(sl < 10 || sl > 330 || sl <= pos || sl%10 != 0);
		//newDay();
		//shortTransaction(val,pos,tp,sl);
		tradeStatus = 0;
	}
	if((34-tail->close )== 34 - (pos/10) && isTradeActive == false){
		
		isTradeActive = true;
		
	}
	isTradeOnGoing = true;
	updateTransactionPositionBar();
	
}
void longTransaction(int value, int position, int tp, int sl){
	
	
	//isTradeOnGoing = true;
	
	
	if( (34-(pos/10) >= 34-tail->highest) && (34-(pos/10) <= 34-tail->lowest) && isTradeActive == false){
		isTradeActive = true;
		
	}
	
	
	if(isTradeActive == true){
		
		if((34-tail->highest) <= 34 - (tp/10)){
			
			int reward = (value * abs(tail->close*10 - pos)) / 100;
			countReward(reward);
			return;
		}
		
		else if((34-tail->lowest) >= 34 - (sl/10)){
			
			
			
			int reward = ((value * abs(tail->close*10- pos))/ 100) * -1;
			countReward(reward);
			return;
			
		}
	}
}

void shortTransaction(int value, int position, int tp, int sl){
	
	//isTradeOnGoing = true;
	
	
	if( (34-(pos/10) >= 34-tail->highest) && (34-(pos/10) <= 34-tail->lowest) && isTradeActive == false){
		isTradeActive = true;
		
	}
	
	
	if(isTradeActive == true){
		
		if((34-tail->highest) <= 34 - (sl/10)){
			
			int reward = ((value * abs(tail->close*10 - pos))/ 100) * -1;
			countReward(reward);
			return;
		}
		
		else if((34-tail->lowest) >= 34 - (tp/10)){
			
			
			int reward = (value * abs(tail->close*10 - pos)) / 100;
			countReward(reward);
			return;
			
		}
	}
	
}

void countReward(int reward){
	
	tradeStatus = -1;
	isTradeActive = false;
	isTradeOnGoing = false;
	//int value, int position,int takeProfit, int stopLoss,int reward
	transaction *new_data = createTransactionData(val,pos,tp,sl,reward);
	insertToHistory(new_data);
	val = 0;
	pos = 0;
	tp = 0;
	sl = 0;
	
	user->currency += reward;
	if(user->currency < 0){
		user->currency = 0;
	}
	
	memset(chartColor,-1,sizeof(chartColor));
	i =1;
	generateChart();
	generateChartContent(start);
}


void generateChart(){
	
	int length = CHART_LENGTH;
	int width = CHART_WIDTH;
	
	for(int i = 0; i < length; i++){
		for(int j = 0; j < width; j++){
			if(i==0 || i == length-1){
				chart[i][j] = '#';
				
			}else if(j == 0 || j == width-1){
				chart[i][j] = '#';
			}else{
				chart[i][j] = '-';
			}
		}
	}
	
}

void generateChartContent(chartContent *position){
	chartContent *curr;
	if(head == NULL){
		srand(time(NULL));
		memset(chartColor, -1, sizeof(chartColor));
		for(int i = 0; i < 20; i++){
			//srand(time(NULL));
			//sleep(1);
			makeChartContent();
		}
		
	
//		makeChartContent();
//		makeChartContent();
//		insertContentToChart(22,20,22,18,0);
//		insertContentToChart(20,25,29,16,1);
		curr = head;
	}else{
		curr = position;
	}
	
//	if(curr == NULL){
//		printf("NUll\n");
//		return;
//	}
		
	
	int length = CHART_WIDTH -1;
	while(curr!= NULL && i < length){
		
		if(curr->close >= curr->open){
//			printf("here\n");
//			printf("%d\n", curr);
			int top = 34 - curr->close;
			int bottom = 34 - curr->open;
			
			for(int j = top; j <= bottom;j++){
				chart[j][i] = 219;
				chartColor[j][i] = 1;
			}
			if(curr->highest > curr->close){
				
				top = 34 - curr->highest;
				bottom = 34 - curr->close-1;
				for(int j = top; j <= bottom; j++){
					chart[j][i] = 179;
					chartColor[j][i] = 1;
				}
			}	
		
			if(curr->lowest < curr->open){
				
				top = 34- curr->open +1;
				bottom = 34 - curr->lowest;
				
				for(int j = top; j <= bottom; j++){
					chart[j][i] = 179;
					chartColor[j][i] = 1;
				}
				//printf("yes\n");
			}
			
		
		}else if(curr->close < curr->open){
			
			int top = 34 - curr->open;
			int bottom = 34 - curr->close;
			for(int j =top; j<= bottom;j++){
				chart[j][i] = 219;
				chartColor[j][i] = 0;
			}
			
			if(curr->highest > curr->open){
				top = 34 - curr->highest;
				bottom  = 34 - curr->open - 1;
				for(int j = top; j <= bottom; j++){
					
					chart[j][i] = 179;
					chartColor[j][i] = 0;
				}
			}
			
			if(curr->lowest < curr->close){
				
				top = 34 - curr->close + 1;
				bottom = 34 - curr->lowest;
				
				for(int j = top;j<= bottom; j++){
					chart[j][i] = 179;
					chartColor[j][i] = 0;
				}
			}
			
		}
		i++;
		curr = curr->next;
		
	}
	
}

void printChart(){
	
	int length = CHART_LENGTH;
	int width = CHART_WIDTH;
	
	for(int i = 0; i < length; i++){
		
		for(int j = 0; j < width; j++){
			if(chartColor[i][j] == -1){
				printf("\033[0m");
				printf("%c", chart[i][j]);
				
			}else if(chartColor[i][j] == 1){
				printf("\033[0;32m");
				printf("%c", chart[i][j]);
				
			}else if(chartColor[i][j] == 0){
				printf("\033[0;31m");
				printf("%c", chart[i][j]);
				
			}else if(chartColor[i][j] == 2){ // tp(green)
				printf("\033[0;32m");
				printf("%c", chart[i][j]);
				
			}else if(chartColor[i][j] == 3){ // position(white)
				printf("\033[0;33m");
				printf("%c", chart[i][j]);
			//	printf("\033[0;31m");
				
			}else if(chartColor[i][j] == 4){ // sl(red)
				printf("\033[0;31m");
				printf("%c", chart[i][j]);
				
			}
		
//			
		}
		if(i == 0 || i == length-1){
			printf("###\n");
		}
		else
			printf("\033[0;31m%d\n",(34-i)*10);
	}
	
}

void insertToHistory(transaction *new_data){
	
	
	if (user->data == NULL) {
        user->data = new_data;
        return;
    }

	
	if(new_data->reward > user->data->reward){
		new_data->next = user->data;
		user->data = new_data;
		return;
	}
	
	
	transaction *curr = user->data;
	while(curr->next && curr->next->reward > new_data->reward){
		curr = curr->next;
	}
	
	if(!curr->next){
		curr->next = new_data;
		return;
	}
	
	
	new_data->next = curr->next;
	curr->next = new_data;
	
	return;
}

void viewTradeHistory(){
	
//	if(user->data == NULL){
//		user->data = queue;
//	}
	system("cls");
	userData *found = search(user->email);
	if(found->data== NULL){
		
		printf("No Transaction History\n\n");
		printf("Press enter to continue.."); getchar();
		return;
		
	}else{
		printf("Username: %s\n", user->username);
		printf("==============================================\n");
		transaction *curr = found->data;
		int idx = 0;
		while(curr){
			printf("No. %d\n", idx+1);
			printf("Value         : %d\n", curr->value);
			printf("Position      : %d\n", curr->position);
			printf("Take Profit   : %d\n", curr->takeProfit);
			printf("Stop Loss     : %d\n", curr->stopLoss);
			printf("Reward        : %d\n\n", curr->reward);
			idx++;
			curr = curr->next;
		}
		
	}
	printf("\nPress enter to continue..");
	getchar();
	return;
}
void viewGuidePage(){
	system("cls");
	printf("What Is Forex?\n");
	printf("\"Forex\", short for foreign exchange, is a global decentralized marketplace for trading currencies.\n");
	printf("In forex trading, participants buy one currency by selling another currency simultaneously, with the aim of profiting from fluctuations in exchange rates.\n");
	printf("It is one of the largest and most liquid financial markets in the world, operating 24 hours a day, five days a week.\n\n");
	
	printf("What Is Candle Stick?\n");
	printf("\"Canlde Stick\" in charts are a type of financial chart used to represent price movements in trading markets, including forex.\n");
	printf("They visually display the open, high, low, and close prices for a specific period.\n");
	printf("If the close price is higher than the open price, the candle color will be green.\n");
	printf("Then if the close price is less than the open price, the candle color will be red.\n");
	printf("Shadow or tick is the highest and the lowest price of a candle.\n\n");
	
	printf("What Is Position?\n");
	printf("\"Position\" in forex trading refers to where we want to enter the market at certain price point\n\n");
	
	printf("What Is Long?\n");
	printf("\"Long\" in forex trading refers to a trading position where a trader buys a currency pair\n");
	printf("with the expectation that its value will increase over time.\n\n");
	
	printf("What Is Short?\n");
	printf("\"Short\" in forex trading refers to a trading position where a trader sells a currency pair\n");
	printf("with the expectation that its value will decrease over time.\n\n");
	
	printf("What is Take Profit?\n");
	printf("\"Take Profit\" in forex trading refers to where we will leave the market at the specified price point\n");
	printf("our position will automatically closed after the market price hit our take profit price\n\n");
	
	printf("What Is Stop Loss?\n");
	printf("\"Stop Loss\" in forex trading refers to where we will leave the market at the specified price point\n");
	printf("it's used to make sure that we don't loss all of our money and many more\n");
	printf("same like take profit, our position will automatically closed after the market price hit our take profit price.\n");
	printf("\nPress enter to continue..");getchar();
	return;
}


int validateEmailLogIn(char email[]){
	
	int counter = 0;
//	if(email[0] == '\0');
//		return 1;
		
	
	int len = strlen(email);
	if(len < 8 || len > 36)
		return 1;
		
	for(int  i=0;i<len;i++){
		if(email[i] == '#')
			return 2;
				
		else if(email[i] == '@'){
			counter++;
			if(counter > 1)
				return 3;
				
			char substr[6];
			strncpy(substr,email+i,5);
			if(!strcmp(substr,"@.com"))
				return 9;			
			
//				
		}else if(email[i] == ' ')
			return 4;
	}
	char substr[5];
	strncpy(substr, email+(len-4),len);
		
	if(counter == 0)
		return 3;
	if(strcmp(substr,".com") != 0)
		return 5;
			
		
	userData *found = search(email);
	if(found == NULL)
		return 6;
			
	return 0;
			
	
	
}

int validateEmailRegister(char email[]){
	
	int counter = 0;
//	if(email[0] == '\0');
//		return 1;
		
	
	int len = strlen(email);
	if(len < 6 || len > 36)
		return 1;
		
	for(int  i=0; i<len; i++){
		if(email[i] == '#')
			return 2;
				
		else if(email[i] == '@'){
			counter++;
			if(counter > 1)
				return 3;
					
			char substr[6];
			strncpy(substr,email+i,5);
			if(!strcmp(substr,"@.com"))
				return 9;		
//			}
		}else if(email[i] == ' ')
			return 4;
	}
		
	if(counter == 0)
		return 3;
	char substr[5]= {'\0'};
	strncpy(substr, email+(len-4),4);
			
	if(strcmp(substr,".com") != 0)
		return 5;
		
			
	userData *found = search(email);
	if(found != NULL)
		return 7;
		
	return 0;
			
	
		
}

int validateUsername(char username[]){
	int len = strlen(username);
	if(len < 1 || len > 20){
			
//		printf("username to long or to short!\n");
//		printf("press enter to continue..");getchar();
//		system("cls");
		return 1;
	}else{
		for(int i=0; i<len; i++){
			if((username[i] >= '0' && username[i] <= '9') || 
			   (username[i] >= 'a' && username[i] <= 'z') ||
			   (username[i] >= 'A' && username[i] <= 'Z')){
				   	
				   	continue;
			}else{
//				printf("Username should only contain number and alpahbets\n");
//				printf("Press enter to continue..");getchar();
//				system("cls");
				return 8;
				
			}
		}
		
		return 0;
		
	}
}

int validatePassword(char password[]){
	
	int len = strlen(password);
	if(len < 8 || len > 36)
		return 1;
	
	int alphabet = 0;
	int number = 0;	
	for(int i=0; i<len; i++){
		
		if((password[i] >= '0' && password[i] <= '9') || 
		   (password[i] >= 'a' && password[i] <= 'z') ||
		   (password[i] >= 'A' && password[i] <= 'Z')){
					
			if((password[i] >= 'A' && password[i] <= 'Z') || 
			   (password[i] >= 'a' && password[i] <= 'z')){
					   		
				alphabet++;
					
			}else{
					
				number++;
						
			}
				   	
		}else{				
			return 8;
				
		}	
	}
	
	if(alphabet == 0 || number == 0)
		return 10;
		
	return 0;

}

void error(char variable[],int errNum){
	if(errNum == 1){
		printf("%s must be between 8 - 36 character!\n",variable);
	}else if(errNum ==2){
		printf("%s should not contain #!\n",variable);
	}else if(errNum ==3){
		printf("%s should contain 1 '@'\n",variable);
	}else if(errNum == 4){
		printf("%s should not contain any white space\n",variable);
	}else if(errNum == 5){
		printf("%s should ended with '.com'\n",variable);
	}else if(errNum == 6){
		printf("%s not found\n",variable);
	}else if(errNum == 7){
		printf("This %s is already registered\n",variable);
	}else if(errNum == 8){
		printf("%s should only contain alphabet and number\n",variable);
	}else if(errNum == 9){
		printf("%s must have a domain\n",variable);
	}else if(errNum == 10){
		printf("%s should contain atleast 1 alphabet and 1 number\n", variable);
	}
}

//void tes(char email[]){
//	
//	int len = strlen(email);
//	for(int i =0; i< len;i++){
//		if(email[i] == '@'){
//			char substr[7];
//			strncpy(substr,email+i,5);
//			if(!strcmp(substr,"@.com"))
//				printf("Sama");
//				
//			else
//				printf("beda");
//			
//			getchar();
//			break;
//		}
//	}
//}
void logIn(){
	char email[50] = {'\0'};
	char password[50] = {'\0'};
	userData *found;
	
	do{
		
		do{
			system("cls");
			printf("Email (0 to exit): ");
			scanf("%[^\n]", email);getchar();
			//found = search(email);
			if(email[0] == '\0'){
				printf("Invalid Email!\n");
				printf("Press enter to continue..");getchar();
				system("cls");
				
			}else if(!strcmp(email,"0"))
				return;				
		}while(email[0] == '\0');
		
		
		//tes(email);
		int valid = validateEmailLogIn(email);
//		printf("%d", valid);
//		break;
		printf("Password (0 to exit): ");
		scanf("%[^\n]", password);getchar();
		//printf("\n%s\n", email);
		
		userData *found;
		if(valid == 0){
			found = search(email);
			if(strcmp(found->password, password) != 0){
				printf("Email or password is invalid!\n");
				printf("Press enter to continue.."); getchar();
			}else{
				break;
			}
	
		}else{
			char string[] = "Email";
			error(string, valid);
			printf("Press enter to continue.."); getchar();
		}
			
			
	
	}while(1);
	user = search(email);
	system("cls");
	printf("You Logged In!\n");
	printf("Press enter to continue.."); getchar();
	
	while(isLogOut == false){
		
		userMenuPageInput();
	}
	isLogOut = false;
}

void registerAccount(){
	
	char username[30] = {'\0'};
	char email[50] = {'\0'};
	char password[50] = {'\0'};
	char confPass[50] ={'\0'};
	int len = 0;
	do{
		system("cls");
		printf("Username (0 to exit): ");
		scanf("%[^\n]",username);getchar();
		if(!strcmp(username,"0"))
			return;
		int valid = validateUsername(username);
//		len = strlen(username);
//		if(len < 1 || len > 20){
//			printf("username to long or to short!\n");
//			printf("press enter to continue..");getchar();
//			system("cls");
//		}else if(!valid){
//			
//			printf("Username can only contains number & alphabet\n");
//			printf("Press enter to continue..");getchar();
//			system("cls");
//			
//		}else if(valid)
//			break;

		if(valid == 0)
			break;
			
		else{
			char string[] = "Username";
			error(string, valid);
			printf("Press enter to continue..");getchar();
		}
	
	}while(1);
	
	do{
		
		do{
			system("cls");
			printf("Email (0 to exit): ");
			scanf("%[^\n]", email);getchar();
			//found = search(email);
			if(email[0] == '\0'){
				printf("Invalid Email!\n");
				printf("Press enter to continue..");getchar();
				//system("cls");
					
			}else if(!strcmp(email,"0"))
				return;
					
		}while(email[0] == '\0');
		
		int valid = validateEmailRegister(email);
		if(valid==0){
			break;
		}else{
			char string[] = "Email";
			error(string, valid);
			printf("Press enter to continue..");getchar();
		}
	
	}while(1);
	do{
		
		do{
			system("cls");
			printf("Password(0 to exit): ");
			scanf("%[^\n]", password); getchar();
			if(!strcmp(password, "0"))
				return;
				
			else if(password[0] == '\0'){
				printf("Invalid Password\n");
				printf("Press entert to continue.."); getchar();
				
			}
			
		}while(password[0] == '\0');
		
		int valid = validatePassword(password);
		if(valid == 0)
			break;
			
		else{
			char string[] = "Password";
			error(string,valid);
			printf("Press enter to continue..");getchar();
		}
		
	}while(1);
	do{
	
		do{
			system("cls");
			printf("Confirm Password(0 to exit): ");
			scanf("%[^\n]", confPass); getchar();
			
			if(!strcmp(confPass, "0"))
				return;	
				
			if(confPass[0] == '\0'){
				printf("Please confirm your password\n");
				printf("Press enter to continue..");getchar();
			}
				
		}while(confPass[0] =='\0');
		
		if(strcmp(confPass, password) != 0){
			printf("Confirmation password does not match the password!\n");
			printf("Press enter to continue..");getchar();
			
		}else 
			break;
		
	}while(1);
	insertToHashTable(username,email,password,10000);
	insertToTxt(username,email,password,10000);
	system("cls");
	printf("You are registered!\n");
	printf("Press enter to continue.."); getchar();
	//user = search(email);
	

	return;
}

void exitApp(){
	
	if(user != NULL) updateTxt();
	
	system("cls");
	printf("\n\nMade By - Hendra Tanuwijaya - T004\n\n");
	printf("Thank You"); getchar();
	exit(0);
}



chartContent *createChart(int open, int lowest, int highest, int close, int color){
	
	chartContent *new_data = (chartContent*)malloc(sizeof(chartContent));
	new_data->open = open;
	new_data->lowest = lowest;
	new_data->highest = highest;
	new_data->close = close;
	new_data->color = color;
	//new_data->body = body;
	new_data->next = new_data->prev = NULL;
	
	return new_data;
	
}


void makeChartContent(){
	int open,
		lowest,
		highest,
		close,
		color;
		
	//srand(time(NULL));
	
	if(head == NULL ){
		//srand(time(NULL));
		open = rand() % 32 +1;
		
	}else if(head == tail && head != NULL){
		open = head->close;
		
	}else{
	
		open = tail->close;
		//chartContent *curr = head;
	
	}
	
	int probality = rand() % 100;
	if(probality  < 10){
		close = open;
	}else{
		
		close = countClosePrice(open);
		
	}
	probality = rand() % 100;
	
	if(close > open && probality < 30){
		
			highest = close;
	
	}else if(close < open && probality < 30 ){
		
			highest = open;
		
	}else{
		
		if(close >= open)
			highest = countHighestPrice(close);
			
		else if(close < open){
			highest = countHighestPrice(open);
		}
	}
	
	probality = rand() % 100;
	
	if(close > open && probality < 30){
		lowest = open;
		
	}else if(close < open && probality < 30){
		lowest = close;
		
	}else{
		
		if(close >= open){
			lowest = countLowestPrice(open);
			
		}else if(close < open){
			lowest = countLowestPrice(close);
		}
		
	}
	
	if(close >= open){
		color = 1; //hijau
		
	}else if(close < open){
		color = 0; //merahhh
	}
	
	insertContentToChart(open,close,highest,lowest,color);
	//printf("%d %d %d %d %d\n", open, close, highest, lowest, color);
	
}

void insertContentToChart(int open, int close, int highest, int lowest, int color){
	
	chartContent *new_data = createChart(open,lowest, highest,close,color);
	
	if(head == NULL){
		head = start = tail = new_data;
		return;
	}
	
	tail->next = new_data;
	new_data->prev = tail;
	tail = new_data;
	return;
	
}

int countClosePrice(int open){
		
		int  probality;
		probality = rand() % 2; // 1 | 0 -> higher | lower
		int close;
		if(probality == 1){ 
			
			close = (rand() %6 +1) + open;
			
			if(close > 33){
				close = 33;
				return close;
				
			}
			
			return close;
			
		}else if(probality == 0){
			
			close = (rand() % 6 + 1);
			if(close >= open){
				close = 1;
				return close;
				
			}else{
				
				close = open - close;
				return close;
			}
			
			
		}
	
}

int countHighestPrice(int num){
	
	//srand(time(NULL));
	int highest = (rand() % 5) + num;
	
	if(highest > 33)
		highest = 33;
		
	return highest; 
	
	
}

int countLowestPrice(int num){
	
	//srand(time(NULL));
	int lowest = rand() % 5;
	
	if(lowest >= num)
		return 1;
	
	lowest = num - lowest;
	
	return lowest;	
	
}

transaction *createTransactionData(int value, int position,int takeProfit, int stopLoss,int reward){
	
	transaction *new_data = (transaction*)malloc(sizeof(transaction));
	
	new_data->value = value;
	new_data->position = position;
	new_data->takeProfit = takeProfit;
	new_data->stopLoss = stopLoss;
	new_data->reward = reward;
	new_data->next = NULL;
	
	return new_data;
	
}


userData *createHashData(char username[], char email[], char password[], int currency){
	
	userData *new_data = (userData*)malloc(sizeof(userData));
	strcpy(new_data->username,username);
	strcpy(new_data->email,email);
	strcpy(new_data->password,password);
	new_data->currency = currency;
	new_data->data = NULL;
	new_data->next = NULL;
	return new_data;
	
}
void insertToHashTable(char username[], char email[], char password[], int currency){
	userData *new_data = createHashData(username, email,password,currency);
	
	int idx = hash(username);
	
	if(list[idx] == NULL){
		list[idx] = new_data;
		return;
	}
	
	userData *curr = list[idx];
	
	while(curr->next){
		curr = curr->next;
	}
	
	curr->next = new_data;
	return;
	
}
void insertToTxt(char username[], char email[], char password[], int currency){
	FILE *pt = fopen("account/user.txt", "a");
	
	fprintf(pt, "%s#%s#%s#%d\n", username, email, password,currency);
	
	fclose(pt);
}

void insertTxtToHashTable(){
	
	char username[50];
	char email[50];
	char password[50];
	int currency;
	
	FILE *pt = fopen("account/user.txt","r");
	while(!feof(pt)){
		
		fscanf(pt, "%[^#]#%[^#]#%[^#]#%d\n", username, email,password,&currency);
		//printf("username : %s", username);
		insertToHashTable(username,email,password,currency);
	}
	
	fclose(pt);
}

userData *search(char email[]){
	char username[50];
	char f_email[50];
	char string[50];
	FILE *pt = fopen("account/user.txt","r");
	
	while(!feof(pt)){
		
		fscanf(pt,"%[^#]#%[^#]#%[^\n]\n", username, f_email,string);
		
		if(!strcmp(f_email, email)){
			
			userData *curr;
			int idx = hash(username);
			curr = list[idx];
			if(curr == NULL){
				//printf("kosong\n");
				return NULL;
			}
	//		
			while(curr){
				//printf("%s - %s ->" ,curr->email, email);
				if(strcmp(curr->email, email) == 0){
					//printf("sama\n");
					fclose(pt);
					return curr;
				}
	//			printf("%s", curr->email);
				
				curr = curr->next;
			}
			
			if(curr == NULL)
			//	printf("tidak sama\n");
				return NULL;
		}
			
		
	}
	fclose(pt);
}

int hash(char username[]){
	int key = 0;
	
	int len = strlen(username);
	for(int i = 0; i < len; i++){
		key += username[i];
	}
	
	return key % SIZE;
}

void updateTxt(){
	
	FILE *pt, *temp;
	
	
	char buffer[1001];
	char replace[1001];
	
	pt = fopen("account/user.txt", "r");
	temp = fopen("account/temp.txt", "w");
	
	char username[50];
	char email[50];
	char string[50];
	
	
	bool reading = true;
	//int curr = 1;
	sprintf(replace,"%s#%s#%s#%d\n", user->username, user->email,user->password ,user->currency);
	while(!feof(pt)){
		fscanf(pt, "%[^#]#%[^#]#%[^\n]\n", username, email,string);
		sprintf(buffer,"%s#%s#%s\n", username, email,string);
		
		
		
		if(!strcmp(user->email,email))
			fputs(replace,temp);
		else
			fputs(buffer,temp);
		
	}
		
	fclose(pt);
	fclose(temp);
	remove("account/user.txt");
	rename("account/temp.txt", "account/user.txt");
}

