
import static org.junit.jupiter.api.Assertions.*;

import java.time.LocalDateTime;

import org.junit.Test;


public class JoshTest {
    @Test
    public void ServiceDatabaseTest() {
        ServiceDatabase testDatabase = new ServiceDatabase();
        Provider testProvider = new Provider("provider_name", (short)1, User.role.PROVIDER, "lol", "lmao", "Misery", 11111);
        Member testMember = new Member("member_name", (short)2, "lol", "lmao", "Agony", (short)11111, "Active");
        Service testService = new Service(testProvider, testMember, 598470, LocalDateTime.now());
        testDatabase.add(testService);

        assertEquals(testDatabase.serviceList.get(0).provider.getState(), "Misery");
        assertEquals(testDatabase.serviceList.get(0).member.getState(), "Agony");

        assertEquals(testDatabase.serviceList.get(0).provider.getName(), "provider_name");
        assertEquals(testDatabase.serviceList.get(0).member.getName(), "member_name");
    }

    @Test
    public void ServiceTest() {
        Provider testProvider = new Provider("provider_name", (short)1, User.role.PROVIDER, "lol", "lmao", "Misery", 11111);
        Member testMember = new Member("member_name", (short)2, "lol", "lmao", "Agony", (short)11111, "Active");
        Service testService = new Service(testProvider, testMember, 598470, LocalDateTime.now());

        assertEquals(testService.member.getName(), "member_name");
        assertEquals(testService.member.getStreet(), "lol");
        assertEquals(testService.member.getCity(), "lmao");
        assertEquals(testService.member.getState(), "Agony");

        assertEquals(testService.provider.getName(), "provider_name");
        assertEquals(testService.provider.getStreet(), "lol");
        assertEquals(testService.provider.getCity(), "lmao");
        assertEquals(testService.provider.getState(), "Misery");
    }

    @Test
    public void UserTest() {
        User testUser = new User("test_name", (short)1, "test_street", "test_city", "test_state", 11111, User.role.PROVIDER);
        assertEquals(testUser.getName(), "test_name");
        assertEquals(testUser.getStreet(), "test_street");
        assertEquals(testUser.getCity(), "test_city");
        assertEquals(testUser.getState(), "test_state");
        assertEquals(testUser.getZip(), 11111);
        assertEquals(testUser.getRole(), User.role.PROVIDER);
    }
}