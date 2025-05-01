import java.io.Serializable;

public class User implements Serializable{
    
    private String name;
    private short ID;
    private String street;
    private String city;
    private String state;
    private int zip;
    private role userRole;

    public enum role {PROVIDER, MANAGER, OPERATOR, MEMBER};

    public User(){
        name = "";
        street = "";
        city = "";
        state = "";
        zip = 0;
    }

    public User(String name,short id, role role){
        this.name = name;
        this.ID= id;
        street = "";
        city = "";
        state = "";
        zip = 0;
        this.userRole= role;
    }

    public User(String name,short id, String street, String city, String state, int zip, User.role role){
        this.name = name;
        this.ID= id;
        this.street = street;
        this.city = city;
        this.state = state;
        this.zip = zip;
        this.userRole= role;
    }

    public void setRole(role userRole){
        this.userRole = userRole;
    }

    public role getRole(){
        return userRole;
    }

    public void setName(String name){
        this.name = name;
    }

    public String getName(){
        return this.name;
    }

    public void setID(short ID){
        this.ID = ID;
    }

    public short getID(){
        return this.ID;
    }

    public void setStreet(String street){
        this.street = street;
    }

    public String getStreet(){
        return this.street;
    }
    
    public void setCity(String city){
        this.city = city;
    }

    public String getCity(){
        return this.city;
    }

    public void setState(String state){
        this.state = state;
    }

    public String getState(){
        return this.state;
    }

    public void setZip(int zip){
        this.zip = zip;
    }
    
    public int getZip(){
        return this.zip;
    }

    public String getAddress(){
        return this.street;
    }


}
