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



bool Q=false;
struct Line{
    mutable int m,c;
    mutable long double x;
    Line(int M,int C,int X):m(M),c(C),x(X){}
    bool operator<(const Line& next)const{
        if(Q==false){
            return m > next.m;
        }
        else return x < next.x;
    }
    int get(int X){return m*X+c;}
};
struct Hull : multiset<Line> {
    long double cross(iterator a,iterator b){
        long double A=a->m, B=a->c, C=b->m, D=b->c;
        return (D-B)/(A-C);
    }
    bool isect(iterator a,iterator b){
        if(b==end()){ a->x=INF; return false; }
        if(a->m == b->m) a->x =((a->c > b->c)?-INF:INF);
        else a->x = cross(a,b);
        return a->x >= b->x;
    }
    void add(int M,int C){
        iterator pre,curr,next;
        curr=insert(Line(M,C,0));
        next=pre=curr;
        next++;
        while(isect(curr,next))next=erase(next);
        if(curr!=begin()&&isect(--pre,curr))isect(pre,curr=erase(curr));
        while( (curr=pre)!=begin() && (--pre)->x >= curr->x )isect(pre,erase(curr));
    }
    int query(int X){
        Q=true;
        Line curr=*lower_bound(Line(0,0,X));
        Q=false;
        return curr.get(X);
    }
};





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
