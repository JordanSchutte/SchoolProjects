import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

class ContactTest {

    @Test
    void createValidContact() {
        Contact contact = new Contact("1", "John", "Doe", "1234567890", "Some St.");
        assertEquals("1", contact.getContactID());
    }

    @Test
    void contactIdExceedsLength() {
        assertThrows(IllegalArgumentException.class,
                () -> new Contact("12345678901", "John", "Doe", "1234567890", "Some St."));
    }

    @Test
    void firstNameExceedsLength() {
        assertThrows(IllegalArgumentException.class,
                () -> new Contact("1", "JohnJohnJohn", "Doe", "1234567890", "Some St."));
    }

    @Test
    void lastNameExceedsLength() {
        assertThrows(IllegalArgumentException.class,
                () -> new Contact("1", "John", "DoeDoeDoeDoeDoe", "1234567890", "Some St."));
    }

    @Test
    void invalidPhoneNumber() {
        assertThrows(IllegalArgumentException.class,
                () -> new Contact("1", "John", "Doe", "12345678901", "Some St."));
    }

    @Test
    void addressExceedsLength() {
        assertThrows(IllegalArgumentException.class,
                () -> new Contact("1", "John", "Doe", "1234567890", "Some St. Extra Long Address."));
    }
}
