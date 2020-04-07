struct Node{
	int left, right, parent;
	int key, id, size;
	Node(int k = 0, int i = 0){
		left = right = parent = size = 0;
		key = k;
		id = i; 
	}

	bool operator<(Node& A){
		return key < A.key || (key == A.key && id < A.id);
	}

} node[2000000];

int new_node(int k, int i){
	static int ind = 1;
	node[ind] = Node(k, i);
	return ind++;
}
struct SplayTree{
	int root = 0;

	void push(int j){
		if(!j) return;
		int l = node[j].left;
		int r = node[j].right;

		if(l){
		}
		if(r){
		}
	}

	void up(int j){
		if(!j) return;
		int l = node[j].left;
		int r = node[j].right;
		node[j].size = 1;
		if(l){
			node[j].size += node[l].size;
			node[l].parent = j;
		}
		if(r){
			node[j].size += node[r].size;
			node[r].parent = j;
		}

	}

	void rotate(int j){
		if(!j) return;
		assert(node[j].parent);

		int p = node[j].parent;
		int pp = node[p].parent;

		push(p);
		push(j);

		node[j].parent = pp;
		if(pp){
			if(node[pp].left == p) node[pp].left = j;
			if(node[pp].right == p) node[pp].right = j;
		}
		if(j == node[p].left){
			node[p].left = node[j].right;
			node[j].right = p;
		}
		else{
			node[p].right = node[j].left;
			node[j].left = p;
		}
		up(p);
		up(j);
	}

	void Splay(int j){	
		if(!j) return;
		push(j);

		while(node[j].parent){
			int p = node[j].parent;
			int pp = node[p].parent;

			if(pp){
				if((node[pp].left == p) ^ (node[p].right == j)){
					rotate(p);
				}
				else{
					rotate(j);
				}
			}
			rotate(j);
		}		
		root = j;
	}

	int find(int j, const function<int(int)>& go){
		// k==0 return, k==-1 left, k==1 right
		if(!j) return 0;
		Splay(j);
		while(1){
			push(j);
			int k = go(j);
			if(k == 0){
				Splay(j);
				return j;
			}
			if(k == -1){
				int l = node[j].left;
				if(l) j = l;
				else{
					Splay(j);
					return j;
				}
			}
			if(k == 1){
				int r = node[j].right;
				if(r) j = r;
				else{
					Splay(j);
					return j;
				}
			}
		}
	}

	int rightmost(int t){
		return find(t, [&](int j){return 1;});
	}
	int leftmost(int t){
		return find(t, [&](int j){return -1;});
	}

	int get_kth(int j, int k){ // 1 index
		assert(k <= node[j].size);

		return find(j, [&](int i){
			assert(k);
			int l = node[i].left;
			int r = node[i].right;

			if(k <= node[l].size) return -1;
			if(k == node[l].size + 1) return 0;
			k -= node[l].size + 1;
			return 1;
		});
	}

	int operator[](int i){
		return node[get_kth(root, i)].key;
	}

	int position(int j){
		assert(j);
		Splay(j);
		return node[node[j].left].size + 1;
	}

	int set_root(int j){
		Splay(j);
		return j;
	}


	ii split(int j, const function<bool(int j)>& comp){
		if(!j) return {0, 0};
		assert(!node[j].parent);
		j = find(j, [&](int i){return comp(i) ? 1 : -1;});

		int l = node[j].left;
		int r = node[j].right;
		if(comp(j)){
			node[r].parent = 0;
			node[j].right = 0;
			up(j);
			up(r);
			return {j, r};
		}
		else{
			node[l].parent = 0;
			node[j].left = 0;
			up(l);
			up(j);
			return {l, j};
		}
	}

	int merge(int l, int r){
		if(!l || !r) return max(l, r);

		assert(!node[l].parent && !node[r].parent);
		
		l = rightmost(l);
		Splay(r);
		
		push(r);
		push(l);

		node[l].right = r;
		node[r].parent = l;
		
		up(l);
		return l;
	}

	int add(int i){
		up(i);
		ii p = split(root, [&](int j){return node[j] < node[i];});
		return merge(p.first, merge(i, p.second));
	}

	int erase(int i){
		Splay(i);

		int l = node[i].left;
		int r = node[i].right;
		node[l].parent = 0;
		node[r].parent = 0;
		return merge(l, r);
	}

	int next(int j){
		Splay(j);
		int r = node[j].right;
		if(!r) return 0;
		while(node[r].left){
			push(r);
			r = node[r].left;
		}
		Splay(r);
		return r;
	}
	int prev(int j){
		Splay(j);
		int l = node[j].left;
		if(!l) return 0;
		while(node[l].right){
			push(l);
			l = node[l].right;
		}
		Splay(l);
		return l;
	}

};
