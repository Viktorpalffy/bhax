import java.util.Scanner;

public class Main {   
    public static void main(String args[]){
        Scanner sc = new Scanner(System.in);
        String hason = null;
        String legyen;
        
        System.out.println("Kapjunk-e NullPointerException-t? I/N");
        for(;;){
            legyen = sc.nextLine();
            
            if( legyen.equalsIgnoreCase("I") ){
                if( hason.equals("abrakadabra") ){
                   break;
                }
            }
            
            else if( legyen.equalsIgnoreCase("N")){
                if(!"abrakadabra".equals(hason) ){
                    System.out.println("Nem Kaptunk.");
                    break;
                }
            }           
            else{
                System.out.println("Nem Tudom értelmezni amit írtál. próbáld újra.");
            }           
        }        
    }    
}
