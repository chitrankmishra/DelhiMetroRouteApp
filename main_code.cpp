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
struct node1
    {
        vector <float>p;
    }P[V];
struct station_code
{
    string name;
    int code;
    string color;
};
struct station_code station[V];
float graph[V][V];
string makecapital(string str)
{
    for(int i=0;i<str.length();i++)
    {
        if(str[i]>96&&str[i]<123)
            str[i]=str[i]-32;
    }
    return str;
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
