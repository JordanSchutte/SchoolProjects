import java.util.HashMap;
import java.util.Map;

public class ContactService {
    private Map<String, Contact> contacts;

    public ContactService() {
        this.contacts = new HashMap<>();
    }

    // Add contact
    public void addContact(Contact contact) {
        if (contact == null) {
            throw new IllegalArgumentException("Contact cannot be null.");
        }
        if (contacts.containsKey(contact.getContactID())) {
            throw new IllegalArgumentException("Contact ID already exists.");
        }
        contacts.put(contact.getContactID(), contact);
    }

    // Delete contact
    public void deleteContact(String contactID) {
        if (!contacts.containsKey(contactID)) {
            throw new IllegalArgumentException("Contact with the given ID does not exist.");
        }
        contacts.remove(contactID);
    }

    // Update contact fields
    public void updateFirstName(String contactID, String newFirstName) {
        verifyContactExists(contactID);
        contacts.get(contactID).setFirstName(newFirstName);
    }

    public void updateLastName(String contactID, String newLastName) {
        verifyContactExists(contactID);
        contacts.get(contactID).setLastName(newLastName);
    }

    public void updateNumber(String contactID, String newNumber) {
        verifyContactExists(contactID);
        contacts.get(contactID).setNumber(newNumber);
    }

    public void updateAddress(String contactID, String newAddress) {
        verifyContactExists(contactID);
        contacts.get(contactID).setAddress(newAddress);
    }

    // Private method to verify if a contact exists in the map
    private void verifyContactExists(String contactID) {
        if (!contacts.containsKey(contactID)) {
            throw new IllegalArgumentException("Contact with the given ID does not exist.");
        }
    }
}
