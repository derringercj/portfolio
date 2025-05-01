import java.util.Scanner;

public class Manager extends User{

    private GenerateReport report;
    public static Scanner scanner = new Scanner(System.in);

    //Basic Constructor
    public Manager(){
        super();
    }
    //Data Constructor
    public Manager(String name, short id, String street, String city, String state, short zip){
        super(name, id, street, city, state, zip, User.role.OPERATOR);
    }

    //Prints prints out an individual report
    public void runReport(String r){

        //Print a member's report
        if (r.equals("Member")) {
            //Fetch requested ID
            System.out.print("Member ID: ");
            int id= scanner.nextInt();
            scanner.nextLine();
            //Print report
            report.MemberReports(id);
        }

        //Print a provider's report
        else if (r.equals("Provider")){
            //Fetch requested ID
            System.out.print("Provider ID: ");
            int id= scanner.nextInt();
            scanner.nextLine();
            //Print report
            report.ProviderReports(id);
        }

        //Print an EFT report
        else if (r.equals("EFT")){
            //Fetch requested ID
            System.out.print("Provider ID: ");
            int id= scanner.nextInt();
            scanner.nextLine();
            //Print report
            report.EFTReports(id);
        }

        //Print a summary report
        else if (r.equals("Summary")){
            report.SummaryReports();
        }

        //Print a summary report
        else if (r.equals("All")){
            report.allReports();
        }

        //Invalid report type
        else {
            throw new Error("Invalid report type. Valid report types are: Member , Provider , EFT , Summary.");
        }
    }
}
