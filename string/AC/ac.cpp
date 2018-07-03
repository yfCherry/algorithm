#include <iostream>
#include <string.h>
#include <algorithm>
#include <queue>

#define MAX_N 1000006
#define MAX_Tot 500005

using namespace std;

struct Aho
{
    struct state
    {
        int next[26];
        int fail,cnt;
    }stateTable[MAX_Tot];

    int size;
    queue<int> q;

    void init()
    {
        while(q.size())
            q.pop();

        int i;
        for(i=0;i<MAX_Tot;i++)
        {
            memset(stateTable[i].next,0,sizeof(stateTable[i].next));
            stateTable[i].fail = stateTable[i].cnt = 0;
        }
        size = 1;
    }

    void insert(char* s)
    {
        int i;
        int n = strlen(s);
        int now = 0;
        for(i=0;i<n;i++)
        {
            char c = s[i];
            if(!stateTable[now].next[c-'a'])
                stateTable[now].next[c-'a'] = size++;
            now = stateTable[now].next[c-'a'];
        }
        stateTable[now].cnt++;
    }

    //构造失配指针
    void build()
    {
        stateTable[0].fail = -1;
        q.push(0);

        while(q.size())
        {
            int i;
            int u = q.front();
            q.pop();
           for(i=0;i<26;i++)
           {
                if(stateTable[u].next[i])
                {
                    if(u == 0)
                        stateTable[stateTable[u].next[i]].fail = 0;
                    else
                    {
                        int v = stateTable[u].fail;
                        while(v != -1)
                        {
                            if(stateTable[v].next[i])
                            {
                                stateTable[stateTable[v].next[i]].fail = stateTable[v].next[i];
                                break;
                            }
                            v = stateTable[v].fail;
                        }
                        if(v== -1)
                            stateTable[stateTable[u].next[i]].fail = 0;
                    }
                    q.push(stateTable[u].next[i]);
                }
           }
        }
    }

    int Get(int u)
    {
        int res = 0;
        while(u)
        {
            res = res + stateTable[u].cnt;
            stateTable[u].cnt = 0;
            u = stateTable[u].fail;
        }
    }

    int match(char* s)
    {
        int n = strlen(s);
        int i,res,now;
        res = now = 0;
        for(i=0;i<n;i++)
        {
            char c = s[i];
            if(stateTable[now].next[c-'a'])
            {
                now = stateTable[now].next[c-'a'];
            }
            else
            {
                int p = stateTable[now].fail;
                while(p != -1 && stateTable[p].next[c-'a'] == 0)
                    p = stateTable[p].fail;
                if(p == -1)
                    now = 0;
                else
                    now = stateTable[p].next[c-'a'];
            }

            if(stateTable[now].cnt)
                res = res + Get(now);
        }

        return res;
    }
}aho;

int T;
int N;
char s[MAX_N];

int main()
{
    cin>>T;
    while(T--)
    {
        int i;
        aho.init();
        cin>>N;
        for(i=0;i<N;i++)
        {
            cin>>s;
            aho.insert(s);
        }
        aho.build();
        cin>>s;
        cout<<aho.match(s)<<endl;
    }
    return 0;
}
