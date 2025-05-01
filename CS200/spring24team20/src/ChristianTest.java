import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

public class ChristianTest {

    @Test
    public void runReportFail(){
        Error thrown = assertThrows(Error.class, () -> {
            Manager man = new Manager();
			man.runReport("Nonexistant Type");
        }, "Invalid report type. Valid report types are: Member , Provider , EFT , Summary.");

        assertEquals("Invalid report type. Valid report types are: Member , Provider , EFT , Summary.", thrown.getMessage());
    }

    @Test
    public void addMemberSuccess(){
        UserDatabase users = UserDatabase.readFromFile("log", "Users.chocAn");
        Operator opera = new Operator();
        opera.setMember("Test Name", (short) 500, "789 Fake Street", "Detroit", "MI", (short)12345);
        opera.setUserDatabase(users);
        opera.addMember();

        assertEquals(users.getUser((short)500).getName(), "Test Name");
    }

    @Test
    public void EFTReportsFail(){
        Error thrown = assertThrows(Error.class, () -> {
            GenerateReport report = new GenerateReport();
			report.EFTReports();
        }, "There are no members found within the user database.");

        assertEquals("There are no members found within the user database.", thrown.getMessage());
    }
}
