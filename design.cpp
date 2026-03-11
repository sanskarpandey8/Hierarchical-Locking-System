#include <iostream>
#include<bits/stdc++.h>

using namespace std;

struct TreeNode{
	string name;
	int lockedBy;
	bool isLocked;
	vector<TreeNode*> childs;
	TreeNode* parent;
	set<TreeNode*> lockedDescendents;

	TreeNode(string nm, TreeNode* par){
		name=nm;
		lockedBy=-1;
		parent=par;
		isLocked=false;
	}

	void addChild(vector<string> &a){
		for(string &nm: a){
			childs.push_back(new TreeNode(nm, this));
		}
	}
};

struct MAryTree{
	TreeNode * root;
	unordered_map<string, TreeNode*> nameToTreeNodeMapping;
	MAryTree(string name){
		root= new TreeNode(name, nullptr);
	}

	void makeMArtTree(vector<string> &a, int m){
		queue<TreeNode*>q;
		int k=1,i,n=a.size();
		q.push(root);
		while(!q.empty()){
			TreeNode* r= q.front();
			q.pop();
			nameToTreeNodeMapping[r->name]=r;
			vector<string>b;
			for(i=k;i<min(n,k+m);i++){
				b.push_back(a[i]);
			}
			r->addChild(b);
			for(TreeNode* child: r->childs){
				q.push(child);
			}
			k=i;
		}
	}

	void updateParents(TreeNode * r, TreeNode * curr){
		while(r){
			r->lockedDescendents.insert(curr);
			r=r->parent;
		}
	}
	bool lock(string name, int id){
		TreeNode* r= nameToTreeNodeMapping[name];
		if(r->isLocked || r->lockedDescendents.size())return false;
		TreeNode *par= r->parent;
		while(par){
			if(par->isLocked)return false;
			par=par->parent;
		}
		updateParents(r->parent, r);
		r->isLocked=true;
		r->lockedBy=id;
		return true;
	}

	bool unlock(string name, int id){
		TreeNode* r= nameToTreeNodeMapping[name];
		if(!r->isLocked || r->lockedBy!=id)return false;
		TreeNode *par= r->parent;
		while(par){
			par->lockedDescendents.erase(r);
			par=par->parent;
		}
		r->isLocked=false;
		r->lockedBy=-1;
		return true;
	}
	bool upgradeLock(string name, int id){
		TreeNode* r= nameToTreeNodeMapping[name];
		if(r->isLocked || r->lockedDescendents.size()==0)return false;
		for(TreeNode* ld: r->lockedDescendents){
			if(ld->lockedBy!=id)return false;
		}
		TreeNode *par= r->parent;
		while(par){
			if(par->isLocked)return false;
			par=par->parent;
		}
		set<TreeNode*>stt= r->lockedDescendents;
		for(TreeNode* ld: stt){
			unlock(ld->name, id);
		}
		lock(name,id);
		return true;
	}
};

int main() {
	int n,m,t,i,opType,id;
	string name;
	cin>>n>>m>>t;
	vector<string>a(n);
	for(i=0;i<n;i++){
		cin>>a[i];
	}
	MAryTree * tree= new MAryTree(a[0]);
	tree->makeMArtTree(a, m);
	while(t--){
		cin>>opType>>name>>id;
		if(opType==1){
			if(tree->lock(name, id)){
				cout<<"true";
			}
			else cout<<"false";
		} else if (opType==2) {
			if(tree->unlock(name, id)){
				cout<<"true";
			}
			else cout<<"false";
		} else if (opType==3) {
			if(tree->upgradeLock(name, id)){
				cout<<"true";
			}
			else cout<<"false";
		} 
		cout<<"\n";
	}
}