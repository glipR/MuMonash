#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
const int MAX=1e5+10;
const int MOD=1e9+7;
typedef long long ll;
vector<int>e[MAX];
ll d[MAX][4];
ll suf[MAX];
ll p_sum[MAX];
ll s_sum[MAX];
ll p_s[MAX];
ll s_s[MAX];
void dfs(int k,int fa)
{
    for(int i=0;i<e[k].size();i++)if(e[k][i]==fa)swap(e[k][i],e[k][0]);
    for(int i=1;i<e[k].size();i++)dfs(e[k][i],k);
    suf[e[k].size()]=0;
    p_sum[0]=s_sum[e[k].size()]=1;
    p_s[0]=s_s[e[k].size()]=1;
    for(int i=1;i<e[k].size();i++)
    {
        int nex=e[k][i];
        p_sum[i]=p_sum[i-1]*d[nex][2]%MOD;
        p_s[i]=(d[nex][0]+d[nex][2])%MOD*p_s[i-1]%MOD;
    }
    for(int i=e[k].size()-1;i>=1;i--)
    {
        int nex=e[k][i];
        suf[i]=(d[nex][0]+d[nex][2])%MOD*suf[i+1]%MOD;
        (suf[i]+=(d[nex][0]+d[nex][1])%MOD*s_s[i+1]%MOD)%=MOD;
        s_sum[i]=s_sum[i+1]*d[nex][2]%MOD;
        s_s[i]=(d[nex][0]+d[nex][2])%MOD*s_s[i+1]%MOD;
    }
    d[k][0]=1;
    for(int i=1;i<e[k].size();i++)d[k][0]=d[k][0]*d[e[k][i]][2]%MOD;
    for(int i=1;i<e[k].size();i++)
    {
        int nex=e[k][i];
        d[k][0]+=(d[nex][0]+d[nex][1])%MOD*p_sum[i-1]%MOD*s_sum[i+1]%MOD;
        d[k][1]+=(d[nex][0]+d[nex][1])%MOD*((p_s[i-1]*s_s[i+1]%MOD-p_sum[i-1]*s_sum[i+1]%MOD+MOD)%MOD)%MOD;
        d[k][2]+=(d[nex][0]+d[nex][1])%MOD*suf[i+1]%MOD*p_s[i-1]%MOD;
        d[k][0]%=MOD;
        d[k][1]%=MOD;
        d[k][2]%=MOD;
    }
}
int main()
{
    int n;
    cin>>n;
    for(int i=1;i<n;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        e[x].push_back(y);
        e[y].push_back(x);
    }
    e[1].push_back(0);
    memset(d,0,sizeof d);
    dfs(1,0);
    cout<<(d[1][0]+d[1][2])%MOD<<endl;
    return 0;
}
