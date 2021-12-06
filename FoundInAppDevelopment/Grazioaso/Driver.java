import java.util.ArrayList;
import java.util.Scanner;

public class Driver {
    private static ArrayList<Dog> dogList = new ArrayList<Dog>();
    private static ArrayList<Monkey> monkeyList = new ArrayList<Monkey>();

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
    	char userInput = ' ';

        initializeDogList();
        initializeMonkeyList();

        while (userInput != 'q') {
        	displayMenu();
        	userInput = scan.next().charAt(0);
        	if (userInput == '1') {
        		intakeNewDog(scan);
        	} else if (userInput == '2') {
        		intakeNewMonkey(scan);
        	} else if (userInput == '3') {
        		reserveAnimal(scan);
        	} else if (userInput == '4') {
        		initializeDogList();
        	} else if (userInput == '5') {
        		initializeMonkeyList();
        	} else if (userInput == '6') {
        		printAnimals();
        	} else {
        		System.out.println("Invalid command");
        	}
        }
        
	// Hint: Menu options 4, 5, and 6 should all connect to the printAnimals() method.

    }

    // This method prints the menu options
    public static void displayMenu() {
        System.out.println("\n\n");
        System.out.println("\t\t\t\tRescue Animal System Menu");
        System.out.println("[1] Intake a new dog");
        System.out.println("[2] Intake a new monkey");
        System.out.println("[3] Reserve an animal");
        System.out.println("[4] Print a list of all dogs");
        System.out.println("[5] Print a list of all monkeys");
        System.out.println("[6] Print a list of all animals that are not reserved");
        System.out.println("[q] Quit application");
        System.out.println();
        System.out.println("Enter a menu selection");
    }


    // Adds dogs to a list for testing
    public static void initializeDogList() {
        System.out.println(dogList.toString());
    }


    // Adds monkeys to a list for testing
    //Optional for testing
    public static void initializeMonkeyList() {
    	System.out.println(monkeyList.toString());
    }


    // Complete the intakeNewDog method
    // The input validation to check that the dog is not already in the list
    // is done for you
    public static void intakeNewDog(Scanner scanner) {
        System.out.println("What is the dog's name?");
        scanner.nextLine(); //eats nextline
        String name = scanner.nextLine();
        for(Dog dog: dogList) {
            if(dog.getName().equalsIgnoreCase(name)) {
                System.out.println("\n\nThis dog is already in our system\n\n");
                return; //returns to menu
            }
        }
    	System.out.println("What is " + name + "'s breed?");
    	String breed = scanner.nextLine();
    	System.out.println("What is " + name + "'s sex?");
    	String gender = scanner.nextLine();
    	System.out.println("What is " + name + "'s age?");
    	String age = scanner.nextLine();
    	System.out.println("What is " + name + "'s weight?");
    	String weight = scanner.nextLine();
    	System.out.println("When was the acquisition date?");
    	String date = scanner.nextLine();
    	System.out.println("What country does " + name + " come from?");
    	String country = scanner.nextLine();
    	System.out.println("What is " + name + "'s training status?");
    	String train = scanner.nextLine();
    	System.out.println("Is it true or false that " + name + " is reserved?");
    	Boolean reserved = scanner.nextBoolean();
    	System.out.println("What country does " + name + " service now?");
    	scanner.nextLine(); //eats nextline
    	String service = scanner.nextLine();
    	Dog dog1 = new Dog(name, breed, gender, age, weight, date, country, train, reserved, service);
    	dogList.add(dog1);
    	return;
    }


        // Complete intakeNewMonkey
	//Instantiate and add the new monkey to the appropriate list
        // For the project submission you must also  validate the input
	// to make sure the monkey doesn't already exist and the species type is allowed
        public static void intakeNewMonkey(Scanner scanner) {
            System.out.println("What is the monkey's name?");
            scanner.nextLine(); //eats nextline
            String name = scanner.nextLine();
            for(Monkey monkey: monkeyList) {
                if(monkey.getName().equalsIgnoreCase(name)) {
                    System.out.println("\n\nThis monkey is already in our system\n\n");
                    return; //returns to menu
                }
            }
        	System.out.println("What is " + name + "'s species?");
        	String species = scanner.nextLine();
        	System.out.println("What is " + name + "'s sex?");
        	String gender = scanner.nextLine();
        	System.out.println("What is " + name + "'s age?");
        	String age = scanner.nextLine();
        	System.out.println("What is " + name + "'s weight?");
        	String weight = scanner.nextLine();
        	System.out.println("What is " + name + "'s tail length?");
        	String tail = scanner.nextLine();
        	System.out.println("What is " + name + "'s height?");
        	String height = scanner.nextLine();
        	System.out.println("What is " + name + "'s body length?");
        	String body = scanner.nextLine();
        	System.out.println("When was the acquisition date?");
        	String date = scanner.nextLine();
        	System.out.println("What country does " + name + " come from?");
        	String country = scanner.nextLine();
        	System.out.println("What is " + name + "'s training status?");
        	String train = scanner.nextLine();
        	System.out.println("Is it true or false that " + name + " is reserved?");
        	Boolean reserved = scanner.nextBoolean();
        	System.out.println("What country does " + name + " service now?");
        	scanner.nextLine(); //eats nextline
        	String service = scanner.nextLine();
        	Monkey monkey1 = new Monkey(name, species, gender, age, weight, tail, height, body, date, country, train, reserved, service);
        	monkeyList.add(monkey1);
        	return;
        }

        // Complete reserveAnimal
        // You will need to find the animal by animal type and in service country
        public static void reserveAnimal(Scanner scanner) {
            System.out.println("Here is a list of all unreserved animals:");
            if (RescueAnimal.getReserved() == false) {
            }
        }

        // Complete printAnimals
        // Include the animal name, status, acquisition country and if the animal is reserved.
	// Remember that this method connects to three different menu items.
        // The printAnimals() method has three different outputs
        // based on the listType parameter
        // dog - prints the list of dogs
        // monkey - prints the list of monkeys
        // available - prints a combined list of all animals that are
        // fully trained ("in service") but not reserved 
	// Remember that you only have to fully implement ONE of these lists. 
	// The other lists can have a print statement saying "This option needs to be implemented".
	// To score "exemplary" you must correctly implement the "available" list.
        public static void printAnimals() {
            System.out.println("Here is a list of all animals in our DB:");
            System.out.println("Dogs: ");
            initializeDogList();
            System.out.println("Monkeys: ");
            initializeMonkeyList();
        }
}

