#include <iostream>
#include <time.h>
#include <string>
#include <vector>
using namespace std;

/******************************************/
enum suit {S, H, D, C};//spade,heart,diamond,club
int total_used = 0;

class Card
{
    public:
        int rank;//A,1~10,J,Q,K(1~13)
        //enum suit {S, H, D, C};//spade,heart,diamond,club
        suit type;
        int value;//point 
};
//初始化牌卡
void initcard(Card *deck, int playersnum)
{
    int j = 1, k = 1;
    for (int i = 0; i < (playersnum/4)*52; i++)
    {
        if (j % 4 == 1)//四花色一循環
            j = 1;
        if (i % 13 == 0)//13點一循環
        {
            j++;
            k = 1;
        }
        while (j < 5 && k < 14)
        {
            deck[i].type = (suit)j; 
            deck[i].rank = k;
            k++;
            break;
        }
    }
};
//洗牌
void shuffle(Card *deck)
{
    Card *a, *b, temp;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 100; i++)
    {
        a = deck + rand()%52;
        b = deck + rand()%52;
        temp = *a;
        *a = *b;
        *b = temp;
    }
};
/****************************************/
class Player
{
    public:
        string name;
        int bankroll;
        int bet;
        virtual void strategy() = 0;
};
//create a human player
class Human: public Player
{ 
    public:
        void strategy() {cout << "create a human player";};
        Card hand[10];
        int hand_num = 0;
};
//create a computer player
class Computer: public Player
{ 
    public:
        void strategy() {cout << "create a computer player";};
        Card hand[10];
        int hand_num = 0;
};
/****************************************/

/****************************************/
//新增玩家牌卡
void addHumanCard(Card *deck, Human player, int total_used)
{
    for (int i = total_used; i < (total_used+1); i++)
    {
        player.hand[player.hand_num] = deck[i];
        player.hand_num++;           
    }
    total_used = total_used + 1;
};
void addComputerCard(Card *deck, Computer player, int total_used)
{
    for (int i = total_used; i < (total_used+1); i++)
    {
        player.hand[player.hand_num] = deck[i];
        player.hand_num++;    
    }
    total_used = total_used + 1;
};
/****************************************/
void startbet(Human *human, Computer *computer, int human_num, int computer_num)
{
    cout << "Okay, time for betting!\n";
    cout << "-----------------------\n";
    for (int i = 0; i < human_num; i++)
    {
        cout << human[i].name << ", how much would you like to bet?";
        cin >> human[i].bet;
        cout << "\n";
    }
    for (int i = 0; i < human_num; i++)
    {
        cout << human[i].name << " bets $" << human[i].bet << "\n";
    }
    for (int i = 0; i < computer_num; i++)
    {
        cout << computer[i].name << " bets $" << computer[i].bet << "\n";
    }
}
char getHumanType(Human human, int hand_num)
{
    char ans;
    if ((human.hand[hand_num]).type == 1)
        ans = S;
    if ((human.hand[hand_num]).type == 2)
        ans = H;
    if ((human.hand[hand_num]).type == 3)
        ans = D;
    if ((human.hand[hand_num]).type == 4)
        ans = C;
    return ans;
}
char getComputerType(Computer computer, int hand_num)
{
    char ans;
    if ((computer.hand[hand_num]).type == 1)
        ans = S;
    if ((computer.hand[hand_num]).type == 2)
        ans = H;
    if ((computer.hand[hand_num]).type == 3)
        ans = D;
    if ((computer.hand[hand_num]).type == 4)
        ans = C;
    return ans;
}
void startcard(Human *human, Computer *computer, int human_num, int computer_num)
{
    cout << "The initial starting cards are:" << endl;
    cout << "-------------------------------" << endl;
    for (int i = 0; i < human_num; i++)
    {
        cout << human[i].name << "'s current hand: [xx]";
        cout << " [" << (human[i].hand[1]).rank << getHumanType(human[i], 1) << "]" << endl;
    }
    for (int i = 0; i < computer_num; i++)
    {
        cout << computer[i].name << "'s current hand: [xx]";
        cout << " [" << (computer[i].hand[1]).rank << getComputerType(computer[i], 1) << "]" << endl;
    }
}
void Humanturn(Card *deck, Human human, int total_used, int hand_num)
{
    cout << human.name << "'s turn:" << endl;
    cout << "-----------" << endl;
    cout << human.name << "'s current hand: ";
    for (int i = 0; i < hand_num; i++)
    {
        cout << "[" << (human.hand[i]).rank << getHumanType(human, i) << "]";
    }
    cout << endl;
    int play = 0;
    char ans;
    while (play == 0)
    {
        cout << "Would you like to draw another card (Y or N):";
        cin >> ans;
        if (ans == 'Y')
        {
            cout << human.name << " chooses to draw." << endl;
            addHumanCard(deck, human, total_used);
            for (int i = 0; i < hand_num; i++)
            {
                cout << "[" << (human.hand[i]).rank << getHumanType(human, i) << "]";
            }
        }
        if (ans == 'N')
        {
            cout << human.name << " chooses to stay." << endl;
            play = 1;
        }
    }
}
int Meekturn(Computer Meek)
{
    int ans = 0, has = 0;
    for (int i = 0; i < Meek.hand_num; i++)
    {
        ans = ans + (Meek.hand[i]).value;
        if ((Meek.hand[i].value == 7) && (getComputerType(Meek, i) == 'C'))
            has = 1;
    }
    if ((ans%2 == 0) || (has == 1))
        return 1;
    if (ans%2 == 1)
        return 0;
}
int Randomturn(Computer Random)
{
    int ans = 0;
    for (int i = 0; i < Random.hand_num; i++)
    {
        ans = ans + (Random.hand[i]).value;
    }
    if (ans >= 19)
        return 0;
    else
        return 1;
}
int Dealerturn(Computer Dealer)
{
    int ans = 0;
    for (int i = 0; i < Dealer.hand_num; i++)
    {
        ans = ans + (Dealer.hand[i]).value;
    }
    if (ans <= 16)
        return 1;
    if (ans >= 17)
        return 0;
}
void Computerturn(Card *deck, Computer computer, int total_used, int hand_num)
{
    cout << computer.name << "'s turn:" << endl;
    cout << "-----------" << endl;
    cout << computer.name << "'s current hand: ";
    for (int i = 0; i < hand_num; i++)
    {
        cout << "[" << (computer.hand[i]).rank << getComputerType(computer, i) << "]";
    }
    cout << endl;
    int play = 0;
    while (play == 0)
    {
        if ((Meekturn(computer) == 1) || (Randomturn(computer) == 1) || (Dealerturn(computer) == 1))
        {
            cout << computer.name << " chooses to draw." << endl;
            addComputerCard(deck, computer, total_used);
            for (int i = 0; i < hand_num; i++)
            {
                cout << "[" << (computer.hand[i]).rank << getComputerType(computer, i) << "]";
            }
        }
        if ((Meekturn(computer) == 0) || (Randomturn(computer) == 0) || (Dealerturn(computer) == 0))
        {
            cout << computer.name << " chooses to stay." << endl;
            play = 1;
        }
    }
}
/****************************************/
int main ()
{
    int num_of_players;
    int human_num = 0, computer_num = 0;
    string kind, name;
    //一開始先詢問遊玩人數
    cout << "How many players?";
    cin >> num_of_players;
    //儲存player的空間
    Human humanset[num_of_players];
    Computer computerset[3];
    //4人使用一副牌，8人使用二副牌...以此類推
    Card deck[(num_of_players/4)*52];
    initcard(deck, num_of_players);
    //根據玩家數依序輸入玩家種類，名字，bankroll，若為電腦玩家則根據各電腦玩家類型輸入需要資訊
    //Dealer則無需再輸入名字及bankroll，Meek及Random則須輸入bankroll
    for (int i = 0; i < num_of_players; i++)
    {
        cout << "kind? Human?Dealer?Meek?Random?";
        cin >> kind;
        if (kind.compare("Human") == 0)
        {
            Human human;
            cout << "name?";
            cin >> human.name;
            cout << "bankroll?";
            cin >> human.bankroll;
            humanset[human_num] = human;
            human_num++;
        }
        if (kind.compare("Meek") == 0)
        {
            Computer Meek;
            Meek.name = "Meek";
            cout << "bankroll?";
            cin >> Meek.bankroll;
            Meek.bet = 2;
            computerset[computer_num] = Meek;
            computer_num++;
        }
        if (kind.compare("Random") == 0)
        {
            Computer Random;
            Random.name = "Random";
            cout << "bankroll?";
            cin >> Random.bankroll;
            computerset[computer_num] = Random;
            computer_num++;
        } 
        if (kind.compare("Dealer") == 0)
        {
            Computer Dealer;
            Dealer.name = "Dealer";
            Dealer.bankroll = 10000;
            computerset[computer_num] = Dealer;
            computer_num++;
        } 
    }
    //依玩家數量制定的牌庫洗牌
    //shuffle(deck);
    //開始
    int play = 0;
    while (play == 0)
    {
        shuffle(deck);
        for (int i = 0; i < human_num; i++)
        {
            addHumanCard(deck, humanset[i], total_used);
            addHumanCard(deck, humanset[i], total_used);
        }
        for (int i = 0; i < computer_num; i++)
        {
            addComputerCard(deck, computerset[i], total_used);
            addComputerCard(deck, computerset[i], total_used);
        }
        startbet(humanset, computerset, human_num, computer_num);
        startcard(humanset, computerset, human_num, computer_num);
        for (int i = 0; i < human_num; i++)
        {
            Humanturn(deck, humanset[i], total_used, humanset[i].hand_num);
        }
        for (int i = 0; i < computer_num; i++)
        {
            Computerturn(deck, computerset[i], total_used, computerset[i].hand_num);
        }
    }



}