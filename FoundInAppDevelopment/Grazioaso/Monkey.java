
public class Monkey extends RescueAnimal{
	private String tailLength;
	private String height; //instance variables
	private String bodyLength;
    private String species;
	
    public Monkey(String name, String species, String gender, String age, String weight, 
    String tail, String height, String body, String acquisitionDate, String acquisitionCountry, 
    String trainingStatus, Boolean reserved, String inServiceCountry) {
        setName(name);
        setSpecies(species);
        setGender(gender);
        setAge(age);
        setWeight(weight);
        setTailLength(tail);
        setHeight(height);
        setBodyLength(body);
        setAcquisitionDate(acquisitionDate);
        setAcquisitionLocation(acquisitionCountry);
        setTrainingStatus(trainingStatus);
        setReserved(reserved);
        setInServiceCountry(inServiceCountry);
    }
	
	public String getSpecies() {
		return species;
	}

	public void setSpecies(String species) {
		this.species = species;
	}

	public String getTailLength() {
		return tailLength;
	}
	
	public void setTailLength(String tailLength) {
		this.tailLength = tailLength;
	}
	
	public String getHeight() {
		return height;
	}
	
	public void setHeight(String height) {
		this.height = height;
	}
	
	public String getBodyLength() {
		return bodyLength;
	}
	
	public void setBodyLength(String bodyLength) {
		this.bodyLength = bodyLength;
	}
	
}
