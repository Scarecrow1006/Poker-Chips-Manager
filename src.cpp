#include<iostream>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

using namespace std;

class player{
	public:
		int money;
		int move;
		int stake;
		//bool onBoard;
		bool fold;
		char initials[5];
		bool makeMove(void);
		void bid(int);
};

class table{
	public:
		int money;
		int high_bid;
};

table tbl;
player pl[20];
int startMoney;
int nop;
int BIG_BLIND;
int round_players;
int call_check_count=0;
int deck_cards=0;
int BigB=0;
int to_do_flag=0;

int start();
void show();
void next_round(int);
void reset();
void show_list();

int main(){
	start();
	int i,round_no=0;
	bool over;
	while(nop!=1){
		round_players=nop;
		pl[BigB].bid(BIG_BLIND);
		tbl.high_bid=BIG_BLIND/2;
		for(i=BigB+1;round_players>1;i++){
			i=i%nop;
			if(!pl[i].fold){
				over=pl[i].makeMove();
				if(over){
					break;
				}
			}
		}
		next_round(round_players);
	}
	return 0;
}

int start(){
	cout<<"Enter no. of Players(Less than 20): ";
	cin>>nop;
	Sleep(500);
	//clrscr();
	int i;
	cout<<"Enter Starting Money: ";
	cin>>startMoney;
	Sleep(500);
	//clrscr();
	cout<<"Enter Big Blind: ";
	cin>>BIG_BLIND;
	Sleep(500);
	system("cls");
	for(i=0;i<nop;i++){
		pl[i].money=startMoney;
		cout<<"Player Initials: ";
		scanf(" %s",pl[i].initials);
		pl[i].fold=false;
		//pl[i].onBoard=true;
		pl[i].stake=0;
	}
	tbl.money=0;
	return nop;
}

void show(){
	int i;
	system("cls");
	if(to_do_flag==1){
		cout<<"******* Open Card from Deck *******\n";
		to_do_flag=0;
	}
	if(to_do_flag==2){
		cout<<"******* All Players Show Cards *******\n";
		tp_do_flag=0;
	}
	cout<<"\t\tSTAKE\n";
	for(i=0;i<nop;i++){
		if(!(pl[i].fold)) cout<<pl[i].initials<<": \t"<<pl[i].money<<"\t"<<pl[i].stake<<"\n";
		else cout<<pl[i].initials<<": \tFOLD\n";
	}
	cout<<"Table: \t"<<tbl.money<<"\n";
	cout<<"Highest Bid: "<<tbl.high_bid<<"\n";
	cout<<"_____________________________\n";
}

void player::bid(int bid_money){
	money=money-bid_money;
	tbl.money=tbl.money+bid_money;
	stake=stake+bid_money;
	if(money<0) money=0;
}

bool player::makeMove(void){
	show();
	cout<<initials<<"'s move\nEnter 1 to fold, 2 to call,3 to Raise :";
	cin>>move;
	if((move<1)||(move>3)){
		cout<<"Retry: ";
		cin>>move;
	}
	switch(move){
		case 1:
			fold=true;
			round_players--;
			call_check_count=0;
			break;
		case 2:
			if(stake<tbl.high_bid){
				if(money>tbl.high_bid){
					bid(tbl.high_bid-stake);
				}
				else bid(money);
			}
			call_check_count++;
			if(call_check_count==round_players){
				if(deck_cards==3){
					//cout<<"******* All Players Show cards *******\n";
					to_do_flag=2;
					deck_cards=0;
					return true;
				}
				else{
					//cout<<"******* Open Card from Deck *******\n";
					to_do_flag=1;
					deck_cards++;
					call_check_count=0;
				}
			}
			break;
		case 3:
			cout<<"Raise to: ";
			cin>>tbl.high_bid;
			bid(tbl.high_bid-stake);
			call_check_count=0;
			break;
	}
	return false;
}

void next_round(int round_players){
	int i;
	int winner;
	if(round_players==1){
		for(i=0;i<nop;i++){
			if(!pl[i].fold){
				pl[i].money=pl[i].money+tbl.money;
				break;
			}
		}
	}
	else{
		show_list();
		cin>>winner;
		winner--;
		pl[winner].money=pl[winner].money+tbl.money;
	}
	reset();
}

void show_list(){
	int i;
	for(i=0;i<nop;i++){
		if(!(pl[i].fold)){
			cout<<"Player "<<i+1<<": ";
			printf("%s\n",pl[i].initials);
		}
	}
	cout<<"Enter winning player number: ";
}

void reset(){
	tbl.money=0;
	int i,j;
	for(i=0;i<nop;i++){
		if(pl[i].money==0){
			for(j=i;j<nop-1;j++){
				pl[j]=pl[j+1];
			}
			nop--;
			i--;
		}
	}
	for(i=0;i<nop;i++){
		pl[i].stake=0;
		pl[i].fold=false;
	}
	tbl.high_bid=0;
	BigB++;
	BigB=BigB%nop;
}







