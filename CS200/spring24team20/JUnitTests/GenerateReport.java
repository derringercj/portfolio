//REMINDER:
//Requirements of what to print is at bottom of GenerateReport class.

import java.time.format.DateTimeFormatter;
import java.util.Locale;

public class GenerateReport {
    
    UserDatabase printUser = new UserDatabase();
    ServiceDatabase printService = new ServiceDatabase();

    public void MemberReports(int ID)
    {
		if (ID < 1)
		{
			throw new Error("ID cannot be less than 1");
		}
		
        //First, let's see if there are even users to pull from.
        if(printUser.getUsers() == null || printUser.getUsers().size() < 1)
        {
            System.out.println("There are no members found within the database.");
            return;
        }

        User foundUser = printUser.getUser(ID);

        if(!printUser.verifyUser(foundUser))
        {
            System.out.println("Could not find user with that ID.");
            return;
        }

        User.role memberRole = User.role.MEMBER;
        User.role userRole = foundUser.getRole();

        Member foundMember = new Member(foundUser.getName(), foundUser.getID(), foundUser.getStreet(), foundUser.getCity(),
                                        foundUser.getState(), (short) foundUser.getZip(), "");

        if (userRole == memberRole) {
            
            String zipcode = String.valueOf(foundUser.getZip());
            if (zipcode.length() > 5)
            {
                zipcode = zipcode.substring(0,5);
            }
            
            System.out.printf("Name: %.25s\n", foundUser.getName()); //Provider name (25 characters).
            System.out.printf("Number: %d\n", foundUser.getID()); //Provider ID.
            System.out.printf("Address: %.25s\n", foundUser.getAddress()); //Provider street address (25 characters).
            System.out.printf("City: %.14s\n", foundUser.getCity()); //Provider city (14 characters).
            System.out.printf("State: %.2s\n", foundUser.getState()); //Provider state (2 letters).
            System.out.printf("Zipcode: %s\n", zipcode); //Provider ZIP code (5 digits).

            for(int i = 0; i < printService.serviceList.size(); i++)
            {
                if(printService.serviceList.get(i).member.getID() == foundMember.getID())
                {
                    System.out.printf("%s: %s, %s\n", DateTimeFormatter.ofPattern("MM-dd-yyyy", Locale.ENGLISH).format(printService.serviceList.get(i).dateTime),
                                                                printService.serviceList.get(i).provider.getName(),
                                                                printService.serviceList.get(i).comments); 
                }
                //For loop of all services and providers
                //Date of service (MM–DD–YYYY).
                //Provider name (25 characters).
                //Service name (20 characters).
            }
        }
        else
        {
            return;
        }

        System.out.println("");

        return;
    }

    public void ProviderReports(int ID)
    {
		if (ID < 1)
		{
			throw new Error("ID cannot be less than 1");
		}
		
        //First, let's see if there are even users to pull from.
        if(printUser.getUsers() == null || printUser.getUsers().size() < 1)
        {
            System.out.println("There are no providers found within the database.");
            return;
        }

        User foundUser = printUser.getUser(ID);

        if(!printUser.verifyUser(foundUser))
        {
            System.out.println("Could not find user with that ID.");
            return;
        }

        User.role providerRole = User.role.PROVIDER;
        User.role userRole = foundUser.getRole();
        
        Provider foundProvider = new Provider(foundUser.getName(), foundUser.getID(), foundUser.getStreet(), foundUser.getCity(),
                                        foundUser.getState(), (short) foundUser.getZip(), "");

        if (userRole == providerRole) {
            
            String zipcode = String.valueOf(foundUser.getZip());
            if (zipcode.length() > 5)
            {
                zipcode = zipcode.substring(0,5);
            }
            
            System.out.printf("Name: %.25s\n", foundUser.getName()); //Provider name (25 characters).
            System.out.printf("Number: %d\n", foundUser.getID()); //Provider ID.
            System.out.printf("Address: %.25s\n", foundUser.getAddress()); //Provider street address (25 characters).
            System.out.printf("City: %.14s\n", foundUser.getCity()); //Provider city (14 characters).
            System.out.printf("State: %.2s\n", foundUser.getState()); //Provider state (2 letters).
            System.out.printf("Zipcode: %s\n", zipcode); //Provider ZIP code (5 digits).

            //For each service provided, the following details are required:
            //for loop for this part
            

            for(int i = 0; i < printService.serviceList.size(); i++)
            {
                if(printService.serviceList.get(i).provider.getID() == foundProvider.getID())
                {
                    System.out.printf("%s: %s, %s\n", DateTimeFormatter.ofPattern("MM-dd-yyyy", Locale.ENGLISH).format(printService.serviceList.get(i).dateTime),
                                                                printService.serviceList.get(i).member.getName(),
                                                                printService.serviceList.get(i).code); 
                }
                //For loop of all services and providers
                //Date of service (MM–DD–YYYY).
                //Member name (25 characters).
                //Service name (20 characters).
            }
        }
        else
        {
            return;
        }

        System.out.println("");

        return;
    }
    

    public void EFTReports(int ID)
    {
        //Give EFT reports based off of electronic funding data written to disk
        if (ID < 1)
		{
			throw new Error("ID cannot be less than 1");
		}
		
        //First, let's see if there are even users to pull from.
        if(printUser.getUsers() == null || printUser.getUsers().size() < 1)
        {
            System.out.println("There are no providers found within the database.");
            return;
        }

        User foundUser = printUser.getUser(ID);

        if(!printUser.verifyUser(foundUser))
        {
            System.out.println("Could not find user with that ID.");
            return;
        }

        User.role providerRole = User.role.PROVIDER;
        User.role userRole = foundUser.getRole();
        Provider foundProvider = new Provider(foundUser.getName(), foundUser.getID(), foundUser.getStreet(), foundUser.getCity(),
                                        foundUser.getState(), (short) foundUser.getZip(), "");
        
        int getFee = 0;

        if (userRole == providerRole) {
            System.out.printf("Name: %.25s\n", foundUser.getName()); //Provider name (25 characters).
            System.out.printf("Number: %d\n", foundUser.getID()); //Provider ID.
            
            for(int i = 0; i < printService.serviceList.size(); i++)
            {
                if(printService.serviceList.get(i).provider.getID() == foundProvider.getID())
                {
                    getFee += printService.serviceList.get(i).fee;
                }
            }

            System.out.printf("Amount: $%d\n", getFee); //Provider amount.
        }
        else
        {
            return;
        }

        System.out.println("");

        return;
    }
    
    public void SummaryReports()
    {
        //First, let's see if there are even users to pull from.
        if(printUser.getUsers() == null || printUser.getUsers().size() < 1)
        {
            System.out.println("There are no providers found within the database.");
            return;
        }

        int amountOfProviders = 0;
        int totalFee = 0;
        int amountOfConsultations = 0;

        //Get all users and siphon out Providers
        for(int j = 0; j < printUser.users.size(); j++)
        {
            User foundUser = printUser.getUser(printUser.users.get(j).getID());

            if(!printUser.verifyUser(foundUser))
            {
                System.out.println("Could not find user with that ID.");
                return;
            }

            User.role providerRole = User.role.PROVIDER;
            User.role userRole = foundUser.getRole();
            Provider foundProvider = new Provider(foundUser.getName(), foundUser.getID(), foundUser.getStreet(), foundUser.getCity(),
                                                    foundUser.getState(), (short) foundUser.getZip(), "");

            if (userRole == providerRole) {

                //Since the user role is a provider, let's just count the amount of providers.
                amountOfProviders++;

                //Get fee and consultation values in scope per each provider, as well as showing the current provider once in the loop.
                int currentFee = 0;
                int currentConsultation = 0;
                boolean getProvider = false;
    
                //For loop to get all consultations and fees.
                for(int i = 0; i < printService.serviceList.size(); i++)
                {
                    if(printService.serviceList.get(i).provider.getID() == foundProvider.getID())
                    {
                        //End for loop
                        if(!getProvider)
                        {
                            System.out.printf("Provider: %s\n", foundProvider.getName()); //Provider name.
                            getProvider = true;
                        }

                        amountOfConsultations++;
                        currentConsultation++;
                        totalFee += printService.serviceList.get(i).fee;
                        currentFee += printService.serviceList.get(i).fee;
                    }
                }
                System.out.printf("Consultation(s): %d\n", currentConsultation); //Current consultation.
                System.out.printf("Fee: $%d\n\n", currentFee); //Current fee.
            }
            else
            {
                continue;
            }
        }
        
        //End for loop
        System.out.printf("Total Providers: %d\n", amountOfProviders); //Total Providers.
        System.out.printf("Total Consultations: %d\n", amountOfConsultations); //Total Consultations.
        System.out.printf("Total Fee: $%d\n", totalFee); //Total fees.

        System.out.println("");
        return;
    }
    
    public void allReports()
    {
        String longLine = "----------------------------------------------";
        System.out.println("Printing all reports...");

        //Members
        System.out.println(longLine);
        for(int i = 0; i < printUser.users.size(); i++)
        {
            MemberReports(printUser.users.get(i).getID());
        }
        System.out.println(longLine);

        //Providers
        for(int i = 0; i < printUser.users.size(); i++)
        {
            ProviderReports(printUser.users.get(i).getID());
        }
        System.out.println(longLine);

        //EFT Reports
        for(int i = 0; i < printUser.users.size(); i++)
        {
            EFTReports(printUser.users.get(i).getID());
        }
        System.out.println(longLine);

        //Summary Reports
        SummaryReports();
        System.out.println(longLine);
    }
    
}

/*
 *  Straight from the ChocAn requirements for the report:

MEMBERS:
Each member who has consulted a ChocAn provider during that week receives a list of
services provided to that member, sorted in order of service date. The report, which is also
sent as an e-mail attachment, includes:
 Member name (25 characters).
 Member number (9 digits).
 Member street address (25 characters).
 Member city (14 characters).
 Member state (2 letters).
 Member ZIP code (5 digits).
 For each service provided, the following details are required:
 Date of service (MM–DD–YYYY).
 Provider name (25 characters).
 Service name (20 characters).

PROVIDERS:
Each provider who has billed ChocAn during that week receives a report, sent as an
e-mail attachment, containing the list of services he or she provided to ChocAn members.
To simplify the task of verifi cation, the report contains the same information as that entered
on the provider’s form, in the order that the data were received by the computer. At the end
of the report is a summary including the number of consultations with members and the
total fee for that week. That is, the fields of the report include:
 Provider name (25 characters).
 Provider number (9 digits).
 Provider street address (25 characters).
 Provider city (14 characters).
 Provider state (2 letters).
 Provider ZIP code (5 digits).
 For each service provided, the following details are required:
 Date of service (MM–DD–YYYY).
 Date and time data were received by the computer (MM–DD–YYYY HH:MM:SS).
 Member name (25 characters).
 Member number (9 digits).
 Service code (6 digits).
 Fee to be paid (up to $999.99).
 Total number of consultations with members (3 digits).
 Total fee for week (up to $99,999.99).

EFT:
A record consisting of electronic funds transfer (EFT) data is then written to a disk;
banking computers will later ensure that each provider’s bank account is credited with the
appropriate amount.

SUMMARY:
 A summary report is given to the manager for accounts payable. The report lists every
provider to be paid that week, the number of consultations each had, and his or her total
fee for that week. Finally, the total number of providers who provided services, the total
number of consultations, and the overall fee total are printed. 

 */