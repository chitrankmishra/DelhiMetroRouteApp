#include <iostream>
#include<stdio.h>
#include <limits.h>
#include<string.h>
#include<math.h>
#include<cstdlib>
#include<vector>
#include<fstream>
#include<time.h>
#include<windows.h>
using namespace std;
const int V=248;
struct station_code
{
    string name;
    int code;
    string color;
};
struct station_code station[V];
float graph[V][V];

struct node1
    {
        vector <float>p;
    }P[V];
string makecapital(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>96&&str[i]<123)
            str[i]=str[i]-32;
    }
    return str;
}
void drawbox(int, int, int, int, int);
void secondWindow();
void clrscreen();
void delay(unsigned int ms);
void gotoxy(int x,int y);
int timetaken(float dist);
int money(float dist);
void Details(int t);
void Path(float dist,int e,int st);
int minDistance(float dist[], bool sptSet[]);
void dijkstra(float graph[V][V], int src,int targ);
int printSolution(float dist[], int n,int src,int temp);
void take_input();
void logo(int x, int y);
void secondWindow();
void UI();

COORD coord;
void clrscreen()
{
    system("cls");
    drawbox(1,0,117,29,0);
}



void Path(float dist,int e,int st)
{
    int t=e,s;
    gotoxy(16,11);
    cout<<"THE SHORTEST PATH IS : ";

    int pos_x=12;
    int pos_y=15;
    vector <int> path;
    path.push_back(t);
    while(t!=st)
    {
        s=P[t].p.size();
        t=P[t].p[s-1];
        path.push_back(t);
    }
    vector <int>::iterator i=path.end();
    string str;
    string color;
    gotoxy(44,13);
    cout<<"****** LOADING ******";
    delay(2000);
    gotoxy(42,13);
    cout<<"****** ROUTE FOUND ******";
    vector<int>::iterator i2=path.end();
    i2--;
    int n_of_stations=0;
    while(i!=path.begin())
    {
        i--;
        color=station[*i].color;
        if(color=="BLUE")
            system("color 09");
        else if(color=="YELLOW")
            system("color 06");
        else if(color=="PINK")
            system("color 0D");
        else if(color=="RED")
            system("color 04");
        else if(color=="MAGENTA")
            system("color 05");
        else if(color=="VOILET")
            system("color 01");
        else if(color=="GREEN")
            system("color 02");
        else if(color=="AQUA")
            system("color 03");
        else if(color=="ORANGE")
            system("color 0C");

        if(i!=i2)
        {
        if(station[*(i2)].color!=station[*(i)].color)
        {
            pos_x=8;
            pos_y++;
            gotoxy(pos_x,pos_y);
            cout<<"{change from "<<station[*i2].color<<" to "<<station[*i].color<<"}";
            pos_x=12;
            pos_y++;
            gotoxy(pos_x,pos_y);
        }
        i2--;
        }
        str=station[*i].name;
        if(pos_x+5+str.size()<106)
        {
            gotoxy(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        else
        {
            pos_x=12;
            pos_y++;
            gotoxy(pos_x,pos_y);
            cout<<" ->> "<<str;
            pos_x=pos_x+str.size()+5;
        }
        n_of_stations++;
        delay(700);
    }
    delay(1000);
    gotoxy(72,11);
    cout<<"PATH LENGTH IS : "<<dist<<" KM";
    delay(1000);
    gotoxy(16,10);
    cout<<"AVERAGE TIME : "<<timetaken(dist)<<" MIN";
    delay(1000);
    gotoxy(72,10);
    cout<<"AVERAGE FARE : Rs. "<<money(dist);
    delay(1000);
    gotoxy(72,12);
    cout<<"NO OF STATIONS : "<<n_of_stations-1;

    delay(2500);
    gotoxy(44,8);
    cout<<"WANT TO SEARCH AGAIN ?  ";
    string choice;
    cin>>choice;
    choice=makecapital(choice);
    if(choice=="Y"||choice=="YES")
        secondWindow();
    gotoxy(5,30);
    char ch;
    scanf("%c",&ch);
    cout<<endl;
}


void dijkstra(float graph[V][V], int src,int targ)
{
    float dist[V];
     bool sptSet[V];
     for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
     dist[src] = 0;
     for (int count = 0; count < V-1; count++)
     {
         int u = minDistance(dist, sptSet);
       sptSet[u] = true;
       for (int v = 0; v < V; v++)
         if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX
                                       && dist[u]+graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
                P[v].p.push_back(u);
            }
     }
     printSolution(dist, V,src,targ);
}


void take_input()
{

        string start_s,end_s,line,col;
        
        cout<<"ENTER THE STARTING STATION:";
        
        getline(cin,start_s);
        cout<<"ENTER THE DESTINATION STATION:"
        getline(cin,end_s);

        //for(int i=0;i<V;i++)
        //cout<<station[i].name<<" "<<station[i].code<<" "<<station[i].color<<endl;

        start_s=makecapital(start_s);
        end_s=makecapital(end_s);

        int startcode,endcode;
        int startflag=0,endflag=0;
        for(int i=0;i<V;i++)
        {
            if(station[i].name==start_s)
            {
                startcode=station[i].code;
                startflag=1;
            }
            if(station[i].name==end_s)
            {
                endcode=station[i].code;
                endflag=1;
            }
        }

        if(startflag==0)
        {
            cout<<"WRONG STARTING STATION NAME ENTERED";
            char ch;
            scanf("%c",&ch);
            //secondWindow();
            return;
        }
        if(endflag==0)
        {
            cout<<"WRONG DESTINATION STATION NAME ENTERED";
            char ch;
            scanf("%c",&ch);
            //secondWindow();
            return;
        }
         dijkstra(graph,startcode,endcode);
}




int main()
{
    int temp,n1,n2;
    float dis;
    ifstream fin;
    fin.open("node_values_new.txt");
/*     while (fin) {

        getline(fin, line);                                     // Read a Line from File

        cout << line << endl;                                   // Print line in Console
    }
*/
    for(int i=0;i<V;i++)
    {
       for(int j=0;j<V;j++)
        graph[i][j]=0;
    }
    for(int i=1;i<=V;i++)
    {
        fin>>temp;
        fin>>n1;
        //cout<<temp<<" "<<n1<<endl;
        for( int j=0;j<temp;j++)
        {
           fin>>n2;
           fin>>dis;
           //cout<<" "<<n2<<" "<<dis<<endl;
           graph[n1-1][n2-1]=dis;
        }
        //cout<<endl;
    }
        string line,col;
        ifstream code;
        ifstream color;
        code.open("stationcodes.txt");
        color.open("stationcolorcodes.txt");
        for(int i=0;i<V;i++)
        {
            getline(code, line);
            station[i].name=line;
            station[i].code=i;
            getline(color,col);
            station[i].color=col;
        }
    // Writing the matrix
    /*ofstream matrix;
    matrix.open("matrix.txt");
    matrix<<"  ";
    for(int i=0;i<V;i++)
        matrix<<i<<" ";
    matrix<<endl;
    for(int i=0;i<V;i++)
    {
        for(int j=0;j<V;j++)
        {
            if(j==0)
                matrix<<i<<" ";
            matrix<<graph[i][j]<<" ";
        }
        matrix<<endl;
    }*/
    //UI();
    //secondWindow();
    //take_input(graph);
}
