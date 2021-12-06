public class Dog extends Pet {
	int dogSpaceNumber;
	
	public Dog(String petName, int petAge, int dogSpaceNumber, int daysStay) {
		super(PetType.DOG, petName, petAge, 0, dogSpaceNumber, daysStay, 0.0);
		this.dogSpaceNumber = dogSpaceNumber;
	}
	
	public int getDogSpaceNumber() {
		return dogSpaceNumber;
	}

	public void setDogSpaceNumber(int dogSpaceNumber) {
		this.dogSpaceNumber = dogSpaceNumber;
	}
}
