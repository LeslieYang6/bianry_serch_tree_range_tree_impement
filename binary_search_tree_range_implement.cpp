#include<iostream>
#include<random>
using namespace std;


struct node{
    int key;
    int size;//用于储存以此节点为root结点的二叉树的结点个数
    node *right;
    node *left;
    explicit node(int key)
    {
        this->key=key;
        size=1;
        right= nullptr;
        left=  nullptr;
    }
};

//用于更新ｓｕｂｔｒｅｅ的大小
void getsubtreesize(node*root)
{
    if(root->left&&root->right)
        root->size=root->left->size+root->right->size+1;
    if(root->left&&!root->right)
        root->size=root->left->size+1;
    if(!root->left&&root->right)
        root->size=root->right->size+1;
}

node *NewNode(int key)
{
    node *newnode;
    newnode=new node(key);
    return newnode;
}

node *insert(node*root,int key)
{
    //root为空，申请新结点
    if(!root)
       return NewNode(key);
    if(key>root->key)
        root->left=insert(root->left,key);
    else
        root->right=insert(root->right,key);
    getsubtreesize(root);
    return root;
}
//用于获得第ｉｔｈ元素
int Rank(node *root,int i)
{   if(i==root->right->size+1)
       return root->key;
    if(i<(root->right->size+1))
        return Rank(root->right,i);
    else return Rank(root->left,i-root->right->size-1);

}

//删除元素
node *Delete(node*root,int key)
{
    if(!root)
    {
        cout<<"not found";
        return root;
    }
    if(key>root->key)
        root->left=Delete(root->left,key);
    if(key<root->key)
        root->right=Delete(root->right,key);
    if(root->key==key)
    {
        if(root->right== nullptr)
            root=root->left;
        else
            {
            if (root->left == nullptr)
                root = root->right;
            else
            {
                node*temp=root->right;
                while(temp->left)
                    temp=temp->left;
                root->key=temp->key;
                temp->key=key;
                root=Delete(root->right,key);
            }
        }
    }
    if(root)
        getsubtreesize(root);
    return root;
}

//用于排序和显示
void inordertraverse(node *root)
{
    if(!root)
        return;
    inordertraverse(root->right);
    cout<<root->key<<" ";
    inordertraverse(root->left);
}

int main()
{
    node *root=nullptr;
    for(int i=0;i<1000;i++)
        root=insert(root,rand()%1000);
    root=Delete(root,958);
    inordertraverse(root);
    cout<<Rank(root,999);
}