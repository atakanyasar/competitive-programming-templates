namespace Trie{

	struct node{
		node* left = nullptr;
		node* right = nullptr;
		int cnt = 0;
	}*root = nullptr;

	node& add(node*& curr, int x, int w = (1ll << 32)){
		if(curr == nullptr) curr = new node;
		curr->cnt++;
		if(w){
			if(x & w) curr->right = &add(curr->right, x, w >> 1);
			else curr->left = &add(curr->left, x, w >> 1);
		}
		return *curr;
	}
	node& erase(node*& curr, int x, int w = (1ll << 32)){
		assert(curr != nullptr);
		curr->cnt--;
		if(w){
			if(x & w) curr->right = &erase(curr->right, x, w >> 1);
			else curr->left = &erase(curr->left, x, w >> 1);
		}
		if(!curr->cnt) delete curr, curr = nullptr;
		return *curr;
	}

	int max_xor(node*& curr, int x, int w = (1ll << 32)){
		assert(curr != nullptr);
		if(w){
			if(((x&w)==0 && curr->right != nullptr) || curr->left == nullptr) return (w ^ (x&w)) | max_xor(curr->right, x, w >> 1);
			else return (x&w) | max_xor(curr->left, x, w >> 1);
		}
		else return 0;
	}
}
