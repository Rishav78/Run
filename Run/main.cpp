#include <iostream>
#include<conio.h>
#include<time.h>
#include<vector>
#include<windows.h>

using namespace std;
int z=0;
int h;
class Moving
{
    char **Border;
    int m,n;
    int Herox,Heroy;
    vector<int> obstacleX,obstacleY;
    vector<int> bulletx,bullety;
    int n1,flag=0;//no of obstacle
    int up;
    int prevx,prevy;
    float lvl;
    enum special_ability{invisible,destroy,double_point,none};
    special_ability ability;
    int abilityX, abilityY, ability_no, T;
public:
    int score;
    Moving()
    {
        score=0;
        lvl=0;
        up=0;
        T=-1;
        ability=none;
        abilityX=0, abilityY=0, ability_no=0;
        flag=0;
        n1=4;
        cin >> m >> n;
        Border = new char*[m];
        for(int i=0;i<m;i++)
        {
            Border[i] = new char[n];
        }
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                if(i==0 || j==0 || i==(m-1) || j==(n-1))
                {
                    Border[i][j]='#';
                }
                else
                {
                    Border[i][j]=' ';
                }
            }
        }
    }

    void Draw_ob()
    {
        Herox = prevx = m-2;
        Heroy = prevy = n/2;
        Border[Herox][Heroy]='H';
    }
    void start()
    {
        Border[Herox][Heroy]=' ';
        if(kbhit())
        {
            switch(getch())
            {
            case 'w':
                {
                    if(Herox>1)
                    {
                        --Herox;
                    }
                    break;
                }
            case 'a':
                {
                    if(Heroy>1)
                    {
                        --Heroy;
                    }
                    break;
                }
            case 'd':
                {
                    if(Heroy<(n-2))
                    {
                        ++Heroy;
                    }
                    break;
                }
            case 's':
                {
                    if(Herox<(m-2))
                    {
                        ++Herox;
                    }
                    break;
                }
            case 'p':
                {
                    cout << endl << score <<endl;
                    system("pause");
                }
            }
        }
        Border[Herox][Heroy]='H';
    }
    void obstacle()
    {
        int x;
        srand(++z);
        if(obstacleX.size()==0 || obstacleX[obstacleX.size()-1]>((n/2)-lvl))
        {
            if(ability==double_point)
            {
                score=score+4;
            }
            else
            {
                score=score+2;
            }
            flag=1;
            time_t now = time(0);
            tm *ltm = localtime(&now);
            srand(ltm->tm_sec*z++);
            for(int i=0;i<rand()%n1;i++)
            {
                obstacleX.push_back(1);
                z=rand();
                srand(ltm->tm_sec*z++);
                if(x=rand()%(n-1))
                {
                    obstacleY.push_back(x);
                }
                else
                {
                    obstacleY.push_back(1);
                    x=1;
                }
                Border[1][x]='O';
            }
        }
        if(lvl<((n/2)-1) && score==(up+20))
        {
            up=score;
            if(n1<=6)
            {
                n1++;
            }
            lvl=lvl+0.5;
        }
    }
    void move_obstacle()
    {
        for(int i=0;i<obstacleX.size();)
        {
            if(obstacleX[i]==Herox && obstacleY[i]==Heroy)
            {
                if(ability_no==1)
                {
                    obstacleX.erase(obstacleX.begin()+i);
                    obstacleY.erase(obstacleY.begin()+i);
                    Border[Herox][Heroy]='H';
                }
                else
                {
                    throw 1;
                }
            }
            else if(obstacleX[i]==(m-2))
            {
                Border[obstacleX[i]][obstacleY[i]]=' ';
                obstacleX.erase(obstacleX.begin()+i);
                obstacleY.erase(obstacleY.begin()+i);
            }
            else
            {
                Border[obstacleX[i]][obstacleY[i]]=' ';
                ++obstacleX[i];
                Border[obstacleX[i]][obstacleY[i]]='O';
                i++;
            }
        }
    }
    void Draw()
    {
        system("cls");
        for(int i=0;i<m;i++)
        {
            for(int j=0;j<n;j++)
            {
                cout << Border[i][j];
            }
            cout << endl;
        }
        time_t now = time(0);
        tm *ltm = localtime(&now);
        if(ability_no!=0)
        {
            if((T-ltm->tm_sec)>0)
            {
                cout << T-ltm->tm_sec;
            }
            else
            {
                cout << T - ltm->tm_sec + 60;
            }
        }
    }
    void generate_ability()
    {
        int x;
        if(abilityX==0 && ability==none && T==-1)
        {
           for(int i=0;i<1;i++)
           {
                abilityX=1;
                time_t now = time(0);
                tm *ltm = localtime(&now);
                srand(ltm->tm_sec*z++);
                x=rand()%(n-2)+ 1;
                abilityY=x;
                for(int i=0;i<obstacleX.size();i++)
                {
                    if(abilityY==obstacleY[i] && abilityX==obstacleX[i])
                    {
                        abilityX=0;
                        abilityY=1;
                        this->generate_ability();
                        return;
                    }
                }
                srand(ltm->tm_sec*z++);
                if((rand()%4)==1)
                {
                    ability=invisible;
                    Border[1][x]='I';
                }
                else if((rand()%4)==2)
                {
                    ability=destroy;
                }
                else
                {
                    ability=double_point;
                    Border[1][x]='C';
                }
           }
        }
        else
        {
            time_t now = time(0);
            tm *ltm = localtime(&now);
            if(T==ltm->tm_sec)
            {
                T=-1;
                ability=none;
                abilityX=0;
                abilityY=1;
                ability_no=0;
            }
        }
    }
    void move_ability()
    {
        if(abilityX!=0 && abilityY!=0 && T==-1)
        {
            if(abilityX==Herox && abilityY==Heroy)
            {
                time_t now = time(0);
                tm *ltm = localtime(&now);
                T = (ltm->tm_sec + 20)%60;
                if(ability==invisible)
                {
                    ability_no=1;
                }
                else if(ability==destroy)
                {
                    ability_no=2;
                }
                else
                {
                    ability_no=3;
                }
            }
            else if(abilityX==(m-2))
            {
                Border[abilityX][abilityY]=' ';
                abilityX=0;
                abilityY=0;
                ability_no=0;
                ability=none;
            }
            else
            {
                Border[abilityX][abilityY]=' ';
                ++abilityX;
                if(ability==invisible)
                {
                    Border[abilityX][abilityY]='I';
                }
                else if(ability==destroy)
                {
                    Border[abilityX][abilityY]='D';
                }
                else
                {
                    Border[abilityX][abilityY]='C';
                }
            }
        }
    }
    void kill_enemy()
    {
        for(int i=0;i<bulletx.size();i++)
        {
            for(int j=0;j<obstacleX.size();)
            {
                if(bulletx[i]==obstacleX[j] && bullety[i]==obstacleY[j])
                {
                    score=score+10;
                    obstacleX.erase(obstacleX.begin()+j);
                    obstacleY.erase(obstacleY.begin()+j);
                    break;
                }
                else
                {
                    j++;
                }
            }
        }
    }
    void bullet()
    {
        if(ability_no==2)
        {
            Border[prevx][prevy]=' ';
        }
        for(int i=0;i<bulletx.size();)
        {
            if(bulletx[i]<2)
            {
                Border[bulletx[i]][bullety[i]]=' ';
                bulletx.erase(bulletx.begin()+i);
                bullety.erase(bullety.begin()+i);
            }
            else
            {
                Border[bulletx[i]][bullety[i]]=' ';
                --bulletx[i];
                Border[bulletx[i]][bullety[i]]='|';
                i++;
            }
        }
        if(ability_no==2)
        {
           Border[Herox-1][Heroy]='|';
            bulletx.push_back(Herox-1);
            bullety.push_back(Heroy);
            prevx=Herox-1;
            prevy=Heroy;
        }
    }

    ~Moving()
    {
        delete Border;
    }
};

int main()
{
    int score=50,lvl=60;
    Moving obj;
    obj.Draw_ob();
    while(true)
    {
        if(obj.score>=score && lvl>0)
        {
            score+=obj.score;
            lvl=lvl-5;
        }
        try
        {
            obj.Draw();
            obj.start();
            obj.obstacle();
            obj.generate_ability();
            obj.bullet();
            obj.kill_enemy();
            obj.move_obstacle();
            obj.move_ability();
            Sleep(lvl);
        }
        catch(int i)
        {
            cout << "GAME OVER" << endl;
            break;
        }
    }
    cout << "FINAL SCORE: " <<  obj.score;
    return 0;
}
