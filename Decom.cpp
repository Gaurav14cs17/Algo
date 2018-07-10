#include"bits/stdc++.h"
using namespace std;
const int N = 20010;



struct Trie{
int root , tot;
int child[N*30][2] , cnt[30*N];

void init( ){
root = tot =1;
child[1][0] = child[1][1] = 0;
cnt[1] =1;
}




void insert( const int x ){  
int * node = & root;
for( int i =31 ; i>=0 ; --i ){
    node = &child[*node][(x>>i)&1];
    if(*node ==0){
         *node = ++tot;
          child[tot][0] = child[tot][1] =0 ;
          cnt[tot] = 0;
    }
    cnt[*node]++;
  }

}


int query( const int x){

int res =0;
int * node = &root ;
for( int i = 31 ; i>=0 ; --i ){

int now = (x>>i )&1;
int store = *node;

if(now ==0){
    node = &child[*node][1];
    if(cnt[*node]) res = res + (1<<i);
    else node = &child[store][0];
}else{
node = &child[*node][0];
if(cnt[*node]) res = res +  (1<<i);
else node = &child[store][1];

}

}


return res;
}


} trie;



const int block = 200;
int n, m, t;
int A[N], B[N];
int prefix[block][N], suffix[block][N];



int main( void ){
scanf("%d%d%d",&n,&m,&t);
for( int i =1 ; i<=n ; ++i ){
    scanf("%d",A+i);
    B[i]  =A[i];
    A[i] = A[i] ^A[i-1];
}


for(int i= n-1 ; i>=1 ; --i )B[i]= B[i] ^ B[i+1];


for( int i =1 ; i<=n ; i = i + block ){
    int id = (i-1)/block, Max =0;
    trie.init();
    for( int j =i ; j<=n; ++j ){
        trie.insert( A[j-1]);
        Max = max( Max , trie.query( A[j]));
        prefix[id][j]=Max;
    }
}


for( int i = block ; i<=n ; i = i + block ){

    int id = i/block -1 , Max=0;
    trie.init();
    for( int j =i ; j>=1 ; --j ){
        trie.insert(B[j+1]);
        Max = max( Max , trie.query( B[j]));
        suffix[id][j] =  Max;
    }
}

int ans =0;
for( int i =1 ; i<=m ; ++i ){
    int x, y;
    scanf("%d%d",&x,&y);
    int l = ( x + ans *t )%n +1;
    int r = ( y + ans*t)%n +1;
    if( l >r ) swap( l ,r );


    ans = 0;
    trie.init();
    if(r - l +1 <= block ){
        for( int j = l ; j<=r ; ++j ){
            trie.insert( A[j-1]);
            ans = max( ans , trie.query(A[j]));
        }
    }else{
    int il = ( l-1+block-1)/block;
    int ir = r/block -1;

    ans = max( prefix[il][r] , suffix[ir][l]);

    for( int j = l ; j<=il*block; ++j )trie.insert(A[j-1]);
    for( int j = (ir+1)*block+1 ; j<=r ; ++j )
        ans = max(ans , trie.query( A[j]));

    }
    printf("%d\n",ans);
}



}

