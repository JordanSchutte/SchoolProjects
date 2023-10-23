public class Contact {
    private final String contactID;
    private String firstName;
    private String lastName;
    private String number;
    private String address;

    public Contact(String contactID, String firstName, String lastName, String number, String address) {
        if (contactID == null || contactID.length() > 10) {
            throw new IllegalArgumentException("Contact ID cannot be null and must not exceed 10 characters");
        }

        if (firstName == null || firstName.length() > 10) {
            throw new IllegalArgumentException("First name cannot be null and must not exceed 10 characters");
        }

        if (lastName == null || lastName.length() > 10) {
            throw new IllegalArgumentException("Last name cannot be null and must not exceed 10 characters");
        }

        if (number == null || number.length() != 10 || !number.matches("\\d{10}")) {
            throw new IllegalArgumentException("Number must be exactly 10 digits and cannot be null");
        }

        if (address == null || address.length() > 30) {
            throw new IllegalArgumentException("Address cannot be null and must not exceed 30 characters");
        }

        this.contactID = contactID;
        this.firstName = firstName;
        this.lastName = lastName;
        this.number = number;
        this.address = address;
    }

    // getters for all fields

    public String getContactID() {
        return contactID;
    }

    public String getFirstName() {
        return firstName;
    }

    public String getLastName() {
        return lastName;
    }

    public String getNumber() {
        return number;
    }

    public String getAddress() {
        return address;
    }

    // setters for firstName, lastName, number, and address with validation

    public void setFirstName(String firstName) {
        if (firstName == null || firstName.length() > 10) {
            throw new IllegalArgumentException("First name cannot be null and must not exceed 10 characters");
        }
        this.firstName = firstName;
    }

    public void setLastName(String lastName) {
        if (lastName == null || lastName.length() > 10) {
            throw new IllegalArgumentException("Last name cannot be null and must not exceed 10 characters");
        }
        this.lastName = lastName;
    }

    public void setNumber(String number) {
        if (number == null || number.length() != 10 || !number.matches("\\d{10}")) {
            throw new IllegalArgumentException("Number must be exactly 10 digits and cannot be null");
        }
        this.number = number;
    }

    public void setAddress(String address) {
        if (address == null || address.length() > 30) {
            throw new IllegalArgumentException("Address cannot be null and must not exceed 30 characters");
        }
        this.address = address;
    }
}
