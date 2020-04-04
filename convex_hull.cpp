bool Q = true;

struct Line{

	mutable int m, n;
	mutable long double p;

	Line(){}
	Line(int _m, int _n, long double _p = INF): m(_m), n(_n), p(_p){}

	bool operator<(const Line& X)const{

		if(Q) return m < X.m; // max

		else return p < X.p;

	}

};

struct Hull : multiset<Line> {

	long double cross(iterator A, iterator B){

		long double m1 = A->m, m2 = B->m;
		long double n1 = A->n, n2 = B->n;

		if(m1 == m2) return n1 >= n2 ? INF : -INF; // max

		return (n1 - n2) / (m2 - m1); 

	}

	bool isect(iterator A, iterator B){

		if(B == end()){

			A->p = INF;

			return false;

		}

		A->p = cross(A, B);

		return !(A->p < B->p);

	}

	void add(int m, int n){

		iterator curr = insert(Line(m, n));

		while(isect(curr, next(curr))) erase(next(curr));

		if(curr == begin()) return;

		while(isect(prev(curr), curr)) curr = erase(curr);

		while(prev(curr) != begin() && isect(prev(prev(curr)), prev(curr))){

			erase(prev(curr));

			isect(prev(curr), curr);

		}

	}

	int query(int x){

		Q = false;
		iterator curr = lower_bound(Line(0, 0, x));
		Q = true;

		return curr->m * x + curr->n;

	}

};

/***********************************************************/

struct Point{

	mutable long double x, y;

	Point(){}
	Point(long double _m, long double _n): x(_m), y(_n){}

	bool operator<(const Point& X)const{

		return x < X.x || (x == X.x && y < X.y);

	}

};

struct ConvexHull : multiset<Point> {

	bool isect(iterator A, iterator B, iterator C){

		if(C == begin() || B == begin() || C == end() || B == end() || A == end()){

			return false;

		}

		if(A->x == B->x) return true;
		if(B->x == C->x) false;

		return (B->y - A->y) / (B->x - A->x) >= (C->y - B->y) / (C->x - B->x);

	}

	void add(int x, int y){

		iterator curr = insert(Point(x, y));

		while(isect(curr, next(curr), next(next(curr)))) erase(next(curr));

		while(isect(prev(curr), curr, next(curr))) curr = erase(curr);

		while(isect(prev(prev(curr)), prev(curr), curr)){

			erase(prev(curr));

		}

	}

	bool query(){

		///

	}

};


/****************************************************************/

struct LinearHull : deque<Line>{

	long double cross(Line& A, Line& B){
		long double m1 = A.m, m2 = B.m;
		long double n1 = A.n, n2 = B.n;

		if(m1 == m2){
			return (n1 > n2 ? -INF : INF);
		}
		return (n1 - n2) / (m2 - m1);
	}
	bool isect(Line& A, Line& B){

		A.p = cross(A, B);

		return !(A.p < B.p);
	}
	void add_back(int m, int n){
		Line curr = Line(m, n, INF);
		if(size() > 0){
			isect(back(), curr);
			while(size() > 1 && isect(*prev(--end()), back())){
			pop_back();
			isect(back(), curr);
			} 
		}
		push_back(curr);
	}
	void add_front(int m, int n){
		Line curr = Line(m, n, INF);
		while(!empty() && isect(curr, front())){
			pop_front();
		}
		if(empty())curr.p = INF;

		push_front(curr);
	}

	int query(int x){
		if(empty()) return INF;
		Q = false;
		iterator temp = lower_bound(begin(), end(), Line(0, 0, x));
		Q = true;
		return temp->m * x + temp->n;
	}
};
