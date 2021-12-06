import java.util.Scanner;
//Jordan Schutte 11/21/2021

public class Pet {
	public enum PetType {
		CAT,
		DOG
	}

	PetType petType;
	String petName;
	int petAge;
	int dogSpaces = 30;
	int catSpaces = 12;
	int daysStay;
	boolean grooming;
	double amountDue;
	
	Scanner scan = new Scanner(System.in);

	public Pet(PetType petType, String petName, int petAge, int dogSpaces, int catSpaces, int daysStay,
			double amountDue) {
		super();
		this.petType = petType;
		this.petName = petName;
		this.petAge = petAge;
		this.dogSpaces = dogSpaces;
		this.catSpaces = catSpaces;
		this.daysStay = daysStay;
		this.amountDue = amountDue;
	}
	// Getters and setters for everything
	public PetType getPetType() {
		return petType;
	}
	public void setPetType(PetType petType) {
		this.petType = petType;
	}
	public String getPetName() {
		return petName;
	}
	public void setPetName(String petName) {
		this.petName = petName;
	}
	public int getPetAge() {
		return petAge;
	}
	public void setPetAge(int petAge) {
		this.petAge = petAge;
	}
	public int getDogSpaces() {
		return dogSpaces;
	}
	public void setDogSpaces(int dogSpaces) {
		this.dogSpaces = dogSpaces;
	}
	public int getCatSpaces() {
		return catSpaces;
	}
	public void setCatSpaces(int catSpaces) {
		this.catSpaces = catSpaces;
	}
	public int getDaysStay() {
		return daysStay;
	}
	public void setDaysStay(int daysStay) {
		this.daysStay = daysStay;
	}
	public double getAmountDue() {
		return amountDue;
	}
	public void setAmountDue(double amountDue) {
		this.amountDue = amountDue;
	}
}
