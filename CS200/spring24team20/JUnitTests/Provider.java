import java.util.ArrayList;
import java.util.Arrays;

public class Provider extends User{

    //variables only needed for provider
    //provider directory
    private ArrayList<String> direct= new ArrayList<>(Arrays.asList("598470 - Dietitian", "883948 - Aerobics Exercise"));
    private String type;

    public Provider(){
        super();
    }

    public Provider(String name, short ID, String street, String city, String state, int zip, String type){
        super();
        setName(name);
        setID(ID);
        setStreet(street);
        setCity(city);
        setState(state);
        this.type = type;
        setZip(zip);
    }

    public Provider(String name, Short iD, User.role provider, String street, String city, String state, int zip) {
        super(name, iD, street, city, state, zip, provider);
    }

    //gets and set
    public String getType(){
        return type;
    }
    public void setType(String type){
        this.type = type;
    }
    public ArrayList<String> getDirectory(){
        return direct;
    }
}
