#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;

/*
题目：扑克

题目描述：

描述：
In 5-card draw poker, a player is dealt a hand of five cards (which may be looked at). The player may then discard between zero and five of his or her cards and have them replaced by the same number of cards from the top of the deck (which is face down). The object is to maximize the value of the final hand. The different values of hands in poker are given at the end of this problem. Normally the player cannot see the cards in the deck and so must use probability to decide which cards to discard. In this problem, we imagine that the poker player is psychic and knows which cards are on top of the deck. Write a program which advises the player which cards to discard so as to maximize the value of the resulting hand.

5张牌的大小比较：

1.straight-flush：同花顺。牌面为T（10） - A，这里不论花色是否同样；

2.four-of-a-kind：四条，牌面有4个同样的值。

3.full-house：船牌，牌面有3个同样值，剩下2个也同样值。

4.flush：同花，五张牌的花色同样，不是同花顺；

5.straight：顺子。五张牌的值连续，A能够作为1也能够作为14；

6.three-of-a-kind：三条，牌面有3个同样的值；

7.two-pairs：两对。牌面有2个对子。

8.one-pair：一对，牌面有一个对子，即2个同值；

9.highest-card：大牌，没有以上牌型。

输入：
Input will consist of a series of lines, each containing the initial five cards in the hand then the first five cards on top of the deck. Each card is represented as a two-character code. The first character is the face-value (A=Ace, 2–9, T=10, J=Jack, Q=Queen, K=King) and the second character is the suit (C=Clubs, D=Diamonds, H=Hearts, S=Spades). Cards will be separated by single spaces. Each input line will be from a single valid deck, that is there will be no duplicate cards in each hand and deck.

输出：
Each line of input should produce one line of output, consisting of the initial hand, the top five cards on the deck, and the best value of hand that is possible. Input is terminated by end of file. Note: Use the sample input and output as a guide. Note that the order of the cards in the player’s hand is irrelevant, but the order of the cards in the deck is important because the discarded cards must be replaced from the top of the deck. Also note that examples of all types of hands appear in the sample output, with the hands shown in decreasing order of value.

样例1：
输入：

TH JH QC QD QS QH KH AH 2S 6S

2H 2S 3H 3S 3C 2D 3D 6C 9C TH

2H 2S 3H 3S 3C 2D 9C 3D 6C TH

2H AD 5H AC 7H AH 6H 9H 4H 3C

AC 2D 9C 3S KD 5S 4D KS AS 4C

KS AH 2H 3C 4H KC 2C TC 2D AS

AH 2C 9S AD 3C QH KS JS JD KD

6C 9C 8C 2D 7C 2H TC 4C 9S AH

3D 5S 2H QD TD 6S KH 9H AD QH

输出：

Hand: TH JH QC QD QS Deck: QH KH AH 2S 6S Best hand: straight-flush

Hand: 2H 2S 3H 3S 3C Deck: 2D 3D 6C 9C TH Best hand: four-of-a-kind

Hand: 2H 2S 3H 3S 3C Deck: 2D 9C 3D 6C TH Best hand: full-house

Hand: 2H AD 5H AC 7H Deck: AH 6H 9H 4H 3C Best hand: flush

Hand: AC 2D 9C 3S KD Deck: 5S 4D KS AS 4C Best hand: straight

Hand: KS AH 2H 3C 4H Deck: KC 2C TC 2D AS Best hand: three-of-a-kind

Hand: AH 2C 9S AD 3C Deck: QH KS JS JD KD Best hand: two-pairs

Hand: 6C 9C 8C 2D 7C Deck: 2H TC 4C 9S AH Best hand: one-pair

Hand: 3D 5S 2H QD TD Deck: 6S KH 9H AD QH Best hand: highest-card*/ 

string a[9] = { "straight-flush","four-of-a-kind","full-house","flush","straight","three-of-a-kind","two-pairs","one-pair","highest-card" };
string hand[10], deck[10];
int num[20], col[10];
int ans, n;

int value(char ch) {
    if (ch == 'T') return 10;
    if (ch == 'J') return 11;
    if (ch == 'Q') return 12;
    if (ch == 'K') return 13;
    if (ch == 'A') return 1;
    return ch - '0';
}

int color(char ch) {
    if (ch == 'S') return 1;
    if (ch == 'H') return 2;
    if (ch == 'D') return 3;
    if (ch == 'C') return 4;
}

int search() {
    int st = 0, two = 0, three = 0;
    //straight flush
    for (int i = 1; i <= 4; i++)
        if (col[i] == 5) {
            for (int j = 1; j <= 13; j++)
                if (num[j] != 0) {
                    st++;
                    if (st == 5) return 0;
                    if (st == 4 && num[1]) return 0;
                }
                else st = 0;
        }
    //four of kind
    for (int i = 1; i <= 13; i++)
        if (num[i] == 4) return 1;
    for (int i = 1; i <= 13; i++) {
        if (num[i] == 2) two++;
        if (num[i] == 3) three++;
    }
    //full house
    if (two && three) return 2;
    //flush
    for (int i = 1; i <= 4; i++)
        if (col[i] == 5) return 3;
    //straight
    st = 0;
    for (int i = 1; i <= 13; i++)
        if (num[i]) {
            st++;
            if (st == 5) return 4;
            if (st == 4 && num[0]) return 4;
        }
        else st = 0;
    //three of a kind
    if (three) return 5;
    // tow pairs
    if (two > 1) return 6;
    //one pair
    if (two) return 7;
    //high card
    return 8;
}

void dfs(int now) {
    if (now >= 5) {
        int t = search();
        if (ans > t) ans = t;
        return;
    }
    int t1, t2;
    t1 = value(hand[now][0]);
    t2 = color(hand[now][1]);
    num[t1]++;
    col[t2]++;
    dfs(now + 1);
    num[t1]--;
    col[t2]--;
    t1 = value(deck[n][0]);
    t2 = color(deck[n][1]);
    num[t1]++;
    col[t2]++;
    n++;
    dfs(now + 1);
    num[t1]--;
    col[t2]--;
    n--;
}

int main() {
    while (cin >> hand[0]) {
        memset(num, 0, sizeof(num));
        memset(col, 0, sizeof(col));
        cout << "Hand: ";
        for (int i = 1; i < 5; i++)
            cin >> hand[i];
        for (int i = 0; i < 5; i++)
            cout << hand[i] << " ";

        cout << "Deck: ";
        for (int i = 0; i < 5; i++) {
            cin >> deck[i];
            cout << deck[i] << " ";
        }
        ans = 10;
        n = 0;
        dfs(0);
        cout << "Best hand: ";
        cout << a[ans] << endl;
    }
    return 0;
}
