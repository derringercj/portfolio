import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.Scanner;


public class Main {
    public static Scanner scanner= new Scanner(System.in);
    static UserDatabase users= UserDatabase.readFromFile("log", "Users.chocan");
    static ServiceDatabase services= ServiceDatabase.readFromFile("log", "Services.chocan");

    public static void main(String[] args) {
        User admin= new User("Admin",(short)999,User.role.OPERATOR);
        users.addUser(admin);
        System.out.println("Welcome to ChocAn.");
        mainMenu();
        
    }

    public static void mainMenu(){
        System.out.println("Please select from the following menu:");
        System.out.println("Login, Quit");
        System.out.print("Choice: ");
        
        String choice= scanner.nextLine();
        if(choice.equals("Login")){
            login();
        }
        else if(choice.equals("Quit")){
            quit();
        }
        else{
            System.out.println("Error: Undefined Choice");
            mainMenu();
        }
    }

    /**
     * 
     */
    public static void managerMenu(){
        GenerateReport report= new GenerateReport();
        report.printUser = users;
        System.out.println("Please choose from the following choices:");
        System.out.println("Run [Summary] Report, [Provider] Report, [Member] Report, [EFT] Report, [All] Reports, Main Menu, or Quit.");
        System.out.print("Choice: ");
        String choice= scanner.nextLine();

        
        if(choice.equals("Summary")){
            report.SummaryReports();
            managerMenu();
        }
        else if(choice.equals("Provider")){
            report.ProviderReports();
            managerMenu();
        }
        else if(choice.equals("Member")){
            report.MemberReports();
            managerMenu();
        }
        else if(choice.equals("EFT")){
            report.EFTReports();
            managerMenu();
        }
        else if(choice.equals("All")){
            report.allReports();
            managerMenu();
        }
        else if(choice.equals("Main Menu")){
            mainMenu();
        }
        else if(choice.equals("Quit")){
            quit();
        }
        else{
            System.out.println("Error: Undefined Choice");
            managerMenu();
        }


    }

    public static void operatorMenu(){
        System.out.println("Please choose from the following choices:");
        System.out.println("[Add] User, [Update] User, [Remove] User, Main Menu, or Quit.");
        System.out.print("Choice: ");
        String choice= scanner.nextLine();

        if(choice.equals("Add")){
            System.out.print("Name: ");
            String name= scanner.nextLine();
            System.out.print("ID: ");
            Short ID= scanner.nextShort();
            scanner.nextLine();
            System.out.print("Role: ");
            String role= scanner.nextLine();
            System.out.print("Street: ");
            String street= scanner.nextLine();
            System.out.print("City: ");
            String city= scanner.nextLine();
            System.out.print("State: ");
            String state= scanner.nextLine();
            System.out.print("Zip: ");
            int zip= scanner.nextInt();
            scanner.nextLine();

            if(role.equals("Provider")){
                User user= new Provider(name, ID, User.role.PROVIDER, street, city, state, zip);
                users.addUser(user);
                saveUsers();
            }
            else if(role.equals("Member")){
                System.out.print("Status: ");
                String status= scanner.nextLine();
                if(status.equals("Active")){
                    User user= new Member(name, ID, User.role.MEMBER, street, city, state, zip,Member.Status.ACTIVE);
                    users.addUser(user);
                }
                else{
                    User user= new Member(name, ID, User.role.MEMBER, street, city, state, zip,Member.Status.ACTIVE);
                    users.addUser(user);
                }
                saveUsers();
            }
            else if(role.equals("Operator")){
                User user= new User(name, ID, street, city, state, zip, User.role.OPERATOR); //Change to Operator when class made
                users.addUser(user);
                saveUsers();
            }
            else if(role.equals("Manager")){
                User user= new User(name, ID, street, city, state, zip, User.role.MANAGER); //Change to Manager when class made
                users.addUser(user);
                saveUsers();
            }
            System.out.println("User Added.");
            operatorMenu();
        }
        else if(choice.equals("Update")){
            System.out.println("Please enter the ID of the User you want to update.");
            System.out.print("ID: ");
            short ID= scanner.nextShort();
            scanner.nextLine();

            try {
                User user= users.getUser(ID);
                if(user == null){
                    throw new NullPointerException("User not found.");
                }

                System.out.println("Please enter all new information, if not changing, leave blank.");
                System.out.print("Name: ");
                user.setName(scanner.nextLine());
                System.out.println("ID: " + user.getID());
                System.out.println("Role: " + user.getRole());
                System.out.print("Street: ");
                user.setStreet(scanner.nextLine());
                System.out.print("City: ");
                user.setCity(scanner.nextLine());
                System.out.print("State: ");
                user.setState(scanner.nextLine());
                System.out.print("Zip: ");
                user.setZip(scanner.nextInt());
                scanner.nextLine();

                saveUsers();
                System.out.println("User Updated.");
                operatorMenu();

            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
                operatorMenu();
            }
        }
        else if(choice.equals("Remove")){
            System.out.println("Please enter the ID of the user you want to remove.");
            System.out.print("ID: ");
            short ID= scanner.nextShort();
            scanner.nextLine();

            try {
                User user= users.getUser(ID);
                if(user == null){
                    throw new NullPointerException("User not Found.");
                }
                users.removeUser(user);

                saveUsers();
                System.out.println("User Removed.");
                operatorMenu();
            } catch (Exception e) {
                System.out.println(e.getMessage());
                operatorMenu();
            }
        }
        else if(choice.equals("Main Menu")){
            mainMenu();
        }
        else if(choice.equals("Quit")){
            quit();
        }
        else{
            System.out.println("Error: Undefined Choice");
            operatorMenu();
        }
    }

    public static void providerMenu(User provider){
        System.out.println("Please choose from the following choices:");
        System.out.println("[Add] Service, View Directory, Main Menu, or Quit.");
        System.out.print("Choice: ");
        String choice= scanner.nextLine();

        if(choice.equals("Add")){
            System.out.println("Please fill out the following information to add a service.");
            System.out.println("Provider ID: " + provider.getID());
            System.out.println("Provider Name: " + provider.getName());
            System.out.print("Member ID: ");
            short memberID= scanner.nextShort();

            try {
                User user= users.getUser(memberID);
                if(user == null){
                    throw new NullPointerException("User not Found.");
                }
                else if(!(user instanceof Member)){
                    throw new Exception("User is not a member.");
                }
                Member member = (Member) user;
                
                System.out.print("Verifying Member ");
                for(int i=0; i<15; i++){
                    System.out.print(".");
                    Thread.sleep(5);
                }
                System.out.println();

                if(member.getStatus() == Member.Status.ACTIVE){
                    System.out.println("Member Verified.");
                }
                else if(member.getStatus() == Member.Status.SUSPENDED){
                    throw new Exception("Member Status Suspended.");
                }
                else{
                    throw new Exception("Unknown Member Status.");
                }

                System.out.print("Service Code: ");
                int code= scanner.nextInt();
                scanner.nextLine();

                LocalDateTime serviceDT= LocalDateTime.now();
                System.out.println("Service Date: "+ serviceDT);

                System.out.print("Comments: ");
                String comments= scanner.nextLine();

                System.out.print("Adding Service ");
                for(int i=0; i<15; i++){
                    System.out.print(".");
                    Thread.sleep(5);
                }
                System.out.println();

                services.add(new Service((Provider)provider, member, code, serviceDT,comments));
                saveServices();
                System.out.println("Service Added.");

                providerMenu(provider);


            } catch (Exception e) {
                System.out.println("Error: " + e.getMessage());
                providerMenu(provider);
            }

        }
        else if(choice.equals("View Directory")){
            Provider provider2= (Provider) provider;
            ArrayList<String> directory= provider2.getDirectory();

            for (String entry : directory) {
                System.out.println(entry);
            }
            System.out.println();
            providerMenu(provider);
        }
        else if(choice.equals("Main Menu")){
            mainMenu();
        }
        else if(choice.equals("Quit")){
            quit();
        }
        else{
            System.out.println("Error: Undefined Choice");
            providerMenu(provider);
        }
    }

    public static void login(){
        System.out.println("Please enter the following information to login");
        System.out.print("Name: ");
        scanner.nextLine();
        System.out.print("ID: ");
        short id= scanner.nextShort();
        scanner.nextLine();

        try {
            User user= users.getUser(id);
            if(user == null){
                throw new NullPointerException("User not Found.");
            }

            if(user.getRole()== User.role.MANAGER){
                System.out.println("Welcome to the Manager Portal, " + user.getName());
                managerMenu();
            }
            else if(user.getRole() == User.role.PROVIDER){
                System.out.println("Welcome to the Provider Portal, " + user.getName());
                providerMenu(user);
            }
            else if(user.getRole() == User.role.OPERATOR){
                System.out.println("Welcome to the Operator Portal, " + user.getName());
                operatorMenu();
            }
            else{
                throw new Exception("User does not have permission to login.");
            }
        } catch (Exception e) {
            System.out.println(e.getMessage());
            mainMenu();
        }
    }

    public static void saveUsers(){
        users.writeToFile("log");
    }

    public static void saveServices(){
        services.writeToFile("log");
    }

    public static void quit(){
        System.exit(0);
    }
}