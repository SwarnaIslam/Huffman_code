#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
char str[1000];
ll n;//the length of the min heap array
set<char>character;//to get distinct characters.
map<char,ll>frequency;
map<char,string>encode;
map<string,char>decode;//for first way
struct node{
          char ch;
          ll freq;
          struct node *left,*right;
};
struct node *pq[1000];
struct node* new_node(char a,ll f,struct node *left_child,struct node *right_child)//creating new node
{
          struct node *temp=(struct node*)malloc(sizeof(struct node));
          temp->ch=a;
          temp->freq=f;
          temp->left=left_child;
          temp->right=right_child;
          return temp;

}
void show_frequency_table()
{
          set<char>::iterator it;
          cout<<"Frequency table:"<<endl;
          for(it=character.begin();it!=character.end();it++)
                    cout<<*it<<":"<<frequency[*it]<<endl;
}
void encoding(struct node *temp,string strg)
{
          if(temp->left==NULL&&temp->right==NULL)
          {
                    encode[temp->ch]=strg;
                    decode[strg]=temp->ch;
                    if(temp->ch==' '){cout<<"Blank space";}
                    else if(temp->ch=='\n'){cout<<"New line";}
                    else{cout<<temp->ch;}
                    cout<<":"<<strg<<endl;
                    return;
          }
          encoding(temp->left,strg+"0");
          encoding(temp->right,strg+"1");
}
//First way:(using map)
void decoding(string prefix_code)
{
          ll i;
          string s;
          for(i=0;prefix_code[i]!='\0';i++)
          {
                    s.push_back(prefix_code[i]);
                    if(decode[s]!='\0'){
                              cout<<decode[s];
                              s="";
                    }
          }
}
//Second way:(traversing tree)
/*void decoding(string prefix_code,struct node *root)
{
          ll i;
          struct node *r=(struct node*)malloc(sizeof(struct node));
          r=root;
          for(i=0;prefix_code[i]!='\0';i++)
          {
                    if(prefix_code[i]=='1'&&r->right!=NULL)r=r->right;
                    else if(prefix_code[i]=='0'&&r->left!=NULL)r=r->left;
                    if(r->ch!='\0'){
                              cout<<r->ch;
                              r=root;
                    }
          }
}*/
void min_heapify(ll n,ll root)
{
          ll l=root*2+1,r=root*2+2,minimum=root;
          if(l<n&&pq[minimum]->freq>pq[l]->freq)minimum=l;
          if(r<n&&pq[minimum]->freq>pq[r]->freq)minimum=r;
          if(pq[minimum]->freq!=pq[root]->freq)
          {
                    swap(pq[minimum],pq[root]);
                    min_heapify(n,minimum);
          }
}
void insert_heap(ll len)
{
          while(len)
          {
                    ll parent=(len-1)/2;
                    if(pq[parent]->freq>pq[len]->freq){
                              swap(pq[parent],pq[len]);
                              len=parent;
                    }
                    else return;
          }
}
struct node* extract_min()
{
        if(n==0)return NULL;
        struct node *r=(struct node*)malloc(sizeof(struct node));
        r=pq[0];
        swap(pq[0],pq[n-1]);
        n--;
        min_heapify(n,0);
        return r;
}
void huffman_code()
{
          set<char>::iterator it;
          ll i=0;
          n=character.size();
          for(it=character.begin();it!=character.end();it++)
          {
                    pq[i]=new_node(*it,frequency[*it],NULL,NULL);
                    insert_heap(i);
                    i++;
          }
          while(n>1)
          {
                    struct node *left_child=(struct node*)malloc(sizeof(struct node)),*right_child=(struct node*)malloc(sizeof(struct node));
                    left_child=extract_min();
                    right_child=extract_min();
                    pq[n]=new_node('\0',left_child->freq+right_child->freq,left_child,right_child);//creating the parent
                    insert_heap(n);// inserting the parent in the min heap
                    n++;
          }
          show_frequency_table();
          struct node *root=NULL;
          root=pq[0];
          encoding(root,"");
          string pre_code;//prefix code
          cout<<"Encoded message is:"<<endl;
          for(i=0;str[i]!='\0';i++)
          {
                    cout<<encode[str[i]];
                    pre_code=pre_code+encode[str[i]];
          }
          cout<<"\nLength of the prefix code:"<<pre_code.size()<<endl;
          cout<<"Decoded message is:"<<endl;
          decoding(pre_code);
}
int main()
{
          FILE *file;
          file=fopen("Message.txt","r");
          char a;
          ll i=0;
          while((a=fgetc(file))!=EOF)
          {
                    str[i]=a;
                    frequency[a]++;
                    character.insert(a);
                    i++;
          }
          huffman_code();
          cout<<"\nActual message is:\n"<<str<<endl;
}
