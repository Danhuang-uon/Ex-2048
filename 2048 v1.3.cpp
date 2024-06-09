#include <bits/stdc++.h>
#include <conio.h>
#define SIZE 15
using namespace std;
int s[SIZE][SIZE];
int vis[SIZE][SIZE];
const int n=4;
const int Limit=2048;
int score,Max_score;
void Print()
{
	system("cls");
	Max_score=max(Max_score,score); 
	cout<<"---"<<"score:"<<score<<"-----"<<"Max_score:"<<Max_score<<"---"<<"\n\n";
	for(int i=1;i<=n;++i)
	{
		for(int j=1;j<=n;++j)
			cout<<setw(5)<<s[i][j];
		cout<<"\n\n";
	}
}
void Addnew()
{
	int tot=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(s[i][j]==0)
				++tot;
	int op=rand()%tot,type=rand()%3;
	tot=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			if(s[i][j]==0)
			{
				if(tot==op)
				{
					if(type<=1)
						s[i][j]=2;
					else
						s[i][j]=4;
				}
				++tot;
			}
		}
}
void PreMake()
{
	score=0;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			s[i][j]=0;
	for(int i=1;i<=3;++i)
		Addnew();
}
int Get()
{
	char c1=_getch();
	if(c1!=-32)
		return 0;
	char c2=_getch();
	switch(c2)
	{
		case 72://up
			return 1;
			break;
		case 80://down
			return 2;
			break;
		case 75://left
			return 3;
			break;
		case 77://right
			return 4;
			break;
		default:
			return 0;
			break;
	}
}
bool CheckMove(int op)
{
	if(op==1)//up
	{
		for(int i=2;i<=n;++i)
			for(int j=1;j<=n;++j)
				if(s[i-1][j]==0 || s[i-1][j]==s[i][j])
					return true;
	}
	else	if(op==2)//down
	{	
		for(int i=n-1;i>=1;--i)
			for(int j=1;j<=n;++j)
				if(s[i+1][j]==0 || s[i+1][j]==s[i][j])
					return true;
	}
	else	if(op==3)//left
	{	
		for(int j=2;j<=n;++j)
			for(int i=1;i<=n;++i)
				if(s[i][j-1]==0 || s[i][j-1]==s[i][j])
					return true;
	}
	else//right
	{
		for(int j=n-1;j>=1;--j)
			for(int i=1;i<=n;++i)
				if(s[i][j+1]==0 || s[i][j+1]==s[i][j])
					return true;
	}
	return false;
}
void Move(int op)
{
	if(!CheckMove(op))
		return;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			vis[i][j]=0;
	if(op==1)//up
	{
		for(int i=2;i<=n;++i)
			for(int j=1;j<=n;++j)
			{
				int now=i;
				while(now>=2 && s[now-1][j]==0)
					swap(s[now][j],s[now-1][j]),--now;
				if(now==1)
					continue;
				if(vis[now-1][j]==0 && s[now-1][j]==s[now][j])
				{
					s[now][j]=0;
					s[now-1][j]*=2;
					score+=s[now-1][j];
					vis[now-1][j]=1;
				}
			}
	}
	else	if(op==2)//down
	{	
		for(int i=n-1;i>=1;--i)
			for(int j=1;j<=n;++j)
			{
				int now=i;
				while(now<=n-1 && s[now+1][j]==0)
					swap(s[now][j],s[now+1][j]),++now;
				if(now==n)
					continue;
				if(vis[now+1][j]==0 && s[now+1][j]==s[now][j])
				{
					s[now][j]=0;
					s[now+1][j]*=2;
					score+=s[now+1][j];
					vis[now+1][j]=1;
				}
			}
	}
	else	if(op==3)//left
	{	
		for(int j=2;j<=n;++j)
			for(int i=1;i<=n;++i)
			{
				int now=j;
				while(now>=2 && s[i][now-1]==0)
					swap(s[i][now],s[i][now-1]),--now;
				if(now==1)
					continue;
				if(vis[i][now-1]==0 && s[i][now-1]==s[i][now])
				{
					s[i][now]=0;
					s[i][now-1]*=2;
					score+=s[i][now-1];
					vis[i][now-1]=1;
				}
			}
	}
	else//right
	{
		for(int j=n-1;j>=1;--j)
			for(int i=1;i<=n;++i)
			{
				int now=j;
				while(now<=n-1 && s[i][now+1]==0)
					swap(s[i][now],s[i][now+1]),++now;
				if(now==n)
					continue;
				if(vis[i][now+1]==0 && s[i][now+1]==s[i][now])
				{
					s[i][now]=0;
					s[i][now+1]*=2;
					score+=s[i][now+1];
					vis[i][now+1]=1;
				}
			}
	}
	Addnew();
}
bool CheckWin()
{
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
			if(s[i][j]==Limit)
				return true;
	return false;
}
bool SolveWin()
{
	Print();
	cout<<"你赢了!\n";
	cout<<"按1重新开始，按0退出游戏\n";
	while(1)
	{
		char ch=_getch();
		if(ch=='0')
			return 0;
		else	if(ch=='1') 
			return 1;
	} 
}
bool CheckLose()
{
	for(int i=1;i<=4;++i)
		if(CheckMove(i))
			return false;
	return true;
}
bool SolveLose()
{
	Print();
	cout<<"你输了!\n";
	cout<<"按1重新开始，按0退出游戏\n";
	while(1)
	{
		char ch=_getch();
		if(ch=='0')
			return 0;
		else	if(ch=='1') 
			return 1;
	} 
}
bool Playing()
{
	while(true)
	{
		int op=Get();
		if(!op)
			continue;
		Move(op);
		if(CheckWin())
			return SolveWin();
		if(CheckLose())
			return SolveLose();
		Print();
	}
}
void StartGame()
{
	srand(time(0));
	Max_score=0;
	while(1)
	{
		PreMake();
		Print();
		if(!Playing())
			return;
	}
}
int main()
{
	StartGame();
	return 0;
} 
