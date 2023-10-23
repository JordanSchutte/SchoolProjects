import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ContactServiceTest {

    @Test
    void addValidContact() {
        ContactService service = new ContactService();
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "Some St.");
        service.addContact(contact);
    }

    @Test
    void addDuplicateContactId() {
        ContactService service = new ContactService();
        Contact contact1 = new Contact("1", "John", "Doe", "1234567890", "Some St.");
        Contact contact2 = new Contact("1", "Jane", "Doe", "0987654321", "Another St.");
        service.addContact(contact1);
        assertThrows(IllegalArgumentException.class, () -> service.addContact(contact2));
    }

    @Test
    void deleteExistingContact() {
        ContactService service = new ContactService();
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "Some St.");
        service.addContact(contact);
        service.deleteContact("1");
    }

    @Test
    void deleteNonExistingContact() {
        ContactService service = new ContactService();
        assertThrows(IllegalArgumentException.class, () -> service.deleteContact("1"));
    }

    @Test
    void updateExistingContact() {
        ContactService service = new ContactService();
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "Some St.");
        service.addContact(contact);
        service.updateFirstName("1", "Jane");
    }

    @Test
    void updateNonExistingContact() {
        ContactService service = new ContactService();
        assertThrows(IllegalArgumentException.class, () -> service.updateFirstName("1", "Jane"));
    }
}
