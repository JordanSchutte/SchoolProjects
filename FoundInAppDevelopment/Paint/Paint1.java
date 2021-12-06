import java.util.Scanner;

public class Paint1 {

    public static void main(String[] args) {
        Scanner scnr = new Scanner(System.in);
        double wallHeight = 0.0;
        double wallWidth = 0.0;
        double wallArea = 0.0;
        double gallonsPaintNeeded = 0.0;
        
        final double squareFeetPerGallons = 350.0;
        
        // Implement a do-while loop to ensure input is valid
        try {
        	do {
                System.out.println("Enter wall height (feet): "); // Prompt user to input wall's height
                wallHeight = scnr.nextDouble();
                if (wallHeight <= 0) {
                	System.out.println("Invalid height");
                }
        	} while (wallHeight <= 0);
        } catch (Exception excpt) {
        	System.out.println("Invalid height");
        	wallHeight = scnr.nextDouble();
        }


        // Implement a do-while loop to ensure input is valid
    	do {
            System.out.println("Enter wall width (feet): "); // Prompt user to input wall's Width
            wallWidth = scnr.nextDouble();
            if (wallWidth <= 0) {
            	System.out.println("Invalid Width");
            }
    	} while (wallWidth <= 0);

        // Calculate and output wall area
        wallArea = wallHeight * wallWidth;
        System.out.println("Wall area: " + wallArea + " square feet");

        // Calculate and output the amount of paint (in gallons) needed to paint the wall
        gallonsPaintNeeded = wallArea/squareFeetPerGallons;
        System.out.println("Paint needed: " + gallonsPaintNeeded + " gallons");

    }
}
