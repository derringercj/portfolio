import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;


class DevinTest {

	@Test
	void MemberTest() {
		Error thrown = assertThrows(Error.class, () -> {
			GenerateReport report = new GenerateReport();
			report.MemberReports();
        }, "There are no members found within the user database.");

        assertEquals("There are no members found within the user database.", thrown.getMessage());
	}

	@Test
	void ProviderTest() {
		Error thrown = assertThrows(Error.class, () -> {
			GenerateReport report = new GenerateReport();
			report.ProviderReports();
        }, "There are no members found within the user database.");

        assertEquals("There are no members found within the user database.", thrown.getMessage());
	}
	
	@Test
	void testSuccessProvider() {
		Provider testPro = new Provider("John doe", (short)1, "123 Ave", "Tuscaloosa", 
					"AL", 35404, "NA");

        assertEquals(35404, testPro.getZip());
	}

	@Test
	void testSanityProvider() {
		Provider testPro = new Provider("John doe", (short)1, "123 Ave", "Tuscaloosa", 
				"AL", 35404, "NA");

		testPro.setZip(1);
		testPro.setZip(23456);
        assertEquals(23456, testPro.getZip());
	}

}
