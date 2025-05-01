
import static org.junit.Assert.assertEquals;
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;

public class CharstelTests{

//Test for Failure
	@Test
	void testMemberParameters() {
		assertThrows(IllegalArgumentException.class, () -> {
            new Member("Ali", (short)-2, "899 12th Street", "Tuscaloosa", "AL", (short)35401, "ACTIVE");
        }, "Expected IllegalArgumentException for invalid ID");
	}

//Test for Success
	@Test
	public void testProviderNoParameters() {
		Provider test = new Provider();
		
		assertEquals("", test.getName());
		/*assertEquals(0, test.getID());
		assertEquals("", test.getStreet());
		assertEquals("", test.getCity());
		assertEquals("", test.getState());
		assertEquals(0, test.getZip());
		assertEquals("", test.getType());*/
	}
	
//Test for Sanity
	@Test
    public void testDatabaseStateUnchangedByGetUser() {
        UserDatabase ud = new UserDatabase();

        User testUser = new User("Sanity Test", (short)11111, "1212 Sanity Drive", "Sanity", "TestState", 11111, User.role.MEMBER);
        ud.addUser(testUser);

        int sizeBeforeGet = ud.getUsers().size();

        User retrievedUser = ud.getUser(11111);
        assertNotNull(retrievedUser, "The user should be found.");

        int sizeAfterGet = ud.getUsers().size();

        assertEquals(sizeBeforeGet, sizeAfterGet, "Size shouldn't change because of getUser().");
    }
}