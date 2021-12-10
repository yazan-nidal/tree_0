#include<iostream>
#include<queue>
#include<stack>
using namespace std;
typedef char type_data;

struct node
{ 
	type_data data;
	int height;
	int ocurrence;
	node* left;
	node* right;
};

int maX(int x,int y)
{ 
	if(x>y)return x;
	return y;
}

int heighT(node *T)
{
	if(T==NULL)return 0;
	return T->height;
}

node* MAK(type_data data)
{ 
	node *T=new node;
	T->data=data;
	T->ocurrence=1;
	T->height=1;
	T->left=T->right=NULL;
	return T;
}

void right_ROTATE(node *&T)
{	
	node *TL=T->left;
	node *TR=TL->right;
	
	TL->right=T;
	T->left=TR;

	T->height=maX(heighT(T->left),heighT(T->right))+1;
	TL->height=maX(heighT(TL->left),heighT(TL->right))+1;

	T=TL;
}

void left_ROTATE(node *&T)
{	
	node *TR=T->right;
	node *TL=TR->left;
	
	TR->left=T;
	T->right=TL;

	T->height=maX(heighT(T->left),heighT(T->right))+1;
	TR->height=maX(heighT(TR->left),heighT(TR->right))+1;

	T=TR;
}

int get_BALANCE(node *T)
{ 
	if(T==NULL)return 0;
	return heighT(T->left)-heighT(T->right);
}

void insert_BST(node *&T,type_data data)
{
	if(T==NULL)T=MAK(data);
else
{ 
	if(data > T->data)insert_BST(T->right,data);
else
{ 
	if(data < T->data)insert_BST(T->left,data);
	else{ T->ocurrence=T->ocurrence + 1;}
}
}

T->height=maX(heighT(T->left),heighT(T->right))+1;

int b=get_BALANCE(T);

if(b < -1 && data > T->right->data){left_ROTATE(T); return;}

if(b > 1 && data < T->left->data){right_ROTATE(T); return;}

if (b > 1 && data > T->left->data)  
{  
	left_ROTATE(T->left);  
    right_ROTATE(T); 
	return;
 }

if (b < -1 && data < T->right->data)  
{  
	right_ROTATE(T->right);  
    left_ROTATE(T); 
	return;
 }

}

node* min_node_VALUE(node *T)  
{  
   node *current=T;  
while (current->left != NULL){current=current->left;}
    return current;  
}

bool node_EXIST(node *T, type_data data) 
{ 
    if (T == NULL)return false;
    if (T->data == data)return true; 
    bool res1=node_EXIST(T->left,data); 
	bool res2=node_EXIST(T->right,data);  
    return res1 || res2; 
}

void bL_DEL(node *&T)
{
		if(T==NULL)return;

	T->height=maX(heighT(T->left),heighT(T->right))+1;

	int b=get_BALANCE(T);

	if(b < -1 && get_BALANCE(T->right) <= 0){left_ROTATE(T); return;}

	if(b > 1 && get_BALANCE(T->left) >= 0){right_ROTATE(T); return;}

	if (b > 1 && get_BALANCE(T->left) < 0)  
	{  
	left_ROTATE(T->left);  
    right_ROTATE(T); 
	return;
	}

	if (b < -1 && get_BALANCE(T->right) > 0)  
	{  
	right_ROTATE(T->right);  
    left_ROTATE(T); 
	return;
	}

}
void delete_NODE(node *&T,type_data data)
{
	if(T==NULL){return;}
	else{
	bL_DEL(T);
	if(data < T->data){bL_DEL(T); delete_NODE(T->left,data); bL_DEL(T); return;}
	if(data > T->data){bL_DEL(T); delete_NODE(T->right,data); bL_DEL(T); return;}
	if(T->left == NULL || T->right == NULL)
	{
		node *temp;
		if(T->left != NULL){temp=T->left;} else{temp=T->right;}
		if(temp == NULL){temp=T; T=NULL;} else{*T=*temp;} delete temp;
	}
	else
	{
		node *temp=min_node_VALUE(T->right);
		T->data=temp->data; T->ocurrence=temp->ocurrence;
		bL_DEL(T);
		delete_NODE(T->right,temp->data);
		bL_DEL(T);
	}
	bL_DEL(T);
	}

}
void delete_node(node *&T,type_data data)
{
	if(T==NULL)return;
	node *T2=NULL;
	queue<node*> q;
	q.push(T);
	while(!q.empty())
	{
	if(!q.empty()){node *t=q.front(); q.pop();
	if(t->left != NULL){q.push(t->left);}
	if(t->right != NULL){q.push(t->right);}
	if(t->data != data){for(int i=0;i<t->ocurrence;i++){insert_BST(T2,t->data);}}
	else{}
	delete t;
		}
	}
	T=T2;
}

void print_inorder(node *T)  
{  
    if(T == NULL)return;  
		print_inorder(T->left);
		cout<<"	"<<T->data<<" the ocurrence : "<<T->ocurrence<<"\n";
		print_inorder(T->right);
}  

int node_LEV(node *T,node *above,bool &b)
{
	if(T==NULL)return 0;
	if(T==above){b=true; return 1;}
	int l=0;
	int l2=0;
	if(!b)
	{l=node_LEV(T->left,above,b)+b;}
	if(!b)
	{l2=node_LEV(T->right,above,b)+b;}
	return l+l2;
}

void print_TREE(node *T)
{   cout<<"\n";
	if(T == NULL){cout<<"	empty tree !! \n\n"; return;}
	int d=(T->height)-1;
	queue<int> h_space;
	queue<int> elemnt;
	for(int i=0;i<=d;i++){ int temp=pow(2.0,(double)(d-i)); h_space.push(temp); /*cout<<temp;*/ int temp2=pow(2.0,(double)(i));elemnt.push(temp2);/*cout<<" "<<temp2<<"\n";*/}//cout<<"\n";
	stack<int>space_n;
	int m=0;
	for(int i=1;i<=d;i++){m=(m*2)+1; space_n.push(m);/*cout<<m<<" ";*/}
	space_n.push(0);
	bool b=true;
	queue<node*>q;
	q.push(T);
	node *space=new node; space->right=space->left=NULL;
	int re=0,count=0;
	cout<<"\n";
	for(int i=0;i<=d;i++){
	for(int e=0;e<h_space.front();e++){cout<<" ";}
	for(int j=0;j<elemnt.front();j++){
	node *t=q.front(); q.pop();
	if(t->left != NULL){q.push(t->left);}else{q.push(space); }
	if(t->right != NULL){q.push(t->right);}else{q.push(space);}
	if(t==space){cout<<" ";}
	else{cout<<t->data;}
	for(int z=0;z<space_n.top();z++){cout<<" ";}
	}cout<<"\n\n"; elemnt.pop();  h_space.pop(); space_n.pop();
	
	}
	cout<<"\n	end print tree ; \n\n";
}

void print_lev_by_LEV(node *T)
{
	 cout<<"\n";
	if(T == NULL){cout<<"\n	empty tree !! \n\n"; return;}

	queue<node*>q;
	q.push(T);
	
	while(!q.empty())
	{
		node *t=NULL;
		t=q.front(); q.pop(); cout<<t->data<<" ";
	
		if(t->left != NULL){q.push(t->left);}
		if(t->right != NULL){q.push(t->right);}
		bool hg=false,hj=false;
		if(!q.empty()){
			if(node_LEV(T,t,hg) < node_LEV(T,q.front(),hj))
			{cout<<"\n";}}
	}

		cout<<"\n	end print level by level ; \n\n";

}



void destruc_TREE(node *&T)
{
	queue<node*> q;
	if(T==NULL)return;
	q.push(T);
	while(!q.empty())
	{
		if(!q.empty()){node *t=q.front(); q.pop();
	if(t->left != NULL){q.push(t->left);}
	if(t->right != NULL){q.push(t->right);}
	delete t;
		}
	}
	T=NULL;
}

bool digtS(char m){if((m>='0')&&(m<='9')){return true;}else{return false;}}

int reaD_INT(node *&T)
{
cout<<"\n	Enter data  -- NOTE:  end input in enter folostop  ' . '\n ";
int pol=0;
int rt=1;
while(true){
pol=0;
char m[100]=" ";
cin>>m;
if(m[0]=='.'){return 0;}
int k=1;
int i=0;
if(m[i]=='-'){k=-1; i++;}
if(digtS(m[i])==1){
while(digtS(m[i])==1 && m[i]!=NULL && m[i]!='.'){
pol=pol*10+(m[i++]-'0');}
pol*=k;
}
insert_BST(T, pol); 
if(m[i]=='.'){
return 0;}

}
cout<<"\n\n";
}//end read

void reaD_CHAR(node *&T){
cout<<"\n Enter data  -- NOTE:  end input in enter folostop  ' . '\n ";
char m;
cin>>m;
while(m != '.')
{ insert_BST(T,m); 
cin>>m;
}
cout<<"\n\n";
}
void L_M(node *&T)
{int r=-4;
while(r!=8)
{
	cout<<"	1- Read Tree :\n";
	cout<<"	2- Delete node :\n";
	cout<<"	3- Insert node :\n";
	cout<<"	4- Print Tree inorder :\n";
	cout<<"	5- Print Tree as a Tree :\n";
	cout<<"	6- Print tree levl by levrl :\n";
	cout<<"	7- Clear Screen :\n";
	cout<<"	8- Exait ! \n";
	cout<<"	Enter opthion : "; cin>>r;

	switch(r)
	{
	case 1:{
		if(T==NULL){reaD_CHAR(T);}
		else{
			destruc_TREE(T); 
			T=NULL; 
			reaD_CHAR(T); 
			}
		   break;
		   };

	case 2:{
	type_data kn;
	cout<<"\n	Enter node want be deleted : "; cin>>kn;
	if(node_EXIST(T,kn)){delete_NODE(T,kn);}
	else{cout<<"\n	not found the node \n\n";}
		   break;
		   };

	case 3:{
	type_data kn;
	cout<<"\n	Enter data want be insert : "; cin>>kn;
	insert_BST(T,kn);
		   break;
		   };

	case 4:{
	cout << "\n	Inorder traversal for the balanced binary search tree is: \n\n";
	 if(T == NULL){cout<<"\n	empty tree !! \n\n";}  
	 else{
	print_inorder(T);  
	cout<<"\n	end print Inorder ; \n\n";}
		   break;
		   };

	case 5:{
    cout<<"\n	traversal for the balanced binary search tree  as a tree : \n\n";
	print_TREE(T);
		   break;
		   };
	case 6:{
	cout<<"\n	traversal for the balanced binary search tree  level by level : \n\n";
	print_lev_by_LEV(T);
		   break;
		   };

	case 7:{system("cls"); break;};

	case 8:{break;};

	default:{cout<<"\n	error opthion \n\n";};

	}
}
cout<<"\n\n	End of PRoGRaM :-> \n\n";
}

void main()
{
node *kT=NULL;
L_M(kT);


}