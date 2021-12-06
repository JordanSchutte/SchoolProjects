import java.util.Scanner;

public class PetBag {
	Scanner scan = new Scanner(System.in);
	final int INITIAL_DOG_SPACE_COUNT = 30;
	final int INITIAL_CAT_SPACE_COUNT = 12;
	Dog[] dogSpaces = new Dog[INITIAL_DOG_SPACE_COUNT];
	Cat[] catSpaces = new Cat[INITIAL_CAT_SPACE_COUNT];
	
	public void run() { //this will act as the home screen
		while (true) {
			System.out.println("Welcome to Pet Bag!");
			System.out.println("Will you be: ");
			System.out.println("1.) checking in");
			System.out.println("2.) checking out");
			int check = scan.nextInt();
			if (check == 1) {
				checkIn();
			} else if (check == 2) {
				checkOut();
			} else {
				System.out.println("Invalid command");
			}	
		}		
	}
	public int getOpenDogSpace() { //this will get the cage number available for checking in dog
		for (int i = 0; i < dogSpaces.length; ++i) {
			if (dogSpaces[i] == null) {
				return i;
			}
		}
		return -1;
	}
	public int getOpenCatSpace() { //this will get the cage number available for checking in cat
		for (int i = 0; i < catSpaces.length; ++i) {
			if (catSpaces[i] == null) {
				return i;
			}
		}
		return -1;
	}
	
	public void checkIn() { //This will take user input of their pet details
		System.out.println("Will you be checking in a dog or a cat?");
		String checkin = scan.nextLine();
		System.out.println("What is the name of your " + checkin + "?");
		String petname = scan.nextLine();
		System.out.println("What is the age of " + petname + "?");
		int petage = scan.nextInt();
		System.out.println("How many days will " + petname + " be staying with us?");
		int daysStay = scan.nextInt();
		if (checkin == "dog") {
			int slot = getOpenDogSpace();
			if (slot < 0) {
				System.out.println("No avaliable dog spaces right now!");
				return;
			}
			Dog dog = new Dog(petname, petage, slot, daysStay);
			dogSpaces[slot] = dog;
		} else if (checkin == "cat") {
			int slot = getOpenCatSpace();
			if (slot < 0) {
				System.out.println("No avaliable cat spaces right now!");
				return;
			}
			Cat cat = new Cat(petname, petage, slot, daysStay);
			catSpaces[slot] = cat;
		} else {
			// ERROR
		}
    }
    
    public void checkOut() { //This will open the spot the checked-out pet occupies
    	System.out.println("While you be checking out a dog or a cat?");
    	String checkout = scan.nextLine();
    	System.out.println("What is the name of your " + checkout + "?");
    	String petname = scan.nextLine();
    	if (checkout == "dog") {
    		getPet();
    	} else if (checkout == "cat") {
    		getPet();
    		
    	}
    }
    
    public void getPet() { //this will get all details about a certain pet requested by name
        
    }
    
    public void createPet() { //this will add a new pet to the DB
        
    }
    
    public void updatePet() { //this will update a previously housed pets details
        
    }
	public static void main(String[] args) {
		PetBag bag = new PetBag();
		bag.run();
	}
	}
