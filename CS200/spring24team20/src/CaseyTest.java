import static org.junit.jupiter.api.Assertions.*;

import org.junit.After;
import org.junit.Before;
import org.junit.jupiter.api.Test;


public class CaseyTest {

    @Before
    public void setUp(){
        System.out.println("Testing Starting");
        System.out.println("________________________________________________________");
    }

    @Test
    public void addServiceDatabaseForSuccess(){
        ServiceDatabase services = ServiceDatabase.readFromFile("log", "Services.chocan");
        Provider provider = new Provider("Test", (short)30, "Bandit", "Beavercreek", "Ohio", 45434, "Type");
        Member member = new Member("Test2", (short)20, User.role.MEMBER, "Southfield", "Beavercreek", "Ohio", 45487, Member.Status.ACTIVE);
        Service service = new Service(provider, member, 50, null);
        
        services.add(service);

        assertEquals(service.member.getID(), member.getID());
    }
    
    @Test
    public void userTestForException(){
        User testUser = new User("Casey Derringer", (short)100, User.role.OPERATOR);

        assertFalse(testUser.getID() == 10);
    }

    @Test
    public void userDatabaseTestForSanity(){
        UserDatabase database = new UserDatabase();

        User user1 = new User("Casey", (short)20, "Bandit", "Beavercreek", "Ohio", 45434, User.role.MANAGER);
        database.addUser(user1);
        database.totalUsers();
        database.removeUser(user1);
        database.totalUsers();
        
        assertEquals(0, database.userCount);
    
    }


    @After
    public void tearDown(){
        System.out.println("________________________________________________________");
        System.out.println("Testing Complete");
    }
}
