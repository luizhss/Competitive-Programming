/*
	Dazzling Stars - 2019 LA Regional
*/

    #include <bits/stdc++.h>
     
    using namespace std;
     
    #define FOR(i, n) for(int i = 0; i < (int) n; i++)
    #define PB push_back
    #define all(x) x.begin(), x.end()
    #define rall(x) x.rbegin(), x.rend()
    #define F first
    #define S second
     
    typedef long long ll;
    typedef vector<int> vi;
    typedef pair<int,int> pii;
     
    const int MAX = 1e5+7;
    const double PI = 3.14159265358979323846;
    const double EPS = 1e-6;
     
    struct point2d{
    	int x, y;
     
    	point2d(): x(0), y(0) {}
     
    	point2d(int x, int y): x(x), y(y) 
    	{}
     
    	point2d operator-(const point2d& other) const{
    		return point2d(x - other.x, y - other.y);
    	}
     
    	point2d orthonormal(const point2d& other){
    		return point2d(-other.y, other.x);
    	}
     
    	double abs(){
    		return sqrt(1.0*x*x + 1.0*y*y);
    	}
     
    	void inverse(){
    		x = -x; y = -y;
    	}
     
    	int dot(const point2d& other){
    		return x*other.x + y * other.y;
    	}
    };
     
    double angle(point2d a, point2d b){
    	return acos(a.dot(b) / a.abs() / b.abs());
    }
     
    void fix_ranges(vector<pair<double,double>>& v){
    	sort(all(v));
    	vector<pair<double,double>> aux;
    	double l = v[0].F, r = v[0].S;
    	for(int i = 1; i < (int)v.size(); i++){
    		auto& [lx, rx] = v[i];
     
    		if(r < lx){
    			aux.PB({l, r});
    			l = lx; r = rx;
    		}else{
    			r = rx;
    		}
    	}
    	aux.PB({l, r});
    	v = aux;
    }
     
    int main(){
    	ios::sync_with_stdio(false); cin.tie(0);
     
    	int n; cin >> n;
    	vector<point2d> c(n);
    	vi b(n);
    	FOR(i, n){
    		cin >> c[i].x >> c[i].y >> b[i];
    	}
     
    	vi idxs(n ,0); iota(all(idxs), 0);
    	sort(all(idxs), [&b](int& i, int& j){
    		return b[i] > b[j];
    	});
     
    	int b0, b1;
    	point2d p0, p1;
    	vector<pair<double, double>>ranges(1, {0, 4.0*PI});
    	FOR(i, n){
    		b0 = b[idxs[i]];
    		p0 = c[idxs[i]];
    		for(int j = i+1; j < n; j++){
    			b1 = b[idxs[j]];
    			p1 = c[idxs[j]];
     
    			if(b0 == b1) continue;
     
    			auto dir = p1-p0;
    			double theta = angle(dir, point2d(1, 0));
    			if(dir.y < 0) theta = 2.0*PI - theta;
     
    			double lx = theta, rx = theta+PI;
    			double l2 = lx+2.0*PI, r2 = rx+2.0*PI;
    			
    			vector<pair<double,double>> aux;
    			for(auto& [l, r]: ranges){
    				if(!(rx < l || r < lx)){
    					aux.PB({max(l, lx), min(r, rx)});
    				}
     
    				if(!(r2 < l || r < l2)){
    					aux.PB({max(l, l2), min(r, r2)});
    				}
    			}
     
    			if(aux.empty()){
    				cout << "N\n";
    				return 0;
    			}
    			fix_ranges(aux);
    			ranges = aux;
    		}
    	}
     
    	if(ranges.empty()) cout << "N\n";
    	else cout << "Y\n";
     
    	return 0;
    }