public class Cat extends Pet {
	int catSpaceNumber;

	public Cat(String petName, int petAge, int catSpaceNumber, int daysStay) {
		super(PetType.CAT, petName, petAge, 0, catSpaceNumber, daysStay, 0.0);
		this.catSpaceNumber = catSpaceNumber;
	}

	public int getCatSpaceNumber() {
		return catSpaceNumber;
	}

	public void setCatSpaceNumber(int catSpaceNumber) {
		this.catSpaceNumber = catSpaceNumber;
	}
}
