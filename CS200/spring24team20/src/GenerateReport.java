//REMINDER:
//Requirements of what to print is at bottom of GenerateReport class.

import java.time.format.DateTimeFormatter;
import java.util.Locale;

public class GenerateReport {
    
    UserDatabase printUser = new UserDatabase();
    ServiceDatabase printService= ServiceDatabase.readFromFile("log", "Services.chocan");

    public void MemberReports()
    {
        //First, let's see if there are even users to pull from.
        if(printUser.getUsers() == null || printUser.getUsers().size() < 1)
        {
            throw new Error("There are no members found within the user database.");
        }
        
      //Get all users and siphon out Providers
        for(int j = 0; j < printUser.users.size(); j++)
        {
            User foundUser = printUser.getUser(printUser.users.get(j).getID());

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
                
                System.out.printf("Name: %.25s\n", foundUser.getName()); //Member name (25 characters).
                System.out.printf("Number: %d\n", foundUser.getID()); //Member ID.
                System.out.printf("Address: %.25s\n", foundUser.getAddress()); //Member street address (25 characters).
                System.out.printf("City: %.14s\n", foundUser.getCity()); //Member city (14 characters).
                System.out.printf("State: %.2s\n", foundUser.getState()); //Member state (2 letters).
                System.out.printf("Zipcode: %s\n", zipcode); //Member ZIP code (5 digits).

                for(int i = 0; i < printService.serviceList.size(); i++)
                {
                    if(printService.serviceList.get(i).member.getID() == foundMember.getID())
                    {
                        System.out.printf("%s: %s, %s\n", DateTimeFormatter.ofPattern("MM-dd-yyyy", Locale.ENGLISH).format(printService.serviceList.get(i).dateTime),
                                                                    printService.serviceList.get(i).provider.getName(),
                                                                    printService.serviceList.get(i).comments); 
                    }
                }
                System.out.println("");
            }
            else
            {
                continue;
            }
        }

        return;
    }

    public void ProviderReports()
    {
        //First, let's see if there are even users to pull from.
        if(printUser.getUsers() == null || printUser.getUsers().size() < 1)
        {
            throw new Error("There are no members found within the user database.");
        }
        
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
                    if(printService.serviceList.get(i).provider.getID() == foundProvider.getID())
                    {
                        System.out.printf("%s: %s, %s\n", DateTimeFormatter.ofPattern("MM-dd-yyyy", Locale.ENGLISH).format(printService.serviceList.get(i).dateTime),
                                                                    printService.serviceList.get(i).member.getName(),
                                                                    printService.serviceList.get(i).code); 
                    }
                }
                System.out.println("");
            }
            else
            {
                continue;
            }
        }

        return;
    }
    

    public void EFTReports()
    {
        //First, let's see if there are even users to pull from.
        if(printUser.getUsers() == null || printUser.getUsers().size() < 1)
        {
            throw new Error("There are no members found within the user database.");
        }
        
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
                System.out.println("");
            }
            else
            {
                continue;
            }
        }

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
                for(int i = 0; i < printUser.users.size(); i++)
                {
                    if(printUser.users.get(i).getID() == foundProvider.getID())
                    {
                        //End for loop
                        if(!getProvider)
                        {
                            System.out.printf("Provider: %s\n", foundProvider.getName()); //Provider name.
                            getProvider = true;
                            for(int k = 0; k < printService.serviceList.size(); k++)
                            {
                            	if(printService.serviceList.get(k).provider.getID() == foundProvider.getID())
	                            {
	                                amountOfConsultations++;
	                                currentConsultation++;
	                                totalFee += printService.serviceList.get(k).fee;
	                                currentFee += printService.serviceList.get(k).fee;
                            	}
                            }
                        }
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
        System.out.println("MEMBER(S):");
        System.out.println(longLine);
        MemberReports();
        System.out.println(longLine);

        //Providers
        System.out.println("PROVIDER(S):");
        System.out.println(longLine);
        ProviderReports();
        System.out.println(longLine);

        //EFT Reports
        System.out.println("EFT:");
        System.out.println(longLine);
        EFTReports();
        System.out.println(longLine);

        //Summary Reports
        System.out.println("SUMMARY:");
        System.out.println(longLine);
        SummaryReports();
        System.out.println(longLine);
    }
    
}