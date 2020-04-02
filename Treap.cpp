#define rand() (rand() * rand() + rand() + 1)
 
struct Node{
 
	int left, right;
	int key;
	int prior;

	Node(int k = 0){
		left = right = key = prior = 0;
		key = k;
	}

	bool operator<(Node& A){
		return key < A.key;
	}
	bool operator==(Node& A){
		return key == A.key;
	}
 
};
 
Node node[2000000];
 
namespace Treap{
 
	int root = 0;
	int ind = 1;
 
	int new_node(){
		return ind++;
	}



	void push(int j){

		if(!j) return;

		int l = node[j].left;
		int r = node[j].right;

		if(l){
			
		}

		if(r){
			
		}


	}

	void print(int j){
		if(!j)return;
		push(j);

		int l = node[j].left;
		int r = node[j].right;

		if(l){
			print(l);
		}
		if(r){
			print(r);
		}
	}

	void up(int j){

		if(!j) return;

		int l = node[j].left;
		int r = node[j].right;


	}

	void split(int j, Node v, int& l, int& r){

		push(j);

		if(!j) l = r = 0;

		else if(node[j] < v){

			split(node[j].right, v, node[j].right, r);

			l = j;

		}

		else{

			split(node[j].left, v, l, node[j].left);
 
			r = j;
 
		}
		
		push(j);
		push(node[j].left);
		push(node[j].right);
		up(j);
 
	}

	void merge(int& j, int l, int r){

		push(l);
		push(r);

		if(!l || !r) j = max(l, r);

		else if(node[l].prior > node[r].prior){

			merge(node[l].right, node[l].right, r);

			j = l;

		} 

		else{

			merge(node[r].left, l, node[r].left);

			j = r;
		}

		push(j);
		push(node[j].left);
		push(node[j].right);
		up(j);

	}

	void insert(int& j, int i){

		push(j);

		if(!j) j = i;

		else if(node[i].prior > node[j].prior){

			split(j, node[i].key, node[i].left, node[i].right);

			j = i;

		}
		else {
			if(node[i] < node[j]) insert(node[j].left, i);
			else insert(node[j].right, i);
		}
 
		push(node[j].left);
		push(node[j].right);
		up(j);
 
	}
	
	int erase(int& j, Node v){

		push(j);

		if(node[j] == v) {
			int ret = j;
			merge(j, node[j].left, node[j].right);
			return ret;
		}
		else{
			if(v < node[j]) return erase(node[j].left, v);
			else return erase(node[j].right, v);
		}
		
		push(node[j].left);
		push(node[j].right);
		up(j);

	}
 
	int add(int v){
		int j = new_node();
		node[j].key = v;
		node[j].prior = rand();
		insert(root, j);
		return j;
	}
 
 
	void update(){
 
 
	}
	
}
