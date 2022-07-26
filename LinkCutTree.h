struct Node{
	int left, right, parent;
	int key, id, size, vir;
	Node(int k = 0, int i = 0){
		left = right = parent = size = vir = 0;
		key = k;
		id = i;
	}

	bool operator<(Node& A){
		return key < A.key || (key == A.key && id < A.id);
	}
	bool operator==(Node& A){
		return id == A.id;
	}
} node[600000];

struct LinkCutTree{

	bool nroot(int j){
		assert(j);
		int p = node[j].parent;
		return p && (node[p].left == j || node[p].right == j);
 	}
 	bool is_left(int j, int i){
 		return i && node[i].left == j;
 	}

	void up(int j){
		if(!j) return;
		int l = node[j].left;
		int r = node[j].right;

		node[j].size = node[j].vir + 1;

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
		int p = node[j].parent;
		int pp = node[p].parent;
		assert(j);
		assert(p);

		node[j].parent = pp;
		if(nroot(p)){
			is_left(p, pp) ? node[pp].left = j : node[pp].right = j;
		}
		if(is_left(j, p)){
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
		assert(j);
		while(nroot(j)){
			int p = node[j].parent;
			int pp = node[p].parent;

			if(nroot(p)){ 
				if(is_left(j, p) ^ is_left(p, pp)){
					rotate(j);
				}
				else rotate(p);
			}
			rotate(j);
		}
	}

	void access(int j){
		int i = 0;
		while(j){
			Splay(j);

			node[j].vir += node[node[j].right].size;

			node[j].right = i;


			node[j].vir -= node[node[j].right].size;

			up(j); 

			i = j;
			j = node[j].parent;
		}
	}

	int find_root(int j){
		access(j);
		Splay(j);
		while(node[j].left){
			j = node[j].left;
		}
		Splay(j);
		return j;
	}

	void link(int j, int p){

		access(j);
		Splay(j);
		assert(!node[j].left);

		node[j].parent = p;

		node[p].vir += node[j].size;
		up(p);

	}

	void cut(int j){
		access(j);
		Splay(j);

		int l = node[j].left;
		node[l].parent = 0;
		node[j].left = 0;
		up(j);

	}

} LCT;