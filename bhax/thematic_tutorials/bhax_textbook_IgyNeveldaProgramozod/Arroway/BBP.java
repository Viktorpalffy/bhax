public class BBP {
   public static void main(String[] args) {
	int k = 6; 
	System.out.println(magic(k));
   }

   public static String magic(int k) {
	double s1 = solve(Math.pow(10,k), 1);
	double s4 = solve(Math.pow(10,k), 4);
	double s5 = solve(Math.pow(10,k), 5);
	double s6 = solve(Math.pow(10,k), 6);

	s1 = cut(s1);
	s4 = cut(s4);
	s5 = cut(s5);
	s6 = cut(s6);

	double pi = 4*s1 -2*s4 - s5 -s6;

	pi = cut(pi);

	String[] hexa = {"A", "B", "C", "D", "E", "F"};
	String result = "";

	while(cut(pi) != 0) {
	   pi = pi*16;
	   if((int)pi >= 10) {
		result = result.concat(hexa[(int)pi - 10]);
	   }
	   else {
		result = result.concat(Integer.toString((int)pi));
	   }
	   pi = cut(pi);
	}
	return result;
   }

   public static double cut(double db) {
	if(db < 0) {
	   return db - (int)db+1;
	}
	else {
	   return db - (int)db;
	}
   }

   public static double solve(double d, double num) {
	double sum = 0.0;

	for(int i = 0; i <= d; i++) {
	   sum += mod(16, (d-i), 8*i+num) / (8*i + num);
	}
	return sum ;
   }

   public static double mod(double b, double n, double k) {
	double t = 1;
	double r = 1;

	while(t <= n) {
	   t = t * 2;
	}

	while(true) {
	   if(n >= t) {
		r = (b * r) % k;
		n= n - t;
	   }
	   t = t / 2;
	   if(t >= 1) {
		r = (r*r) % k;
	   }
	   else {
		break;
	   }
	}
	return r;
   }
}
