#include<iostream>
#include<fstream>
#include <vector>
#include<map>
#include<sstream>
using namespace std;
typedef struct node* LPTR;
 struct node
{
    string item;
    int cnt;
    vector<LPTR> child;
};
LPTR T;
map<string,int> L1;
LPTR new_node(string k)
{
    LPTR temp=new (struct node);
    temp->item=k;
    temp->cnt=1;
    return temp;
}
void insert(vector<string> trans, LPTR &p, int i)
{
    if(i==trans.size())
        return ;
    int flag=0;
    for(int j=0; j<p->child.size(); j++)
    {
        if(p->child[j]->item==trans[i])
        {
            flag=1;
            p->child[j]->cnt++;
            insert(trans, p->child[j], i+1);
            break;
        }
    }
    if(flag==0)
    {
       LPTR temp=new_node(trans[i]);
        p->child.push_back(temp);
        insert(trans, p->child[p->child.size()-1], i+1);
    }
}

bool compare(string x, string y)
{
    return (L1[x] > L1[y]);
}

void print_tree(LPTR p, vector<pair<string,int>> path)
{
    path.push_back({p->item,p->cnt});
    
    for(int i=0; i<p->child.size(); i++)
    {
        print_tree(p->child[i], path);
    }
    if(p->child.size()==0)
    {
        for(int i=0; i<path.size(); i++)
        {cout<<path[i].first<<","<<path[i].second<<"  ";}
        cout<<endl;
    }
    path.pop_back();
    
}
int main()
{
    //Taking input from AprioriInput.txt to vvs G
    vector<vector<string>> G;
    int record_cnt=0;
    {
    ifstream ifs("AprioriInput.txt");
    string temp;
    while(getline(ifs,temp))
    {
        stringstream ss(temp);
        string temp1;
        vector<string> S;
        while(getline(ss,temp1,' '))
        {
            if(temp1[0]!='T')
            S.push_back(temp1);
        }
        record_cnt++;
        G.push_back(S);
    }
    ifs.close();
    }
    
    //Finding  C1
    
    for(int i=0; i<G.size(); i++)
    {
        for(int j=0; j<G[i].size(); j++)
        {
            L1[G[i][j]]++;
        }
    }
    
    
    T=new_node("{}");
    for(int i=0; i<G.size(); i++)
    {
        sort(G[i].begin(), G[i].end(), compare);
        insert(G[i], T, 0);
    }
    
    vector<pair<string,int>> path;
    print_tree(T,path );
}
