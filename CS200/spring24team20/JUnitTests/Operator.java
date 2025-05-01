public class Operator extends User{

    private UserDatabase userDatabase;

    //Have a private User that is created with the relevant info. 
    private User newUser;
    private boolean newMember = false;
    private boolean newProvider = false;

    public Operator(){
        super();
    }

    public Operator(String name, short id, String street, String city, String state, short zip){
        super(name, id, street, city, state, zip, User.role.OPERATOR);
    }

    //Set the User Database
    public void setUserDatabase(UserDatabase database){
        this.userDatabase = database;
    }

//MEMBER FUNCTIONS:

    //Set the new user to the desired member
    public void setMember(String name, short id, String street, String city, String state, short zip){
        newUser = new User(name, id, street, city, state, zip,User.role.MEMBER);
        newMember = true;
        newProvider = false;
    }
    //Add a member to the user database
    public void addMember(){
        if (!newMember) {                                                         //Checks to make sure a valid user type is selected
            throw new Error("A new user of the type 'member' is needed.");
        }
        userDatabase.addUser(newUser);
    }
    //Edit an existing provider
    public void editMember(User p){
        if (!newMember) {                                                         //Checks to make sure a valid user type is selected
            throw new Error("A new user of the type 'member' is needed.");
        }
        userDatabase.updateUser(p, newUser);
    }
    //Remove a provider from the user database
    public void removeMember(User p){
        userDatabase.removeUser(p);
    }

//PROVIDER FUNCTIONS:

    //Set the new user to the desired provider
    public void setProvider(String name, short id, String street, String city, String state, short zip, String type){
        newUser = new Provider(name, id, street, city, state, zip, type);
        newMember = false;
        newProvider = true;
    }
    //Add a provider to the user database
    public void addProvider(){
        if (!newProvider) {                                                         //Checks to make sure a valid user type is selected
            throw new Error("A new user of the type 'provider' is needed.");
        }
        userDatabase.addUser(newUser);
    }
    //Edit an existing provider
    public void editProvider(User p){
        if (!newProvider) {                                                         //Checks to make sure a valid user type is selected
            throw new Error("A new user of the type 'provider' is needed.");
        }
        userDatabase.updateUser(p, newUser);  
    }
    //Remove a provider from the user database
    public void removeProvider(User p){
        userDatabase.removeUser(p);
    }
}
