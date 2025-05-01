public class Member extends User {

    //only variable not defined in user
    private Status status;

    public enum Status{ACTIVE, SUSPENDED};

    public Member(String name, short ID, String street, String city, String state, short zip, String status){
        super();
        
        setName(name);
        setID(ID);
        setStreet(street);
        setCity(city);
        setState(state);
        setZip(zip);
        
        this.status = Member.Status.ACTIVE;
    }

    public Member(String name, Short iD, User.role member, String street, String city, String state, int zip, Member.Status status) {
        super(name, iD, street, city, state, zip, member);
        this.status= status;
    }

    //gets and set Status
    public Status getStatus(){
        return this.status;
    }
    public void setStatus(Status status){
        this.status = status;
    }
}
