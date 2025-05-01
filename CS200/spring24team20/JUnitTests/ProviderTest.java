import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

//import edu.ua.cs.cs200.lab10.RomanNumeral;

class ProviderTest {

	@Test
	void testSuccessProvider() {
		Provider testPro = new Provider("John doe", (short) 1, "123 Ave", "Tuscaloosa", 
					"AL", 35404, "Awesome");

        assertEquals(35404, testPro.getZip());
	}

	@Test
	void testFailProvider() {
		IllegalArgumentException thrown = assertThrows(IllegalArgumentException.class, () -> {
			new Provider("John doe", (short) 1, "123 Ave", "Tuscaloosa", 
					"AL", 1, "Awesome");
        }, "Zipcode must be five digits.");

        assertEquals("Zipcode must be five digits.", thrown.getMessage());
	}

	@Test
	void testSanityProvider() {
		Provider testPro = new Provider("John doe", (short) 1, "123 Ave", "Tuscaloosa", 
					"AL", 35404, "Awesome");

		testPro.setZip(1);
		testPro.setZip(23456);
        assertEquals(23456, testPro.getZip());
	}

}
