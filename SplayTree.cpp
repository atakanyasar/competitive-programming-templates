struct Node{
	int left, right, parent;
	int key, id;
	Node(int k = 0, int i = 0){
		left = right = parent = 0;
		key = k;
		id = i; 
	}

	bool operator<(Node& A){
		return key < A.key || (key == A.key && id < A.id);
	}
} node[2000000];

struct SplayTree{
	int root = 0;

	int new_node(int k, int i){
		static int ind = 1;
		node[ind] = Node(k, i);
		return ind++;
	}

	void Lrotate(int& j){
		int r = node[j].right;
		if(!r) return;

		node[r].parent = node[j].parent;
		node[j].parent = r;

		node[j].right = node[r].left;
		node[r].left = j;

		j = r;
	}

	void Rrotate(int& j){
		int l = node[j].left;
		if(!l) return;

		node[l].parent = node[j].parent;
		node[j].parent = l;

		node[j].left = node[l].right;
		node[l].right = j;

		j = l;
	}

	void Splay(int j){	
		while(root != j){
			int& l = node[root].left;
			int& r = node[root].right; 
			
			if(node[j] < node[root]){

				if(j == l){
					Rrotate(root);
				}
				else{
					if(node[j] < node[l]){
						Rrotate(l);
						Rrotate(root);
					}
					else{
						Lrotate(l);
						Rrotate(root);
					}
				}

			}
			else{
				if(j == r){
					Lrotate(root);
				}
				else{
					if(node[j] < node[r]){
						Rrotate(r);
						Lrotate(root);
					}
					else{
						Lrotate(r);
						Lrotate(root);
					}
				}
			}
		}		
	}

	void insert(int& j, int i){
		if(!j){
			j = i;
			Splay(i);
		}
		else{
			if(node[i] < node[j]){
				insert(node[j].left, i);
			}
			else insert(node[j].right, i);
		}
	}
	void add(int k, int i){
		insert(root, new_node(k, i));
	}

};