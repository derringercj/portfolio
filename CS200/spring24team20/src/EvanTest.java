import static org.junit.jupiter.api.Assertions.*;

import org.junit.After;
import org.junit.Before;
import org.junit.jupiter.api.Test;

public class EvanTest {
    @Before
    public void setUp(){
        System.out.println("Testing Starting");
        System.out.println("________________________________________________________");
    }

    @Test
    public void addMember(){
        UserDatabase users= UserDatabase.readFromFile("log", "Users.chocAn");
        User testUser= new Member("Jane Doe", (short) 50, User.role.MEMBER, "123 Nowhere Ave", "Tuscaloosa", "AL", 35401, Member.Status.ACTIVE);
        users.addUser(testUser);

        assertEquals(users.getUser((short)50).getName(), testUser.getName());
    }

    @Test
    public void removeMember(){
        UserDatabase users= UserDatabase.readFromFile("log", "Users.chocAn");
        User testUser= new Member("Jane Doe", (short) 51, User.role.MEMBER, "123 Nowhere Ave", "Tuscaloosa", "AL", 35401, Member.Status.ACTIVE);
        users.addUser(testUser);
        users.removeUser(testUser);

        assertEquals(users.getUser((short)51), null);
    }

    @Test
    public void member(){
        User testUser= new Member("Jane Doe", (short) 99, User.role.MEMBER, "123 Nowhere Ave", "Tuscaloosa", "AL", 35401, Member.Status.ACTIVE);

        assertInstanceOf(Member.class, testUser);
    }

    @After
    public void tearDown(){
        System.out.println("________________________________________________________");
        System.out.println("Testing Complete");
    }
}
