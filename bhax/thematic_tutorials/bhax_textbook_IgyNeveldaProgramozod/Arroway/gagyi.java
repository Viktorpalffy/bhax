import java.util.Scanner;
public class Gagyi{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		System.out.println("Álljon e le a program? igen ha igen, bármi más ha nem");
		Integer t;
		Integer x;
		
		if(sc.nextLine().equals("igen")){
			x = 127;
			t = 127;
		}
		else{
			t = 128;
			x = 128;
		}
		while (x <= t && x >= t && t != x);
	}

}
